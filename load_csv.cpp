#include <Eigen/Dense>
#include <vector>
#include <fstream>
#include <iostream>

using namespace Eigen;
// typedef Matrix< float, Dynamic, Dynamic, ColMajor > EMatrix;

template<typename M>
M load_csv (const std::string & path) {
// int load_csv (const std::string & path) {
    std::ifstream indata;
    indata.open(path);
    std::string line;

    std::vector<std::string> headers;
    std::vector<std::string> dates;
    std::vector<double> values;

    unsigned int rows = 0;
    
    // First line goes to column headers
    std::getline(indata, line);
    std::stringstream lineStream(line);
    std::string header;

    while (getline(lineStream, header, ',')) {
        headers.push_back(header);
    }

    while (std::getline(indata, line)) {
        std::stringstream lineStream(line);
        std::string cell;

        std::getline(lineStream, cell, ',');
        dates.push_back(cell);

        while (std::getline(lineStream, cell, ',')) {
            values.push_back(std::stod(cell));
        }
        ++rows;
    }
    // return 0;
    return Map<const Matrix<typename M::Scalar, M::RowsAtCompileTime, M::ColsAtCompileTime, RowMajor>>(values.data(), rows, values.size()/rows);
}

// int main() {
//     MatrixXd A = load_csv<MatrixXd>("C:\\Users\\evanw\\options\\test.csv");
//     // load_csv("C:\\Users\\evanw\\options\\GOOG.csv");
//     // MatrixXd A = MatrixXd::Random(3,3);
//     std::cout << A;
// }
