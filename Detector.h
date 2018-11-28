#ifndef Detector_h
#define Detector_h
#include <iostream>
#include <ctime>
#include "TRandom.h"

class Detector{

 public:
  Detector();
  void SetMean(Double_t a){mean_=a;}
  void SetStdev(Double_t a){stdev_=a;}
  Double_t GetMean(){return mean_;}
  Double_t GetStdev(){return stdev_;}
  Double_t GausModifier();
  void SetGen(TRandom* );
  
 private:
  Double_t mean_,stdev_; //parameter of detector
  TRandom* rnd_;
};


#endif
