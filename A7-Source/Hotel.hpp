#ifndef __HOTEL_H__
#define __HOTEL_H__

#include "Exceptions.hpp"
#include "DeluxeRoom.hpp"
#include "LuxuryRoom.hpp"
#include "PremiumRoom.hpp"
#include "StandardRoom.hpp"
#include "Comment.hpp"
#include "Rating.hpp"
#include <iomanip>
#include <numeric>

#define ROUND_UP_TO_TWO_DECIMAL_PLACES 2
#define SPACE ' '
#define COLON ':'
#define	STAR_TEXT "star: "
#define OVERVIEW_TEXT "overview: "
#define AMENITIES_TEXT "amenities: "
#define	CITY_TEXT "city: "
#define	LATITUDE_TEXT "latitude: "
#define LONGITUDE_TEXT "longitude: "
#define ROOM_SHOW_TEXT "#rooms: "
#define PRICE_TEXT "price: "
#define LOCATION_TEXT "location: "
#define CLEANLINESS_TEXT "cleanliness: "
#define STAFF_TEXT "staff: "
#define FACILITIES_TEXT	"facilities: "
#define VALUE_FOR_MONEY_TEXT "value_for_money: "
#define OVERALL_RATING_TEXT "overall_rating: "
#define UNIQUE_ID_ELEMENT 0
#define PROPERTY_NAME_ELEMENT 1
#define OVERVIEW_ELEMENT 2
#define CITY_ELEMENT 3
#define IMAGE_URL_ELEMENT 4
#define LATITUDE_ELEMENT 0
#define LONGITTUDE_ELEMENT 1
#define FIRST_RATE 1

class Hotel
{
public:
	Hotel(std::vector<std::string> hotel_string, int hotel_star, std::string hotel_facilities, std::vector<double> hotel_double, std::vector<std::vector<Room*> > hotel_rooms, std::vector<int> room_price, Rating ratings);
	void show_summary_of_hotel_info();
	int calculate_hotel_total_num_of_rooms();
	double calculate_hotel_average_price();
	std::string get_hotel_unique_id();
	void show_full_hotel_info();
	void add_new_comment(std::string username, std::string comment);
	void show_all_comment();
	void add_new_rating(std::string username, std::vector<double> ratings);
	void show_all_ratings();
	std::string get_hotel_city();
	int get_hotel_star_rating();
	bool have_room_for_reserve(std::string room_type,int quantity,int check_in, int check_out);
	int find_room_type(std::string room_type);
	std::vector<Room*> reserve_room(std::string room_type, int quantity, int check_in, int check_out);
	int calculate_reserve_cost(std::string room_type, int quantity, int check_in, int check_out);
	std::string get_hotel_property_name();
	int get_hotel_room_price(int room_type);
	double calculate_personal_rating();
	void update_manual_weights(std::vector<double> manual_weights, std::string current_user_name);


private:
	std::string hotel_unique_id;
	std::string hotel_property_name;
	int hotel_star_rating;
	std::string hotel_overview;
	std::string hotel_property_amenities;
	std::string hotel_city;
	double hotel_latitude;
	double hotel_longitude;
	std::string hotel_image_url;
	std::vector<std::vector<Room*> > hotel_rooms_info;
	std::vector<int> hotel_room_price;
	std::vector<Comment> hotel_comments;
	std::vector<Rating> hotel_ratings;
	std::vector<double> manual_weights;
	std::string current_user_name;

};

#endif 