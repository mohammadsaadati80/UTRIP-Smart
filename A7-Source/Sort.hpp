#ifndef  __SORT_H__
#define __SORT_H__
 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <functional>
#include "Hotel.hpp"
#include "ManageWeights.hpp"
#include "User.hpp"
#include <map>

#define NAME "name"
#define STAR_RATING "star_rating"
#define STANDARD_ROOM_PRICE "standard_room_price"
#define DELUXE_ROOM_PRICE "deluxe_room_price"
#define LUXURY_ROOM_PRICE "luxury_room_price"
#define PREMIUM_ROOM_PRICE "premium_room_price"
#define AVERAGE_ROOM_PRICE "average_room_price"
#define ID "id"
#define CITY "city"
#define RATING_PERSONAL "rating_personal"

class Sort
{
public:
	Sort();
	bool is_actived();
	void update_sort(std::string property, bool order);
	void deactive_sort();
	std::vector<Hotel*> my_sort(std::vector<Hotel*> filtered_hotel);
	std::vector<Hotel*> sort_based_on_property_type(std::vector<Hotel*> filtered_hotel);
	std::vector<Hotel*> sort_based_on_id(std::vector<Hotel*> filtered_hotel);
	static bool sort_id_asc(Hotel* first_hotel, Hotel* second_hotel);
	static bool sort_id_des(Hotel* first_hotel, Hotel* second_hotel);
	std::vector<Hotel*> sort_based_on_city(std::vector<Hotel*> filtered_hotel);
	static bool sort_city_id_asc(Hotel* first_hotel, Hotel* second_hotel);
	static bool sort_city_id_des(Hotel* first_hotel, Hotel* second_hotel);
	std::vector<Hotel*> sort_based_on_name(std::vector<Hotel*> filtered_hotel);
	static bool sort_name_id_asc(Hotel* first_hotel, Hotel* second_hotel);
	static bool sort_name_id_des(Hotel* first_hotel, Hotel* second_hotel);
	std::vector<Hotel*> sort_based_on_star(std::vector<Hotel*> filtered_hotel);
	static bool sort_star_id_asc(Hotel* first_hotel, Hotel* second_hotel);
	static bool sort_star_id_des(Hotel* first_hotel, Hotel* second_hotel);
	std::vector<Hotel*> sort_based_on_average_room_price(std::vector<Hotel*> filtered_hotel);
	static bool sort_average_room_price_id_asc(Hotel* first_hotel, Hotel* second_hotel);
	static bool sort_average_room_price_id_des(Hotel* first_hotel, Hotel* second_hotel);
	std::vector<Hotel*> sort_based_on_room_price(std::vector<Hotel*> filtered_hotel,int room_type);
	std::vector<Hotel*> sort_based_on_rating_personal(std::vector<Hotel*> filtered_hotel);
	std::vector<Hotel*> update_ratings_weight_for_hotels(std::vector<Hotel*> filtered_hotel);
	void check_number_of_user_reservation();
	static bool sort_rating_personal_id_asc(Hotel* first_hotel, Hotel* second_hotel);
	static bool sort_rating_personal_id_des(Hotel* first_hotel, Hotel* second_hotel);
	void update_manual_weights_active(std::vector<double> weights, bool activation);
	void update_manual_weights_inactive(bool activation);
	void show_manual_weights_status();
	void show_estimated_weights();
	void update_user(User* current_user);
	
private:
	bool activation_status;
	bool ascending;
	std::string sort_type;
	ManageWeights manage_weights;
	User* current_user;

};

#endif 