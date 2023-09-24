#include <Eigen/Dense>
#include <Eigen/Core>

#include <cmath>

using namespace Eigen;


VectorXd calculate_percent_change(VectorXd vec) {
    VectorXd ret = MatrixXd(vec.rows(), 1);
    ret(0) = 1;

    for (int j = 1; j < vec.size(); j++) {
        if (vec(j - 1) == 0) ret(j) = 0;
        else ret(j) = (vec(j) - vec(j - 1)) / vec(j - 1);
    };

    return ret;
}

double stdev(VectorXd vec) {
    return std::sqrt((vec.array() - vec.mean()).square().sum() / (vec.size() - 1));
}
