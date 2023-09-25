#ifndef POSITION_H
#define POSITION_H

#include "ticker.h"
#include "trade.h"
#include "cash.h"

#include <list>

class Position {
  public:
    std::list<Trade> trades;

    quantity_t quantity;

    Position(quantity_t starting_quantity = 0);

    void update_position(money order_price, quantity_t order_quantity, Direction direction);

    money update_value(money price);

};

#endif