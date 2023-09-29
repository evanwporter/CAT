#include "backtester.h"

#include <chrono>

Backtester::Backtester() {};

void Backtester::run()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    Portfolio p = Portfolio(&dh);
    RiskHandler rh = RiskHandler(&dh, &p);
    Strategy s = Strategy(&dh, &rh);

    for(dh.current = dh.warmup_period; dh.current < dh.total_bars; dh.current++) {
        p.update_value();
        for (auto symbol : dh.symbols) {
            if (dh.symbol_data_locations[symbol][0] <= dh.current && dh.current < dh.symbol_data_locations[symbol][1]) {
                s.on_data(symbol);
            };
        };
    };
    m = Metrics(&p);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    m.TIME_TAKEN = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

}
void Backtester::metrics(){
    m.display_metrics();
};
