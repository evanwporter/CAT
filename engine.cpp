#include "Engines/backtester.h"

using namespace CAT;
int main() {
    Backtester bt;

    if (bt.dh.mode == "backtest") {
        std::cout << "here1";
        bt.run();
        std::cout << "here1";
        bt.metrics();
    }
    
    else if (bt.dh.mode == "optimize") {
        bt.optimize();
    }

    return 0;
}