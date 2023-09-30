#ifndef BUYANDHOLD_H
#define BUYANDHOLD_H

#include "../DataHandler/dh.h"
#include "../RiskHandler/risk.h"
#include "strategy.h"

#include <unordered_map>
#include <string>

namespace CAT {
  
class BuyAndHold : public Strategy {
    public:
      BuyAndHold(DataHandler *data_handler,  RiskHandler *risk_handler);

      void on_data(std::string symbol);

      std::unordered_map<std::string, bool> traded;

};
};

#endif