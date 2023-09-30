#include "ma_crossover.h"
#include "../utility.h"

using namespace CAT;

MovingAverageCrossover::MovingAverageCrossover(DataHandler *data_handler, RiskHandler *risk_handler, unsigned int wdow)
{
    dh = data_handler;
    rh = risk_handler;
    window = wdow;
}

void MovingAverageCrossover::on_data(std::string symbol)
{
    MoneyVectorX bars = dh->getLatestBarsN(symbol, 30).col(dh->symbol_headers[symbol]["Adj Close"]);
    money last_price = bars(0);
    money current_price = bars(1);
    if (last_price < current_price) rh->on_signal(symbol, Direction::LONG_);
    else rh->on_signal(symbol, Direction::SHORT_);
}