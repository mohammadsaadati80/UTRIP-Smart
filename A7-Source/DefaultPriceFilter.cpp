#include "DefaultPriceFilter.hpp"
using namespace std;

DefaultPriceFilter::DefaultPriceFilter()
{
	filter_actived = true;
	price_filter_activation_status = false;
	current_user = NULL;
}

bool DefaultPriceFilter::get_filter_status() { return filter_actived & !(price_filter_activation_status) & (current_user->get_user_reservation_number() >= MIN_RESERVE);}

void DefaultPriceFilter::update_user_logined(User* current_user)
{
	this->current_user = current_user;
}

void DefaultPriceFilter::change_activation_status(bool new_activation_status)
{
	filter_actived = new_activation_status;
}

void DefaultPriceFilter::change_price_filter_activation_status(bool new_activation_status)
{
	price_filter_activation_status = new_activation_status;
}

vector<Hotel*> DefaultPriceFilter::apply_filter(vector<Hotel*> filtered_hotel_info)
{
	vector<vector<int>> current_user_reservation_details = current_user->get_user_reservation_details();
	double sample_avg = calculate_sample_avg(current_user_reservation_details);
	double sample_standard_deviation = calculate_sample_standard_deviation(current_user_reservation_details, sample_avg);
	vector<Hotel*> new_filtered_hotel;
	for (int current = 0; current < filtered_hotel_info.size();current++)
		if (check_can_choose_current_hotel(filtered_hotel_info[current], sample_avg, sample_standard_deviation))
			new_filtered_hotel.push_back(filtered_hotel_info[current]);
	return new_filtered_hotel;
}

double DefaultPriceFilter::calculate_sample_avg(vector<vector<int>> current_user_reservation_details)
{
	double sum = double(accumulate(current_user_reservation_details.begin(), current_user_reservation_details.end(), double(0), [](double total, vector<int> current) { return total + double(current[ROOM_PRICE] * current[NUMBER_OF_ROOMS]);}));
	return sum / double(calculate_sample_size(current_user_reservation_details));
}

int DefaultPriceFilter::calculate_sample_size(vector<vector<int>> current_user_reservation_details)
{
	return accumulate(current_user_reservation_details.begin(), current_user_reservation_details.end(), 0, [](int total, vector<int> current) {return total + current[NUMBER_OF_ROOMS];});
}

double DefaultPriceFilter::calculate_sample_standard_deviation(vector<vector<int>> current_user_reservation_details, double sample_avg)
{
	double sample_standard_deviation = double(accumulate(current_user_reservation_details.begin(), current_user_reservation_details.end(), double(0), [&](double total, vector<int> current_room) {return total + current_room[NUMBER_OF_ROOMS] * pow((current_room[ROOM_PRICE] - sample_avg), 2);}));
	return sqrt(sample_standard_deviation / double(calculate_sample_size(current_user_reservation_details) - 1));
}

bool DefaultPriceFilter::check_can_choose_current_hotel(Hotel* current_hotel, double sample_avg, double sample_standard_deviation)
{
	if (abs(current_hotel->calculate_hotel_average_price() - sample_avg) <= double(COEFFICIENT_OF_SAMPLE_STANDARD_DEVIATION)*sample_standard_deviation)
		return true;
	else
		return false;
}