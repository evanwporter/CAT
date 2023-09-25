#include <Eigen/Dense>
#include <Eigen/Core>

#include <cmath>

using namespace Eigen;


template <typename I, typename R>
Matrix< R, Dynamic, 1 > pct_change(Matrix< I, Dynamic, 1 > vec) {
    Matrix< R, Dynamic, 1 > ret = Matrix< R, Dynamic, Dynamic >(vec.rows(), 1);
    ret(0) = 1;

    for (int j = 1; j < vec.size(); j++) {
        if (vec(j - 1) == 0) ret(j) = 0;
        else ret(j) = (vec(j) - vec(j - 1)) / vec(j - 1);
    };

    return ret;
}

template <typename T>
double stdev(Matrix< T, Dynamic, 1 > vec) {
    return std::sqrt((vec.array() - vec.mean()).square().sum() / (vec.size() - 1));
}

template <typename T>
Matrix< T, Dynamic, Dynamic > covariance(Matrix< T, Dynamic, Dynamic > M) {
    // Returns covariance matrix
    Matrix< T, Dynamic, Dynamic > centered = M.rowwise() - M.colwise().mean();
    Matrix< T, Dynamic, Dynamic > cov = (centered.adjoint() * centered) / double(M.rows() - 1);

    return cov;
}

template <typename T>
double cov(Matrix< T, Dynamic, 1 > x, Matrix< T, Dynamic, 1 > y) {
    // Returns scalar quantity
    Matrix< T, Dynamic, 1 > xM = (x.array() - x.mean());
    Matrix< T, Dynamic, 1 > yM = (y.array() - y.mean());
    Matrix< T, Dynamic, 1 > MM = xM.array() * yM.array();

    return MM.sum() / x.size();
}

template <typename T>
Matrix< T, Dynamic, Dynamic > correlation(Matrix< T, Dynamic, Dynamic > COV){
    // Returns correlation matrix
    auto Dinv = COV.inverse();
    return Dinv * COV * Dinv;
}

template <typename T>
void cumulative_product(Matrix< T, Dynamic, 1 > vec, Matrix< T, Dynamic, 1 >& make_vec, float offset = 0) {

    make_vec = Matrix< T, Dynamic, Dynamic >(vec.size(), 1);

    make_vec(0) = vec(0);
    vec.array() += offset;

    for (int j = 1; j < vec.size(); j++) {
        make_vec(j) = (vec(j) * make_vec(j - 1));
    };

}
