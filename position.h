#ifndef POSITION_H
#define POSITION_H

#include "ticker.h"
#include "trade.h"

class Position {
  public:
    Ticker ticker;
    Trade *latest_trade;

    double quantity;

    Position();

    void add_trade(double order_price, double order_quantity, Direction direction);

    double update_value(double price);

};

#endif