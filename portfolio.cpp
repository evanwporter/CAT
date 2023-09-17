#include "portfolio.h"

Portfolio::Portfolio() {};

Portfolio::Portfolio(DataHandler *data_handler)
{
    dh = data_handler;

    for(std::string symbol : dh->symbols) {
        positions[symbol] = Position();
        holdings[symbol].reserve(dh->symbol_dates[symbol].size());
    };
    positions["USD"] = Position();
}

void Portfolio::on_signal(double price, std::string symbol, Direction direction)
{
    update_position(price, symbol, 1, direction);
}

void Portfolio::update_position(double price, std::string symbol, int quantity, Direction direction)
{
    positions[symbol].add_trade(price, quantity, direction);
}

void Portfolio::update_value(double price)
{
    for(std::string symbol : dh->symbols) {
        holdings[symbol].push_back(positions[symbol].update_value(price));
    };

}
