#include "Detector.h"
#include "TRandom.h"
#include "Generator.h"

Detector::Detector(){}

void Detector::SetGen(TRandom* rand){
  rnd_=rand;
}

Double_t Detector::GausModifier(){
  return rnd_->Gaus(Detector::GetMean(),Detector::GetStdev());
}
