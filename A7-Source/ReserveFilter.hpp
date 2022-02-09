#ifndef __RESERVE_FILTER_H__
#define __RESERVE_FILTER_H__

#include "MainFilter.hpp"

class ReserveFilter : public MainFilter
{
public:
	ReserveFilter();
	void add_new_reserve_filter(std::string room_type, int quantity, int check_in, int check_out);
	std::vector<Hotel*> apply_filter(std::vector<Hotel*> filtered_hotel_info);

private:
	std::string room_type;
	int quantity;
	int check_in;
	int check_out;

};

#endif 