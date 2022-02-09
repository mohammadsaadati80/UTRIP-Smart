#ifndef __RESERVE_H__
#define __RESERVE_H__

#include "Room.hpp"

#define SPACE ' '
#define ID_TEXT "id: "
#define HOTEL_TEXT " hotel: "
#define ROOM_TEXT " room: "
#define QUANTITY_TEXT " quantity: "
#define COST_TEXT " cost: "
#define CHECK_IN_TEXT " check_in "
#define CHECK_OUT_TEXT " check_out "


class Reserve
{
public:
	Reserve(int reservation_id, std::vector<Room*> reserved_rooms, int quantity, int cost, int check_in_date, int check_out_date, std::string hotel_id);
	void show_room_id();
	void show_reserve();
	int get_reservation_id();
	int get_cost();
	void cansel_reserve();
	int get_room_price();
	int get_quantity();

private:
	int reservation_id;
	std::vector<Room*> reserved_rooms;
	int check_in_date;
	int check_out_date;
	int quantity;
	int cost;
	std::string hotel_id;
	std::string room_type;

};


#endif 