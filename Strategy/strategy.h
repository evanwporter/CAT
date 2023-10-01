#ifndef STRATEGY_H
#define STRATEGY_H

#include "../DataHandler/dh.h"
#include "../RiskHandler/risk.h"

#include <unordered_map>
#include <string>

namespace CAT {
  
class Strategy {
    public:
      Strategy() {};
      Strategy(DataHandler *data_handler,  RiskHandler *risk_handler, int p) : dh(data_handler), rh(risk_handler), param(p) {};

      DataHandler *dh;
      RiskHandler *rh;

      virtual void on_data(std::string symbol, int p) = 0;

      void modify_param(int p) {
        param = p;
      }

      int param;


};
};

#endif