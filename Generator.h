#ifndef Generator_h
#define Generator_h
#include <iostream>

#include "TLorentzVector.h"

class Generator{

public:
  Generator();
  ~Generator();
  void GeneratePrimary(Double_t mass, Double_t momentum);
  void DecaySim(Double_t m0,Double_t m1, Double_t m2);
  TLorentzVector* GetV0(){return &v0_;}
  TLorentzVector* GetV1(){return &v1_;}
  TLorentzVector* GetV2(){return &v2_;}
  
private:

  TLorentzVector v0_;
  TLorentzVector v1_;
  TLorentzVector v2_;
  Double_t x_,y_,z_;
  
};

#endif
