#ifndef __ROOM_H__
#define __ROOM_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <functional>
#include "ReserveDate.hpp"

#define STANDARD_ROOM 0
#define DELUXE_ROOM 1
#define LUXURY_ROOM 2
#define PREMIUM_ROOM 3
#define STANDARD_ROOM_TYPE "standard"
#define DELUXE_ROOM_TYPE "deluxe"
#define LUXURY_ROOM_TYPE "luxury"
#define PREMIUM_ROOM_TYPE "premium"
#define FIRST_ROOM 0

class Room
{
public:
	Room(int rate);
	bool is_empty_room(int check_in, int check_out);
	void reserve_room(int check_in, int check_out);
	int get_room_rate();
	std::string get_room_id();
	std::string get_room_type();
	void cansel_reserve(int check_in, int check_out);

private:
	std::string room_id;
	int rate;
	std::vector<ReserveDate> reserve_dates;
	std::string room_type;

protected:
	void initialization(std::string room_id, std::string room_type);
	

};


 
#endif