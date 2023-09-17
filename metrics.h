#ifndef METRICS_h
#define METRICS_h

#include "portfolio.h"

#include <vector>

using namespace Eigen;

// typedef Matrix<double, 1, Dynamic> Vector;

class Metrics {
    public:
      Portfolio *portfolio;

      std::vector<double> returns;
      Metrics(Portfolio *portfolio);

      Matrix<double, Dynamic, Dynamic> holdings;

      VectorXd TOTAL_RETURNS, TOTAL_EQUITY, EQUITY_CURVE;

      double SHARPE_RATIO(int periods);

      static double std(VectorXd vec);
      static void cumulative_product(Eigen::VectorXd vec, VectorXd& make_vec);
    
      double MAX_DRAWDOWN, TOTAL_RETURN, PnL;

      int DRAWDOWN_DURATION;

      void display_metrics();
    
    private:
      void calculate_drawdown();



};

#endif