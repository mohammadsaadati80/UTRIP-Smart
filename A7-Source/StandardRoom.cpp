#include "StandardRoom.hpp"
using namespace std;

StandardRoom::StandardRoom(int _rate, int room_number)
	:Room::Room(_rate)
{
	initialization(STANDARD_ROOM_ID + to_string(room_number), STANDARD_ROOM_TYPE);
}