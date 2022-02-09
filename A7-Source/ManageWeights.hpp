#ifndef __MANAGE_WEIGHTS_H__
#define __MANAGE_WEIGHTS_H__

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
#include "Rating.hpp"

#define LOCATION_TEXT_MANUAL_WEIGHT "location"
#define CLEANLINESS_TEXT_MANUAL_WEIGHT "cleanliness"
#define STAFF_TEXT_MANUAL_WEIGHT "staff"
#define FACILITIES_TEXT_MANUAL_WEIGH "facilities"
#define VALUE_FOR_MONEY_TEXT_MANUAL_WEIGHT "value_for_money"
#define ACTIVE "active"
#define TRUE "true"
#define FALSE "false"
#define SPACE ' '
#define ROUND_UP_TO_TWO_DECIMAL_PLACES 2
#define EPSILON 0.0001
#define ALPHA 1
#define FIRST_ELEMENT 0
#define NUMBER_OF_WEIGHT_ESTIMATION 1000
#define MIN_OF_USER_RESERVATION 5
#define TWO_DECIMAL_PLACES 100

struct EstimateWeight
{
	std::vector<double> weight;
	double approximation_error;
};

class ManageWeights
{
public:
	ManageWeights();
	void update_weights_active(std::vector<double> weights, bool activation);
	void update_weights_inactive( bool activation);
	void show_status();
	void show_weights(std::vector<double> weights);
	std::vector<double> get_weights();
	bool get_avtivation_status();
	std::vector<double> calculate_weight_estimation(std::vector<Rating> user_rating);
	std::vector<double> find_estimated_weights(std::vector<std::vector<double> > category_rates, std::vector<double> overall_rating);
	std::vector<double> first_weight_initialization();
	std::vector<double> calculate_new_weight_delta(std::vector<double> weights,std::vector<std::vector<double> > category_rates, std::vector<double> overall_rating);
	double calculate_current_delta_for_current_rate(std::vector<double> weights, int current_delta, std::vector<double> rates, double overall_rating);
	double calculate_overall_rating_approximation_error(std::vector<double> weights, std::vector<double> rates, double overall_rating);
	std::vector<double> update_weights(std::vector<double> weights,std:: vector<double> weights_delta);
	EstimateWeight create_new_estinate_weights(std::vector<double> weights, std::vector<std::vector<double> > category_rates, std::vector<double> overall_rating);
	std::vector<double> find_min_weights(std::vector<EstimateWeight> estimate_weight_result);

private:
	std::vector<double> weights;
	bool activation;

};

#endif 