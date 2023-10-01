#ifndef MA_CROSSOVER_H
#define MA_CROSSOVER_H

#include "../DataHandler/dh.h"
#include "../RiskHandler/risk.h"
#include "strategy.h"

#include <unordered_map>
#include <string>

namespace CAT {
  
class MovingAverageCrossover : public Strategy {
    public:
      MovingAverageCrossover(DataHandler *data_handler,  RiskHandler *risk_handler, int p = 30);

      void on_data(std::string symbol, int p);

      int param = 0;
};
};

#endif
