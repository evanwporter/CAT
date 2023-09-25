#include "risk.h"
#include "../utility.h"
#include "../DataHandler/dh.h"

#include <cmath>
#include <iostream>


RiskHandler::RiskHandler() {};

RiskHandler::RiskHandler(DataHandler *data_handler,  Portfolio *p) {
    dh = data_handler;
    portfolio = p;

    weights["APPL"][0] = 0;
    weights["APPL"][1] = .5;

    weights["GOOG"][0] = 0;
    weights["GOOG"][1] = .5;

    // weights["MSFT"][0] = 0;
    // weights["MSFT"][1] = .25;

    // weights["BRK-B"][0] = 0;
    // weights["BRK-B"][1] = .25;

}

double RiskHandler::check_weights(std::string symbol, double weight_adjustment, money price, Direction direction) {
    // Weight Adjustment is how of asset to buy or sell
    // Reflected as a percentage of Total Equity

    double max_weight, current_weight, potential_weight;

    current_weight = (portfolio->holdings[symbol][dh->current]) / portfolio->TE);

    if (direction == Direction::LONG) {
        max_weight = weights[symbol][1];
        potential_weight = current_weight + (weight_adjustment * 1);
    }
    else {
        max_weight = weights[symbol][0];
        potential_weight = current_weight + (weight_adjustment * -1);
    };
    
    std::cout << symbol << " " << current_weight << " " << portfolio->holdings[symbol][dh->current] << " ";


    // Scale quantity down
    if (max_weight < potential_weight) {
        weight_adjustment = max_weight - current_weight;
    }
    return weight_adjustment;
};

void RiskHandler::on_signal(std::string symbol, Direction direction)
{
    money price = dh->getLatestBarsN(symbol, 1)(dh->symbol_headers[symbol]["Adj Close"]);
    double WA = check_weights(symbol, .4, price, direction);

    // int quantity = (portfolio->TE * WA / price);
    int quantity = 1;
    std::cout << " " << portfolio->positions[symbol].quantity * price << " " << WA << " " << portfolio->TE << " " << price << " " << portfolio->positions[symbol].quantity << std::endl;

    for (auto i: portfolio->holdings[symbol]) std::cout << i << " ";
    if (quantity != 0) portfolio->on_fill(symbol, price, quantity, direction);
}