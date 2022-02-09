#ifndef __PREMIUM_ROOM_H__
#define __PREMIUM_ROOM_H__

#include "Room.hpp"

#define PREMIUM_ROOM_ID 'p'

class PremiumRoom : public Room
{
public:
	PremiumRoom(int rate, int room_number);

private:

};

#endif 