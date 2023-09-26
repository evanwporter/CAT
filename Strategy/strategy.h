#ifndef STRATEGY_H
#define STRATEGY_H

#include "../DataHandler/dh.h"
#include "../RiskHandler/risk.h"

#include <unordered_map>
#include <string>

class Strategy {
    public:
      Strategy(DataHandler *data_handler,  RiskHandler *risk_handler);

      DataHandler *dh;
      RiskHandler *rh;

      void on_data(std::string symbol);

      std::unordered_map<std::string, bool> traded;


};

#endif