#include "strategy.h"
#include "../direction.h"

Strategy::Strategy() {};

void Strategy::on_data()
{
    if (!traded) {
        portfolio->on_signal("GOOG", Direction::LONG);
        portfolio->on_signal("AAPL", Direction::LONG);
        traded = true;
    }
};