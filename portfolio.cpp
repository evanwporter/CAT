#include "ticker.h"
#include "trade.h"
#include "position.h"
#include "portfolio.h"

#include <unordered_map>
#include <string>
#include <vector>


Portfolio::Portfolio()
{
    symbols = {"APPL", "GOOGL", "USD"};
    for(auto symbol : symbols) {
        positions[symbol] = Position();
    };
    positions["USD"] = Position();
}