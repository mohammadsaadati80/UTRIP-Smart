#include "Tools.hpp"
using namespace std;

vector<Hotel> Tools::read_hotels_info(string file_address, string ratings_file_address)
{
	vector<Hotel> hotels_info;
	vector<string> file_lines = read_file_lines(file_address);
	vector<string> ratings_file_lines = read_file_lines(ratings_file_address);
	for (int current = FIRST_VALID_LINE; current < file_lines.size(); current++)
		hotels_info.push_back(create_new_hotel(file_lines[current], ratings_file_lines));
	return hotels_info;
}

vector<string> Tools::read_file_lines(string address)
{
	vector<string> read_file_lines;
	ifstream file(address.c_str());
	string line;
	while (getline(file, line))
		read_file_lines.push_back(line);
	return read_file_lines;
}

Hotel Tools::create_new_hotel(string line, vector<string> ratings_file_lines)
{
	stringstream string_stream(line);
	vector<int> room_number;
	vector<int> room_price;
	vector<string> hotel_string;
	vector<double> hotel_double;
	int hotel_int_star;
	string hotel_facilities;
	for (int current = 0; current < HOTEL_ELEMENTS; current++)
	{
		string current_line;
		getline(string_stream, current_line, MAIN_SEPARATOR);
		if (current == UNIQUE_ID_ELEMENT || current == PROPERTY_NAME_ELEMENT || current == OVERVIEW_ELEMENT + 1 || current == CITY_ELEMENT + 2 || current == IMAGE_URL_ELEMENT + 4)
			hotel_string.push_back(current_line);
		if (current == HOTEL_STAR_ELEMENT)
			hotel_int_star = stoi(current_line);
		if (current == LATITUDE_ELEMENT + 6 || current == LONGITTUDE_ELEMENT + 6)
			hotel_double.push_back(stod(current_line));
		if (current == HOTEL_FACILITIES)
			hotel_facilities = current_line;
		if (current >= FIRST_ROOM_NUMBER_ELEMENT && current <= LAST_ROOM_NUMBER_ELEMENT)
			room_number.push_back(stoi(current_line));
		if (current >= FIRST_ROOM_PRICE_ELEMENT && current <= LAST_ROOM_PRICE_ELEMENT)
			room_price.push_back(stoi(current_line));
	}
	vector<vector<Room*> > hotel_rooms = create_rooms_of_hotel(room_number, room_price);
	Rating hotel_ratings = create_rating_of_hotel(hotel_string[UNIQUE_ID_ELEMENT], ratings_file_lines);
	return Hotel(hotel_string, hotel_int_star, hotel_facilities, hotel_double, hotel_rooms, room_price, hotel_ratings);
}

vector<string> Tools::create_hotel_facilities_vector(string line)
{
	vector<string> hotel_facilities;
	stringstream string_stream(line);
	string current_facilities;
	while (getline(string_stream, current_facilities, SPECIAL_SEPARATOR))
		hotel_facilities.push_back(current_facilities);
	return hotel_facilities;
}

vector<vector<Room*> > Tools::create_rooms_of_hotel(vector<int> room_number, vector<int> room_price)
{
	vector<vector<Room*> > hotel_rooms(NUMBER_OF_ROOM_TYPES);
	for (int current = 0; current < room_number[STANDARD_ROOM]; current++)
	{
		StandardRoom* new_room = new StandardRoom(room_price[STANDARD_ROOM], current + 1);
		hotel_rooms[STANDARD_ROOM].push_back(new_room);
	}
	for (int current = 0; current < room_number[DELUXE_ROOM]; current++)
	{
		DeluxeRoom* new_room = new DeluxeRoom(room_price[DELUXE_ROOM], current + 1);
		hotel_rooms[DELUXE_ROOM].push_back(new_room);
	}	
	for (int current = 0; current < room_number[LUXURY_ROOM]; current++)
	{
		LuxuryRoom* new_room = new LuxuryRoom(room_price[LUXURY_ROOM], current + 1);
		hotel_rooms[LUXURY_ROOM].push_back(new_room);
	}	
	for (int current = 0; current < room_number[PREMIUM_ROOM]; current++)
	{
		PremiumRoom* new_room = new PremiumRoom(room_price[PREMIUM_ROOM], current + 1);
		hotel_rooms[PREMIUM_ROOM].push_back(new_room);
	}
	return hotel_rooms;
}

Rating Tools::create_rating_of_hotel(string hotel_id, vector<string> ratings_file_lines)
{
	vector<double> rates;
	for (int current = 0;current < ratings_file_lines.size();current++)
	{
		stringstream string_stream(ratings_file_lines[current]);
		string current_line;
		getline(string_stream, current_line, MAIN_SEPARATOR);
		if (current_line == hotel_id)
		{
			for (int current_rate = 0;current_rate <= OVERALL_RATING_ELEMENT;current_rate++)
			{
				getline(string_stream, current_line, MAIN_SEPARATOR);
				rates.push_back(stod(current_line));
			}
			break;
		}
	}
	return Rating(rates);
}

vector<string> Tools::delete_element_of_vector(vector<string> args, int element)
{
	args.erase(args.begin() + element);
	return args;
}