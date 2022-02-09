#include "Room.hpp"
using namespace std;

Room::Room(int _rate)
{
	rate = _rate;
}

void Room::initialization(string room_id, string room_type)
{
	this->room_id = room_id;
	this->room_type = room_type;
}

bool Room::is_empty_room(int check_in, int check_out)
{
	for (int current = 0;current < reserve_dates.size(); current++)
		if (reserve_dates[current].have_overlap(check_in, check_out))
			continue;
		else
			return false;
	return true;
}

void Room::reserve_room(int check_in, int check_out)
{
	reserve_dates.push_back(ReserveDate(check_in, check_out));
}

int Room::get_room_rate() { return rate; }

string Room::get_room_id() { return room_id; }

string Room::get_room_type() { return room_type; }

void Room::cansel_reserve(int check_in, int check_out)
{
	for(int current =0; current < reserve_dates.size(); current++)
		if (reserve_dates[current].check_dates_equal(check_in, check_out))
		{
			reserve_dates.erase(reserve_dates.begin() + current);
			return;
		}
}