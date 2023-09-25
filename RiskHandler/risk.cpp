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

}

double RiskHandler::check_weights(std::string symbol, double weight_adjustment, cents price, Direction direction) {
    // Weight Adjustment is how of asset to buy or sell
    // Reflected as a percentage of Total Equity

    double max_weight, current_weight, potential_weight;

    if (direction == Direction::LONG) {
        max_weight = weights[symbol][1];
    }
    else max_weight = weights[symbol][0];
    
    if (portfolio->holdings[symbol][-1] == 0) current_weight = 0;
    else current_weight = (portfolio->holdings[symbol][-1] / portfolio->TE);
    potential_weight = current_weight + (weight_adjustment * direction);

    std::cout << symbol << " " << current_weight << " " << portfolio->holdings[symbol][-1] << " ";


    // Scale quantity down
    if (max_weight < potential_weight) {
        weight_adjustment = max_weight - current_weight;
    }
    return weight_adjustment;
};

void RiskHandler::on_signal(std::string symbol, Direction direction)
{
    cents price = dh->getLatestBarsN(symbol, 1)(dh->symbol_headers[symbol]["Adj Close"]);
    // double WA = check_weights(symbol, .4, price, direction);

    // int quantity = (portfolio->TE * WA / price);
    int quantity = 1;
    // std::cout << WA << " " << portfolio->TE << " " << price << std::endl;
    if (quantity != 0) portfolio->on_fill(symbol, price, quantity, direction);
}