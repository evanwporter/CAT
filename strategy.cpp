#include "strategy.h"
#include "direction.h"

Strategy::Strategy() {};

void Strategy::on_data()
{
    portfolio->on_signal(100, "GOOG", Direction::LONG);
};
