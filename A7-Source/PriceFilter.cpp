#include "PriceFilter.hpp"
using namespace std;

PriceFilter::PriceFilter()
{
	filter_actived = false;
}

void PriceFilter::add_new_price_filter( double min_price, double max_price)
{
	this->min_price = min_price;
	this->max_price = max_price;
	filter_actived = true;
}

vector<Hotel*> PriceFilter::apply_filter(vector<Hotel*> filtered_hotel_info)
{
	vector<Hotel*> new_filtered_hotel;
	for (int current = 0; current < filtered_hotel_info.size();current++)
		if (filtered_hotel_info[current]->calculate_hotel_average_price() >= min_price && filtered_hotel_info[current]->calculate_hotel_average_price() <= max_price)
			new_filtered_hotel.push_back(filtered_hotel_info[current]);
	return new_filtered_hotel;
}