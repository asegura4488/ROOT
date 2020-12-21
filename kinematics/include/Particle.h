#ifndef PARTICLE_H
#define PARTICLE_H

#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TLine.h>
#include <TMath.h>
#include <TMultiGraph.h>
#include <TTimer.h> 

#include <iostream>
#include <chrono>


class Particle{

 public:
	Particle();
	Particle(Double_t x0_, Double_t y0, Double_t vx0, Double_t vy0);
	~Particle();
        void Showr0();
        void SetGravity(Double_t g_);
        Double_t GetGravity();
        Double_t GetX(Double_t t);
        Double_t GetVx(Double_t t); 
        Double_t GetY(Double_t t);
        Double_t GetVy(Double_t t);

        void GetValues(Double_t t);
        void VectorP(Double_t);
        void VectorV(Double_t); 
        void VectorA(Double_t); 
        TGraph* Graph(Double_t t);
	TGraph* GenericG(string Xlabel_, string Ylabel_);
	TGraph* NullGraph(Double_t X_, Double_t Y_);	

        Double_t g;
 
 private:

	Double_t x0;
        Double_t y0;
	Double_t vx0;
	Double_t vy0;

	Double_t x;
        Double_t vx;
        Double_t y;
        Double_t vy;

        Double_t X[2];
        Double_t Y[2];
        TGraph *R;
        TLine *line;

};

#endif
