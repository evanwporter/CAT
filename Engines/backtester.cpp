#include "backtester.h"

#include <chrono>

using namespace CAT;

Backtester::Backtester() {};

void Backtester::run()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    p = Portfolio(&dh);
    rh = RiskHandler(&dh, &p);
    s = std::make_unique<MovingAverageCrossover>(&dh, &rh);

    for(dh.current = dh.warmup_period; dh.current < dh.total_bars; dh.current++) {
        p.update_value();
        for (auto symbol : dh.symbols) {
            if (dh.symbol_data_locations[symbol][0] <= dh.current && dh.current < dh.symbol_data_locations[symbol][1]) {
                s->on_data(symbol, 30);
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

    std::vector<int> param;
    std::vector<double> results;
    for (int i = 10; i < 30; i++) {
        p = Portfolio(&dh);
        rh = RiskHandler(&dh, &p);
        s = std::make_unique<MovingAverageCrossover>(&dh, &rh, i);
        // s->modify_param(i);

        for(dh.current = dh.warmup_period; dh.current < dh.total_bars; dh.current++) {
            p.update_value();
            for (auto symbol : dh.symbols) {
                if (dh.symbol_data_locations[symbol][0] <= dh.current && dh.current < dh.symbol_data_locations[symbol][1]) {
                    s->on_data(symbol, i);
                };
            };
        };

        m = Metrics(&p);
        m.TIME_TAKEN = 0;   
        results.push_back(m.TOTAL_RETURN);
        param.push_back(i);

        std::cout << m.TOTAL_RETURN << " ";

    }
    // std::cout << std::distance(results.begin(), std::max_element(results.begin(), results.end()));
}

// void Backtester::optimizer_run() {
//     for(dh.current = dh.warmup_period; dh.current < dh.total_bars; dh.current++) {
//         p.update_value();
//         for (auto symbol : dh.symbols) {
//             if (dh.symbol_data_locations[symbol][0] <= dh.current && dh.current < dh.symbol_data_locations[symbol][1]) {
//                 s->on_data(symbol);
//             };
//         };
//     };
//     std::cout << "here4;

//     m = Metrics(&p);
//     m.TIME_TAKEN = 0;   
// }
