#include "ManageFilter.hpp"
using namespace std;

void ManageFilter::add_all_hotels(vector<Hotel> &hotel_info)
{
	for (int current = 0; current < hotel_info.size(); current++)
		all_hotel_info.push_back(&hotel_info[current]);
	city_filter = new CityFilter;
	star_filter = new StarFilter;
	price_filter = new PriceFilter;
	reserve_filter = new ReserveFilter;
	default_price_filter = new DefaultPriceFilter;
	filters.push_back(city_filter);
	filters.push_back(star_filter);
	filters.push_back(price_filter);
	filters.push_back(reserve_filter);
	filters.push_back(default_price_filter);
}

void ManageFilter::add_new_city_filter(string city)
{
	city_filter->add_new_city_filter(city);
	filters[CITYFILTER] = city_filter;
}

void ManageFilter::add_new_star_filter(int min_star, int max_star)
{
	if (min_star > LAST_VALID_MIN_STAR || min_star < FIRST_VALID_MIN_STAR || max_star > LAST_VALID_MAX_STAR || max_star < FIRST_VALID_MAX_STAR || max_star < min_star)
		throw BadRequestException();
	star_filter->add_new_star_filter(min_star, max_star);
	filters[STARFILTER] = star_filter;
}

void ManageFilter::add_new_price_filter(double min_price, double max_price)
{
	if (min_price < VALID_PRICE || max_price < VALID_PRICE || max_price < min_price)
		throw BadRequestException();
	price_filter->add_new_price_filter(min_price, max_price);
	filters[PRICEFILTER] = price_filter;
	default_price_filter->change_price_filter_activation_status(true);
	filters[DEFAULTPRICEFILTER] = default_price_filter;
}

void ManageFilter::add_new_reserve_filter(string room_type, int quantity, int check_in, int check_out)
{
	if(check_in > check_out)
		throw BadRequestException();
	reserve_filter->add_new_reserve_filter(room_type, quantity, check_in, check_out);
	filters[RESERVEFILTER] = reserve_filter;
}

void ManageFilter::change_default_price_fliter_activation_status(bool new_activation_status)
{
	default_price_filter->change_activation_status(new_activation_status);
	filters[DEFAULTPRICEFILTER] = default_price_filter;
}

void ManageFilter::update_default_price_filter_user_logined(User* current_user)
{
	default_price_filter->update_user_logined(current_user);
	filters[DEFAULTPRICEFILTER] = default_price_filter;
}

void ManageFilter::delete_all_filters()
{
	filtered_hotel_info = all_hotel_info;
	for (int current = 0;current < filters.size() - 1;current++)
		filters[current]->deactive_fliter();
	default_price_filter->change_price_filter_activation_status(false);
	filters[DEFAULTPRICEFILTER] = default_price_filter;
}

void ManageFilter::show_hotels_info()
{
	filtered_hotel_info = all_hotel_info;
	for (int current = 0;current < filters.size();current++)
		if (filters[current]->get_filter_status() == true)
			filtered_hotel_info = filters[current]->apply_filter(filtered_hotel_info);
	filtered_hotel_info = my_sort.my_sort(filtered_hotel_info);
	show_summary_of_hotels_info(filtered_hotel_info);
}

void ManageFilter::show_summary_of_hotels_info(vector<Hotel*> filtered_hotel_info)
{
	if (filtered_hotel_info.size() == 0)
		throw EmptyException();
	if (filters[DEFAULTPRICEFILTER]->get_filter_status())
		cout << DEFAULT_PRICE_FILTER_MASSAGE << endl;
	for (int current = 0; current < filtered_hotel_info.size();current++)
		filtered_hotel_info[current]->show_summary_of_hotel_info();
}

void ManageFilter::update_sort(string propertyy, bool order)
{
	my_sort.update_sort(propertyy, order);
}

void ManageFilter::delete_sort()
{
	my_sort.deactive_sort();
}

void ManageFilter::update_manual_weights_active(vector<double> weights, bool activation)
{
	my_sort.update_manual_weights_active(weights, activation);
}

void ManageFilter::update_manual_weights_inactive(bool activation)
{
	my_sort.update_manual_weights_inactive(activation);
}

void ManageFilter::show_manual_weights_status()
{
	my_sort.show_manual_weights_status();
}

void ManageFilter::show_estimated_weights()
{
	my_sort.show_estimated_weights();
}

void ManageFilter::update_sort_user(User* current_user)
{
	my_sort.update_user(current_user);
}