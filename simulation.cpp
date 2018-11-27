#include <iostream>
#include <cmath>
#include <ctime>

#include "Generator.h"
#include "Detector.h"
#include "ScatteringDet.h"
#include "EnergyLossDet.h"

#include "TLorentzVector.h"
#include "TMath.h"

#define pmax 3.5
#define thmax 0.01
#define par1 0.1
#define par2 0.02
#define NScatDet 3
#define m0 5.3
#define pz 4
#define m1 0.5
#define m2 0.13

int main(){

  Generator* g1= new Generator();
  Double_t beta,E;
  bool debug=true;

  
  //lab frame
  E=TMath::Sqrt(pz*pz+m0*m0);
  beta=pz/E;
  
  g1->GeneratePrimary(m0,pz);
    
  if(debug) std::cout<< "PRIMARY PARTICLE GENERATED LAB FRAME"<<std::endl;
  if(debug) std::cout<<g1->GetV0()->Px()<<" "<<g1->GetV0()->Py() << " " << g1->GetV0()->Pz() << " "<< g1->GetV0()->E()<<std::endl;
  if(debug) std::cout<<std::endl;

  g1->GetV0()->Boost(0,0,-beta); //boost to the Center of mass frame
  if(debug) std::cout<< "PRIMARY PARTICLE GENERATED C.O.M. FRAME"<<std::endl;
  if(debug) std::cout<<g1->GetV0()->Px()<<" "<<g1->GetV0()->Py() << " " << g1->GetV0()->Pz() << " "<< g1->GetV0()->E()<<std::endl;
  if(debug) std::cout<<std::endl;

  g1->DecaySim(m0,m1,m2);

  g1->GetV1()->Boost(0,0,beta); //return on lab frame
  g1->GetV2()->Boost(0,0,beta); //return on lab frame

  if(debug) std::cout<< "LAB FRAME AFTER DECAY P1,P2" << std::endl;
  if(debug) std::cout<<g1->GetV1()->Px()<<" "<<g1->GetV1()->Py() << " " << g1->GetV1()->Pz() << " "<< g1->GetV1()->E()<<"     "<<g1->GetV1()->M()<<std::endl;
  if(debug) std::cout<<g1->GetV2()->Px()<<" "<<g1->GetV2()->Py() << " " << g1->GetV2()->Pz() << " "<< g1->GetV2()->E()<<"     "<<g1->GetV2()->M()<<std::endl;
  if(debug) std::cout<<std::endl;

  //The two particle are in Lab frame
  //Simulation of detector interaction

  ScatteringDet* Sdet1= new ScatteringDet();
  Sdet1->SetMean(0);
  Sdet1->SetStdev(pmax*thmax/g1->GetV1()->P());

  ScatteringDet* Sdet2= new ScatteringDet();
  Sdet2->SetMean(0);
  Sdet2->SetStdev(pmax*thmax/g1->GetV2()->P());

  EnergyLossDet* Edet1= new EnergyLossDet();
  Edet1->SetMean(par1*g1->GetV1()->P());
  Edet1->SetStdev(par2*g1->GetV1()->P());
  
  EnergyLossDet* Edet2= new EnergyLossDet();
  Edet2->SetMean(par1*g1->GetV2()->P());
  Edet2->SetStdev(par2*g1->GetV2()->P());
  
  
  if(g1->GetV1()->Pz()>0 && g1->GetV2()->Pz()>0 ){
    if(debug) std::cout<< "SCATTERING PROCESS..." << std::endl; 
    for(int i=0;i<NScatDet;i++){
      Sdet1->ActionScat(g1->GetV1());
      Sdet2->ActionScat(g1->GetV2());      
      
      if(debug) std::cout<<g1->GetV1()->Px()<<" "<<g1->GetV1()->Py() << " " << g1->GetV1()->Pz() << " "<< g1->GetV1()->E()<<"     "<<g1->GetV1()->M()<<std::endl;
      if(debug) std::cout<<g1->GetV2()->Px()<<" "<<g1->GetV2()->Py() << " " << g1->GetV2()->Pz() << " "<< g1->GetV2()->E()<<"     "<<g1->GetV2()->M()<<std::endl;
      if(debug) std::cout<<std::endl;
    }//chiudo for
  }else{std::cout << "BAD PRODUCTION" << std::endl;}//chiudo if

  if(debug) std::cout<< "ENERGY LOSS PROCESS..." << std::endl;

  if(debug) std::cout<< "BEFORE" << std::endl;
  
  if(debug) std::cout<<g1->GetV1()->Px()<<" "<<g1->GetV1()->Py() << " " << g1->GetV1()->Pz() << " "<< g1->GetV1()->E()<<"     "<<g1->GetV1()->M()<<std::endl;
  if(debug) std::cout<<g1->GetV1()->Px()/g1->GetV1()->P()<<" "<<g1->GetV1()->Py()/g1->GetV1()->P() << " " << g1->GetV1()->Pz()/g1->GetV1()->P() << " "<< g1->GetV1()->E()<<"     "<<g1->GetV1()->M()<<std::endl;

  if(debug) std::cout<<g1->GetV2()->Px()<<" "<<g1->GetV2()->Py() << " " << g1->GetV2()->Pz() << " "<< g1->GetV2()->E()<<"     "<<g1->GetV2()->M()<<std::endl;
  if(debug) std::cout<<g1->GetV2()->Px()/g1->GetV2()->P()<<" "<<g1->GetV2()->Py()/g1->GetV2()->P() << " " << g1->GetV2()->Pz()/g1->GetV2()->P() << " "<< g1->GetV2()->E()<<"     "<<g1->GetV2()->M()<<std::endl;

  if(debug) std::cout<<std::endl;
  
  Edet1->EnergyLoss(g1->GetV1());
  Edet2->EnergyLoss(g1->GetV2());

  if(debug) std::cout<< "AFTER" << std::endl;
  
  if(debug) std::cout<<g1->GetV1()->Px()<<" "<<g1->GetV1()->Py() << " " << g1->GetV1()->Pz() << " "<< g1->GetV1()->E()<<"     "<<g1->GetV1()->M()<<std::endl;
  if(debug) std::cout<<g1->GetV1()->Px()/g1->GetV1()->P()<<" "<<g1->GetV1()->Py()/g1->GetV1()->P() << " " << g1->GetV1()->Pz()/g1->GetV1()->P() << " "<< g1->GetV1()->E()<<"     "<<g1->GetV1()->M()<<std::endl;

  if(debug) std::cout<<g1->GetV2()->Px()<<" "<<g1->GetV2()->Py() << " " << g1->GetV2()->Pz() << " "<< g1->GetV2()->E()<<"     "<<g1->GetV2()->M()<<std::endl;
  if(debug) std::cout<<g1->GetV2()->Px()/g1->GetV2()->P()<<" "<<g1->GetV2()->Py()/g1->GetV2()->P() << " " << g1->GetV2()->Pz()/g1->GetV2()->P() << " "<< g1->GetV2()->E()<<"     "<<g1->GetV2()->M()<<std::endl;

  if(debug) std::cout<<std::endl;

  
}
