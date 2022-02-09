#ifndef __DEFAULT_PRICE_FILTER_H__
#define __DEFAULT_PRICE_FILTER_H__

#include "MainFilter.hpp"
#include "User.hpp"

#define DEFAULT_PRICE_FILTER_MASSAGE "* Results have been filtered by the default price filter."
#define MIN_RESERVE 10
#define NUMBER_OF_ROOMS 1
#define ROOM_PRICE 0
#define COEFFICIENT_OF_SAMPLE_STANDARD_DEVIATION 2 

class DefaultPriceFilter : public MainFilter
{
public:
	DefaultPriceFilter();
	std::vector<Hotel*> apply_filter(std::vector<Hotel*> filtered_hotel_info);
	bool get_filter_status();
	void update_user_logined(User* current_user);
	void change_activation_status(bool new_activation_status);
	void change_price_filter_activation_status(bool new_activation_status);
	double calculate_sample_avg(std::vector<std::vector<int>> current_user_reservation_details);
	int calculate_sample_size(std::vector<std::vector<int>> current_user_reservation_details);
	double calculate_sample_standard_deviation(std::vector<std::vector<int>> current_user_reservation_details, double sample_avg);
	static bool check_can_choose_current_hotel(Hotel* current_hotel, double sample_avg, double sample_standard_deviation);

private:
	bool price_filter_activation_status;
	User* current_user;

};

#endif 