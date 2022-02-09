#include "ManageWeights.hpp"
using namespace std;

ManageWeights::ManageWeights()
{
	activation = false;
}

void ManageWeights::update_weights_active(vector<double> weights, bool activation)
{
	this->weights = weights;
	this->activation = activation;
}

void ManageWeights::update_weights_inactive(bool activation)
{
	this->activation = activation;
	this->weights.clear();
}

void ManageWeights::show_status()
{
	if (activation)
	{
		cout << ACTIVE << SPACE << TRUE << SPACE;
		show_weights(weights);
	}
		
	else
		cout << ACTIVE << SPACE << FALSE << endl;
}

void ManageWeights::show_weights(vector<double> weights)
{
	vector<string> propertyy;
	propertyy.push_back(LOCATION_TEXT_MANUAL_WEIGHT);
	propertyy.push_back(CLEANLINESS_TEXT_MANUAL_WEIGHT);
	propertyy.push_back(STAFF_TEXT_MANUAL_WEIGHT);
	propertyy.push_back(FACILITIES_TEXT_MANUAL_WEIGH);
	propertyy.push_back(VALUE_FOR_MONEY_TEXT_MANUAL_WEIGHT);
	for (int current = 0; current < weights.size(); current++)
	{
		weights[current] = trunc(weights[current] * double(TWO_DECIMAL_PLACES));
		weights[current] /= double(TWO_DECIMAL_PLACES);
		cout << propertyy[current] << SPACE << fixed << setprecision(ROUND_UP_TO_TWO_DECIMAL_PLACES) << weights[current] << SPACE;
	}
	cout << endl;
}

vector<double> ManageWeights::get_weights() { return weights; }

bool ManageWeights::get_avtivation_status() { return activation; }

vector<double> ManageWeights::calculate_weight_estimation(vector<Rating> user_rating)
{
	vector<vector<double> > category_rates(user_rating.size());
	vector<double> overall_rating;
	for(int current_rate = 0; current_rate < user_rating.size(); current_rate++)
		for (int current = 0; current < RATING_SIZE; current++)
			if (current == OVERALL_RATING_ELEMENT)
				overall_rating.push_back(user_rating[current_rate].get_rate_member(current));
			else
				category_rates[current_rate].push_back(user_rating[current_rate].get_rate_member(current));
	return find_estimated_weights(category_rates, overall_rating);
}

vector<double> ManageWeights::find_estimated_weights(vector<vector<double> > category_rates, vector<double> overall_rating)
{
	vector<double> weights = first_weight_initialization();
	vector<EstimateWeight> estimate_weight_result;
	for(int counter = 0; counter < NUMBER_OF_WEIGHT_ESTIMATION; counter++)
	{
		vector<double> weights_delta = calculate_new_weight_delta(weights, category_rates, overall_rating);
		weights = update_weights(weights, weights_delta);
		estimate_weight_result.push_back(create_new_estinate_weights(weights, category_rates, overall_rating));
	}
	return find_min_weights(estimate_weight_result);
}

vector<double> ManageWeights::first_weight_initialization()
{
	vector<double> weights(OVERALL_RATING_ELEMENT);
	for_each(weights.begin(), weights.end(), [](double &current_weight) {current_weight = (rand() % OVERALL_RATING_ELEMENT + 1);});
	return weights;
}

vector<double> ManageWeights::calculate_new_weight_delta(vector<double> weights, vector<vector<double> > category_rates, vector<double> overall_rating)
{
	vector<double> weights_delta(OVERALL_RATING_ELEMENT, double(0));
	for (int current_delta = 0; current_delta < OVERALL_RATING_ELEMENT; current_delta++)
		for (int current_rate = 0;current_rate < category_rates.size(); current_rate++)
			weights_delta[current_delta] += calculate_current_delta_for_current_rate(weights, current_delta, category_rates[current_rate], overall_rating[current_rate]);
	return weights_delta;
}

double ManageWeights::calculate_current_delta_for_current_rate(vector<double> weights, int current_delta, vector<double> rates, double overall_rating)
{
	vector<double> new_epsilon_weights = weights;
	new_epsilon_weights[current_delta] += double(EPSILON);
	return (double(calculate_overall_rating_approximation_error(new_epsilon_weights, rates, overall_rating)) - double(calculate_overall_rating_approximation_error(weights, rates, overall_rating))) / double(EPSILON);
}

double ManageWeights::calculate_overall_rating_approximation_error(vector<double> weights, vector<double> rates, double overall_rating)
{
	double rates_sum = 0;
	for (int current = 0; current < OVERALL_RATING_ELEMENT; current++)
		rates_sum += rates[current] * weights[current];
	double weights_sum = accumulate(weights.begin(), weights.end(), double(0));
	double new_overall_rating = double(rates_sum) / double(weights_sum);
	return pow((new_overall_rating - overall_rating), 2);
}

vector<double> ManageWeights::update_weights(vector<double> weights, vector<double> weights_delta)
{
	for (int current = 0; current < weights.size(); current++)
	{
		weights[current] += double(-1)*double(ALPHA)*weights_delta[current];
		if (weights[current] < double(FIRST_VALID_RATING))
			weights[current] = double(FIRST_VALID_RATING);
		if (weights[current] > double(LAST_VALID_RATING))
			weights[current] = double(LAST_VALID_RATING);
	}
	return weights;
}

EstimateWeight ManageWeights::create_new_estinate_weights(vector<double> weights, vector<vector<double> > category_rates, vector<double> overall_rating)
{
	EstimateWeight new_estinate_weights;
	new_estinate_weights.weight = weights;
	new_estinate_weights.approximation_error = double(0);
	for (int current_rate = 0; current_rate < category_rates.size(); current_rate++)
		new_estinate_weights.approximation_error += calculate_overall_rating_approximation_error(weights, category_rates[current_rate], overall_rating[current_rate]);
	return new_estinate_weights;
}

vector<double> ManageWeights::find_min_weights(vector<EstimateWeight> estimate_weight_result)
{
	int min_element = 0;
	for (int current = 0; current < estimate_weight_result.size(); current++)
		if (estimate_weight_result[current].approximation_error < estimate_weight_result[min_element].approximation_error)
			min_element = current;
	return estimate_weight_result[min_element].weight;
}