#include "dh.h"
#include "simdjson.h"

#include <vector>
#include <algorithm>
#include <string>
#include <string_view>
#include <iostream>

using namespace simdjson;


DataHandler::DataHandler() {
    ondemand::parser parser;
    padded_string json = padded_string::load("settings.json");
    settings = parser.iterate(json);

    for (ondemand::value symbol : settings["SYMBOLS"]) {
        symbols.push_back(std::string(std::string_view(symbol.get_string())));
    };

    std::string path = std::string(std::string_view(settings["DATA_DIRECTORY"].get_string()));

    for(std::string symbol : symbols) load_csv(symbol, "C:\\Users\\evanw\\options\\");

    for(std::string symbol : symbols) total_symbol_dates = unionize(total_symbol_dates, symbol, symbol_dates[symbol]);

    total_bars = total_symbol_dates.size();
};

void DataHandler::load_csv(const std::string &symbol, const std::string &path)
{
    // int load_csv (const std::string & path) {
    std::ifstream indata;
    indata.open(path + symbol + ".csv");
    std::string line;

    std::vector<double> values;

    unsigned int rows = 0;
    
    // First line goes to column headers
    std::getline(indata, line);
    std::stringstream lineStream(line);
    std::vector<std::string> headers;
    std::string header;

    while (getline(lineStream, header, ',')) {
        headers.push_back(header);
    }

    while (std::getline(indata, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::getline(lineStream, cell, ',');
        std::istringstream ss(cell);

        // symbol_dates[symbol].push_back(std::stod(cell));
        symbol_dates[symbol].push_back(stoll(cell));

        while (std::getline(lineStream, cell, ',')) {
            cents val = std::stod(cell) * 1000000;
            values.push_back( val );
        };
        ++rows;
    };

    // Starts at 1 to eliminate Date header
    for(unsigned int i = 1; i < headers.size(); i++){
        symbol_headers[symbol][headers[i]] = i - 1;
    };

    symbol_data[symbol] = Map<const Matrix<typename MatrixXd::Scalar, MatrixXd::RowsAtCompileTime, MatrixXd::ColsAtCompileTime, RowMajor>> (values.data(), rows, values.size()/rows);
};

Eigen::MatrixXd DataHandler::getLatestBarsN(std::string symbol, int N)
{
    // a = {0, 1, 2, 3, 4, 5}
    // b = {3, 4, 5, 6, 7, 8}
    // c = {0, 1, 2, 3, 4, 5, 6, 7, 8}
    // current = 6
    // symbol = b
    // N = 2
    // a_loc = {0, 5}
    // b_loc = {3, 8}
    // return {5, 6} indices: {2, 3}
    return symbol_data[symbol].topRows(current - symbol_data_locations[symbol][0]).bottomRows(N);
};

std::vector<datetime64> DataHandler::unionize(std::vector<datetime64> a, std::string symbol, std::vector<datetime64> b) {
    // unsigned int a_loc[2] = {0, a.size()};
    unsigned int b_loc[2] = {0, b.size()};

    std::vector<datetime64> c;

    int i = 0, j = 0;
    while( i < a.size() && j < b.size()) {

        if( a[ i ] == b[ j ] ) {
            c.push_back( a[ i ] );
            ++i, ++j;
        }
        else if( a[ i ] < b[ j ] ) c.push_back( a[ i++ ] );
        else c.push_back( b[ j++ ] );

        // if (i == 1 && j > 0) a_loc[0] = j - 1;
        if (i > 0 && j == 1) b_loc[0] = i - 1;

    }

    while( i < a.size()) c.push_back( a[ i++ ] );
    while( j < b.size()) c.push_back( b[ j++ ] );

    // a_loc[1] += a_loc[0] - 1;
    b_loc[1] += b_loc[0] - 1;

    symbol_data_locations[symbol][0] = b_loc[0];
    symbol_data_locations[symbol][1] = b_loc[1];

    return c;
}