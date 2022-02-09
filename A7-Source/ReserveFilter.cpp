#include "ReserveFilter.hpp"
using namespace std;

ReserveFilter::ReserveFilter()
{
	filter_actived = false;
}

void ReserveFilter::add_new_reserve_filter(string room_type, int quantity, int check_in, int check_out)
{
	this->room_type = room_type;
	this->quantity = quantity;
	this->check_in = check_in;
	this->check_out = check_out;
	filter_actived = true;
}

vector<Hotel*> ReserveFilter::apply_filter(vector<Hotel*> filtered_hotel_info)
{
	vector<Hotel*> new_filtered_hotel;
	for (int current = 0; current < filtered_hotel_info.size();current++)
		if (filtered_hotel_info[current]->have_room_for_reserve(room_type, quantity, check_in, check_out))
			new_filtered_hotel.push_back(filtered_hotel_info[current]);
	return new_filtered_hotel;
}