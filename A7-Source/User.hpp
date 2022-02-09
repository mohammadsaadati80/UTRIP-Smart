#ifndef __USER_H__
#define __USER_H__

#include "Room.hpp"
#include "DeluxeRoom.hpp"
#include "LuxuryRoom.hpp"
#include "PremiumRoom.hpp"
#include "StandardRoom.hpp"
#include "Reserve.hpp"
#include "Exceptions.hpp"
#include "Rating.hpp"

class User
{
public:
	User(std::string email, std::string username, std::string password);
	bool is_duplicate_user(std::string email, std::string username);
	bool login(std::string email, std::string password);
	void logout();
	void wallet_amount(double amount);
	void wallet_count(int count);
	void show_wallet_count(int end);
	std::string get_user_name();
	double get_user_wallet_amount();
	void add_new_reserve(std::vector<Room*> reserved_rooms, int quantity, int cost, int check_in, int check_out, std::string hotel_id);
	void show_reserve();
	void cansel_reserve(int reserve_id);
	int get_user_reservation_number();
	std::vector<std::vector<int>> get_user_reservation_details();
	void add_new_rating(std::vector<double> ratings, std::string hotel_id);
	std::vector<Rating> get_user_ratings();

private:
	std::string user_name;
	std::string user_email;
	size_t user_password_hash;
	bool user_logged;
	double user_wallet_amount;
	std::vector<double> user_wallet_turnover;
	std::vector<Reserve> user_rooms_reserved;
	int number_of_user_reservation;
	std::vector<Rating> user_ratings;

};

#endif 