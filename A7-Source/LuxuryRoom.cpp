#include "LuxuryRoom.hpp"
using namespace std;

LuxuryRoom::LuxuryRoom(int _rate, int room_number)
	:Room::Room(_rate)
{
	initialization(LUXURY_ROOM_ID + to_string(room_number), LUXURY_ROOM_TYPE);
}