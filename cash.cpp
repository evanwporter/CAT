#include "cash.h"
#include "direction.h"

CASH::CASH() {};

double CASH::update_value(double price)
{
    return quantity;
};

void CASH::update_position(double order_price, double order_quantity, Direction direction)
{
    // self.quantity -= commission;
    // self.total_commission += commission  
    quantity = quantity + (-1 * direction * order_quantity * order_price);
}