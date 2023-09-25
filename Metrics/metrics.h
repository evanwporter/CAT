#ifndef METRICS_h
#define METRICS_h

#include "../Portfolio/portfolio.h"
#include "../utility.h"

#include <vector>
#include <string>

using namespace Eigen;


class Metrics {
    public:
      Metrics(Portfolio *p);
      // Metrics(Portfolio *p, std::chrono::duration<std::chrono::microseconds> time_elapsed);

      Portfolio *portfolio;

      MoneyMatrixX holdings;

      MoneyVectorX RETURNS, TOTAL_EQUITY, EQUITY_CURVE;

      double SHARPE_RATIO(int periods);

      // static double std(VectorXd vec);
      // static void cumulative_product(Eigen::VectorXd vec, VectorXd& make_vec);
    
      double MAX_DRAWDOWN, TOTAL_RETURN, PnL;
      double TIME_TAKEN;

      int DRAWDOWN_DURATION;

      void display_metrics();

      void printf_csv(std::string path, MoneyMatrixX matrix);
    
    private:
      void calculate_drawdown();

};

#endif