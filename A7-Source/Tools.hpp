#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include "Hotel.hpp"
#include "Room.hpp"
#include "DeluxeRoom.hpp"
#include "LuxuryRoom.hpp"
#include "PremiumRoom.hpp"
#include "StandardRoom.hpp"

#define MAIN_SEPARATOR ','
#define SPECIAL_SEPARATOR '|'
#define FIRST_VALID_LINE 1
#define NUMBER_OF_ROOM_TYPES 4
#define HOTEL_STAR_ELEMENT 2
#define HOTEL_FACILITIES 4
#define FIRST_ROOM_NUMBER_ELEMENT 9
#define LAST_ROOM_NUMBER_ELEMENT 12
#define FIRST_ROOM_PRICE_ELEMENT 13
#define LAST_ROOM_PRICE_ELEMENT 16
#define HOTEL_ELEMENTS 17

class Tools
{
public:
	std::vector<Hotel> read_hotels_info(std::string file_address, std::string ratings_file_address);
	std::vector<std::string> read_file_lines(std::string address);
	Hotel create_new_hotel(std::string line, std::vector<std::string> ratings_file_lines);
	std::vector<std::string> create_hotel_facilities_vector(std::string line);
	std::vector<std::vector<Room*> > create_rooms_of_hotel(std::vector<int> room_number, std::vector<int> room_price);
	Rating create_rating_of_hotel(std::string hotel_id, std::vector<std::string> ratings_file_lines);
	std::vector<std::string> delete_element_of_vector(std::vector<std::string> args, int element);

private:

};

#endif 