#ifndef STRATEGY_H
#define STRATEGY_H

#include "dh.h"
#include "portfolio.h"


class Strategy {
    public:
      Strategy();

      DataHandler *dh;
      Portfolio *portfolio;

      void on_data();

};

#endif