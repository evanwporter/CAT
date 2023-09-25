#include "position.h"
#include "trade.h"
#include "../utility.h"

#include <iostream>
#include <Eigen/Dense>
 
using Eigen::MatrixXd;
using namespace std;

Position::Position(quantity_t starting_quantity)
{
    quantity = starting_quantity;
}

void Position::update_position(money order_price, quantity_t order_quantity, Direction direction)
{
    trades.push_front(Trade(0, order_price, quantity, direction));
    quantity += ( direction * order_quantity );
}
money Position::update_value(money price)
{
    return quantity * price;
};