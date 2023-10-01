#ifndef UTILITY_H
#define UTILITY_H

#include <Eigen/Core>
#include <Eigen/Dense>

#include "Libraries/simdjson.h"

// namespace CAT {

enum Direction 
{
    LONG_ = 1,
    SHORT_ = -1
};

// Milliseconds
typedef unsigned long long datetime64;

typedef long money;
typedef long quantity_t;

typedef Eigen::Matrix< money, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor > MoneyMatrixX;
typedef Eigen::Matrix< money, Eigen::Dynamic, 1 > MoneyVectorX;
typedef Eigen::Matrix< double, Eigen::Dynamic, 1 > PercentVectorX;

// struct {
//     simdjson::ondemand::document doc;
//     std::string mode;
//     bool quiet;
//     money initial_cash;
//     unsigned long money_mult = 1;
//     unsigned long warmup_period = 1;
//     std::vector<std::string> symbols;
// } bt_settings;

// };

#endif