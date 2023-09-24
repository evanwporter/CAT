#ifndef POSITION_H
#define POSITION_H

#include "ticker.h"
#include "trade.h"
#include "cash.h"

#include <list>

class Position {
  public:
    std::list<Trade> trades;

    double quantity;

    Position(double starting_quantity = 0);

    void update_position(double order_price, double order_quantity, Direction direction);

    double update_value(long price);

};

#endif