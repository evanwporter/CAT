#include "strategy.h"
#include "../utility.h"

Strategy::Strategy(DataHandler *data_handler,  RiskHandler *risk_handler) {
    dh = data_handler;
    rh = risk_handler;

    for (auto symbol : dh->symbols) {
        traded[symbol] = false;
    };
}

void Strategy::on_data(std::string symbol)
{
    if (!traded[symbol]) {
        rh->on_signal(symbol, Direction::LONG_);
        traded[symbol] = true;
    }
};