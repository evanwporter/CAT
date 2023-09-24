#ifndef STRATEGY_H
#define STRATEGY_H

#include "../DataHandler/dh.h"
#include "../Portfolio/portfolio.h"


class Strategy {
    public:
      Strategy();

      DataHandler *dh;
      Portfolio *portfolio;

      void on_data();

      bool traded = false;

};

#endif