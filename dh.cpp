#include "dh.h"

DataHandler::DataHandler(){};

void DataHandler::load_csv(const std::string &symbol, const std::string &path)
{
    // int load_csv (const std::string & path) {
    std::ifstream indata;
    indata.open(path);
    std::string line;

    std::vector<double> values;

    unsigned int rows = 0;
    
    // First line goes to column headers
    std::getline(indata, line);
    std::stringstream lineStream(line);
    std::string header;

    while (getline(lineStream, header, ',')) {
        symbol_headers[symbol].push_back(header);
    }

    while (std::getline(indata, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::getline(lineStream, cell, ',');
        std::istringstream ss(cell);

        symbol_dates[symbol].push_back(std::stod(cell));

        while (std::getline(lineStream, cell, ',')) {
            values.push_back(std::stod(cell));
        }
        ++rows;
    }

    symbol_data[symbol] = Map<const Matrix<typename MatrixXd::Scalar, MatrixXd::RowsAtCompileTime, MatrixXd::ColsAtCompileTime, RowMajor>> (values.data(), rows, values.size()/rows);
}