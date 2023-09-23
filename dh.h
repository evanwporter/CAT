#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <Eigen/Dense>

#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <map>
#include <iomanip>

using namespace Eigen;

// Milliseconds
typedef unsigned long long datetime64;

typedef long cents;

class DataHandler {
    private:
      void load_csv(const std::string &symbol, const std::string &path);

    public:
      std::unordered_map<std::string, std::unordered_map<std::string, int>> symbol_headers;
      // std::unordered_map<std::string, std::vector<std::string>> symbol_dates;
      std::unordered_map<std::string, std::vector<datetime64>> symbol_dates;
      std::unordered_map<std::string, Matrix<typename MatrixXd::Scalar, MatrixXd::RowsAtCompileTime, MatrixXd::ColsAtCompileTime, RowMajor>> symbol_data;
      // std::unordered_map<std::string, std::unordered_map<std::string, std::vector<long int>>> symbol_data;

      // stores the location of the symbol data relative to the master collection
      std::unordered_map<std::string, unsigned int[2]> symbol_data_locations;


      std::map<std::string, int> s;

      std::vector<datetime64> total_symbol_dates;

      unsigned int total_bars;

      // std::unordered_map<std::string, std::vector<double>> symbol_data;

      
      // std::vector<double> values;

      DataHandler();
      DataHandler(std::vector<std::string> sym);

      std::vector<std::string> symbols;

      int data_size;

      Eigen::MatrixXd getLatestBarsN(std::string symbol, int N);

      unsigned int current;

      std::vector<datetime64> unionize(std::vector<datetime64> a, std::string symbol, std::vector<datetime64> b);

};

#endif