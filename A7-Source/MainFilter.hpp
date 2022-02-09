#ifndef __MAIN_FILTER_H__
#define __MAIN_FILTER_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <functional>
#include <numeric>
#include "Hotel.hpp"


class MainFilter
{
public:
	virtual bool get_filter_status();
	virtual std::vector<Hotel*> apply_filter(std::vector<Hotel*> filtered_hotel_info) = 0;
	virtual void deactive_fliter();

private:
	
protected:
	bool filter_actived;

};

#endif 