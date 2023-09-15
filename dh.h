#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <Eigen/Dense>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <iomanip>

using namespace Eigen;

// Milliseconds
typedef std::uint64_t datetime64;

class DataHandler {
    public:
      std::unordered_map<std::string, std::vector<std::string>> symbol_headers;
      std::unordered_map<std::string, std::vector<datetime64>> symbol_dates;
      std::unordered_map<std::string, Matrix<typename MatrixXd::Scalar, MatrixXd::RowsAtCompileTime, MatrixXd::ColsAtCompileTime, RowMajor>> symbol_data;

      DataHandler();
      void load_csv(const std::string &symbol, const std::string &path);
};

#endif