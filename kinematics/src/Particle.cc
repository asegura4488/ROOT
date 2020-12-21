#include "../include/Particle.h"

Particle::Particle(){
}

Particle::Particle(Double_t x0_, Double_t y0_, Double_t vx0_, Double_t vy0_):
	x0(x0_),y0(y0_),vx0(vx0_),vy0(vy0_),g(0.),x(0.),y(0.),vx(0),vy(0.){
}

void Particle::Showr0(){
  
  std::cout << " Initial conditions: " << x0 << "," << y0 << std::endl;
}


void Particle::SetGravity(Double_t g_){
   g = g_;
/*
   x0 = x;
   y0 = y;
   vx0 = vx;
   vy0 = vy;
*/
}

Double_t Particle::GetGravity(){
   return g;
 }

Double_t Particle::GetX(Double_t t){
   x = x0 + vx0*t;
   return x;
}

Double_t Particle::GetVx(Double_t t){
   vx = vx0;   
   return vx;
}

Double_t Particle::GetY(Double_t t){
   y = y0 + vy0*t + 0.5*g*TMath::Power(t,2);
   return y;
}

Double_t Particle::GetVy(Double_t t){
  vy = vy0 + g*t;
  return vy;
}

void Particle::GetValues(Double_t t){
  std::cout <<	" time: " << t << 
		" Position: " << GetX(t) << " , " << GetY(t) << 
		" Velocity: " << GetVx(t) << " , " << GetVy(t) << std::endl;  
}

void Particle::VectorP(Double_t t){

  line = new TLine(0., 0., GetX(t), GetY(t));
  line->SetLineColor(2);
  line->Draw();

}

void Particle::VectorV(Double_t t){
  
  line = new TLine(GetX(t), GetY(t), GetX(t)+GetVx(t), GetY(t)+GetVy(t));
  line->SetLineColor(7);
  line->SetLineWidth(2); 
  line->Draw();

}

void Particle::VectorA(Double_t t){

 line = new TLine(GetX(t), GetY(t), GetX(t), GetY(t)+g);
 line->SetLineColor(1);
 line->SetLineWidth(3); 
 line->Draw();

}

TGraph* Particle::Graph(Double_t t){

   X[0] = GetX(t);
   Y[0] = GetY(t);
   R = new TGraph(1,X,Y);

   R->SetMarkerSize(1.5);
   R->SetMarkerStyle(20);
   R->SetMarkerColor(4);

   return R;
   }

TGraph* Particle::GenericG(string Xlabel_, string Ylabel_){

   R = new TGraph();
   
   R->SetTitle("");
   R->GetXaxis()->SetTitle(Xlabel_.c_str());
   R->GetXaxis()->SetTitleSize(0.05);
   R->GetXaxis()->SetTitleOffset(1.0);
   R->GetXaxis()->SetLabelSize(0.05);
   R->GetXaxis()->SetLabelOffset(0.01);

   R->GetYaxis()->SetTitle(Ylabel_.c_str());
   R->GetYaxis()->SetTitleSize(0.05);
   R->GetYaxis()->SetTitleOffset(1.0);
   R->GetYaxis()->SetLabelSize(0.05);
   R->GetYaxis()->SetLabelOffset(0.01);

   R->SetMarkerSize(0.5);
   R->SetMarkerStyle(20);
   R->SetMarkerColor(1);
   R->SetLineColor(1);

   return R;

   }

TGraph* Particle::NullGraph(Double_t X_, Double_t Y_){

   X[0] = 0.0;
   Y[0] = 0.0;
   X[1] = X_;
   Y[1] = Y_;

   R = new TGraph(2,X,Y);

   R->SetTitle("");
   R->GetXaxis()->SetTitle("X[m]");
   R->GetXaxis()->SetTitleSize(0.05);
   R->GetXaxis()->SetTitleOffset(1.0);
   R->GetXaxis()->SetLabelSize(0.05);
   R->GetXaxis()->SetLabelOffset(0.01);

   R->GetYaxis()->SetTitle("Y[m]");
   R->GetYaxis()->SetTitleSize(0.05);
   R->GetYaxis()->SetTitleOffset(1.0);
   R->GetYaxis()->SetLabelSize(0.05);
   R->GetYaxis()->SetLabelOffset(0.01);

   R->SetMarkerSize(0);
   R->SetMarkerStyle(20);
   R->SetMarkerColor(1);
   R->SetLineColor(0);

   return R;
}

Particle::~Particle(){

}

