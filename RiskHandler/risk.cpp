// #include "risk.h"
// #include "../Direction.h"
// #include "../DataHandler/dh.h"

// RiskHandler::RiskHandler() {};

// RiskHandler::RiskHandler(DataHandler *data_handler,  Portfolio *p) {
//     dh = data_handler;
//     portfolio = p;

//     weights["APPL"] = .5;
//     weights["GOOG"] = .5;
// }

// double RiskHandler::check_weights(std::string symbol, double weight_adjustment, cents price, Direction direction) {
//     // Weight Adjustment is how of asset to buy or sell
//     // Reflected as a percentage of Total Equity

//     double* max_weight = weights[symbol];
//     double current_weight = (portfolio->holdings[symbol][-1] / portfolio->TE);
//     double potential_weight = current_weight + (weight_adjustment * direction);

//     if (max_weight < potential_weight) {
//         // Scale quantity down
//         weight_adjustment = max_weight - current_weight;
//     }

//     return weight_adjustment;
// }

// void RiskHandler::check_leverage()
// {

// }
