#include "User.hpp"
using namespace std;

User::User(string email, string username, string password)
{
	user_email = email;
	user_name = username;
	user_password_hash = hash<string>{}(password);
	user_logged = true;
	number_of_user_reservation = 0;
	user_wallet_amount = double(0);
	user_wallet_turnover.push_back(user_wallet_amount);
}

bool User::is_duplicate_user(string email, string username)
{
	if (user_name == username || user_email == email)
		return true;
	else
		return false;
}

bool User::login(string email, string password)
{
	if (user_email == email && user_password_hash == hash<string>{}(password) && user_logged == false)
	{
		user_logged = true;
		return true;
	}
	else
		return false;
}

void User::logout()
{
	user_logged = false;
}

void User::wallet_amount(double amount)
{
	user_wallet_amount += amount;
	user_wallet_turnover.push_back(user_wallet_amount);
}

void User::wallet_count(int count)
{
	if (count > user_wallet_turnover.size())
		show_wallet_count(user_wallet_turnover.size());
	else
		show_wallet_count(count);
}

void User::show_wallet_count(int end)
{
	for (int current = 0; current < end; current++)
		cout << int(user_wallet_turnover[user_wallet_turnover.size() - 1 - current]) << endl;
}

string User::get_user_name() { return user_name; }

double User::get_user_wallet_amount() { return user_wallet_amount; }

void User::add_new_reserve(vector<Room*> reserved_rooms, int quantity, int cost, int check_in, int check_out, string hotel_id)
{
	number_of_user_reservation++;
	user_rooms_reserved.push_back(Reserve(number_of_user_reservation, reserved_rooms, quantity, cost, check_in, check_out, hotel_id));
	user_wallet_amount -= cost;
	user_wallet_turnover.push_back(user_wallet_amount);
	user_rooms_reserved[user_rooms_reserved.size() - 1].show_room_id();
}

void User::show_reserve()
{
	if (user_rooms_reserved.size() == 0)
		throw EmptyException();
	for (int current = user_rooms_reserved.size() - 1; current >= 0; current--)
		user_rooms_reserved[current].show_reserve();
}

void User::cansel_reserve(int reserve_id)
{
	for(int current =0;current < user_rooms_reserved.size(); current++)
		if (user_rooms_reserved[current].get_reservation_id() == reserve_id)
		{
			user_rooms_reserved[current].cansel_reserve();
			wallet_amount(double(user_rooms_reserved[current].get_cost()) / double(2));
			user_rooms_reserved.erase(user_rooms_reserved.begin() + current);
			return;
		}
	throw NotFoundException();
}

int User::get_user_reservation_number() { return user_rooms_reserved.size(); }

vector<vector<int>> User::get_user_reservation_details()
{
	vector<vector<int>> user_reservation_details(user_rooms_reserved.size());
	for (int current = 0; current < user_rooms_reserved.size(); current++)
	{
		user_reservation_details[current].push_back(user_rooms_reserved[current].get_room_price());
		user_reservation_details[current].push_back(user_rooms_reserved[current].get_quantity());
	}
	return user_reservation_details;
}

void User::add_new_rating(vector<double> ratings, string hotel_id)
{
	for (int current = 0; current < user_ratings.size(); current++)
		if (user_ratings[current].get_hotel_id() == hotel_id)
		{
			user_ratings[current].update_rates(ratings);
			return;
		}
	user_ratings.push_back(Rating(ratings, hotel_id));
}


vector<Rating> User::get_user_ratings() { return user_ratings; }