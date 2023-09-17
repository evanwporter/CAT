#include "ticker.h"
#include "position.h"
#include "direction.h"
#include "dh.h"
#include "strategy.h"

#include <chrono>

#include <Eigen/Dense>
#include <Eigen/Core>

#include <iostream>


using namespace std;


int main() {
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

    Eigen::MatrixXd holdings(p.holdings["GOOG"].size(), dh.symbols.size() + 2);
    int i = 1;
    for(std::string symbol : dh.symbols){
        holdings.col(i) = Eigen::Map<Eigen::VectorXd, Eigen::Unaligned>(
            p.holdings[symbol].data(), p.holdings[symbol].size()
        );
        i++;
    };
    holdings.col(0) = Eigen::Map<Eigen::VectorXd, Eigen::Unaligned>(
        p.CASH_holding.data(), p.CASH_holding.size()
    );
    // Total Equity
    holdings.col(i) = holdings.rowwise().sum();

    std::cout << p.positions["GOOG"].quantity << std::endl;

    // std::cout << holdings;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    return 0;
}