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
#include "../Libraries/robin_hood.h"
#include "../utility.h"


namespace sd = simdjson;
using namespace Eigen;

namespace CAT {
class DataHandler {
    private:
      void load_csv(const std::string &symbol, const std::string &path);
      std::vector<datetime64> unionize(std::vector<datetime64> a, std::string symbol, std::vector<datetime64> b);

    public:
      robin_hood::unordered_map<std::string, robin_hood::unordered_map<std::string, int>> symbol_headers;
      robin_hood::unordered_map<std::string, std::vector<datetime64>> symbol_dates;
      robin_hood::unordered_map<std::string, MoneyMatrixX> symbol_data;

      // stores the location of the symbol data relative to the master collection
      robin_hood::unordered_map<std::string, unsigned int[2]> symbol_data_locations;

      std::map<std::string, int> s;

      std::vector<datetime64> total_symbol_dates;
      std::vector<std::string> symbols;

      bt_settings* settings;

      unsigned int total_bars, current, data_size;

      DataHandler();
      DataHandler(bt_settings *bts);

      MoneyMatrixX getLatestBarsN(std::string symbol, int N);

};
};

#endif