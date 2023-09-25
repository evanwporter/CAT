#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <Eigen/Dense>

#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <map>
#include <iomanip>
#include <string>
#include <string_view>

#include "../Libraries/simdjson.h"
#include "../utility.h"


namespace sd = simdjson;
using namespace Eigen;

class DataHandler {
    private:
      void load_csv(const std::string &symbol, const std::string &path);
      std::vector<datetime64> unionize(std::vector<datetime64> a, std::string symbol, std::vector<datetime64> b);

    public:
      std::unordered_map<std::string, std::unordered_map<std::string, int>> symbol_headers;
      std::unordered_map<std::string, std::vector<datetime64>> symbol_dates;
      std::unordered_map<std::string, MatrixXl> symbol_data;

      // stores the location of the symbol data relative to the master collection
      std::unordered_map<std::string, unsigned int[2]> symbol_data_locations;

      std::map<std::string, int> s;

      std::vector<datetime64> total_symbol_dates;
      std::vector<std::string> symbols;// = {"GOOG", "AAPL"};

      sd::ondemand::document settings;
      bool quiet = true;
      unsigned long money_mult = 1;

      unsigned int total_bars, current, data_size;

      DataHandler();
      // DataHandler(std::vector<std::string> sym);

      MatrixXl getLatestBarsN(std::string symbol, int N);
};

#endif