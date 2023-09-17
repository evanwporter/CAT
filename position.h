#ifndef POSITION_H
#define POSITION_H

#include "ticker.h"
#include "trade.h"
#include "cash.h"

#include <list>

class Position : public CASH {
  public:
    std::list<Trade> trades;

    Position();

    void update_position(double order_price, double order_quantity, Direction direction);

    double update_value(double price);

};

#endif