# CAT

(C++ Algorithmic Trader)

Originally this project was too calculate the Block-Scholes model and various other ways of pricing an option. However I decided to pivot it to a port of AT in pure C++ (something I've been wanting to do for a while).

Whereas AT is more focused on crypto, CAT is only focused on stocks, thus it doesn't concern itself with many of nuances of crypto such as quote and base side of a pair.

In the future I forsee myself working solely on CAT (rather than AT or Sloth). After all Sloth was created purely for AT. And CAT is better that AT in almost every performance based metric.

Why is speed important?

Because of optimizations of the backtest around a variable. Optimizations require the backtest to be run numerous times thus the backtester needs to be quick, and unfortunately python was too slow. (Also I really like optimizing things). 

## Settings

I used simdjson to parse settings.json. SimdJSON works as an iterator, thus its very important that the keys in the settings file are not moved out of the order that they are placed in.

## File Organization

This repo isn't really meant to be used by anyone else so I organized all of the files in a way that made sense to me. If this repo was to be used elsewhere then I would probably use the [Pitchfork Layout](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs).

## A Note On Risk Management

I believe that the most important part of an Algorithmic is the risk management function. The strategy/signal generator is secondary.

## Compiling

I used VS code to compile the program. The settings I used are located in the `.vscode/launch.json`. Again this program was meant for widespread use then I would've likely used Visual Studio and adopted a more standard file organization policy.

## TODO:
* ~~Parse everything (relevant) out of settings.json~~
* Risk management
  * ~~Position sizing~~
  * ~~Portfolio weightings~~
  * Use correlation to create optimal weightings
    * Implement hierarchical risk parity and Black-Litterman allocation
    * MOAR RISK MANAGEMENT!!! (can never be safe enough)
* ~~File organization and structure~~
* Convert strings to string_view for memory efficiency
* More strategies
  * ~~Abstract Base Strategy Class~~
* ~~Put direction in enum file/folder~~
* Use chrono or roll my own timestamp manager
* ~~Add optimization function~~
* Add errors
* Add << operator variadic table
  * Add << operator to Metrics
* Use c++ std::variant to allow more types within the settings.json
