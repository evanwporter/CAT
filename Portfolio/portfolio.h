#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "ticker.h"
#include "trade.h"
#include "position.h"
#include "cash.h"
#include "../utility.h"
#include "../DataHandler/dh.h"

#include "../Libraries/robin_hood.h"

#include <unordered_map>
#include <string>
#include <vector>

namespace CAT {
class Portfolio {
  public:
    bt_settings* settings;

    robin_hood::unordered_map<std::string, Position> positions;
    robin_hood::unordered_map<std::string, std::vector<money>> holdings;

    CASH CASH_position;
    std::vector<money> CASH_holding;

    DataHandler *dh;

    Portfolio();

    // Portfolio(DataHandler *data_handler);
    Portfolio(DataHandler *data_handler, bt_settings *bts);

    void on_fill(std::string symbol, money price, int quantity, Direction direction);

    void update_position(long price, std::string symbol, int quantity, Direction direction);

    void update_value();//bool edit = false);

    std::vector<double> TOTAL_EQUITY, ASSETS, LIABILITIES;

    double A, L, TE;

};
};

#endif