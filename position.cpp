#include "position.h"
#include "trade.h"
#include "direction.h"


#include <iostream>
#include <Eigen/Dense>

 
using Eigen::MatrixXd;
using namespace std;

Position::Position()
{
    quantity = 0;
}

void Position::update_position(double order_price, double order_quantity, Direction direction)
{
    trades.push_front(Trade(0, order_price, quantity, direction));
    quantity = quantity + ( direction * order_quantity );
}
double Position::update_value(double price)
{
    return quantity * price;
};