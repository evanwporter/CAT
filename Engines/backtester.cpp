#include "backtester.h"

Backtester::Backtester() {};

void Backtester::run()
{
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
}
void Backtester::metrics(){
    m.display_metrics();
};
