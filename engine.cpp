#include "Engines/backtester.h"

using namespace CAT;
int main() {
    Backtester bt;

    if (bt.dh.mode == "backtest") {
        bt.run();
        bt.metrics();
    }
    
    else if (bt.dh.mode == "optimize") {
        bt.optimize();
    }

    return 0;
}