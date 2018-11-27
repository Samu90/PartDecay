#include "Detector.h"
#include "TRandom.h"

Detector::Detector(){}

Detector::Detector(Double_t m,Double_t s){
  mean_=m;
  stdev_=s;
  
}

Double_t Detector::GausModifier(){

  TRandom rnd;
  return rnd.Gaus(Detector::GetMean(),Detector::GetStdev());
  
}
