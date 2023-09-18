#include "ticker.h"
#include "position.h"
#include "direction.h"
#include "dh.h"
#include "strategy.h"
#include "metrics.h"

#include <chrono>

#include <Eigen/Dense>
#include <Eigen/Core>

#include <iostream>


using namespace std;


void engine() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    vector<std::string> symbols = {"GOOG"};

    DataHandler dh = DataHandler(symbols);
    Portfolio p = Portfolio(&dh);
    Strategy strategy = Strategy();

    strategy.dh = &dh;
    strategy.portfolio = &p;

    for(dh.current = 0; dh.current < dh.symbol_dates["GOOG"].size(); dh.current++) {
        if (dh.current > 100) {
            strategy.on_data();
            p.update_value();
        }
    }

    // std::cout << p.positions["GOOG"].quantity << std::endl;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    Metrics m(&p);
    m.TIME_TAKEN = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

    // std::cout << m.holdings;

    m.display_metrics();
}

int main() {
    engine();
    return 0;
}