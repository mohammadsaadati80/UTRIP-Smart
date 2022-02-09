#ifndef __MANAGE_FILTER_H__
#define __MANAGE_FILTER_H__

#include "MainFilter.hpp"
#include "CityFilter.hpp"
#include "PriceFilter.hpp"
#include "StarFilter.hpp"
#include "ReserveFilter.hpp"
#include "DefaultPriceFilter.hpp"
#include "Sort.hpp"

#define CITYFILTER 0
#define STARFILTER 1
#define PRICEFILTER 2
#define RESERVEFILTER 3
#define DEFAULTPRICEFILTER 4
#define VALID_PRICE 0
#define FIRST_VALID_MIN_STAR 1  
#define LAST_VALID_MIN_STAR 5
#define FIRST_VALID_MAX_STAR 1  
#define LAST_VALID_MAX_STAR 5
#define FIRST_VALID_RESERVE 1
#define LAST_VALID_RESERVE 30

class ManageFilter
{
public:
	void add_all_hotels(std::vector<Hotel> &hotel_info);
	void add_new_city_filter(std::string city);
	void add_new_star_filter(int min_star, int max_star);
	void add_new_price_filter(double min_price, double max_price);
	void add_new_reserve_filter(std::string room_type, int quantity, int check_in, int check_out);
	void change_default_price_fliter_activation_status(bool new_activation_status);
	void update_default_price_filter_user_logined(User* current_user);
	void delete_all_filters();
	void show_hotels_info();
	void show_summary_of_hotels_info(std::vector<Hotel*> filtered_hotel_info);
	void update_sort(std::string property, bool order);
	void delete_sort();
	void update_manual_weights_active(std::vector<double> weights, bool activation);
	void update_manual_weights_inactive(bool activation);
	void show_manual_weights_status();
	void show_estimated_weights();
	void update_sort_user(User* current_user);

private:
	std::vector<Hotel*> all_hotel_info;
	std::vector<Hotel*> filtered_hotel_info;
	std::vector<MainFilter*> filters;
	CityFilter* city_filter;
	StarFilter* star_filter;
	PriceFilter* price_filter;
	ReserveFilter* reserve_filter;
	DefaultPriceFilter* default_price_filter;
	Sort my_sort;

};

#endif 