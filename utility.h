#ifndef UTILITY_H
#define UTILITY_H

#include <Eigen/Core>
#include <Eigen/Dense>


enum Direction 
{
    LONG = 1,
    SHORT = -1
};

// Milliseconds
typedef unsigned long long datetime64;

typedef long money;

typedef Eigen::Matrix< money, Eigen::Dynamic, Eigen::Dynamic > MoneyMatrixX;
typedef Eigen::Matrix< money, Eigen::Dynamic, 1 > MoneyVectorX;


#endif