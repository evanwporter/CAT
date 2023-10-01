#include "ma_crossover.h"
#include "../utility.h"

using namespace CAT;

MovingAverageCrossover::MovingAverageCrossover(DataHandler *data_handler, RiskHandler *risk_handler)
{
    dh = data_handler;
    rh = risk_handler;

    if (dh->mode == "backtest") {
        // dh->settings.rewind();
        parameter = dh->settings["RUN TIME PARAMETERS"].get_int64();
    }
}

void MovingAverageCrossover::on_data(std::string symbol)
{
    MoneyVectorX bars = dh->getLatestBarsN(symbol, parameter).col(dh->symbol_headers[symbol]["Adj Close"]);
    money moving_average = bars.mean();
    money current_price = bars.tail<1>()[0];
    if (moving_average < current_price) rh->on_signal(symbol, Direction::LONG_);
    else rh->on_signal(symbol, Direction::SHORT_);
}

// void MovingAverageCrossover::on_data(std::string symbol, int p)
// {
//     MoneyVectorX bars = dh->getLatestBarsN(symbol, p).col(dh->symbol_headers[symbol]["Adj Close"]);
//     money moving_average = bars.mean();
//     money current_price = bars.tail<1>()[0];
//     if (moving_average < current_price) rh->on_signal(symbol, Direction::LONG_);
//     else rh->on_signal(symbol, Direction::SHORT_);
// }