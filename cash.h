#ifndef CASH_H
#define CASH_H

#include "Direction.h"

class CASH {
    public:
      double quantity;
      CASH();
      void update_position(double order_price, double order_quantity, Direction direction);
      double update_value(double price);
};

#endif