#ifndef Evolution_h
#define Evolution_h

#include "Particle.h"

#include <TGFrame.h>
#include <TGButton.h>
#include <TGButtonGroup.h>
#include <TGNumberEntry.h>
#include <TTimer.h>
#include <TGStatusBar.h>
#include <TVector3.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TAxis.h>
#include <TArrow.h>

#include <iostream>

class Evolution : public TGMainFrame{

  public:
      Evolution();
      Evolution(const TGWindow *p, UInt_t w, UInt_t h);
      virtual ~Evolution(); 
      void DrawF();
      void EnableTimer();
      void RestartTimer(); 
      void DisableTimer();
      void Run();
      void CreateObjects();

      void UpdateTime(Double_t &time, Int_t &Counter_);
      void SetParticle(Particle *p_);


      void UpdateVectors();
      void SetValues(TVector3 *V, Int_t i);
 
      void ChangeAcceleration(Double_t time, Double_t new_a);

      void SetStyle(TGraph **g1, string x_, string y_, Int_t index);      

      bool isEqual(Double_t t0, Double_t t1);

      void RemovePrePoints(Int_t Counter);
      void RemovePostPoints(Int_t Counter);

      void PlotGraphs(TVector3 *V, TGCheckButton *B);
      
      void SetArrowStyle(TArrow **A1, Int_t index);
      void PlotArrow(Particle *p);

    
      Particle *p; 
      

  private:

      TGMainFrame *frame;
      TGCompositeFrame *subframe1; 
      TGCompositeFrame *subframe2;
      TGVerticalFrame  *subframe3;
      TGCompositeFrame *subframe4;
      TGCompositeFrame *subframe5;
      TGCompositeFrame *subframe6;
      TGCompositeFrame *subframe7; 
      TGCompositeFrame *subframe8; 

      TGTextButton *TStart;
      TGTextButton *TRestart;
      TGTextButton *TStop;
      TGTextButton *TExit;

      TGNumberEntry *Txmin;
      TGNumberEntry *Tymin; 
      TGNumberEntry *Txmax;
      TGNumberEntry *Tymax;

      TGStatusBar *Stime;
      TGStatusBar *SPosition;
      TGStatusBar *SVelocity;
      TGStatusBar *SAcceleration;

      TGCheckButton *Xplot;
      TGCheckButton *Yplot;
      TGCheckButton *Zplot;
   
      TGCheckButton *VXplot;
      TGCheckButton *VYplot;
      TGCheckButton *VZplot;
   
      TGCheckButton *AXplot;
      TGCheckButton *AYplot;
      TGCheckButton *AZplot;

      TArrow *PositionArrow;
      TGCheckButton *PaintPArrow;
      TArrow *VelocityArrow;
      TGCheckButton *PaintVArrow;
      TArrow *AccelerationArrow;
      TGCheckButton *PaintAArrow;
    
      TTimer *timer;
 
      
      TGraph *Null;
      TGraph *Generic;
      TGraph *GenericP;

      TMultiGraph *Trayectory;

 
      TCanvas *c1;
      TCanvas *Plots;
 
      Double_t TIME;
      Int_t Counter;

      char GenericChar[30];
      
      TVector3 *EPosition;
      TVector3 *EVelocity;  
      TVector3 *EAcceleration;    

  protected:

      //
};

#endif 
