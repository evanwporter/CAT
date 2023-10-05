#include "Engines/engine.h"

using namespace CAT;
int main() {
    Backtester bt;

    if (bt.settings.mode == "backtest") {
        bt.run();
        bt.metrics();
    }
    
    else if (bt.settings.mode == "optimize") {
        bt.optimize();
    }

    else {
        std::cout << "Specify in settings.json either backtest or optimize" << std::endl;
    }

    return 0;
}