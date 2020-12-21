#include "../include/Evolution.h"

Evolution::Evolution(){
}

  Double_t Evolution::t = 0.0;
  Double_t Evolution::deltat = 0.01;
  TCanvas* Evolution::c1 = new TCanvas("c1","Kinematics 2D", 50,50,500,500 );
  TGraph*  Evolution::Null_;
  TGraph*  Evolution::Graph1;
  TMultiGraph* Evolution::TMulti;

  TTimer* Evolution::counter = new TTimer("Evolution::UpdateAll()", 10, kTRUE);

Evolution::Evolution(Double_t deltat_){

 // c1 = new TCanvas("c1","Kinematics 2D", 50,50,500,500 );
  px = new TCanvas("px","Position vs time", 600,100,250,250 );
  py = new TCanvas("py","Position vs time", 850,100,250,250 );
  vx = new TCanvas("vx","Velocity vs time", 600,400,250,250 );
  vy = new TCanvas("vy","Velocity vs time", 850,400,250,250 );
  a = new TCanvas("a","acceleration vs time", 1000,600,250,250 );

}

void Evolution::Start(){

  
  counter->TurnOn();
//  start = std::chrono::system_clock::now();


}

void Evolution::Stop(){

	counter->TurnOff();
/*
	end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        double run_time_real=elapsed_seconds.count();
        std::cout << " Real Time: " << run_time_real << std::endl;
       // delete c1, px, py, vx, vy, a;

*/
}



void Evolution::UpdateAll(){

  static Particle *p1 = new Particle(0.0,0.0,2.0,50.0);

  if(t == 0.0) p1->SetGravity(3.50);
  else if(t == 2.72){
   p1->SetGravity(4.50);
   std::cout << "# cosa " << std::endl;  
  }
  else if(t == 10.) p1->SetGravity(-9.80); 

 // UpdateTrajectory(p1);
  //std::cout << t << std::endl;
  t += deltat; 

  c1->cd();
  c1->Clear();
  Null_ = p1->NullGraph(200.,400.);
  Null_->Draw();
  Graph1 = p1->Graph(t);
  TMulti = new TMultiGraph();
//  TMulti->Add(Null_);
  TMulti->Add(Graph1);
  TMulti->Draw("P"); 

   // Plot vectors
  p1->VectorP(t);
  p1->VectorV(t);
  p1->VectorA(t);

  c1->Modified();
  c1->Update();

  //p1->GetValues(t);

  if(p1->GetY(t) < 0.0) Stop();


}



void Evolution::UpdateTrajectory(Particle **p1){

  t += deltat;
  c1->cd();
  c1->Clear();
  Null_ = (*p1)->NullGraph(2.,4000.);
  Null_->Draw();
  Graph1 = (*p1)->Graph(t);
  TMulti = new TMultiGraph();
  TMulti->Add(Null_);
  TMulti->Add(Graph1);
  TMulti->Draw("P"); 

   // Plot vectors
  (*p1)->VectorP(t);
  (*p1)->VectorV(t);
  (*p1)->VectorA(t);

  c1->Modified();
  c1->Update();

  (*p1)->GetValues(t);
}

void Evolution::Update(){

/*   
  if(TIME == 0.0) p1->SetGravity(3.50);
  else if (TIME == 0.33) p1->SetGravity(4.50);
  else if (TIME == 35.0 ) p1->SetGravity(-9.81);
*/
  t += deltat;

  
  /*
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
*/
 
  

 
}



Evolution::~Evolution(){
 //delete c1, px, py, vx, vy, a;
}

