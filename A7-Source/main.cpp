#include "Utrip.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	Tools tools;
	vector<Hotel> hotels_info = tools.read_hotels_info(argv[HOTELS_FILE], argv[RATINGS_FILE]);
	Utrip utrip(hotels_info);
	utrip.get_command();
	return 0;
}