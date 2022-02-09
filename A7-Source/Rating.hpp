#ifndef __RATING_H__
#define __RATING_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

#define RATING_SIZE 6
#define LOCATION_ELEMENT 0
#define CLEANLINESS_ELEMENT 1
#define STAFF_ELEMENT 2
#define FACILITIES_ELEMENT	3
#define VALUE_FOR_MONEY_ELEMENT 4
#define OVERALL_RATING_ELEMENT 5
#define FIRST_VALID_RATING 1
#define LAST_VALID_RATING 5

class Rating
{
public:
	Rating(std::string username, std::vector<double> rates);
	Rating(std::vector<double> rates);
	Rating(std::vector<double> rates, std::string hotel_id);
	std::string get_username();
	std::string get_hotel_id();
	void update_rates(std::vector<double> rates);
	double get_rate_member(int element_number);
	

private:
	std::string username;
	std::vector<double> rates;
	std::string hotel_id;

};

#endif