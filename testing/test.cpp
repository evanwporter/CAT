#include "../Libraries/decimal.h"
#include <iostream>

using namespace std;
using namespace dec;

// int main () {
//     decimal<2> value(143125);
//     cout << "Value #1 is: " << value << endl;
//     // declare precise value with digits after decimal point
//     decimal<2> b("0.11");

//     // perform calculations as with any other numeric type
//     value += b;

//     // displays: Value #2 is: 143125.11
//     cout << "Value #2 is: " << value << endl;
//     return 0;
// }

#include <cmath>
#include <complex>

#include <Eigen/Dense>

// class MyDouble {
//     public:
//         double value;
//         MyDouble() : value() {};
//         MyDouble(double val) : value(val) {};

//         template<typename T>
//             MyDouble& operator+=(T rhs) {
//                 value = static_cast<double>(value + rhs);
//                 return *this;
//             }

//         template<typename T>
//             MyDouble& operator-=(const T &rhs) {
//                 value = static_cast<double>(value - rhs);
//                 return *this;
//             }

//         template<typename T>
//             MyDouble& operator*=(T rhs) {
//                 value = static_cast<double>(value * rhs);
//                 return *this;
//             }

//         template<typename T>
//             MyDouble& operator/=(T rhs) {
//                 value = static_cast<double>(value / rhs);
//                 return *this;
//             }

//         MyDouble operator-() const {
//             return -value;
//         }

//         friend std::ostream& operator<<(std::ostream& out, const MyDouble& val) {
//             out << val.value << " m";
//             return out;
//         }

//         explicit operator double() {
//             return value;
//         }
// };

// #define OVERLOAD_OPERATOR(op,ret) ret operator op(const MyDouble &lhs, const MyDouble &rhs) { \
//         return lhs.value op rhs.value; \
//     }

// OVERLOAD_OPERATOR(+, MyDouble)
// OVERLOAD_OPERATOR(-, MyDouble)
// OVERLOAD_OPERATOR(*, MyDouble)
// OVERLOAD_OPERATOR(/, MyDouble)

// OVERLOAD_OPERATOR(>, bool)
// OVERLOAD_OPERATOR(<, bool)
// OVERLOAD_OPERATOR(>=, bool)
// OVERLOAD_OPERATOR(<=, bool)
// OVERLOAD_OPERATOR(==, bool)
// OVERLOAD_OPERATOR(!=, bool)


// MyDouble sqrt(MyDouble val) {
//     return std::sqrt(val.value);
// }
// MyDouble abs(MyDouble val) {
//     return std::abs(val.value);
// }
// MyDouble abs2(MyDouble val) {
//     return val * val;
// }
// bool isfinite(const MyDouble &) { return true; }

namespace Eigen {
    template<> struct NumTraits<decimal>
        : NumTraits<double>
        {
            typedef MyDouble Real;
            typedef MyDouble NonInteger;
            typedef MyDouble Nested;
            enum {
                IsComplex = 0,
                IsInteger = 0,
                IsSigned = 1,
                RequireInitialization = 0,
                ReadCost = 1,
                AddCost = 3,
                MulCost = 3
            };
        };

    template<typename BinaryOp>
    struct ScalarBinaryOpTraits<decimal, double, BinaryOp> { typedef decimal ReturnType;  };

    template<typename BinaryOp>
    struct ScalarBinaryOpTraits<double, decimal, BinaryOp> { typedef decimal ReturnType;  };
}

int main() {
    Eigen::Matrix<decimal, 2, 2> test;
    test << 1, 2, 3, 4;

    Eigen::Matrix<double, 2, 2> reference;
    reference << 1, 2, 3, 4;

    std::cout << test;
}