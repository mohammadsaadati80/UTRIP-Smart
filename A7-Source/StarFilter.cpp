#include "StarFilter.hpp"
using namespace std;

StarFilter::StarFilter()
{
	filter_actived = false;
}

void StarFilter::add_new_star_filter(int min_star, int max_star)
{
	this->min_star = min_star;
	this->max_star = max_star;
	filter_actived = true;
}

vector<Hotel*> StarFilter::apply_filter(vector<Hotel*> filtered_hotel_info)
{
	vector<Hotel*> new_filtered_hotel;
	for (int current = 0; current < filtered_hotel_info.size();current++)
		if (filtered_hotel_info[current]->get_hotel_star_rating() >= min_star && filtered_hotel_info[current]->get_hotel_star_rating() <= max_star)
			new_filtered_hotel.push_back(filtered_hotel_info[current]);
	return new_filtered_hotel;
}