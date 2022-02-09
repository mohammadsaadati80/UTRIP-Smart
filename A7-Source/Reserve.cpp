#include "Reserve.hpp"
using namespace std;

Reserve::Reserve(int reservation_id, vector<Room*> reserved_rooms, int quantity, int cost, int check_in_date, int check_out_date, std::string hotel_id)
{
	this->reservation_id = reservation_id;
	this->reserved_rooms = reserved_rooms;
	this->quantity = quantity;
	this->cost = cost;
	this->check_in_date = check_in_date;
	this->check_out_date = check_out_date;
	this->hotel_id = hotel_id;
	this->room_type = reserved_rooms[FIRST_ROOM]->get_room_type();
}

void Reserve::show_room_id()
{
	for (int current = 0;current < reserved_rooms.size(); current++)
	{
		cout << reserved_rooms[current]->get_room_id();
		if (current < reserved_rooms.size())
			cout << SPACE;
	}
	cout << endl;
}

void Reserve::show_reserve()
{
	cout << ID_TEXT << reservation_id << HOTEL_TEXT << hotel_id << ROOM_TEXT << room_type << QUANTITY_TEXT << quantity << COST_TEXT << cost << CHECK_IN_TEXT << check_in_date << CHECK_OUT_TEXT << check_out_date << endl;
}

int Reserve::get_reservation_id() { return reservation_id; }

int Reserve::get_cost() { return cost; }

void Reserve::cansel_reserve()
{
	for (int current = 0;current < reserved_rooms.size(); current++)
		reserved_rooms[current]->cansel_reserve(check_in_date, check_out_date);
}

int Reserve::get_room_price() { return reserved_rooms[FIRST_ROOM]->get_room_rate(); }

int Reserve::get_quantity() { return quantity; }