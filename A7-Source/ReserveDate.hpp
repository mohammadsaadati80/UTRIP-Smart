#ifndef __RESERVE_DATE_H__
#define __RESERVE_DATE_H__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <functional>

class ReserveDate
{
public:
	ReserveDate(int check_in, int check_out);
	bool have_overlap(int check_in, int check_out);
	bool check_dates_equal(int check_in, int check_out);

private:
	int check_in;
	int check_out;

};

#endif