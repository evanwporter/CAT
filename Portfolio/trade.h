#ifndef TRADE_H
#define TRADE_H

#include <string>
#include "../direction.h"


// For space efficiency, each trade is a node in a linked list.
// Linked lists are being used since trades doesn't need to be
// accessed all that often if at all.
// And when it is accessed, it will be accessed all at once,
// thus it doesn't matter if looping is done.
class Trade {
  public:
    double time;

    // Doesn't really matter that the trade knows what symbol its trading
    // Ticker ticker;

    double size;
    
    Direction direction;

    // Average Price
    long price;

    // Trade *previous_trade;

    Trade();

    Trade(
      const int execution_time, 
      const int average_price,
      const int position_size, 
      const Direction dir
    ): time(execution_time), price(average_price), size(position_size), direction(dir) {};
};

#endif