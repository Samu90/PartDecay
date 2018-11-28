#include <iostream>
#include <cmath>
#include <ctime>
#include <string>

#include "Generator.h"
#include "Detector.h"
#include "ScatteringDet.h"
#include "EnergyLossDet.h"

#include "TLorentzVector.h"
#include "TMath.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TROOT.h"
//#define pmax 3.5 //da configurare a mano
//#define thmax 0.01 //da configurare a mano
#define par1 0.1
#define par2 0.02
#define NScatDet 3
#define m0 5.3
#define pz 4
#define m1 0.5
#define m2 0.13
#define nevent 10000

Double_t InvMass(TLorentzVector* v1, TLorentzVector* v2){
  TLorentzVector temp(0,0,0,0);
  temp=*v1+*v2;
  
  return (temp.M());
}

void Process(Double_t pmax, Double_t thmax, Double_t* dataVec){

  Generator* g1= new Generator();
  Double_t beta,E,Ei1,Ei2;
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

  Ei1=g1->GetV1()->E();
  Ei2=g1->GetV2()->E();
  
  
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
  
  
  // if(g1->GetV1()->Pz()>0 && g1->GetV2()->Pz()>0 ){

    if(debug) std::cout<< "SCATTERING PROCESS..." << std::endl; 

    for(int i=0;i<NScatDet;i++){
      Sdet1->ActionScat(g1->GetV1());
      Sdet2->ActionScat(g1->GetV2());      

      dataVec[i]=InvMass(g1->GetV1(),g1->GetV2());
      
      if(debug) std::cout<<g1->GetV1()->Px()<<" "<<g1->GetV1()->Py() << " " << g1->GetV1()->Pz() << " "<< g1->GetV1()->E()<<"     "<<g1->GetV1()->M()<<std::endl;
      if(debug) std::cout<<g1->GetV2()->Px()<<" "<<g1->GetV2()->Py() << " " << g1->GetV2()->Pz() << " "<< g1->GetV2()->E()<<"     "<<g1->GetV2()->M()<<std::endl;
      if(debug) std::cout<<std::endl;
    }//chiudo for

    //}else{if(debug) std::cout << "BAD PRODUCTION" << std::endl;}//chiudo if

  if(debug) std::cout<< "ENERGY LOSS PROCESS..." << std::endl;

  if(debug) std::cout<< "BEFORE" << std::endl;
  
  if(debug) std::cout<<g1->GetV1()->Px()<<" "<<g1->GetV1()->Py() << " " << g1->GetV1()->Pz() << " "<< g1->GetV1()->E()<<"     "<<g1->GetV1()->M()<<std::endl;
  if(debug) std::cout<<g1->GetV1()->Px()/g1->GetV1()->P()<<" "<<g1->GetV1()->Py()/g1->GetV1()->P() << " " << g1->GetV1()->Pz()/g1->GetV1()->P() << " "<< g1->GetV1()->E()<<"     "<<g1->GetV1()->M()<<std::endl;

  if(debug) std::cout<<g1->GetV2()->Px()<<" "<<g1->GetV2()->Py() << " " << g1->GetV2()->Pz() << " "<< g1->GetV2()->E()<<"     "<<g1->GetV2()->M()<<std::endl;
  if(debug) std::cout<<g1->GetV2()->Px()/g1->GetV2()->P()<<" "<<g1->GetV2()->Py()/g1->GetV2()->P() << " " << g1->GetV2()->Pz()/g1->GetV2()->P() << " "<< g1->GetV2()->E()<<"     "<<g1->GetV2()->M()<<std::endl;

  if(debug) std::cout<<std::endl;
  
  Edet1->EnergyLoss(g1->GetV1());
  Edet2->EnergyLoss(g1->GetV2());

  dataVec[3]=InvMass(g1->GetV1(),g1->GetV2());
  
  if(debug) std::cout<< "AFTER" << std::endl;
  
  if(debug) std::cout<<g1->GetV1()->Px()<<" "<<g1->GetV1()->Py() << " " << g1->GetV1()->Pz() << " "<< g1->GetV1()->E()<<"     "<<g1->GetV1()->M()<<std::endl;
  if(debug) std::cout<<g1->GetV1()->Px()/g1->GetV1()->P()<<" "<<g1->GetV1()->Py()/g1->GetV1()->P() << " " << g1->GetV1()->Pz()/g1->GetV1()->P() << " "<< g1->GetV1()->E()<<"     "<<g1->GetV1()->M()<<std::endl;

  if(debug) std::cout<<g1->GetV2()->Px()<<" "<<g1->GetV2()->Py() << " " << g1->GetV2()->Pz() << " "<< g1->GetV2()->E()<<"     "<<g1->GetV2()->M()<<std::endl;
  if(debug) std::cout<<g1->GetV2()->Px()/g1->GetV2()->P()<<" "<<g1->GetV2()->Py()/g1->GetV2()->P() << " " << g1->GetV2()->Pz()/g1->GetV2()->P() << " "<< g1->GetV2()->E()<<"     "<<g1->GetV2()->M()<<std::endl;

  if(debug) std::cout<<std::endl;

  dataVec[4]= g1->GetV1()->E()/Ei1 ;
  dataVec[5]= g1->GetV2()->E()/Ei2;


  delete g1,Sdet1,Sdet2,Edet1,Edet2;
}


int main(int argc, char *argv[]){

  //gROOT->SetBatch(kTRUE);

  
  Double_t pmax,thmax;
  Double_t Nrms=7;
  Double_t data[6]={0}; //0...3 invariant mass after detector, 4,5 response for m1 and m2
  int i;
  if (argc<3){
    std::cout << "enter -> " << argv[0] <<" PMax ThetaMax" << std::endl;
    return 0;
  }

  pmax = atof(argv[1]);
  thmax = atof(argv[2]);

  TH1D* HistoInvMass[4];
  TH1D* HistoResp[2];
  
  for (i=0;i<4;i++){
    if(i<2) HistoResp[i]=new TH1D(("Response M"+std::to_string(i+1)).c_str(),("Response M"+std::to_string(i+1)).c_str(),2000,0.8,1.1);
    HistoInvMass[i]= new TH1D(("InvmassDet"+std::to_string(i+1)).c_str(),("InvmassDet"+std::to_string(i+1)).c_str(),2000,4.75,5.35);
  }

  
  for(i=0;i<2;i++){
    Process(pmax,thmax,data);
    HistoInvMass[0]->Fill(data[0]);
    HistoInvMass[1]->Fill(data[1]);
    HistoInvMass[2]->Fill(data[2]);
    HistoInvMass[3]->Fill(data[3]);
    HistoResp[0]->Fill(data[4]);
    HistoResp[1]->Fill(data[5]);

    //std::cout<< data[0]<<" "<< data[1]<<" "<<data[2] << " " << data[3]<<" "<< data[4] <<std::endl;
  }

  TCanvas* CanvInvMass = new TCanvas("canv1","InvMass",1200,800);
  TCanvas* CanvResp = new TCanvas("canv2","Response",1200,800);

  CanvInvMass->Divide(2,2);
  CanvResp->Divide(2,1);
  
  for(i=0;i<4;i++){
    if(i<2){
      CanvResp->cd(i+1);
      HistoResp[i]->GetXaxis()->SetRangeUser(HistoResp[i]->GetMean()-5*HistoResp[i]->GetRMS(),HistoResp[i]->GetMean()+5*HistoResp[i]->GetRMS());
      HistoResp[i]->Draw("HISTO");
    }
    CanvInvMass->cd(i+1);
    HistoInvMass[i]->GetXaxis()->SetRangeUser(HistoInvMass[i]->GetMean()-5*HistoInvMass[i]->GetRMS(),HistoInvMass[i]->GetMean()+5*HistoInvMass[i]->GetRMS());
    HistoInvMass[i]->Draw("HISTO");
  }
  
  CanvInvMass->SaveAs("invmass.pdf");
  CanvResp->SaveAs("response.pdf");
  
  return 0;   
}
