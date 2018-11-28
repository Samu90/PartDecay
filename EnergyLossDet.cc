#include <iostream>

#include "EnergyLossDet.h"
#include "TLorentzVector.h"
#include "Detector.h"
#include "TVector3.h"
#include "TMath.h"

EnergyLossDet::EnergyLossDet(){}

EnergyLossDet::~EnergyLossDet(){}

void EnergyLossDet::EnergyLoss(TLorentzVector* vec){

  Double_t ELoss,NewE,NewP,M;
  TVector3 versor(vec->Vect()*=1/vec->P());
  
  M = vec->M();
  ELoss = GausModifier();
  NewE = vec->E() - ELoss;
  NewP = TMath::Sqrt(NewE*NewE-M*M);

  versor*=NewP;

  vec->SetVect(versor);
  vec->SetE(NewE);
  
}
