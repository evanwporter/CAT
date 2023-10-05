#ifndef RISK_H
#define RISK_H

#include <unordered_map>
#include <string>

#include "../DataHandler/dh.h"
#include "../Portfolio/portfolio.h"


namespace CAT {
class RiskHandler {
    private:
      double check_weights(std::string symbol, double weight_adjustment, money price, Direction direction);
      inline void generate_weights(std::string method = "equal");

      void check_leverage();
      bool simple;

    public:
      RiskHandler();
      RiskHandler(DataHandler *data_handler,  Portfolio *p, bt_settings *bts);

      DataHandler *dh;
      Portfolio *portfolio;
      bt_settings *settings;

      double TE;

      // Maximum Leverage Ratio
      // Defined in settings
      // Calculated as Leverage to TE
      double MLR = 0;

      // Cash Buffer
      double CB;

      // The weights are how much of the Total Equity are in a particular asset
      // Weight bounds are predefined maximum weights for each asset
      // This function checks to see if the proposed trade will go over 
      // or under the weight bounds
      std::unordered_map<std::string, double[2]> weights;
      double CASH_weight[2];

      // How much of an asset to buy or sell
      // Reflected as a percentage of Total Equity
      // weight_adjustment = .1

      void on_signal(std::string symbol, Direction direction);


};
};

#endif