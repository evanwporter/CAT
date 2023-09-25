#include "Portfolio/ticker.h"
#include "Portfolio/position.h"
#include "utility.h"
#include "DataHandler/dh.h"
#include "Strategy/strategy.h"
#include "Metrics/metrics.h"

#include <chrono>

#include <Eigen/Dense>
#include <Eigen/Core>

#include <iostream>


using namespace std;


void engine() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // vector<std::string> symbols = {"GOOG", "AAPL"};

    DataHandler dh = DataHandler();
    Portfolio p = Portfolio(&dh);
    RiskHandler rh = RiskHandler(&dh, &p);
    Strategy strategy = Strategy();

    strategy.dh = &dh;
    strategy.rh = &rh;

    for(dh.current = 0; dh.current < dh.total_bars; dh.current++) {
        if (dh.current > 100) {
            p.update_value();
            strategy.on_data();
        };
    };

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    Metrics m(&p);
    m.TIME_TAKEN = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

    // std::cout << Eigen::Matrix({m.EQUITY_CURVE, m.RETURNS});
    // std::cout << m.holdings;

    m.display_metrics();

}

int main() {
    engine();
    return 0;
}