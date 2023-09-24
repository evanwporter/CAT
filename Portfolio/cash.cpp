#include "cash.h"
#include "../utility.h"

#include <iostream>

CASH::CASH() {}

CASH::CASH(double starting_quantity) {
    quantity = starting_quantity;
};

double CASH::update_value(long price)
{
    return quantity;
};

void CASH::update_position(double order_price, double order_quantity, Direction direction)
{
    // self.quantity -= commission;
    // self.total_commission += commission 

    // std::cout << "You have " << quantity << std::endl;
    // std::cout << "Deducted " << (-1 * direction * order_quantity * order_price) << " from the bank." << std::endl;;

    quantity = quantity + (-1 * direction * order_quantity * order_price);
}