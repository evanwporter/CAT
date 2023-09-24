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
    MatrixXd centered = M.rowwise() - M.colwise().mean();
    MatrixXd cov = (centered.adjoint() * centered) / double(M.rows() - 1);

    return cov;
}

double cov(VectorXd x, VectorXd y) {
    // Returns scalar quantity
    VectorXd xM = (x.array() - x.mean());
    VectorXd yM = (y.array() - y.mean());
    VectorXd MM = xM.array() * yM.array();

    return MM.sum() / x.size();
}

MatrixXd correlation(MatrixXd COV){
    // Returns correlation matrix
    auto Dinv = COV.inverse();
    return Dinv * COV * Dinv;
}

void cumulative_product(Eigen::VectorXd vec, Eigen::VectorXd& make_vec, float offset = 0) {

    make_vec = Eigen::MatrixXd(vec.size(), 1);

    make_vec(0) = vec(0);
    vec.array() += offset;

    for (int j = 1; j < vec.size(); j++) {
        make_vec(j) = (vec(j) * make_vec(j - 1));
    };

}
