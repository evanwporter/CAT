// #include "Portfolio/ticker.h"
// #include "Portfolio/position.h"
// #include "Portfolio/portfolio.h"
// #include "utility.h"
// #include "DataHandler/dh.h"
// #include "Strategy/strategy.h"
// #include "Metrics/metrics.h"

// #include <chrono>

// #include <Eigen/Dense>
// #include <Eigen/Core>

// #include <iostream>

// using namespace std;


// void engine() {
//     std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

//     DataHandler dh = DataHandler();
//     Portfolio p = Portfolio(&dh);
//     RiskHandler rh = RiskHandler(&dh, &p);
//     Strategy strategy = Strategy(&dh, &rh);

//     for(dh.current = dh.warmup_period; dh.current < dh.total_bars; dh.current++) {
//         p.update_value();
//         for (auto symbol : dh.symbols) {
//             if (dh.symbol_data_locations[symbol][0] <= dh.current && dh.current < dh.symbol_data_locations[symbol][1]) {
//                 strategy.on_data(symbol);
//             };
//         };
//     };

//     std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

//     Metrics m(&p);
//     m.TIME_TAKEN = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

//     // std::cout << Eigen::Matrix({m.EQUITY_CURVE, m.RETURNS});
//     // std::cout << m.holdings;

//     m.display_metrics();

//     // std::cout << dh.symbol_data["GOOG"];
//     // std::cout << dh.symbol_data["AAPL"];
// }

// int main() {
//     engine();
//     return 0;
// }

#include "Engines/backtester.h"

int main() {
    Backtester bt = Backtester();
    bt.run();
    bt.metrics();
    return 0;
}