#ifndef METRICS_h
#define METRICS_h

#include "../Portfolio/portfolio.h"
#include "../utility.h"

#include <vector>
#include <string>

using namespace Eigen;

namespace CAT {
class Metrics {
    public:
      Metrics();
      Metrics(Portfolio *p);
      // Metrics(Portfolio *p, std::chrono::duration<std::chrono::microseconds> time_elapsed);

      Portfolio *portfolio;

      MoneyMatrixX holdings, TOTAL_EQUITY;

      PercentVectorX RETURNS, EQUITY_CURVE;
      
      double SHARPE_RATIO(int periods);
    
      double MAX_DRAWDOWN, TOTAL_RETURN, PnL;
      double TIME_TAKEN;

      int DRAWDOWN_DURATION;

      void display_metrics();

      void printf_csv(std::string path, MoneyMatrixX matrix);
    
    private:
      void calculate_drawdown();

};
};

#endif