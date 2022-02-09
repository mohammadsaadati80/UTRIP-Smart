#ifndef __PRICE_FILTER_H__
#define __PRICE_FILTER_H__

#include "MainFilter.hpp"

class PriceFilter : public MainFilter
{
public:
	PriceFilter();
	void add_new_price_filter(double min_price, double max_price);
	std::vector<Hotel*> apply_filter(std::vector<Hotel*> filtered_hotel_info);

private:
	double min_price;
	double max_price;

};

#endif 