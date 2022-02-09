#ifndef __CITY_FILTER_H__
#define __CITY_FILTER_H__

#include "MainFilter.hpp"

class CityFilter : public MainFilter
{
public:
	CityFilter();
	void add_new_city_filter(std::string city);
	std::vector<Hotel*> apply_filter(std::vector<Hotel*> filtered_hotel_info);

private:
	
	std::string city;

};

#endif 