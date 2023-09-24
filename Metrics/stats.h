#include <Eigen/Dense>
#include <Eigen/Core>

#include <cmath>

using namespace Eigen;


VectorXd pct_change(VectorXd vec) {
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

MatrixXd covariance(MatrixXd M) {
    // Returns covariance matrix
    MatrixXd centered = RETURNS.rowwise() - RETURNS.colwise().mean();
    MatrixXd cov = (centered.adjoint() * centered) / double(RETURNS.rows() - 1);

    auto Dinv = cov.inverse();

    // std::cout << cov;

    return Dinv * cov * Dinv;
}
