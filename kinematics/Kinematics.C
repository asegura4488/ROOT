#include "include/Particle.h"

TCanvas *c1;
TCanvas *px;
TCanvas *py;
TCanvas *vx;
TCanvas *vy;
TCanvas *a;

TTimer *counter;
Double_t t=0.;
Double_t deltat=0.01;


Int_t i = 0.;
Particle *p1;
TMultiGraph *Generic;
TGraph *PX;
TGraph *PY;
TGraph *VX;
TGraph *VY;
TGraph *A;

std::chrono::time_point<std::chrono::system_clock> start;

void UpdateCanvas(){

  double TIME = t;
   /*
  if(TIME == 0.0) p1->SetGravity(3.50);
  else if (TIME == 0.33) p1->SetGravity(4.50);
  else if (TIME == 35.0 ) p1->SetGravity(-9.81);
*/
  t += deltat;

  c1->cd();
  c1->Clear();

  TGraph *Null_ = p1->NullGraph(50.,50.);
  TGraph *Particle1 = p1->Graph(t);
  Null_->Draw();

  Generic = new TMultiGraph();
  Generic->Add(Null_);
  Generic->Add(Particle1);
  Generic->Draw("P");
  
  // Plot vectors
  p1->VectorP(t);
  p1->VectorV(t);
  p1->VectorA(t);

  c1->Modified();
  c1->Update();
  
  // Position in X
  px->cd();
  px->Clear();
  PX->SetPoint(i,t, p1->GetX(t));
  PX->Draw();

  Generic = new TMultiGraph();
  Generic->Clear();
  Generic->Add(PX);
  Generic->Draw();  
  px->Modified();
  px->Update();

  // Position in Y
  py->cd();
  py->Clear();
  PY->SetPoint(i,t, p1->GetY(t));
  PY->Draw();

  Generic = new TMultiGraph();
  Generic->Clear();
  Generic->Add(PY);
  Generic->Draw();  
  py->Modified();
  py->Update();
  
  // velocity in X
  vx->cd();
  vx->Clear();
  VX->SetPoint(i,t, p1->GetVx(t));
  VX->Draw();

  Generic = new TMultiGraph();
  Generic->Clear();
  Generic->Add(VX);
  Generic->Draw();  
  vx->Modified();
  vx->Update();

  // velocity in Y
  vy->cd();
  vy->Clear();
  VY->SetPoint(i,t, p1->GetVy(t));
  VY->Draw();

  Generic = new TMultiGraph();
  Generic->Clear();
  Generic->Add(VY);
  Generic->Draw();  
  vy->Modified();
  vy->Update();

  a->cd();
  a->Clear();
  A->SetPoint(i,t, p1->GetGravity());
  A->Draw();

  Generic = new TMultiGraph();
  Generic->Clear();
  Generic->Add(A);
  Generic->Draw();  
  a->Modified();
  a->Update();

  // Print Values
  p1->GetValues(t);
  i++;

  if(p1->GetY(t) < -0.2){ 
	counter->TurnOff();
        std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        double run_time_real=elapsed_seconds.count();
        std::cout << " Real Time: " << run_time_real << std::endl;
        return 0;
        }

}

void Kinematics(){

p1 = new Particle(0.0,1.0,10.0,20.0);
p1->SetGravity(-9.81);
p1->Showr0();

PX = p1->GenericG("t[s]","X[m]");
PY = p1->GenericG("t[s]","Y[m]");
VX = p1->GenericG("t[s]","Vx[m/s]");
VY = p1->GenericG("t[s]","Vy[m/s]");
A = p1->GenericG("t[s]","a[m/s^{2}]");

c1 = new TCanvas("c1","Kinematics 2D", 50,50,500,500 );
px = new TCanvas("px","Position vs time", 600,100,250,250 );
py = new TCanvas("py","Position vs time", 850,100,250,250 );
vx = new TCanvas("vx","Velocity vs time", 600,400,250,250 );
vy = new TCanvas("vy","Velocity vs time", 850,400,250,250 );
a = new TCanvas("a","acceleration vs time", 1000,600,250,250 );

counter = new TTimer("UpdateCanvas()", 10);
counter->TurnOn();

start = std::chrono::system_clock::now();


}


int main(){
Kinematics();
delete c1,px,py,vx,vy,a;
return 0;
}
