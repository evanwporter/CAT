#include "option.h"

using namespace std;

Option::Option(){
    strike = 0.0;
    spot = 0.0;
    
    IV  = 0.0;
    delta = 0.0;
    gamma = 0.0;
    theta = 0.0;
    vega = 0.0;
    rho = 0.0;
}

// int main()
// {
//     Option obj1;
//     obj1.strike = 10;
//     return 0;
// }