#include "backtester.h"

#include <chrono>

using namespace CAT;

Backtester::Backtester() {
    sd::ondemand::parser parser;
    sd::padded_string json = sd::padded_string::load("settings.json");
    sd::ondemand::document settings = parser.iterate(json);

    bts.mode = std::string(std::string_view(settings["MODE"]));

    for (sd::ondemand::value symbol : settings["SYMBOLS"]) {
        bts.symbols.push_back(std::string(std::string_view(symbol)));
    };

    bts.warmup_period = settings["DATA_WARMUP_PERIOD"].get_uint64();

    bts.quiet = settings["QUIET"].get_bool();
    bts.money_mult = settings["MONEY MULTIPLIER"].get_uint64();
    bts.initial_cash = settings["INITIAL CASH"].get_uint64();

    dh = DataHandler(&bts);
};

void Backtester::run()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    p = Portfolio(&dh, &bts);
    rh = RiskHandler(&dh, &p, &bts);

    s = std::make_unique<MovingAverageCrossover>(&dh, &rh);

    for(dh.current = bts.warmup_period; dh.current < dh.total_bars; dh.current++) {
        for (auto symbol : bts.symbols) {
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
        p = Portfolio(&dh, &bts);
        rh = RiskHandler(&dh, &p, &bts);
        s = std::make_unique<MovingAverageCrossover>(&dh, &rh);
        // s->modify_param(i);
        s->parameter = i;

        for(dh.current = bts.warmup_period; dh.current < dh.total_bars; dh.current++) {
            p.update_value();
            for (auto symbol : bts.symbols) {
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