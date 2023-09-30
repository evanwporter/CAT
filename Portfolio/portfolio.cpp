#include "portfolio.h"
#include "cash.h"

#include <iomanip>

using namespace CAT;

Portfolio::Portfolio() {};

Portfolio::Portfolio(DataHandler *data_handler)
{
    dh = data_handler;

    for(std::string symbol : dh->symbols) {
        positions[symbol] = Position();
        holdings[symbol].reserve(dh->total_bars - 100);
        holdings[symbol].push_back(0);
    };
    CASH_position = CASH(dh->settings["INITIAL CASH"].get_uint64() * dh->money_mult);
    CASH_holding.reserve(dh->total_bars);
    CASH_holding.push_back(CASH_position.quantity);

    // std::cout << "Starting bank amount: " << CASH_position.quantity << std::endl;
    // std::cout << "Effective money mult: " << dh->money_mult << std::endl;

    TOTAL_EQUITY.reserve(dh->total_bars);
    ASSETS.reserve(dh->total_bars);
    LIABILITIES.reserve(dh->total_bars);

}

void Portfolio::on_fill(std::string symbol, money price, int quantity, Direction direction)
{
    // long price = dh->getLatestBarsN(symbol, 1)(dh->symbol_headers[symbol]["Adj Close"]);
    update_position(price, symbol, quantity, direction);

    if (!dh->quiet) std::cout << "Executed trade for 1 share of " << symbol << " at $" 
                              << std::fixed << std::setprecision(2) << (double(price) / double(dh->money_mult)) 
                              << "." << std::endl;

}

void Portfolio::update_position(long price, std::string symbol, int quantity, Direction direction)
{
    positions[symbol].update_position(price, quantity, direction);
    CASH_position.update_position(price, quantity, direction);
}

void Portfolio::update_value()
{   
    long price, value;

    A = 0;
    L = 0;

    for (std::string symbol : dh->symbols) {
        price = dh->getLatestBarsN(symbol, 1)(dh->symbol_headers[symbol]["Adj Close"]);
        value = positions[symbol].update_value(price);
        holdings[symbol].push_back(value);

        if (value > 0) A += value;
        else L += value;

        // if (symbol == "GOOG" && positions["GOOG"].quantity < 1) std::cout << value << " "
        //                                                                   << price << " " << positions["GOOG"].quantity << std::endl;
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