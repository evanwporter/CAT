#include "Engines/backtester.h"

int main() {
    Backtester bt = Backtester();
    bt.run();
    bt.metrics();
    return 0;
}