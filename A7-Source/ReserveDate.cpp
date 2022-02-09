#include "ReserveDate.hpp"
using namespace std;

ReserveDate::ReserveDate(int check_in, int check_out)
{
	this->check_in = check_in;
	this->check_out = check_out;
}

bool ReserveDate::have_overlap(int check_in, int check_out)
{
	if (this->check_in > check_out || this->check_out < check_in)
		return true;
	else
		return false;
}

bool ReserveDate::check_dates_equal(int check_in, int check_out)
{
	if (this->check_in == check_in && this->check_out == check_out)
		return true;
	else
		return false;
}