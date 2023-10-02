#include "risk.h"
#include "../utility.h"
#include "../DataHandler/dh.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace CAT;

RiskHandler::RiskHandler() {};

RiskHandler::RiskHandler(DataHandler *data_handler,  Portfolio *p) {
    dh = data_handler;
    portfolio = p;

    if (dh->mode == "backtest") simple = dh->settings["SIMPLE RISK"].get_bool();

    generate_weights("equal");

}



double RiskHandler::check_weights(std::string symbol, double weight_adjustment, money price, Direction direction) {
    // Weight Adjustment is how of asset to buy or sell
    // Reflected as a percentage of Total Equity

    double max_weight, current_weight, potential_weight;

    current_weight = ( portfolio->positions[symbol].quantity * (double) price * 100) / (double) portfolio->TE;

    if (direction == Direction::LONG_) {
        max_weight = weights[symbol][1];
        potential_weight = current_weight + (weight_adjustment * 1);
    }
    else {
        max_weight = weights[symbol][0];
        potential_weight = current_weight + (weight_adjustment * -1);
    };
    
    // Scale quantity down
    if (max_weight < potential_weight) {
        weight_adjustment = max_weight - current_weight;
    }
    return weight_adjustment;
}

void RiskHandler::generate_weights(std::string method) {
    if (method == "equal") {
        int n_symbols = dh->symbols.size();
        int individual_weighting = std::floor(100 / n_symbols);
        for (auto symbol : dh->symbols) {
            weights[symbol][0] = 0;
            weights[symbol][1] = individual_weighting;
        }
    }
    else throw std::invalid_argument("At this time only equal weighting is accepted for the weight generation process.");
};

void RiskHandler::on_signal(std::string symbol, Direction direction)
{
    money price = dh->getLatestBarsN(symbol, 1)(dh->symbol_headers[symbol]["Adj Close"]);
    int quantity;

    if (!simple) {
        double WA = check_weights(symbol, .04 * 100, price, direction) / 100;
        quantity = std::floor(double(portfolio->TE) * WA / price);
    }
    else {
        double cost = double(portfolio->TE) * .1;
        if (direction == Direction::LONG_) {
            if (cost > portfolio->CASH_position.quantity) {
                cost = portfolio->CASH_position.quantity;
            };
        } 
        else {
            if (cost > (portfolio->positions[symbol].quantity * price)) {
                cost = portfolio->positions[symbol].quantity * price;
            };
        };
        quantity = std::floor(cost / price);
    }

    if (quantity != 0) portfolio->on_fill(symbol, price, quantity, direction);
};