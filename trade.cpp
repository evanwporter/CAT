#include "trade.h"

using namespace std;

Trade::Trade() {};

Trade::Trade(
    const int execution_time, 
    const int average_price,
    const int position_size, 
    const Direction dir
): time(execution_time), price(average_price), size(position_size), direction(dir) {};
