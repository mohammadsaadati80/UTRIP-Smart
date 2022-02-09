#include "Hotel.hpp"
using namespace std;

Hotel::Hotel(vector<string> hotel_string, int hotel_star, string hotel_facilities, vector<double> hotel_double, vector<vector<Room*> > hotel_rooms, vector<int> room_price, Rating ratings)
{
	hotel_unique_id = hotel_string[UNIQUE_ID_ELEMENT];
	hotel_property_name = hotel_string[PROPERTY_NAME_ELEMENT];
	hotel_star_rating = hotel_star;
	hotel_overview = hotel_string[OVERVIEW_ELEMENT];
	hotel_property_amenities = hotel_facilities;
	hotel_city = hotel_string[CITY_ELEMENT];
	hotel_latitude = hotel_double[LATITUDE_ELEMENT];
	hotel_longitude = hotel_double[LONGITTUDE_ELEMENT];
	hotel_image_url = hotel_string[IMAGE_URL_ELEMENT];
	hotel_rooms_info = hotel_rooms;
	hotel_room_price = room_price;
	hotel_ratings.push_back(ratings);
}

void Hotel::show_summary_of_hotel_info()
{
	cout << hotel_unique_id << SPACE << hotel_property_name << SPACE << hotel_star_rating << SPACE << hotel_city << SPACE << calculate_hotel_total_num_of_rooms() << SPACE << fixed << setprecision(ROUND_UP_TO_TWO_DECIMAL_PLACES) << calculate_hotel_average_price() << SPACE << endl; // last space ???
}

int Hotel::calculate_hotel_total_num_of_rooms()
{
	return accumulate(hotel_rooms_info.begin(), hotel_rooms_info.end(), 0, [](int total, vector<Room*> current_rooms) {return total + current_rooms.size();});
}

double Hotel::calculate_hotel_average_price()
{
	double sum = 0;
	int number = 0;
	for (int current = 0; current < hotel_room_price.size();current++)
		if (hotel_room_price[current] > 0)
		{
			sum += double(hotel_room_price[current]);
			number++;
		}
	if (sum == 0)
		return double(0);
	return double(sum) / double(number);
}

string Hotel::get_hotel_unique_id() { return hotel_unique_id; }

void Hotel::show_full_hotel_info()
{
	cout << hotel_unique_id << endl;
	cout << hotel_property_name << endl;
	cout << STAR_TEXT << hotel_star_rating << endl;
	cout << OVERVIEW_TEXT << hotel_overview << endl;
	cout << AMENITIES_TEXT << hotel_property_amenities << endl;
	cout << CITY_TEXT << hotel_city << endl;
	cout << LATITUDE_TEXT << fixed << setprecision(ROUND_UP_TO_TWO_DECIMAL_PLACES) << hotel_latitude << endl;
	cout << LONGITUDE_TEXT << fixed << setprecision(ROUND_UP_TO_TWO_DECIMAL_PLACES) << hotel_longitude << endl;
	cout << ROOM_SHOW_TEXT << hotel_rooms_info[STANDARD_ROOM].size() << SPACE << hotel_rooms_info[DELUXE_ROOM].size() << SPACE << hotel_rooms_info[LUXURY_ROOM].size() << SPACE << hotel_rooms_info[PREMIUM_ROOM].size() << endl;
	cout << PRICE_TEXT << hotel_room_price[STANDARD_ROOM] << SPACE << hotel_room_price[DELUXE_ROOM] << SPACE << hotel_room_price[LUXURY_ROOM] << SPACE << hotel_room_price[PREMIUM_ROOM] << endl;
}

void Hotel::add_new_comment(string username, string comment)
{
	hotel_comments.push_back(Comment(username, comment));
}

void Hotel::show_all_comment()
{
	for (int current = hotel_comments.size() - 1; current >= 0; current--)
		hotel_comments[current].show_comment();
}

void Hotel::add_new_rating(string username, vector<double> ratings)
{
	for(int current = 0; current < hotel_ratings.size(); current++)
		if (hotel_ratings[current].get_username() == username)
		{
			hotel_ratings[current].update_rates(ratings);
			return;
		}
	hotel_ratings.push_back(Rating(username, ratings));
}

void Hotel::show_all_ratings()
{
	if (hotel_ratings.size() == 0)
		throw NoRatingException();
	vector<double> rating_sum(RATING_SIZE,double(0));
	for (int current_rating_member = 0; current_rating_member < RATING_SIZE; current_rating_member++)
		for (int current_rating = 0; current_rating < FIRST_RATE; current_rating++)
			rating_sum[current_rating_member] += hotel_ratings[current_rating].get_rate_member(current_rating_member);
	cout << LOCATION_TEXT << fixed << setprecision(ROUND_UP_TO_TWO_DECIMAL_PLACES) << rating_sum[LOCATION_ELEMENT] / double(FIRST_RATE) << endl;
	cout << CLEANLINESS_TEXT << fixed << setprecision(ROUND_UP_TO_TWO_DECIMAL_PLACES) << rating_sum[CLEANLINESS_ELEMENT] / double(FIRST_RATE) << endl;
	cout << STAFF_TEXT << fixed << setprecision(ROUND_UP_TO_TWO_DECIMAL_PLACES) << rating_sum[STAFF_ELEMENT] / double(FIRST_RATE) << endl;
	cout << FACILITIES_TEXT << fixed << setprecision(ROUND_UP_TO_TWO_DECIMAL_PLACES) << rating_sum[FACILITIES_ELEMENT] / double(FIRST_RATE) << endl;
	cout << VALUE_FOR_MONEY_TEXT << fixed << setprecision(ROUND_UP_TO_TWO_DECIMAL_PLACES) << rating_sum[VALUE_FOR_MONEY_ELEMENT] / double(FIRST_RATE) << endl;
	cout << OVERALL_RATING_TEXT << fixed << setprecision(ROUND_UP_TO_TWO_DECIMAL_PLACES) << rating_sum[OVERALL_RATING_ELEMENT] / double(FIRST_RATE) << endl;
}

string Hotel::get_hotel_city() { return hotel_city; }

int Hotel::get_hotel_star_rating() { return hotel_star_rating; }

bool Hotel::have_room_for_reserve(string _room_type, int quantity, int check_in, int check_out)
{
	int room_type = find_room_type(_room_type);
	int room_can_reserve_number = 0;
	for (int current = 0;current < hotel_rooms_info[room_type].size();current++)
		if (hotel_rooms_info[room_type][current]->is_empty_room(check_in, check_out))
			room_can_reserve_number++;
	if (room_can_reserve_number >= quantity)
		return true;
	else
		return false;
}

int Hotel::find_room_type(string room_type)
{
	if (room_type == STANDARD_ROOM_TYPE)
		return STANDARD_ROOM;
	if (room_type == DELUXE_ROOM_TYPE)
		return DELUXE_ROOM;
	if (room_type == LUXURY_ROOM_TYPE)
		return LUXURY_ROOM;
	if (room_type == PREMIUM_ROOM_TYPE)
		return PREMIUM_ROOM;
	return -1;
}

vector<Room*> Hotel::reserve_room(string _room_type, int quantity, int check_in, int check_out)
{
	int room_type = find_room_type(_room_type);
	vector<Room*> reserved_rooms;
	int reserved_rooms_number = 0;
	for (int current = 0;current < hotel_rooms_info[room_type].size();current++)
		if (hotel_rooms_info[room_type][current]->is_empty_room(check_in, check_out))
		{
			hotel_rooms_info[room_type][current]->reserve_room(check_in, check_out);
			reserved_rooms.push_back(hotel_rooms_info[room_type][current]);
			reserved_rooms_number++;
			if (reserved_rooms_number == quantity)
				break;
		}
	return reserved_rooms;
}

int Hotel::calculate_reserve_cost(string _room_type, int quantity, int check_in, int check_out)
{
	int room_type = find_room_type(_room_type);
	int room_rate = hotel_rooms_info[room_type][FIRST_ROOM]->get_room_rate();
	return room_rate*quantity*(check_out - check_in + 1);
}

string Hotel::get_hotel_property_name() { return hotel_property_name; }

int Hotel::get_hotel_room_price(int room_type)
{
	if (hotel_room_price[room_type] > 0)
		return hotel_room_price[room_type];
	else
		return 0;
}

double Hotel::calculate_personal_rating()
{
	for (int current = 0; current < hotel_ratings.size(); current++)
		if (hotel_ratings[current].get_username() == current_user_name)
			return hotel_ratings[current].get_rate_member(OVERALL_RATING_ELEMENT);
	double weights_sum = 0;
	double rates_sum = 0;
	for (int current = 0; current < OVERALL_RATING_ELEMENT; current++)
	{
		rates_sum += hotel_ratings[FIRST_ROOM].get_rate_member(current)*manual_weights[current];
		weights_sum += manual_weights[current];
	}
	return double(rates_sum) / double(weights_sum);
}

void Hotel::update_manual_weights(vector<double> manual_weights, string current_user_name)
{
	this->manual_weights = manual_weights;
	this->current_user_name = current_user_name;
}