#include "Generator.h"

#include <ctime>
#include <cmath>
#include <iostream>

#include "TRandom.h"
#include "TMath.h"



Generator::Generator(){}

Generator::Generator(TRandom* rndgen){
  SetGenerator(rndgen);
}

Generator::~Generator(){}

void Generator::GeneratePrimary(Double_t m0, Double_t pz){

  Double_t E=TMath::Sqrt(m0*m0+pz*pz);
  v0_.SetPxPyPzE(0,0,pz,E);

}

void Generator::Sphere(Double_t* x, Double_t* y, Double_t* z, Double_t r=1){
  
  Double_t a=0,b=0,r2=1;
  while (r2 > 0.25) {
    a  = GetGen()->Rndm() - 0.5;
    b  = GetGen()->Rndm() - 0.5;
    r2 =  a*a + b*b;
  }
  z_ = r* ( -1. + 8.0 * r2 );
  
  Double_t scale = 8.0 * r * TMath::Sqrt(0.25 - r2);
  x_ = a*scale;
  y_ = b*scale;
}



void Generator::DecaySim(Double_t m0,Double_t m1, Double_t m2){

  Sphere(&x_,&y_,&z_); //Generate uniform distribuited point on a spehre surface
  
  //  std::cout << "VERSOR DECAY PRODUCT GENERATOR"<< std::endl;
  // std::cout << x_<<" "<< y_<<" "<< z_<<" "<<TMath::Sqrt(x_*x_+y_*y_+z_*z_)<<std::endl;
  //std::cout << -x_<<" "<< -y_<<" "<< -z_<<" "<<TMath::Sqrt(x_*x_+y_*y_+z_*z_)<<std::endl; 
  //std::cout<<std::endl;

  //Center of mass frame

  //two body decay formula
  Double_t E1=(m0*m0+m1*m1-m2*m2)/2/m0;
  Double_t p1=TMath::Sqrt(E1*E1-m1*m1);
  Double_t p2=p1;
  Double_t E2=TMath::Sqrt(p2*p2+m2*m2);

  v1_.SetPxPyPzE(p1*x_,p1*y_,p1*z_,E1);
  v2_.SetPxPyPzE(-p2*x_,-p2*y_,-p2*z_,E2);

  //std::cout << "3-VECTOR MOMENTUM GENERATED IN REST FRAME P1 P2"<< std::endl;
  //std::cout<<v1_.Px()<<" "<<v1_.Py()<<" "<<v1_.Pz()<<std::endl;
  //std::cout<<v2_.Px()<<" "<<v2_.Py()<<" "<<v2_.Pz()<<std::endl;
  //std::cout<<std::endl;
}



