#ifndef EnergyLossDet_h
#define EnergyLossDet_h

#include <iostream>
#include <ctime>

#include "Detector.h"
#include "TLorentzVector.h"
#include "TRandom.h"

class EnergyLossDet:public Detector{

 public:
  EnergyLossDet();
  ~EnergyLossDet();
  void EnergyLoss(TLorentzVector*);
  
};


#endif
