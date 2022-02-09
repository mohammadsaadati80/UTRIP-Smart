#include "Sort.hpp"
using namespace std;

Sort::Sort()
{
	activation_status = false;
	ascending = true;
}

bool Sort::is_actived() { return activation_status; }

void Sort::update_sort(string propertyy, bool order)
{
	activation_status = true;
	sort_type = propertyy;
	ascending = order;
}

void Sort::deactive_sort()
{
	activation_status = false;
}

vector<Hotel*> Sort::my_sort(vector<Hotel*> filtered_hotel)
{
	if (activation_status == false)
		sort(filtered_hotel.begin(), filtered_hotel.end(), sort_id_asc);
	else
		filtered_hotel = sort_based_on_property_type(filtered_hotel);
	return filtered_hotel;
}

vector<Hotel*> Sort::sort_based_on_property_type(vector<Hotel*> filtered_hotel)
{
	if (sort_type == ID)
		filtered_hotel = sort_based_on_id(filtered_hotel);
	else if (sort_type == CITY)
		filtered_hotel = sort_based_on_city(filtered_hotel);
	else if (sort_type == NAME)
		filtered_hotel = sort_based_on_name(filtered_hotel);
	else if (sort_type == STAR_RATING)
		filtered_hotel = sort_based_on_star(filtered_hotel);
	else if (sort_type == AVERAGE_ROOM_PRICE)
		filtered_hotel = sort_based_on_average_room_price(filtered_hotel);
	else if (sort_type == STANDARD_ROOM_PRICE)
		filtered_hotel = sort_based_on_room_price(filtered_hotel, STANDARD_ROOM);
	else if (sort_type == DELUXE_ROOM_PRICE)
		filtered_hotel = sort_based_on_room_price(filtered_hotel, DELUXE_ROOM);
	else if (sort_type == LUXURY_ROOM_PRICE)
		filtered_hotel = sort_based_on_room_price(filtered_hotel, LUXURY_ROOM);
	else if (sort_type == PREMIUM_ROOM_PRICE)
		filtered_hotel = sort_based_on_room_price(filtered_hotel, PREMIUM_ROOM);
	else if (sort_type == RATING_PERSONAL)
		filtered_hotel = sort_based_on_rating_personal(filtered_hotel);
	return filtered_hotel;
}

vector<Hotel*> Sort::sort_based_on_id(vector<Hotel*> filtered_hotel)
{
	if(ascending)
		sort(filtered_hotel.begin(), filtered_hotel.end(), sort_id_asc);
	else
		sort(filtered_hotel.begin(), filtered_hotel.end(), sort_id_des);
	return filtered_hotel;
}

bool Sort::sort_id_asc(Hotel* first_hotel, Hotel* second_hotel)
{
	return (first_hotel->get_hotel_unique_id() < second_hotel->get_hotel_unique_id());
}

bool Sort::sort_id_des(Hotel* first_hotel, Hotel* second_hotel)
{
	return (first_hotel->get_hotel_unique_id() > second_hotel->get_hotel_unique_id());
}

vector<Hotel*> Sort::sort_based_on_city(vector<Hotel*> filtered_hotel)
{
	if (ascending)
		sort(filtered_hotel.begin(), filtered_hotel.end(), sort_city_id_asc);
	else
		sort(filtered_hotel.begin(), filtered_hotel.end(), sort_city_id_des);
	return filtered_hotel;
}

bool Sort::sort_city_id_asc(Hotel* first_hotel, Hotel* second_hotel)
{
	if (first_hotel->get_hotel_city() == second_hotel->get_hotel_city())
		return sort_id_asc(first_hotel, second_hotel);
	else
		return (first_hotel->get_hotel_city() < second_hotel->get_hotel_city());
}

bool Sort::sort_city_id_des(Hotel* first_hotel, Hotel* second_hotel)
{
	if (first_hotel->get_hotel_city() == second_hotel->get_hotel_city())
		return sort_id_asc(first_hotel, second_hotel);
	else
		return (first_hotel->get_hotel_city() > second_hotel->get_hotel_city());
}

vector<Hotel*> Sort::sort_based_on_name(std::vector<Hotel*> filtered_hotel)
{
	if (ascending)
		sort(filtered_hotel.begin(), filtered_hotel.end(), sort_name_id_asc);
	else
		sort(filtered_hotel.begin(), filtered_hotel.end(), sort_name_id_des);
	return filtered_hotel;
}

bool Sort::sort_name_id_asc(Hotel* first_hotel, Hotel* second_hotel)
{
	if (first_hotel->get_hotel_property_name() == second_hotel->get_hotel_property_name())
		return sort_id_asc(first_hotel, second_hotel);
	else
		return (first_hotel->get_hotel_property_name() < second_hotel->get_hotel_property_name());
}

bool Sort::sort_name_id_des(Hotel* first_hotel, Hotel* second_hotel)
{
	if (first_hotel->get_hotel_property_name() == second_hotel->get_hotel_property_name())
		return sort_id_asc(first_hotel, second_hotel);
	else
		return (first_hotel->get_hotel_property_name() > second_hotel->get_hotel_property_name());
}

vector<Hotel*> Sort::sort_based_on_star(std::vector<Hotel*> filtered_hotel)
{
	if (ascending)
		sort(filtered_hotel.begin(), filtered_hotel.end(), sort_star_id_asc);
	else
		sort(filtered_hotel.begin(), filtered_hotel.end(), sort_star_id_des);
	return filtered_hotel;
}

bool Sort::sort_star_id_asc(Hotel* first_hotel, Hotel* second_hotel)
{
	if (first_hotel->get_hotel_star_rating() == second_hotel->get_hotel_star_rating())
		return sort_id_asc(first_hotel, second_hotel);
	else
		return (first_hotel->get_hotel_star_rating() < second_hotel->get_hotel_star_rating());
}

bool Sort::sort_star_id_des(Hotel* first_hotel, Hotel* second_hotel)
{
	if (first_hotel->get_hotel_star_rating() == second_hotel->get_hotel_star_rating())
		return sort_id_asc(first_hotel, second_hotel);
	else
		return (first_hotel->get_hotel_star_rating() > second_hotel->get_hotel_star_rating());
}

vector<Hotel*> Sort::sort_based_on_average_room_price(std::vector<Hotel*> filtered_hotel)
{
	if (ascending)
		sort(filtered_hotel.begin(), filtered_hotel.end(), sort_average_room_price_id_asc);
	else
		sort(filtered_hotel.begin(), filtered_hotel.end(), sort_average_room_price_id_des);
	return filtered_hotel;
}

bool Sort::sort_average_room_price_id_asc(Hotel* first_hotel, Hotel* second_hotel)
{
	if (first_hotel->calculate_hotel_average_price() == second_hotel->calculate_hotel_average_price())
		return sort_id_asc(first_hotel, second_hotel);
	else
		return (first_hotel->calculate_hotel_average_price() < second_hotel->calculate_hotel_average_price());
}

bool Sort::sort_average_room_price_id_des(Hotel* first_hotel, Hotel* second_hotel)
{
	if (first_hotel->calculate_hotel_average_price() == second_hotel->calculate_hotel_average_price())
		return sort_id_asc(first_hotel, second_hotel);
	else
		return (first_hotel->calculate_hotel_average_price() > second_hotel->calculate_hotel_average_price());
}

vector<Hotel*> Sort::sort_based_on_room_price(std::vector<Hotel*> filtered_hotel, int room_type)
{
	if (ascending)
		sort(filtered_hotel.begin(), filtered_hotel.end(), [room_type](Hotel* first_hotel, Hotel* second_hotel) {
				if (first_hotel->get_hotel_room_price(room_type) == second_hotel->get_hotel_room_price(room_type))
					return sort_id_asc(first_hotel, second_hotel);
				else
					return (first_hotel->get_hotel_room_price(room_type) < second_hotel->get_hotel_room_price(room_type));
			});
	else
		sort(filtered_hotel.begin(), filtered_hotel.end(), [room_type](Hotel* first_hotel, Hotel* second_hotel) {
				if (first_hotel->get_hotel_room_price(room_type) == second_hotel->get_hotel_room_price(room_type))
					return sort_id_asc(first_hotel, second_hotel);
				else
					return (first_hotel->get_hotel_room_price(room_type) > second_hotel->get_hotel_room_price(room_type));
			});
	return filtered_hotel;
}

vector<Hotel*> Sort::sort_based_on_rating_personal(vector<Hotel*> filtered_hotel)
{
	filtered_hotel = update_ratings_weight_for_hotels(filtered_hotel);
	if (ascending)
		sort(filtered_hotel.begin(), filtered_hotel.end(), sort_rating_personal_id_asc);
	else
		sort(filtered_hotel.begin(), filtered_hotel.end(), sort_rating_personal_id_des);
	return filtered_hotel;
}

vector<Hotel*> Sort::update_ratings_weight_for_hotels(vector<Hotel*> filtered_hotel)
{
	if (manage_weights.get_avtivation_status())
		for (int current = 0; current < filtered_hotel.size(); current++)
			filtered_hotel[current]->update_manual_weights(manage_weights.get_weights(), current_user->get_user_name());
	else
	{
		check_number_of_user_reservation();
		vector<double> estimated_weights = manage_weights.calculate_weight_estimation(current_user->get_user_ratings());
		for (int current = 0; current < filtered_hotel.size(); current++)
			filtered_hotel[current]->update_manual_weights(estimated_weights, current_user->get_user_name());
	}
	return filtered_hotel;
}

void Sort::check_number_of_user_reservation()
{
	if (current_user->get_user_ratings().size() < MIN_OF_USER_RESERVATION)
		throw InsufficientRatings();
}

bool Sort::sort_rating_personal_id_asc(Hotel* first_hotel, Hotel* second_hotel)
{
	if (first_hotel->calculate_personal_rating() == second_hotel->calculate_personal_rating())
		return sort_id_asc(first_hotel, second_hotel);
	else
		return (first_hotel->calculate_personal_rating() < second_hotel->calculate_personal_rating());
}

bool Sort::sort_rating_personal_id_des(Hotel* first_hotel, Hotel* second_hotel)
{
	if (first_hotel->calculate_personal_rating() == second_hotel->calculate_personal_rating())
		return sort_id_asc(first_hotel, second_hotel);
	else
		return (first_hotel->calculate_personal_rating() > second_hotel->calculate_personal_rating());
}

void Sort::update_manual_weights_active(vector<double> weights, bool activation)
{
	manage_weights.update_weights_active(weights, activation);
}

void Sort::update_manual_weights_inactive(bool activation)
{
	manage_weights.update_weights_inactive(activation);
}

void Sort::show_manual_weights_status()
{
	manage_weights.show_status();
}

void Sort::show_estimated_weights()
{
	check_number_of_user_reservation();
	manage_weights.show_weights(manage_weights.calculate_weight_estimation(current_user->get_user_ratings()));
}

void Sort::update_user(User* current_user)
{
	this->current_user = current_user;
}