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

    latest_trade = new Trade(0, 0, 0, Direction::LONG);
    latest_trade->previous_trade = NULL;
}

void Position::add_trade(int order_price, int order_quantity, Direction direction) 
{
    Trade *t = new Trade(0, order_price, quantity, direction);
    t->previous_trade = latest_trade;
    latest_trade = t;

    quantity = quantity + ( direction * order_quantity );

};