#include "Particle.h"

#ifndef EVOLUTION_H
#define EVOLUTION_H

#include <TCanvas.h>
#include <TTimer.h> 
#include <TGraph.h>
#include <TMultiGraph.h>

#include <iostream>
#include <chrono>

class Evolution{

 public:
   Evolution();
   Evolution(Double_t deltat_);
   ~Evolution();
   static void Start();
   static void Stop();
   static void UpdateAll();
   void UpdateTrajectory(Particle **p1);
   void Update();

 private:

  static TCanvas *c1;
  TCanvas *px;
  TCanvas *py;
  TCanvas *vx;
  TCanvas *vy;
  TCanvas *a;

  static TTimer *counter;
  
  static Double_t t;
  static Double_t deltat;
  Int_t iter;

  static TGraph *Null_;
  static TGraph *Graph1;
  static TMultiGraph *TMulti; 

  std::chrono::time_point<std::chrono::system_clock> start;
  std::chrono::time_point<std::chrono::system_clock> end;
};

#endif
