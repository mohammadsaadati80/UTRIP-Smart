#include "DeluxeRoom.hpp"
using namespace std;

DeluxeRoom::DeluxeRoom(int _rate, int room_number)
			:Room::Room(_rate)
{
	initialization(DELUXE_ROOM_ID + to_string(room_number), DELUXE_ROOM_TYPE);
}