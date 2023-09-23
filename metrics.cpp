#include "metrics.h"

#include <Eigen/Dense>
#include <Eigen/Core>

#include <cmath>
#include <algorithm>
// #include <ostream>

#include "VariadicTable.h"

Metrics::Metrics(Portfolio *p) {

    portfolio = p;

    holdings = Eigen::MatrixXd(portfolio->holdings["GOOG"].size(), portfolio->dh->symbols.size() + 1);
    
    // std::cout<<"1";

    int i = 1;
    for(std::string symbol : portfolio->dh->symbols){
        holdings.col(i) = Eigen::Map<Eigen::VectorXd, Eigen::Unaligned>(
            portfolio->holdings[symbol].data(), portfolio->holdings[symbol].size()
        );
        i++;
    };
    // std::cout<<"2";

    holdings.col(0) = Eigen::Map<Eigen::VectorXd, Eigen::Unaligned>(
        portfolio->CASH_holding.data(), portfolio->CASH_holding.size()
    );

    // std::cout<<"3";

    // Total Equity
    TOTAL_EQUITY = holdings.rowwise().sum();

    PnL = TOTAL_EQUITY(TOTAL_EQUITY.size() - 1) - TOTAL_EQUITY(0);

    // std::cout<<"4";

    // Total Returns
    RETURNS = Eigen::MatrixXd(holdings.rows(), 1);
    RETURNS(0) = 1;

    // std::cout<<"5";// << std::endl;

    for (int j = 1; j < TOTAL_EQUITY.size(); j++) {
        if (TOTAL_EQUITY(j - 1) == 0) RETURNS(j) = 0;
        else RETURNS(j) = (TOTAL_EQUITY(j) - TOTAL_EQUITY(j - 1)) / TOTAL_EQUITY(j - 1);
    };

    // std::cout << "TOTAL EQUITY" << std::endl << TOTAL_EQUITY.head(10) << std::endl;

    cumulative_product(RETURNS, EQUITY_CURVE);

    TOTAL_RETURN = EQUITY_CURVE(EQUITY_CURVE.size() - 1);


    // std::cout<<"6";

    // std::cout << RETURNS << std::endl;

    // std::cout<<"7";

    calculate_drawdown();

    // std::cout << max_dd << std::endl;

    // std::cout << SHARPE_RATIO(252) << std::endl;

    // std::cout << "EQ CURVE Head" << std::endl << EQUITY_CURVE.head(10) << std::endl;
    // std::cout << "EQ CURVE Tail" << std::endl << EQUITY_CURVE.tail(10) << std::endl;

}

double Metrics::SHARPE_RATIO(int periods) {
    return std::sqrt(periods) * RETURNS.mean() / std(RETURNS);
}

double Metrics::std(Eigen::VectorXd vec) {
    return std::sqrt((vec.array() - vec.mean()).square().sum() / (vec.size() - 1));
}


void Metrics::calculate_drawdown() {

    Eigen::VectorXd high_water_mark = Eigen::MatrixXd(EQUITY_CURVE.size(), 1);
    Eigen::VectorXd drawdown = Eigen::MatrixXd(EQUITY_CURVE.size(), 1);
    Eigen::VectorXd drawdown_duration = Eigen::MatrixXd(EQUITY_CURVE.size(), 1);

    for (int t = 1; t < EQUITY_CURVE.size(); t++) {
        high_water_mark(t) = std::max(high_water_mark(t - 1), EQUITY_CURVE(t));
        drawdown(t) = high_water_mark(t) - EQUITY_CURVE(t);
        if (drawdown(t) == 0) {
            drawdown_duration(t) = 0;
        }
        else {
            drawdown_duration(t) = drawdown_duration(t-1) + 1;
        };
    //     high_water_mark[t] = max(high_water_mark[t-1], self.eq_curve[t])
    //     drawdown[t]= high_water_mark[t] - self.eq_curve[t]
    //     drawdown_duration[t]= 0 if drawdown[t] == 0 else drawdown_duration[t-1] + 1
    };
    
    MAX_DRAWDOWN = drawdown.maxCoeff();
    DRAWDOWN_DURATION = drawdown_duration.maxCoeff();

};

void Metrics::cumulative_product(Eigen::VectorXd vec, Eigen::VectorXd& make_vec) {
    // Note this function automatically adds one to whatever its cumulatively multiplying.

    make_vec = Eigen::MatrixXd(vec.size(), 1);
    make_vec(0) = vec(0);

    // std::cout << "TOTAL RETURNS" << std::endl << vec.head(10) << std::endl;

    vec.array() += 1.f;

    // std::cout << "TOTAL RETURNS + 1" << std::endl << vec.head(10) << std::endl;

    for (int j = 1; j < vec.size(); j++) {
        make_vec(j) = (vec(j) * vec(j - 1));
    };

}

// void Metrics::printf_csv(std::string path) {
//     std::ofstream out(path);

//     for (auto& row : temp_matrix) {
//         for (auto col : row) out << col << ',';
//         out << '\n';
//     }
// }

void Metrics::display_metrics() {
    VariadicTable<std::string, double> vt({"Metric", "Value"}, 10);

    vt.addRow("Time Taken", TIME_TAKEN);
    vt.addRow("Sharpe Ratio", SHARPE_RATIO(252));
    vt.addRow("Total Return", TOTAL_RETURN);
    vt.addRow("Max DD", MAX_DRAWDOWN);
    vt.addRow("DD Duration", DRAWDOWN_DURATION);
    // vt.addRow("Profit and Loss", PnL);


    vt.print(std::cout);

};

