#ifndef CASH_H
#define CASH_H

#include "Direction.h"

class CASH {
    public:
      double quantity;
      CASH();
      CASH(double starting_quantity);
      void update_position(double order_price, double order_quantity, Direction direction);
      double update_value(long price);
};

#endif