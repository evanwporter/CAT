#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "ticker.h"
#include "trade.h"
#include "position.h"

#include <unordered_map>
#include <string>
#include <vector>

class Portfolio {
  public:
    std::unordered_map<std::string, Position> positions;
    std::vector<std::string> symbols;

    Portfolio();

};

#endif