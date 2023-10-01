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
      Strategy(DataHandler *data_handler,  RiskHandler *risk_handler) : dh(data_handler), rh(risk_handler) {};

      DataHandler *dh;
      RiskHandler *rh;

      virtual void on_data(std::string symbol) = 0;
      // virtual void opt_on_data(std::string symbol, int p) = 0;


      // void modify_param(int p) {
      //   param = p;
      // }

      int parameter;


};
};

#endif