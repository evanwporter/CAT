#include "engine.h"

#include <chrono>

using namespace CAT;

Backtester::Backtester() {
    sd::ondemand::parser parser;
    sd::padded_string json = sd::padded_string::load("settings.json");

    settings.doc = parser.iterate(json);

    settings.mode = std::string(std::string_view(settings.doc["MODE"]));

    for (sd::ondemand::value symbol : settings.doc["SYMBOLS"]) {
        settings.symbols.push_back(std::string(std::string_view(symbol)));
    };

    settings.warmup_period = settings.doc["DATA_WARMUP_PERIOD"].get_uint64();

    settings.quiet = settings.doc["QUIET"].get_bool();
    settings.money_mult = settings.doc["MONEY MULTIPLIER"].get_uint64();
    settings.initial_cash = settings.doc["INITIAL CASH"].get_uint64();

    dh = DataHandler(&settings);
};

void Backtester::run()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    p = Portfolio(&dh, &settings);
    rh = RiskHandler(&dh, &p, &settings);

    s = std::make_unique<MovingAverageCrossover>(&dh, &rh);

    for(dh.current = settings.warmup_period; dh.current < dh.total_bars; dh.current++) {
        for (auto symbol : settings.symbols) {
            if (dh.symbol_data_locations[symbol][0] <= dh.current && dh.current < dh.symbol_data_locations[symbol][1]) {
                s->on_data(symbol);
            };
        };
        p.update_value();
    };

    m = Metrics(&p);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    m.TIME_TAKEN = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

}

void Backtester::metrics(){
    m.display_metrics();
};

void Backtester::optimize () {

    std::vector<int> param;
    std::vector<double> results;
    for (int i = 10; i < 30; i++) {
        p = Portfolio(&dh, &settings);
        rh = RiskHandler(&dh, &p, &settings);
        s = std::make_unique<MovingAverageCrossover>(&dh, &rh);
        // s->modify_param(i);
        s->parameter = i;

        for(dh.current = settings.warmup_period; dh.current < dh.total_bars; dh.current++) {
            p.update_value();
            for (auto symbol : settings.symbols) {
                if (dh.symbol_data_locations[symbol][0] <= dh.current && dh.current < dh.symbol_data_locations[symbol][1]) {
                    s->on_data(symbol);
                };
            };
        };

        m = Metrics(&p);
        m.TIME_TAKEN = 0;   
        results.push_back(m.TOTAL_RETURN);
        param.push_back(i);

        std::cout << m.TOTAL_RETURN << " ";

    }
    // std::cout << std::distance(results.begin(), std::max_element(results.begin(), results.end()));
}