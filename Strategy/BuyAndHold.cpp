#include "BuyAndHold.h"
#include "../utility.h"

using namespace CAT;

// BuyAndHold::BuyAndHold() {};

BuyAndHold::BuyAndHold(DataHandler *data_handler, RiskHandler *risk_handler)
//BuyAndHold::BuyAndHold(DataHandler *data_handler, RiskHandler *risk_handler, bt_settings *bts)
{

    dh = data_handler;
    rh = risk_handler;

    for (auto symbol : settings->symbols) {
        traded[symbol] = false;
    };
}

void BuyAndHold::on_data(std::string symbol)
{
    if (!traded[symbol]) {
        rh->on_signal(symbol, Direction::LONG_);
        traded[symbol] = true;
    }
};