#include "backtester.h"

#include <chrono>

using namespace CAT;

Backtester::Backtester() {};
//     std::string path = GetExePath();
//     if (!std::filesystem::exists(path + "\\settings.json")) std::cout << "ERROR: couldn't load settings.json" << std::endl;

//     simdjson::ondemand::parser parser;
//     simdjson::padded_string json = simdjson::padded_string::load("settings.json");
//     bt_settings.doc = parser.iterate(json);

//     bt_settings.mode = std::string(std::string_view(bt_settings.doc["MODE"]));

//     for (simdjson::ondemand::value symbol : bt_settings.doc["SYMBOLS"]) {
//         bt_settings.symbols.push_back(std::string(std::string_view(symbol)));
//     };

//     bt_settings.warmup_period = bt_settings.doc["DATA_WARMUP_PERIOD"].get_uint64();

//     std::string p = std::string(std::string_view(bt_settings.doc["DATA_DIRECTORY"].get_string()));
    
//     bt_settings.quiet = bt_settings.doc["QUIET"].get_bool();
//     bt_settings.money_mult = bt_settings.doc["MONEY MULTIPLIER"].get_uint64();
//     bt_settings.initial_cash = bt_settings.doc["INITIAL CASH"].get_uint64();
// };

void Backtester::run(int param)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    p = Portfolio(&dh);
    rh = RiskHandler(&dh, &p);
    s = new MovingAverageCrossover(&dh, &rh, param);

    for(dh.current = dh.warmup_period; dh.current < dh.total_bars; dh.current++) {
        p.update_value();
        for (auto symbol : dh.symbols) {
            if (dh.symbol_data_locations[symbol][0] <= dh.current && dh.current < dh.symbol_data_locations[symbol][1]) {
                s->on_data(symbol);
            };
        };
    };
    m = Metrics(&p);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    m.TIME_TAKEN = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

}

void Backtester::metrics(){
    m.display_metrics();
};

void Backtester::optimize () {
    std::vector<unsigned int> param;
    std::vector<double> results;
    for (unsigned int i = 10; i < 30; i++) {
        param.push_back(i);
        run(i);
        results.push_back(m.TOTAL_RETURN);
        std::cout << m.TOTAL_RETURN << " ";
    }
    // std::cout << std::distance(results.begin(), std::max_element(results.begin(), results.end()));
}
