#ifndef BACKTESTER_H
#define BACKTESTER_H

#include "../Portfolio/ticker.h"
#include "../Portfolio/position.h"
#include "../Portfolio/portfolio.h"
#include "../utility.h"
#include "../DataHandler/dh.h"

#include "../Strategy/strategy.h"
#include "../Strategy/BuyAndHold.h"
#include "../Strategy/ma_crossover.h"

#include "../Metrics/metrics.h"

#include "../Libraries/simdjson.h"

#include <Eigen/Dense>
#include <Eigen/Core>

#include <algorithm>
#include <iostream>
#include <vector>



namespace CAT {
class Backtester {
    public:
        Backtester();

        Portfolio p;
        DataHandler dh;
        RiskHandler rh;
        Strategy* s;
        Metrics m;

        void run(int param = 30);

        void metrics();

        void optimize();

};
};

#endif