#include "MainFilter.hpp"
using namespace std;

bool MainFilter::get_filter_status() { return filter_actived; }

void MainFilter::deactive_fliter() { filter_actived = false; }
