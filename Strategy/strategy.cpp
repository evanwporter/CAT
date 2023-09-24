#include "strategy.h"
#include "../utility.h"

Strategy::Strategy() {};

void Strategy::on_data()
{
    if (!traded) {
        for (auto symbol : dh->symbols) rh->on_signal(symbol, Direction::LONG);
        // rh->on_signal("GOOG", Direction::LONG);
        // rh->on_signal("AAPL", Direction::LONG);
        // rh->on_signal("DIS", Direction::LONG);
        traded = true;
    }
};