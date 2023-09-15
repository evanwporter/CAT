#ifndef OPTIONS_H
#define OPTIONS_H

class Option {
  public:
    double strike;
    double spot;
       
    double IV;
    double delta;
    double gamma;
    double theta;
    double vega;
    double rho;

    Option();
};

#endif