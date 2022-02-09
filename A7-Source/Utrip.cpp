#include "Utrip.hpp"
using namespace std;

Utrip::Utrip(vector<Hotel> _hotels_info)
{
	hotels_info = _hotels_info;
	current_user = NULL;
	managefilter.add_all_hotels(hotels_info);
}

void Utrip::print_successful_execution_of_the_command()
{
	cout << OK << endl;
}

vector<string> Utrip::check_can_use_this_order(vector<string> args, int order_size)
{
	check_user_login();
	args = check_have_arg_seperator(tools.delete_element_of_vector(args, FIRST_ELEMENT));
	check_have_correct_args_number(args.size(), order_size);
	return args;
}

void Utrip::check_user_login()
{
	if (current_user == NULL)
		throw PermissionDeniedException();
}

vector<string> Utrip::check_have_arg_seperator(std::vector<std::string> args)
{
	if (args[FIRST_ELEMENT] != SEPARATOR_BEFORE_ARGUMENT)
		throw BadRequestException();
	return tools.delete_element_of_vector(args, FIRST_ELEMENT);
}

void Utrip::check_have_correct_args_number(int args_size, int correct_args_number)
{
	if (args_size != correct_args_number)
		throw BadRequestException();
}

void Utrip::get_command()
{
	string command_line;
	while (getline(cin, command_line))
	{
		try
		{	
			manage_command_line(command_line);
		}
		catch (exception& error)
		{
			cout << error.what();
		}
	}
}

void Utrip::manage_command_line(string command_line)
{
	vector<string> args = read_args_from_line(command_line);
	if(args.size() != 0)
	{
		if (args[FIRST_ELEMENT] == POST_COMMAND)
			check_post_command(tools.delete_element_of_vector(args, FIRST_ELEMENT));
		else if (args[FIRST_ELEMENT] == GET_COMMAND)
			check_get_command(tools.delete_element_of_vector(args, FIRST_ELEMENT));
		else if (args[FIRST_ELEMENT] == DELETE_COMMAND)
			check_delete_command(tools.delete_element_of_vector(args, FIRST_ELEMENT));
		else
			throw BadRequestException();
	}
	else
		throw BadRequestException();
}

vector<string> Utrip::read_args_from_line(string command_line)
{
	stringstream string_stream(command_line);
	string command;
	vector<string> args;
	while (getline(string_stream, command, COMMAND_SEPARATOR))
	{
		if (command != EMPTY_CHARACTER)
			args.push_back(command);
	}
	return args;
}

void Utrip::check_post_command(vector<string> args)
{
	if(args.size() == 0)
		throw BadRequestException();
	if (args[FIRST_ELEMENT] == SIGNUP_COMMAND)
		signup(args);
	else if (args[FIRST_ELEMENT] == LOGIN)
		login(args);
	else if (args[FIRST_ELEMENT] == LOGOUT_COMMAND)
		logout();
	else if (args[FIRST_ELEMENT] == WALLET_COMMAND)
		wallet_amount(args);
	else if (args[FIRST_ELEMENT] == COMMENTS_COMMAND)
		post_comments(args);
	else if (args[FIRST_ELEMENT] == RATINGS_COMMAND)
		post_ratings(args);
	else if (args[FIRST_ELEMENT] == FILTERS_COMMAND)
		filter_detection(args);
	else if (args[FIRST_ELEMENT] == DEFAULT_PRICE_FILTER_COMMAND)
		manage_default_price_filter(args);
	else if (args[FIRST_ELEMENT] == RESERVE_COMMAND)
		post_reserve(args);
	else if (args[FIRST_ELEMENT] == SORT_COMMAND)
		post_sort(args);
	else if (args[FIRST_ELEMENT] == MANUAL_WEIGHT_COMMAND)
		post_manual_weights(args);
	else
		throw NotFoundException();
}

void Utrip::signup(vector<string> args)
{
	args = check_have_arg_seperator(tools.delete_element_of_vector(args, FIRST_ELEMENT));
	check_have_correct_args_number(args.size(), SIGNUP_ARGUMENT_NUMBER);
	string email;
	string username;
	string password;
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == EMAIL)
			email = args[current + 1];
		else if (args[current] == USERNAME)
			username = args[current + 1];
		else if (args[current] == PASSWORD)
			password = args[current + 1];
		else
			throw BadRequestException();
	}
	create_new_user(email, username, password);
}

void Utrip::create_new_user(string email, string username, string password)
{
	for (int current = 0; current < users_info.size(); current++)
		if (users_info[current].is_duplicate_user(email, username) || current_user != NULL)
			throw BadRequestException();
	users_info.push_back(User(email, username, password));
	current_user = &users_info[users_info.size() - 1];
	managefilter.update_default_price_filter_user_logined(&users_info[users_info.size() - 1]);
	managefilter.update_sort_user(&users_info[users_info.size() - 1]);
	print_successful_execution_of_the_command();
}

void Utrip::login(vector<string> args)
{
	args = check_have_arg_seperator(tools.delete_element_of_vector(args, FIRST_ELEMENT));
	check_have_correct_args_number(args.size(), LOGIN_ARGUMENT_NUMBER);
	string email;
	string password;
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == EMAIL)
			email = args[current + 1];
		else if (args[current] == PASSWORD)
			password = args[current + 1];
		else
			throw BadRequestException();
	}
	login_new_user(email, password);
}

void Utrip::login_new_user(string email, string password)
{
	for (int current = 0; current < users_info.size();current++)
		if (users_info[current].login(email, password) && current_user == NULL)
		{
			current_user = &users_info[current];
			managefilter.update_default_price_filter_user_logined(&users_info[current]);
			managefilter.update_sort_user(&users_info[current]);
			print_successful_execution_of_the_command();
			return;
		}
	throw BadRequestException();
}

void Utrip::logout()
{
	if (current_user != NULL)
	{
		current_user->logout();
		current_user = NULL;
		managefilter.delete_all_filters();
		managefilter.update_default_price_filter_user_logined(NULL);
		managefilter.update_sort_user(NULL);
		managefilter.delete_sort();
		print_successful_execution_of_the_command();
	}
	else
		throw PermissionDeniedException();
}

void Utrip::wallet_amount(vector<string> args)
{
	args = check_can_use_this_order(args, WALLET_AMOUNT_ARGUMENT_NUMBER);
	double amount;
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == AMOUNT)
			amount = stod(args[current + 1]);
		else
			throw BadRequestException();
	}
	wallet_amount_current_user(amount);
}

void Utrip::wallet_amount_current_user(double amount)
{
	if (amount <= 0)
		throw BadRequestException();
	current_user->wallet_amount(amount);
	print_successful_execution_of_the_command();
}

void Utrip::post_comments(vector<string> args)
{
	args = check_can_use_this_order(args, POST_COMMENTS_ARGUMENT_NUMBER);
	string hotel_id;
	string comment;
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == HOTEL)
			hotel_id = args[current + 1];
		else if (args[current] == COMMENT)
			comment = args[current + 1];
		else
			throw BadRequestException();
	}
	post_comment_on_hotel(hotel_id, comment);
}

void Utrip::post_comment_on_hotel(string hotel_id, string comment)
{
	for (int current = 0; current < hotels_info.size(); current++)
		if (hotels_info[current].get_hotel_unique_id() == hotel_id)
		{
			hotels_info[current].add_new_comment(current_user->get_user_name(), comment);
			print_successful_execution_of_the_command();
			return;
		}
	throw NotFoundException();
}

void Utrip::post_ratings(vector<string> args)
{
	args = check_can_use_this_order(args, POST_RATINGS_COMMAND_ARGUMENT_NUMBER);
	string hotel_id;
	vector<double> double_args(RATING_SIZE, double(0));
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == HOTEL)
			hotel_id = args[current + 1];
		else if (args[current] == LOCATION)
			double_args[LOCATION_ELEMENT] = stod(args[current + 1]);
		else if (args[current] == CLEANLINESS)
			double_args[CLEANLINESS_ELEMENT] = stod(args[current + 1]);
		else if (args[current] == STAFF)
			double_args[STAFF_ELEMENT] = stod(args[current + 1]);
		else if (args[current] == FACILITIES)
			double_args[FACILITIES_ELEMENT] = stod(args[current + 1]);
		else if (args[current] == VALUE_FOR_MONEY)
			double_args[VALUE_FOR_MONEY_ELEMENT] = stod(args[current + 1]);
		else if (args[current] == OVERALL_RATING)
			double_args[OVERALL_RATING_ELEMENT] = stod(args[current + 1]);
		else
			throw BadRequestException();
	}
	post_rating_on_hotel(hotel_id, double_args);
}

void Utrip::post_rating_on_hotel(string hotel_id, vector<double> raitings)
{
	for (int current = 0; current < raitings.size(); current++)
		if (raitings[current] < FIRST_VALID_RATING || raitings[current] > LAST_VALID_RATING)
			throw BadRequestException();
	for (int current = 0; current < hotels_info.size(); current++)
		if (hotels_info[current].get_hotel_unique_id() == hotel_id)
		{
			hotels_info[current].add_new_rating(current_user->get_user_name(), raitings);
			current_user->add_new_rating(raitings, hotel_id);
			print_successful_execution_of_the_command();
			return;
		}
	throw NotFoundException();
}

void Utrip::filter_detection(vector<string> args)
{
	check_user_login();
	args = check_have_arg_seperator(tools.delete_element_of_vector(args, FIRST_ELEMENT));
	if (args[FIRST_ELEMENT] == CITY)
		manage_city_filter(args);
	else if (args.size() == STAR_FILTERS_ARGUMENT_NUMBER && args[FIRST_ELEMENT].size() == STAR_FILTER_SIZE)
		manage_star_filter(args);
	else if (args.size() == PRICE_FILTERS_ARGUMENT_NUMBER && args[FIRST_ELEMENT].size() == PRICE_FILTER_SIZE)
		manage_price_filter(args);
	else if (args.size() == RESERVE_FILTERS_ARGUMENT_NUMBER)
		manage_reserve_filter(args);
	else
		throw BadRequestException();
}

void Utrip::manage_city_filter(vector<string> args)
{
	string city;
	if (args[FIRST_ELEMENT] == CITY)
		for (int current_city = 1; current_city < args.size(); current_city++)
		{
			city += args[current_city];
			if (current_city < args.size() - 1)
				city += SPACE;
		}
	else
		throw BadRequestException();
	managefilter.add_new_city_filter(city);
	print_successful_execution_of_the_command();
}

void Utrip::manage_star_filter(vector<string> args)
{
	int min_star;
	int max_star;
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == MIN_STAR)
			min_star = stoi(args[current + 1]);
		else if (args[current] == MAX_STAR)
			max_star = stoi(args[current + 1]);
		else
			throw BadRequestException();
	}
	managefilter.add_new_star_filter(min_star, max_star);
	print_successful_execution_of_the_command();
}

void Utrip::manage_price_filter(vector<string> args)
{
	double min_price;
	double max_price;
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == MIN_PRICE)
			min_price = stod(args[current + 1]);
		else if (args[current] == MAX_PRICE)
			max_price = stod(args[current + 1]);
		else
			throw BadRequestException();
	}
	managefilter.add_new_price_filter(min_price, max_price);
	print_successful_execution_of_the_command();
}

void Utrip::manage_reserve_filter(vector<string> args)
{
	string room_type;
	int quantity;
	int check_in;
	int check_out;
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == TYPE)
			room_type = args[current + 1];
		else if (args[current] == QUANTITY)
			quantity = stoi(args[current + 1]);
		else if (args[current] == CHECK_IN)
			check_in = stoi(args[current + 1]);
		else if (args[current] == CHECK_OUT)
			check_out = stoi(args[current + 1]);
		else
			throw BadRequestException();
	}
	managefilter.add_new_reserve_filter(room_type, quantity, check_in, check_out);
	print_successful_execution_of_the_command();
}

void Utrip::post_reserve(vector<string> args)
{
	args = check_can_use_this_order(args, POST_RESERVE_COMMAND_ARGUMENT_NUMBER);
	vector<string> args_string(ROOM_TYPE_ELEMENT + 1);
	vector<int> args_int(CHECK_OUT_ELEMENT + 1);
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == HOTEL)
			args_string[HOTEL_ID_ELEMENT] = args[current + 1];
		else if (args[current] == TYPE)
			args_string[ROOM_TYPE_ELEMENT] = args[current + 1];
		else if (args[current] == QUANTITY)
			args_int[QUANTITY_ELEMENT] = stoi(args[current + 1]);
		else if (args[current] == CHECK_IN)
			args_int[CHECK_IN_ELEMENT] = stoi(args[current + 1]);
		else if (args[current] == CHECK_OUT)
			args_int[CHECK_OUT_ELEMENT] = stoi(args[current + 1]);
		else
			throw BadRequestException();
	}
	reserve_room(args_string, args_int);
}

void Utrip::reserve_room(vector<string> args_string, vector<int> args_int)
{
	for (int current = 0; current < hotels_info.size(); current++)
		if (hotels_info[current].get_hotel_unique_id() == args_string[HOTEL_ID_ELEMENT])
		{
			if (hotels_info[current].have_room_for_reserve(args_string[ROOM_TYPE_ELEMENT], args_int[QUANTITY_ELEMENT], args_int[CHECK_IN_ELEMENT], args_int[CHECK_OUT_ELEMENT]))
			{
				if (current_user->get_user_wallet_amount() >= hotels_info[current].calculate_reserve_cost(args_string[ROOM_TYPE_ELEMENT], args_int[QUANTITY_ELEMENT], args_int[CHECK_IN_ELEMENT], args_int[CHECK_OUT_ELEMENT]))
				{
					vector<Room*> reserved_rooms = hotels_info[current].reserve_room(args_string[ROOM_TYPE_ELEMENT], args_int[QUANTITY_ELEMENT], args_int[CHECK_IN_ELEMENT], args_int[CHECK_OUT_ELEMENT]);
					current_user->add_new_reserve(reserved_rooms, args_int[QUANTITY_ELEMENT], hotels_info[current].calculate_reserve_cost(args_string[ROOM_TYPE_ELEMENT], args_int[QUANTITY_ELEMENT], args_int[CHECK_IN_ELEMENT], args_int[CHECK_OUT_ELEMENT]), args_int[CHECK_IN_ELEMENT], args_int[CHECK_OUT_ELEMENT], hotels_info[current].get_hotel_unique_id());
				}
				else
					throw NotEnoughCreditException();
			}
			else
				throw NotEnoughRoomException();
			return;
		}
	throw NotFoundException();
}

void Utrip::manage_default_price_filter(vector<string> args)
{
	args = check_can_use_this_order(args, DEFAULT_PRICE_FILTER_COMMAND_ARGUMENT_NUMBER);
	bool activation_status;
	if (args[FIRST_ELEMENT] == ACTIVE)
		activation_status = detect_bool_type(args[FIRST_ELEMENT + 1], TRUE, FALSE);
	else
		throw BadRequestException();
	managefilter.change_default_price_fliter_activation_status(activation_status);
	print_successful_execution_of_the_command();
}

bool Utrip::detect_bool_type(std::string propertyy, string correct, string incorrect)
{
	if (propertyy == correct)
		return true;
	else if (propertyy == incorrect)
		return false;
	else
		throw BadRequestException();
}

void Utrip::post_sort(vector<string> args)
{
	args = check_can_use_this_order(args, SORT_COMMAND_ARGUMENT_NUMBER);
	string propertyy;
	bool order;
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == PROPERTY)
			propertyy = detect_sort_type(args[current + 1]);
		else if (args[current] == ORDER)
			order = detect_bool_type(args[current + 1], ASCENDING, DESCENDING);
		else
			throw BadRequestException();
	}
	managefilter.update_sort(propertyy, order);
	print_successful_execution_of_the_command();
}

string Utrip::detect_sort_type(string propertyy)
{
	if (propertyy == ID)
		return ID;
	else if (propertyy == NAME)
		return NAME;
	else if (propertyy == STAR_RATING)
		return STAR_RATING;
	else if (propertyy == CITY)
		return CITY;
	else if (propertyy == STANDARD_ROOM_PRICE)
		return STANDARD_ROOM_PRICE;
	else if (propertyy == DELUXE_ROOM_PRICE)
		return DELUXE_ROOM_PRICE;
	else if (propertyy == LUXURY_ROOM_PRICE)
		return LUXURY_ROOM_PRICE;
	else if (propertyy == PREMIUM_ROOM_PRICE)
		return PREMIUM_ROOM_PRICE;
	else if (propertyy == AVERAGE_ROOM_PRICE)
		return AVERAGE_ROOM_PRICE;
	else if (propertyy == RATING_PERSONAL)
		return RATING_PERSONAL;
	else
		throw BadRequestException();
}

void Utrip::post_manual_weights(std::vector<std::string> args)
{
	check_user_login();
	args = check_have_arg_seperator(tools.delete_element_of_vector(args, FIRST_ELEMENT));
	if (args.size() == MANUAL_WEIGHT_ACTIVE_COMMAND_ARGUMENT_NUMBER)
		find_args_of_manual_weights_active(args);
	else if (args.size() == MANUAL_WEIGHT_INACTIVE_COMMAND_ARGUMENT_NUMBER)
		find_args_of_manual_weights_inactive(args);
	else
		throw BadRequestException();
}

void Utrip::find_args_of_manual_weights_active(vector<string> args)
{
	bool activation;
	vector<double> weights(RATING_SIZE - 1, double(0));
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == LOCATION)
			weights[LOCATION_ELEMENT] = stod(args[current + 1]);
		else if (args[current] == CLEANLINESS)
			weights[CLEANLINESS_ELEMENT] = stod(args[current + 1]);
		else if (args[current] == STAFF)
			weights[STAFF_ELEMENT] = stod(args[current + 1]);
		else if (args[current] == FACILITIES)
			weights[FACILITIES_ELEMENT] = stod(args[current + 1]);
		else if (args[current] == VALUE_FOR_MONEY)
			weights[VALUE_FOR_MONEY_ELEMENT] = stod(args[current + 1]);
		else if (args[current] == ACTIVE)
			activation = detect_bool_type(args[current + 1], TRUE, FALSE);
		else
			throw BadRequestException();
	}
	manual_weights_active(weights, activation);
}

void Utrip::manual_weights_active(vector<double> weights, bool activation)
{
	for (int current = 0; current < weights.size(); current++)
		if (weights[current] < FIRST_VALID_RATING || weights[current] > LAST_VALID_RATING)
			throw BadRequestException();
	managefilter.update_manual_weights_active(weights, activation);
	print_successful_execution_of_the_command();
}

void Utrip::find_args_of_manual_weights_inactive(std::vector<std::string> args)
{
	bool activation;
	if (args[FIRST_ELEMENT] == ACTIVE)
		activation = detect_bool_type(args[FIRST_ELEMENT + 1], TRUE, FALSE);
	else
		throw BadRequestException();
	manual_weights_inactive(activation);
}

void Utrip::manual_weights_inactive(bool activation)
{
	managefilter.update_manual_weights_inactive(activation);
	print_successful_execution_of_the_command();
}

void Utrip::check_get_command(vector<string> args)
{
	if(args.size() == 0)
		throw BadRequestException();
	if (args[FIRST_ELEMENT] == WALLET_COMMAND)
		wallet_count(args);
	else if (args[FIRST_ELEMENT] == HOTELS_COMMAND)
		get_hotel(args);
	else if (args[FIRST_ELEMENT] == COMMENTS_COMMAND)
		get_comments(args);
	else if (args[FIRST_ELEMENT] == RATINGS_COMMAND)
		get_ratings(args);
	else if (args[FIRST_ELEMENT] == RESERVE_COMMAND)
		get_reserve();
	else if (args[FIRST_ELEMENT] == MANUAL_WEIGHT_COMMAND)
		get_manual_weights();
	else if (args[FIRST_ELEMENT] == ESTIMATED_WEIGHTS_COMMAND)
		get_estimated_weights();
	else
		throw NotFoundException();
}

void Utrip::wallet_count(vector<string> args)
{
	args = check_can_use_this_order(args, WALLET_AMOUNT_ARGUMENT_NUMBER);
	int count;
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == COUNT)
			count = stoi(args[current + 1]);
		else
			throw BadRequestException();
	}
	wallet_count_current_user(count);
}

void Utrip::wallet_count_current_user(int count)
{
	if (count > 0)
		current_user->wallet_count(count);
}

void Utrip::get_hotel(vector<string> args)
{
	if (args.size() > SHOW_HOTEL_INFO_ARGUMENT_NUMBER - 1)
		get_hotel_info_by_id(args);
	else
		show_all_hotels_info();
}

void Utrip::get_hotel_info_by_id(vector<string> args)
{
	args = check_can_use_this_order(args, SHOW_HOTEL_INFO_ARGUMENT_NUMBER);
	string id;
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == ID)
			id = args[current + 1];
		else
			throw BadRequestException();
	}
	show_hotel_info_by_id(id);
}

void Utrip::show_hotel_info_by_id(string id)
{
	for (int current = 0; current < hotels_info.size(); current++)
		if (hotels_info[current].get_hotel_unique_id() == id)
		{
			hotels_info[current].show_full_hotel_info();
			return;
		}
	throw NotFoundException();
}

void Utrip::show_all_hotels_info()
{
	check_user_login();
	if (hotels_info.size() == 0)
		throw EmptyException();
	managefilter.show_hotels_info();
}

void Utrip::get_comments(vector<string> args)
{
	args = check_can_use_this_order(args, GET_COMMENTS_ARGUMENT_NUMBER);
	string hotel_id;
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == HOTEL)
			hotel_id = args[current + 1];
		else
			throw BadRequestException();
	}
	get_comment_on_hotel(hotel_id);
}

void Utrip::get_comment_on_hotel(string hotel_id)
{
	for (int current = 0; current < hotels_info.size(); current++)
		if (hotels_info[current].get_hotel_unique_id() == hotel_id)
		{
			hotels_info[current].show_all_comment();
			return;
		}
	throw NotFoundException();
}

void Utrip::get_ratings(vector<string> args)
{
	args = check_can_use_this_order(args, GET_RATINGS_COMMAND_ARGUMENT_NUMBER);
	string hotel_id;
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == HOTEL)
			hotel_id = args[current + 1];
		else
			throw BadRequestException();
	}
	get_rating_on_hotel(hotel_id);
}

void Utrip::get_rating_on_hotel(string hotel_id)
{
	for (int current = 0; current < hotels_info.size(); current++)
		if (hotels_info[current].get_hotel_unique_id() == hotel_id)
		{
			hotels_info[current].show_all_ratings();
			return;
		}
	throw NotFoundException();
}

void Utrip::get_reserve()
{
	check_user_login();
	current_user->show_reserve();
}

void Utrip::get_manual_weights()
{
	check_user_login();
	managefilter.show_manual_weights_status();
}

void Utrip::get_estimated_weights()
{
	check_user_login();
	managefilter.show_estimated_weights();
}

void Utrip::check_delete_command(vector<string> args)
{
	if(args.size() == 0)
		throw BadRequestException();
	if (args[FIRST_ELEMENT] == FILTERS_COMMAND)
		delete_all_filters();
	else if (args[FIRST_ELEMENT] == RESERVE_COMMAND)
		delete_reserve(args);
	else
		throw BadRequestException();
}

void Utrip::delete_all_filters()
{
	check_user_login();
	managefilter.delete_all_filters();
	print_successful_execution_of_the_command();
}

void Utrip::delete_reserve(vector<string> args)
{
	args = check_can_use_this_order(args, DELETE_RESERVE_COMMAND_ARGUMENT_NUMBER);
	int reserve_id;
	for (int current = 0; current < args.size(); current += 2)
	{
		if (args[current] == ID)
			reserve_id = stoi(args[current + 1]);
		else
			throw BadRequestException();
	}
	current_user->cansel_reserve(reserve_id);
	print_successful_execution_of_the_command();
}