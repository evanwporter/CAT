#ifndef RISK_H
#define RISK_H

#include <unordered_map>
#include <string>

class RiskHandler {
    public:
      // Maximum Leverage Ratio
      double MLR = 1;

      // Cash Buffer
      double CB;
 
      std::unordered_map<std::string, double> weight_bounds;

      void check_weights();


    
};

#endif