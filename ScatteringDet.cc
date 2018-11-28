#include <iostream>

#include "ScatteringDet.h"
#include "TLorentzVector.h"
#include "Detector.h"

ScatteringDet::ScatteringDet(){}

ScatteringDet::~ScatteringDet(){}

void ScatteringDet::ActionScat(TLorentzVector* vec){
  Double_t p, theta, phi;
  theta=vec->Theta();
  phi=vec->Phi();
  
  theta+=GausModifier();
  phi+=GausModifier();

  vec->SetTheta(theta);
  vec->SetPhi(phi);
  
}
