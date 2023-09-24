#ifndef STRATEGY_H
#define STRATEGY_H

#include "../DataHandler/dh.h"
#include "../RiskHandler/risk.h"


class Strategy {
    public:
      Strategy();

      DataHandler *dh;
      RiskHandler *rh;

      void on_data();

      bool traded = false;

};

#endif