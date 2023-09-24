#include "strategy.h"
#include "../utility.h"

Strategy::Strategy() {};

void Strategy::on_data()
{
    if (!traded) {
        rh->on_signal("GOOG", Direction::LONG);
        rh->on_signal("AAPL", Direction::LONG);
        traded = true;
    }
};