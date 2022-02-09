#ifndef __STAR_FILTER_H__
#define __STAR_FILTER_H__

#include "MainFilter.hpp"

class StarFilter : public MainFilter
{
public:
	StarFilter();
	void add_new_star_filter(int min_star, int max_star);
	std::vector<Hotel*> apply_filter(std::vector<Hotel*> filtered_hotel_info);

private:
	int min_star;
	int max_star;

};

#endif 