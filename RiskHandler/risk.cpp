#include "risk.h"
#include "../utility.h"
#include "../DataHandler/dh.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace CAT;

RiskHandler::RiskHandler() {};

RiskHandler::RiskHandler(DataHandler *data_handler,  Portfolio *p, bt_settings *bts) {
    dh = data_handler;
    portfolio = p;
    settings = bts;

    if (settings->mode == "backtest") simple = settings->doc["SIMPLE RISK"].get_bool();
    MLR = settings->doc["MAXIMUM LEVERAGE RATIO"].get_uint64();

    // generate_weights("equal");

}



double RiskHandler::check_weights(std::string symbol, double weight_adjustment, money price, Direction direction) {
    // Weight Adjustment is how of asset to buy or sell
    // Reflected as a percentage of Total Equity

    double max_weight, min_weight, symbol_weight, cash_weight, potential_weight;

    // Current weights
    symbol_weight = (( portfolio->positions[symbol].quantity * price ) / (double) portfolio->TE ) * 100;
    cash_weight = ( (double) portfolio->CASH_position.quantity / portfolio->TE ) * 100;

    // std::cout << "Current Weights " << current_weight << " " << current_cash_weight << std::endl;
    // std::cout << "Cash Quantity " << portfolio->CASH_position.quantity << " TE " << portfolio->TE << std::endl;

    if (direction == Direction::LONG_) {
        // CASH WEIGHT goes DOWN
        // SYMBOL WEIGHT goes UP

        // Weight Bounds
        max_weight = weights[symbol][1]; // symbol
        min_weight = CASH_weight[0];     // cash

        double cash_distance = cash_weight - min_weight;               
        double symbol_distance = max_weight - symbol_weight;

        double distance = cash_distance > symbol_distance ? symbol_distance : cash_distance;
        
        if (distance < weight_adjustment) {
            // Scales quanity down
            weight_adjustment = distance;
        }

        // if (current_weight + weight_adjustment > max_weight) weight_adjustment = max_weight - current_weight;
        // if (current_cash_weight - weight_adjustment < min_weight) weight_adjustment = current_cash_weight - min_weight;
    }
    else { // SHORT_
        // CASH WEIGHT goes UP
        // SYMBOL WEIGHT goes DOWN
        
        min_weight = weights[symbol][0]; // symbol
        max_weight = CASH_weight[1];     // cash

        double cash_distance = max_weight - cash_weight;               
        double symbol_distance = symbol_weight - min_weight;

        double distance = cash_distance > symbol_distance ? symbol_distance : cash_distance;
        
        if (distance < weight_adjustment) {
            // Scales quanity up
            weight_adjustment = distance;
        }
    };
    std::cout << " " << symbol << " " << weight_adjustment << " "; 

    return weight_adjustment;
}

void RiskHandler::generate_weights(std::string method) {
    double Max_Total_Weight = 100*MLR + 100;
    double Max_Cash_Weight = 100*MLR + 100;

    double Min_Cash_Weight = 100 - Max_Total_Weight;
    double Min_Total_Weight = 100 - Min_Cash_Weight;

    CASH_weight[0] = Min_Cash_Weight;
    CASH_weight[1] = Max_Cash_Weight;

    if (method == "equal") {

        double individual_max_weight = Max_Total_Weight / settings->symbols.size();
        double individual_min_weight = Min_Total_Weight / settings->symbols.size();

        for (std::string symbol : settings->symbols) {
            weights[symbol][0] = individual_min_weight;
            weights[symbol][1] = individual_max_weight;

            // std::cout << individual_min_weight << " " << individual_max_weight << std::endl;
        }
        // std::cout << Min_Cash_Weight << " " << Max_Cash_Weight;
    }
    else throw std::invalid_argument("At this time only equal weighting is accepted for the weight generation process.");
};

void RiskHandler::on_signal(std::string symbol, Direction direction)
{
    money price = dh->getLatestBarsN(symbol, 1)(dh->symbol_headers[symbol]["Adj Close"]);
    int quantity;

    if (!simple) { // Currently doesn't work
        double WA = check_weights(symbol, 10, price, direction) / 100;
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