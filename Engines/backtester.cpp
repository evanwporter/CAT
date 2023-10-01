#include "backtester.h"

#include <chrono>

using namespace CAT;

Backtester::Backtester() {};

void Backtester::run(int param)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    p = Portfolio(&dh);
    rh = RiskHandler(&dh, &p);
    s = new MovingAverageCrossover(&dh, &rh, param);

    for(dh.current = dh.warmup_period; dh.current < dh.total_bars; dh.current++) {
        p.update_value();
        for (auto symbol : dh.symbols) {
            if (dh.symbol_data_locations[symbol][0] <= dh.current && dh.current < dh.symbol_data_locations[symbol][1]) {
                s->on_data(symbol);
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

void Backtester::optimize () {
    std::vector<unsigned int> param;
    std::vector<double> results;
    for (unsigned int i = 10; i < 30; i++) {
        param.push_back(i);
        run(i);
        results.push_back(m.TOTAL_RETURN);
        std::cout << m.TOTAL_RETURN << " ";
    }
    // std::cout << std::distance(results.begin(), std::max_element(results.begin(), results.end()));
}
