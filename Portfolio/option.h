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

    Option(){
      strike = 0.0;
      spot = 0.0;

      IV  = 0.0;
      delta = 0.0;
      gamma = 0.0;
      theta = 0.0;
      vega = 0.0;
      rho = 0.0;
    }
};

#endif