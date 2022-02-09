#include "PremiumRoom.hpp"
using namespace std;

PremiumRoom::PremiumRoom(int _rate, int room_number)
	:Room::Room(_rate)
{
	initialization(PREMIUM_ROOM_ID + to_string(room_number), PREMIUM_ROOM_TYPE);
}