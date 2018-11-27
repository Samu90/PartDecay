#ifndef ScatteringDet_h
#define ScatteringDet_h

#include <iostream>
#include <ctime>

#include "Detector.h"
#include "TLorentzVector.h"
#include "TRandom.h"

class ScatteringDet:public Detector{

 public:
  ScatteringDet();
  ~ScatteringDet();
  void ActionScat(TLorentzVector*);
  
};


#endif
