#ifndef RISK_H
#define RISK_H

#include <unordered_map>
#include <string>

#include "dh.h"
#include "portfolio.h"

class RiskHandler {
    public:
      RiskHandler();
      RiskHandler(DataHandler *data_handler,  Portfolio *p);

      DataHandler *dh;
      Portfolio *portfolio;

      double TE;

      // Maximum Leverage Ratio
      double MLR = 1;

      // Cash Buffer
      double CB;
 
      std::unordered_map<std::string, double> weight_bounds;

    private:
      void check_leverage();


    
};

#endif