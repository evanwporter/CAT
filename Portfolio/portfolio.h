#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "ticker.h"
#include "trade.h"
#include "position.h"
#include "cash.h"
#include "../utility.h"
#include "../DataHandler/dh.h"

#include <unordered_map>
#include <string>
#include <vector>

class Portfolio {
  public:
    std::unordered_map<std::string, Position> positions;
    std::unordered_map<std::string, std::vector<money>> holdings;

    CASH CASH_position;
    std::vector<money> CASH_holding;

    DataHandler *dh;

    Portfolio();

    Portfolio(DataHandler *data_handler);
    void on_fill(std::string symbol, money price, int quantity, Direction direction);

    void update_position(long price, std::string symbol, int quantity, Direction direction);

    void update_value();//bool edit = false);

    std::vector<double> TOTAL_EQUITY, ASSETS, LIABILITIES;

    double A, L, TE;

};

#endif