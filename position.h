#ifndef POSITION_H
#define POSITION_H

#include "ticker.h"
#include "trade.h"

class Position {
  public:
    Ticker ticker;
    Trade *latest_trade;

    int quantity;

    Position();

    void add_trade(int price, int quantity, Direction direction); 

};

#endif