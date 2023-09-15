#ifndef TICKER_H
#define TICKER_H

#include <string>


class Ticker {
  public:
    std::string ticker;
    std::string type;

    Ticker();

    Ticker(const std::string ticker, const std::string type): ticker(ticker), type(type) {}
};

#endif