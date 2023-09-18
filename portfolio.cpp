#include "portfolio.h"
#include "cash.h"

Portfolio::Portfolio() {};

Portfolio::Portfolio(DataHandler *data_handler)
{
    dh = data_handler;

    for(std::string symbol : dh->symbols) {
        positions[symbol] = Position();
        holdings[symbol].reserve(dh->symbol_dates[symbol].size());
    };
    CASH_position = CASH(10000);
    CASH_holding.reserve(dh->symbol_dates["GOOG"].size());
}

void Portfolio::on_signal(std::string symbol, Direction direction)
{
    double price = dh->getLatestBarsN(symbol, 1)(dh->symbol_headers[symbol]["Close"]);
    update_position(price, symbol, 1, direction);
}

void Portfolio::update_position(double price, std::string symbol, int quantity, Direction direction)
{
    positions[symbol].update_position(price, quantity, direction);
    CASH_position.update_position(price, quantity, direction);
}

void Portfolio::update_value()
{   
    double price;
    for (std::string symbol : dh->symbols) {
        price = dh->getLatestBarsN(symbol, 1)(dh->symbol_headers[symbol]["Close"]);
        holdings[symbol].push_back(positions[symbol].update_value(price));
    };
    CASH_holding.push_back(CASH_position.update_value(1));
}
