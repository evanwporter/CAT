# CAT
WIP port of AT in c++.

Originally this project was too calculate the Block-Scholes model and various other ways of pricing an option. However I decided to pivot it to a port of AT in pure C++ (something I've been wanting to do for a while).

Where as AT is more focused on crypto, CAT is only focused on stocks, thus it doesn't concern itself with many of nuances of crypto such as quote and base side of a pair.

In the future I forsee myself as spending any available time in which I want to code on CAT (rather than AT or Sloth). After all Sloth was created purely for AT. And CAT is better that AT in almost every performance based metric.

Currently works, however it has ~~extremely~~ limited functionality.

CAT stands for C++ Algorithmic Trader.


Meant to be a much faster version of AT.
Edit: This C++ version is so much faster than the python version. There's a difference of night and day when comparing speeds.

This link proved to be exceedingly helpful:
https://eigen.tuxfamily.org/dox/AsciiQuickReference.txt
(putting it here for easy access)

Uses only Eigen 3.4.0
