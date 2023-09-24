#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "ticker.h"
#include "trade.h"
#include "position.h"
#include "cash.h"
#include "../direction.h"
#include "../DataHandler/dh.h"

#include <unordered_map>
#include <string>
#include <vector>

class Portfolio {
  public:
    std::unordered_map<std::string, Position> positions;
    std::unordered_map<std::string, std::vector<double>> holdings;

    CASH CASH_position;
    std::vector<double> CASH_holding;

    DataHandler *dh;

    Portfolio();

    Portfolio(DataHandler *data_handler);
    void on_signal(std::string symbol, Direction direction);

    void update_position(long price, std::string symbol, int quantity, Direction direction);

    void update_value();

    std::vector<double> TOTAL_EQUITY, ASSETS, LIABILITIES;

    double A, L, TE;

};

#endif