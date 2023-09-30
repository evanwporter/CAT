#include "dh.h"
#include "../Libraries/simdjson.h"
#include "filing.h"

#include <vector>
#include <algorithm>
#include <string>
#include <string_view>
#include <iostream>
#include <filesystem>

using namespace simdjson;
using namespace CAT;

DataHandler::DataHandler() {
    std::string path = GetExePath();
    if (!std::filesystem::exists(path + "\\settings.json")) std::cout << "ERROR: couldn't load settings.json" << std::endl;

    ondemand::parser parser;
    padded_string json = padded_string::load("settings.json");
    settings = parser.iterate(json);

    for (ondemand::value symbol : settings["SYMBOLS"]) {
        symbols.push_back(std::string(std::string_view(symbol.get_string())));
    };

    warmup_period = settings["DATA_WARMUP_PERIOD"].get_uint64();

    std::string p = std::string(std::string_view(settings["DATA_DIRECTORY"].get_string()));
    
    quiet = settings["QUIET"].get_bool();
    money_mult = settings["MONEY MULTIPLIER"].get_uint64();
    initial_cash = settings["INITIAL CASH"].get_uint64();

    for(std::string symbol : symbols) load_csv(symbol, path + "\\Data\\");//"C:\\Users\\evanw\\options\\");

    for(std::string symbol : symbols) total_symbol_dates = unionize(total_symbol_dates, symbol, symbol_dates[symbol]);

    total_bars = total_symbol_dates.size();
};

// TODO: Optimize (somehow)
void DataHandler::load_csv(const std::string &symbol, const std::string &path)
{
    std::vector<money> values;

    unsigned int rows = 0;
    std::size_t data_length, data_width;

    // int load_csv (const std::string & path) {
    std::ifstream indata;
    indata.open(path + symbol + ".csv");
    std::string line;
    
    std::getline(indata, line);
    data_length = stoi(line);

    // HEADERS
    // Parse the header/second line
    std::getline(indata, line);
    std::stringstream lineStream(line);
    std::vector<std::string> headers;
    std::string header;
    while (getline(lineStream, header, ',')) {
        headers.push_back(header);
    }
    data_width = headers.size();

    values.reserve(data_length * data_width);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // DATA
    // Parse the rest of the data
    while (std::getline(indata, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::getline(lineStream, cell, ',');
        std::istringstream ss(cell);

        // DATES
        // symbol_dates[symbol].push_back(std::stod(cell));
        symbol_dates[symbol].push_back(stoll(cell));

        // VOLUME
        // while (std::getline(lineStream, cell, ',')) {
        for (unsigned int i = 0; i < headers.size() - 2; i++) {
            std::getline(lineStream, cell, ',');
            money val = std::stod(cell) * money_mult;
            values.push_back(val);
        };

        // VOLUME
        std::getline(lineStream, cell, ',');
        ++rows;
    };
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();


    // Starts at 1 to eliminate Date header
    for(unsigned int i = 1; i < headers.size(); i++) symbol_headers[symbol][headers[i]] = i - 1;

    // for (auto i: values) std::cout << i << " ";

    symbol_data[symbol] = Map<MoneyMatrixX> (values.data(), rows, headers.size() - 2);
    if (!quiet) std::cout << "Loaded " << symbol << ". Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
};

MoneyMatrixX DataHandler::getLatestBarsN(std::string symbol, int N)
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