#include "Engines/backtester.h"

using namespace CAT;
int main() {
    Backtester bt;
    bt.run();
    bt.metrics();
    return 0;
}