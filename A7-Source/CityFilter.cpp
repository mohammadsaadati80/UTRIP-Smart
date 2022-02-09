#include "CityFilter.hpp"
using namespace std;

CityFilter::CityFilter()
{
	filter_actived = false;
}

void CityFilter::add_new_city_filter(string city)
{
	this->city = city;
	filter_actived = true;
}

vector<Hotel*> CityFilter::apply_filter(vector<Hotel*> filtered_hotel_info)
{
	vector<Hotel*> new_filtered_hotel;
	for (int current = 0; current < filtered_hotel_info.size();current++)
		if (filtered_hotel_info[current]->get_hotel_city() == city)
			new_filtered_hotel.push_back(filtered_hotel_info[current]);
	return new_filtered_hotel;
}