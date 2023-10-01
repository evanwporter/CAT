#include "metrics.h"

#include <Eigen/Dense>
#include <Eigen/Core>

#include <cmath>
#include <algorithm>
#include <fstream>

#include "stats.h"

#include "../Libraries/VariadicTable.h"
#include "../utility.h"

using namespace CAT;

Metrics::Metrics() {};

Metrics::Metrics(Portfolio *p)
{

    portfolio = p;

    holdings = MoneyMatrixX(portfolio->CASH_holding.size(), portfolio->dh->symbols.size() + 1);
    
    int i = 1;
    for(std::string symbol : portfolio->dh->symbols){
        holdings.col(i) = Eigen::Map<MoneyVectorX, Eigen::Unaligned>(
            portfolio->holdings[symbol].data(), portfolio->holdings[symbol].size()
        );
        i++;
    };

    holdings.col(0) = Eigen::Map<MoneyVectorX, Eigen::Unaligned>(
        portfolio->CASH_holding.data(), portfolio->CASH_holding.size()
    );

    // Total Equity
    TOTAL_EQUITY = holdings.rowwise().sum();

    PnL = TOTAL_EQUITY(TOTAL_EQUITY.size() - 1) - TOTAL_EQUITY(0);

    RETURNS = pct_change<double, double>(TOTAL_EQUITY.cast<double>());

    // Total Returns
    // RETURNS = Eigen::MatrixXd(holdings.rows(), 1);
    // RETURNS(0) = 1;
    // for (int j = 1; j < TOTAL_EQUITY.size(); j++) {
    //     if (TOTAL_EQUITY(j - 1) == 0) RETURNS(j) = 0;
    //     else RETURNS(j) = (TOTAL_EQUITY(j) - TOTAL_EQUITY(j - 1)) / TOTAL_EQUITY(j - 1);
    // };

    cumulative_product<double>(RETURNS, EQUITY_CURVE, 1);

    TOTAL_RETURN = EQUITY_CURVE(EQUITY_CURVE.size() - 1);

    calculate_drawdown();
}

double Metrics::SHARPE_RATIO(int periods) {
    return std::sqrt(periods) * RETURNS.mean() / stdev(RETURNS);
}

void Metrics::calculate_drawdown() {

    PercentVectorX high_water_mark = PercentVectorX(EQUITY_CURVE.size(), 1);
    PercentVectorX drawdown = PercentVectorX(EQUITY_CURVE.size(), 1);
    PercentVectorX drawdown_duration = PercentVectorX(EQUITY_CURVE.size(), 1);

    for (int t = 1; t < EQUITY_CURVE.size(); t++) {
        high_water_mark(t) = std::max(high_water_mark(t - 1), EQUITY_CURVE(t));
        drawdown(t) = high_water_mark(t) - EQUITY_CURVE(t);
        if (drawdown(t) == 0) {
            drawdown_duration(t) = 0;
        }
        else {
            drawdown_duration(t) = drawdown_duration(t-1) + 1;
        };
    };
    
    MAX_DRAWDOWN = drawdown.maxCoeff();
    DRAWDOWN_DURATION = drawdown_duration.maxCoeff();

};


void Metrics::printf_csv(std::string path, MoneyMatrixX matrix) {
    const static Eigen::IOFormat CSVFormat(StreamPrecision, DontAlignCols, ", ", "\n");
    std::ofstream file(path);
    file << matrix.format(CSVFormat);
}

void Metrics::display_metrics() {
    VariadicTable<std::string, double> vt({"Metric", "Value"}, 10);

    vt.addRow("Time Taken", TIME_TAKEN);
    vt.addRow("Sharpe Ratio", SHARPE_RATIO(252));
    vt.addRow("Total Return", TOTAL_RETURN);
    vt.addRow("Max DD", MAX_DRAWDOWN);
    vt.addRow("DD Duration", DRAWDOWN_DURATION);
    // vt.addRow("Profit and Loss", PnL);

    vt.print(std::cout);

    // MatrixXd l(EQUITY_CURVE.size(), 3);
    // l.col(2) = EQUITY_CURVE;
    // l.col(1) = RETURNS;
    // l.col(0) = TOTAL_EQUITY;

    printf_csv("./h.csv", holdings);

};

