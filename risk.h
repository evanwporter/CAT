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

      // The weights are how much of the Total Equity are in a particular asset
      // Weight bounds are predefined maximum weights for each asset
      // This function checks to see if the proposed trade will go over 
      // or under the weight bounds
      std::unordered_map<std::string, double> weights;

      double RishHandler::check_weights(std::string symbol, double weight_adjustment, cents price, Direction direction);

      // How of asset to buy or sell
      // Reflected as a percentage of Total Equity
      // weight_adjustment = .1

    private:
      void check_leverage();


    
};

#endif