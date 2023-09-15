#include "ticker.h"
#include "position.h"
#include "direction.h"
#include "dh.h"

#include <chrono>

#include <Eigen/Dense>
#include <iostream>


using namespace std;

int main() {
    // Ticker t = Ticker("AAPL", "Stock");

    // Position p = Position();
    
    // p.add_trade(100, 1, Direction::LONG);

    // std::cout << p.quantity;  
    DataHandler d = DataHandler();
  

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    d.load_csv("GOOG", "");

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;


    // auto data = d.symbol_data["GOOG"];

    // Eigen::Matrix<double, Dynamic, 5> h;

    // h = data.topRows(10);

    // std::cout << h << std::endl;

    // for (auto i: d.symbol_dates["GOOG"]) {
    //     std::cout << i << ' ';
    // }



    return 0;
}