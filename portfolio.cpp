#include "portfolio.h"
#include "cash.h"

Portfolio::Portfolio() {};

Portfolio::Portfolio(DataHandler *data_handler)
{
    dh = data_handler;

    for(std::string symbol : dh->symbols) {
        positions[symbol] = Position();
        holdings[symbol].reserve(dh->total_bars);
    };
    CASH_position = CASH(10000);
    CASH_holding.reserve(dh->total_bars);

    TOTAL_EQUITY.reserve(dh->total_bars);
    ASSETS.reserve(dh->total_bars);
    LIABILITIES.reserve(dh->total_bars);

}

void Portfolio::on_signal(std::string symbol, Direction direction)
{
    double price = dh->getLatestBarsN(symbol, 1)(dh->symbol_headers[symbol]["Close"]);
    update_position(price, symbol, 10, direction);

    // std::cout << "Executed trade for 1 share of " << symbol << " at " << price << "." <<std::endl;

    // std::cout << dh->symbol_data["GOOG"] << std::endl;
    // std::cout << dh->getLatestBarsN(symbol, 1) << std::endl;

    // std::cout << dh->symbol_headers[symbol]["Close"] << std::endl;


}

void Portfolio::update_position(double price, std::string symbol, int quantity, Direction direction)
{
    positions[symbol].update_position(price, quantity, direction);
    CASH_position.update_position(price, quantity, direction);
}

void Portfolio::update_value()
{   
    double price, value;

    A = 0;
    L = 0;

    for (std::string symbol : dh->symbols) {
        price = dh->getLatestBarsN(symbol, 1)(dh->symbol_headers[symbol]["Close"]);
        value = positions[symbol].update_value(price);
        holdings[symbol].push_back(value);

        if (value >= 0) A += value;
        else L += value;
    };

    value = CASH_position.update_value(1);
    CASH_holding.push_back(value);

    if (value >= 0) A += value;
    else L += value;

    TE = A + L;

    ASSETS.push_back(A);
    LIABILITIES.push_back(L);
    TOTAL_EQUITY.push_back(TE);
    
}
