#include "BuyAndHold.h"
#include "../utility.h"

using namespace CAT;

BuyAndHold::BuyAndHold() {};

BuyAndHold::BuyAndHold(DataHandler *data_handler, RiskHandler *risk_handler)
{

    dh = data_handler;
    rh = risk_handler;

    for (auto symbol : dh->symbols) {
        traded[symbol] = false;
    };
}

void BuyAndHold::on_data(std::string symbol)
{
    // if (!traded[symbol]) {
    //     rh->on_signal(symbol, Direction::LONG_);
    //     traded[symbol] = true;
    //     std::cout << dh->getLatestBarsN(symbol, 2);
    // }

    // MoneyVectorX bars = dh->getLatestBarsN(symbol, 2).col(dh->symbol_headers[symbol]["Adj Close"]);
    // money last_price = bars(0);
    // money current_price = bars(1);
    // if (last_price < current_price) rh->on_signal(symbol, Direction::LONG_);
    // else rh->on_signal(symbol, Direction::SHORT_);

    MoneyVectorX bars = dh->getLatestBarsN(symbol, 30).col(dh->symbol_headers[symbol]["Adj Close"]);
    money last_price = bars(0);
    money current_price = bars(1);
    if (last_price < current_price) rh->on_signal(symbol, Direction::LONG_);
    else rh->on_signal(symbol, Direction::SHORT_);
};