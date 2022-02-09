#include "Rating.hpp"
using namespace std;

Rating::Rating(std::string username, std::vector<double> rates)
{
	this->username = username;
	this->rates = rates;
}

Rating::Rating(vector<double> rates)
{
	this->rates = rates;
}

Rating::Rating(std::vector<double> rates, std::string hotel_id)
{
	this->rates = rates;
	this->hotel_id = hotel_id;
}

string Rating::get_username() { return username; }

string Rating::get_hotel_id() { return hotel_id; }

void Rating::update_rates(std::vector<double> rates)
{
	this->rates = rates;
}

double Rating::get_rate_member(int element_number) { return rates[element_number]; }