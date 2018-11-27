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

int main(){

  Generator* g1= new Generator();
  Double_t m0,pz,beta,E,m1,m2;
  bool debug=true;

  
  //lab frame
  m0=5.3;
  pz=4;
  m1=0.5;
  m2=0.13;
  E=TMath::Sqrt(pz*pz+m0*m0);
  beta=pz/E;
  
  g1->GeneratePrimary(m0,pz);
  std::cout<<g1->GetV0()->Theta()<<std::endl;
  std::cout<<g1->GetV0()->Phi()<<std::endl;
  
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
  if(debug) std::cout<<g1->GetV1()->Px()<<" "<<g1->GetV1()->Py() << " " << g1->GetV1()->Pz() << " "<< g1->GetV1()->E()<<std::endl;
  if(debug) std::cout<<g1->GetV2()->Px()<<" "<<g1->GetV2()->Py() << " " << g1->GetV2()->Pz() << " "<< g1->GetV2()->E()<<std::endl;
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
  
  
  if(debug) std::cout<< "SCATTERING PROCESS..." << std::endl; 
  
  if(g1->GetV1()->Pz()>0 && g1->GetV2()->Pz()>0 ){
    for(int i=0;i<NScatDet;i++){
      Sdet1->ActionScat(g1->GetV1());
      Sdet2->ActionScat(g1->GetV2());      
      
      if(debug) std::cout<<g1->GetV1()->Px()<<" "<<g1->GetV1()->Py() << " " << g1->GetV1()->Pz() << " "<< g1->GetV1()->E()<<std::endl;
      if(debug) std::cout<<g1->GetV2()->Px()<<" "<<g1->GetV2()->Py() << " " << g1->GetV2()->Pz() << " "<< g1->GetV2()->E()<<std::endl;
      if(debug) std::cout<<std::endl;
    }//chiudo for
  }//chiudo if


  

  
}
