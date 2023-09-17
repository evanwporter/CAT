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

    vector<std::string> symbols = {"GOOG"};

    DataHandler dh = DataHandler(symbols);
    Portfolio p = Portfolio(&dh);
    Strategy strategy = Strategy();

    strategy.dh = &dh;
    strategy.portfolio = &p;


    // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // dh.load_csv("GOOG", "C:\\Users\\evanw\\options\\GOOG.csv");

    // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    for(int i = 0; i < dh.symbol_dates["GOOG"].size(); i++) {
        strategy.on_data();
        p.update_value(100);
    }

    // vector<vector<double>> holdings;
    // holdings.reserve(dh.symbols.size());

    // std::cout << std::endl << dh.symbol_dates.size() << std::endl <<  p.holdings["GOOG"].size() << std::endl;

    Eigen::MatrixXd holdings(2148, 1);//dh.symbols.size(), p.holdings["GOOG"].size());

    // for (auto l : p.holdings["GOOG"]){
    //     std::cout << l;
    // }

    int i = 0;
    // Eigen::VectorXd h;
    for(std::string symbol : dh.symbols){
        Eigen::VectorXd h = Eigen::Map<Eigen::VectorXd, Eigen::Unaligned>(p.holdings[symbol].data(), p.holdings[symbol].size());
        // Eigen::Vector3f h(p.holdings[symbol].data());
        holdings.col(i) = h;
        // std::cout << dh.symbols[i];
        i++;
    };
    std::cout << std::endl << p.positions["GOOG"].quantity;


    // auto data = d.symbol_data["GOOG"];

    // Eigen::Matrix<double, Dynamic, 5> h;

    // h = data.topRows(10);

    // std::cout << h << std::endl;

    // for (auto i: d.values) {
    //     std::cout << i << ' ';
    // }

    return 0;
}