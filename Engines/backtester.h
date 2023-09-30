#ifndef BACKTESTER_H
#define BACKTESTER_H

#include "../Portfolio/ticker.h"
#include "../Portfolio/position.h"
#include "../Portfolio/portfolio.h"
#include "../utility.h"
#include "../DataHandler/dh.h"
#include "../Strategy/strategy.h"
#include "../Strategy/BuyAndHold.h"
#include "../Metrics/metrics.h"

#include <Eigen/Dense>
#include <Eigen/Core>


namespace CAT {
class Backtester {
    public:
        Backtester();

        Portfolio p;
        DataHandler dh;
        RiskHandler rh;
        BuyAndHold s;
        Metrics m;

        void run();

        void metrics();

        void optimize();

};
};

#endif