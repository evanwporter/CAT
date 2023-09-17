#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "ticker.h"
#include "trade.h"
#include "position.h"
#include "direction.h"
#include "dh.h"

#include <unordered_map>
#include <string>
#include <vector>

class Portfolio {
  public:
    std::unordered_map<std::string, Position> positions;
    std::unordered_map<std::string, std::vector<double>> holdings;

    // std::vector<std::vector<double>> holdings;

    DataHandler *dh;

    Portfolio();

    Portfolio(DataHandler *data_handler);
    void on_signal(double price, std::string symbol, Direction direction);

    void update_position(double price, std::string symbol, int quantity, Direction direction);

    void update_value(double price);
};

#endif