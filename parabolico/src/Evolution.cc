#include "../include/Evolution.h"

Evolution::Evolution(){
}

Evolution::Evolution(const TGWindow *p, UInt_t w, UInt_t h): 
	timer(nullptr),
	TIME(0.),
        Counter(-1),
	p(nullptr)
	{

   frame = new TGMainFrame(p,h,w);
   // subframes
   subframe1 = new TGCompositeFrame(frame, 200, 200, kHorizontalFrame | kFixedWidth);
   subframe2 = new TGCompositeFrame(frame, 200, 200, kHorizontalFrame | kFixedWidth);
   subframe3 = new TGVerticalFrame(frame, 200, 200, kFixedWidth);
   subframe4 = new TGCompositeFrame(frame, 200, 200, kHorizontalFrame | kFixedWidth);
   subframe5 = new TGCompositeFrame(frame, 200, 200, kHorizontalFrame | kFixedWidth);
   subframe6 = new TGCompositeFrame(frame, 200, 200, kHorizontalFrame | kFixedWidth);
   subframe7 = new TGCompositeFrame(frame, 200, 200, kHorizontalFrame | kFixedWidth);
   subframe8 = new TGCompositeFrame(frame, 200, 200, kHorizontalFrame | kFixedWidth);
 
   // including subframes
   frame->AddFrame(subframe1, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));
   frame->AddFrame(subframe2, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));
   frame->AddFrame(subframe3, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));
   frame->AddFrame(subframe4, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));
   frame->AddFrame(subframe5, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));
   frame->AddFrame(subframe6, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));
   frame->AddFrame(subframe7, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));
   frame->AddFrame(subframe8, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));


   // Buttons
   TStart = new TGTextButton(subframe1,"&Start");
   TStart->Connect("Clicked()","Evolution",this,"EnableTimer()");

   TRestart = new TGTextButton(subframe1,"&Restart ");
   TRestart->Connect("Clicked()","Evolution",this,"RestartTimer()");

   TStop = new TGTextButton(subframe1,"S&top");
   TStop->Connect("Clicked()","Evolution",this,"DisableTimer()");
   

   // Numeric entries
   Txmin = new TGNumberEntry(subframe2,-100.);
   Tymin = new TGNumberEntry(subframe2,-100.);
   Txmax = new TGNumberEntry(subframe2,500.);
   Tymax = new TGNumberEntry(subframe2,500.);

   // Status Bar
   Stime = new TGStatusBar(subframe3);
   Stime->SetParts(1);
   SPosition = new TGStatusBar(subframe3);
   SPosition->SetParts(3);
   SVelocity = new TGStatusBar(subframe3);
   SVelocity->SetParts(3);
   SAcceleration = new TGStatusBar(subframe3);
   SAcceleration->SetParts(3);

   //Check buttons
   Xplot = new TGCheckButton(subframe4, "&Xplot");
   Yplot = new TGCheckButton(subframe4, "&Yplot");
   Zplot = new TGCheckButton(subframe4, "&Zplot");

   VXplot = new TGCheckButton(subframe5, "&VXplot");
   VYplot = new TGCheckButton(subframe5, "&VYplot");
   VZplot = new TGCheckButton(subframe5, "&VZplot");

   AXplot = new TGCheckButton(subframe6, "&AXplot");
   AYplot = new TGCheckButton(subframe6, "&AYplot");
   AZplot = new TGCheckButton(subframe6, "&AZplot");
   //Yplot->SetOn();
   //Yplot->Connect("Toggled(Bool_t)","Evolution",this,"Plotting()");

   PaintPArrow = new TGCheckButton(subframe7, "Paint X"); 
   PaintVArrow = new TGCheckButton(subframe7, "Paint V"); 
   PaintAArrow = new TGCheckButton(subframe7, "Paint A");

   TExit = new TGTextButton(subframe8, "&Exit ","gApplication->Terminate(0)");


   //Including Buttons on subframes
   subframe1->AddFrame(TStart, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 2));
   subframe1->AddFrame(TRestart, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 2));
   subframe1->AddFrame(TStop, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 2));
   
   subframe2->AddFrame(Txmin, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 0, 2, 2));
   subframe2->AddFrame(Tymin, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 0, 2, 2));
   subframe2->AddFrame(Txmax, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 0, 2, 2));
   subframe2->AddFrame(Tymax, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 0, 2, 2));

   subframe3->AddFrame(Stime, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 0, 2, 2));
   subframe3->AddFrame(SPosition, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 0, 2, 2));
   subframe3->AddFrame(SVelocity, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 0, 2, 2));
   subframe3->AddFrame(SAcceleration, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 0, 2, 2));

   subframe4->AddFrame(Xplot, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 0, 2, 2)); 
   subframe4->AddFrame(Yplot, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 0, 2, 2)); 
   subframe4->AddFrame(Zplot, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 0, 2, 2)); 

   subframe5->AddFrame(VXplot, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 0, 2, 2)); 
   subframe5->AddFrame(VYplot, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 0, 2, 2)); 
   subframe5->AddFrame(VZplot, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 0, 2, 2));  

   subframe6->AddFrame(AXplot, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 0, 2, 2)); 
   subframe6->AddFrame(AYplot, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 0, 2, 2)); 
   subframe6->AddFrame(AZplot, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 0, 2, 2));  

   subframe7->AddFrame(PaintPArrow, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 0, 2, 2)); 
   subframe7->AddFrame(PaintVArrow, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 0, 2, 2)); 
   subframe7->AddFrame(PaintAArrow, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 0, 2, 2)); 

   subframe8->AddFrame(TExit, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 0, 2, 2));

   // Initializing buttons
   TStop->SetEnabled(false);
   TRestart->SetEnabled(false);
   TStart->SetEnabled(true);
   

   CreateObjects();   

}

void Evolution::DrawF(){

  if(frame){

    frame->SetWindowName("Control Buttons");
    frame->SetWMSizeHints(200, 200, 500, 500, 1, 1);
    frame->Resize(GetDefaultSize());
    
    frame->Layout();
    frame->MapSubwindows();
    frame->MapWindow();

  }
  
}

void Evolution::EnableTimer(){

  if(!timer){
    std::cout << " --- Starting simulation --- " << std::endl;

    timer = new TTimer(this, 100, kTRUE);
    timer->Connect("Timeout()", "Evolution", this, "Run()");
    timer->Reset();
    timer->TurnOn(); 

    TStart->SetEnabled(false);
    TRestart->SetEnabled(true);
    TStop->SetEnabled(true);

  }

  else{  
   std::cout << " --- Starting simulation --- " << std::endl; 
   timer->TurnOn();

   TStart->SetEnabled(false);
   TRestart->SetEnabled(true);
   TStop->SetEnabled(true);

  }


}

void Evolution::RestartTimer(){

  if(timer){
    timer->TurnOff();
    timer->Reset();   
    TIME=0.;
    Counter=0;  
    if(p) p->Reset();
    timer->TurnOn(); 

    TStart->SetEnabled(false);
    TRestart->SetEnabled(true);
    TStop->SetEnabled(true);
  }
}

void Evolution::DisableTimer(){

  if(timer){
    std::cout << " --- Stopping simulation --- " << std::endl;  
    timer->TurnOff();
    TStart->SetEnabled(true);
    TRestart->SetEnabled(true);
    TStop->SetEnabled(false);
  }

}

void Evolution::CreateObjects(){


   //Canvases
   c1 = new TCanvas("c1","Trajectory",100,100,500,500);
   Plots = new TCanvas("Plots","Plots",600,100,500,500);

    // Arrows for vectors
   PositionArrow = new TArrow();
   SetArrowStyle(&PositionArrow, 0);
   VelocityArrow = new TArrow();
   SetArrowStyle(&VelocityArrow, 1);
   AccelerationArrow = new TArrow();
   SetArrowStyle(&AccelerationArrow, 2);

   // Graphs
   Null = new TGraph();
   SetStyle(&Null, "X[m]", "Y[m]", 0);
   Generic = new TGraph();
   SetStyle(&Generic, "X[m]", "Y[m]", 1);
   GenericP = new TGraph();
   SetStyle(&GenericP, "t[s]", "X[m]", 2);

   Trayectory = new TMultiGraph();

}

void Evolution::Run(){
 
  UpdateTime(TIME, Counter);
  UpdateVectors();

}

void Evolution::UpdateTime(Double_t &time, Int_t &Counter_){

  time += 1e-1;
  Counter += 1;
 // std::cout << std::setprecision(5) << time << std::endl;

  sprintf(GenericChar,"Time: %.4f", time);
  Stime->SetText(GenericChar,0);
  
}


void Evolution::SetParticle(Particle *p_){
p=p_;
}

void Evolution::ChangeAcceleration(Double_t time, Double_t new_a){

  if(isEqual(TIME, time)) p->SetAcceleration(0.,new_a,0.,TIME);

}

void Evolution::UpdateVectors(){
    
   
  if(p){
  
   p->ChangeVectors(TIME);

   EPosition = p->GetPosition();
   EVelocity = p->GetVelocity();
   EAcceleration = p->GetAcceleration();

//   ChangeAcceleration(5., 4.50);
 //  ChangeAcceleration(30., -9.81);
   
 
   c1->cd();
   c1->Clear();
   
   Null->SetPoint(0,Txmin->GetNumber(),Tymin->GetNumber());
   Null->SetPoint(1,Txmax->GetNumber(),Tymax->GetNumber()); 
   Null->Draw("AP*");
  
   Generic->SetPoint(0,EPosition->x(),EPosition->y());

   Trayectory->Add(Generic);
   Trayectory->Draw("P"); 

   PlotArrow(p);

   c1->Modified();
   c1->Update();
   
   // Second canvas

   Plots->cd();
   Plots->Clear();  

   if(!Xplot->IsOn() && !Yplot->IsOn() && !Zplot->IsOn() && 
      !VXplot->IsOn() && !VYplot->IsOn() && !VZplot->IsOn() &&
      !AXplot->IsOn() && !AYplot->IsOn() && !AZplot->IsOn()) RemovePrePoints(Counter);

   PlotGraphs(EPosition, Xplot); 
   PlotGraphs(EPosition, Yplot);
   PlotGraphs(EPosition, Zplot); 

   PlotGraphs(EVelocity, VXplot); 
   PlotGraphs(EVelocity, VYplot);
   PlotGraphs(EVelocity, VZplot); 
  
   PlotGraphs(EAcceleration, AXplot); 
   PlotGraphs(EAcceleration, AYplot);
   PlotGraphs(EAcceleration, AZplot); 
   
   Plots->Modified();
   Plots->Update();
   
   

   SetValues(EPosition, 0);
   SetValues(EVelocity, 1);
   SetValues(EAcceleration, 2);
   
  }  // Particle activate


  else{
   std::cout << " --- Particle is not initiated --- " << std::endl;
   exit(1);
  } 

}

void Evolution::PlotGraphs(TVector3 *V, TGCheckButton *B){

   bool isPosition=false;
   bool isVelocity=false;
   bool isAcceleration=false;

   string label_ = "";
   if(B == Xplot || B == Yplot || B == Zplot) isPosition=true;   
   else if(B == VXplot || B == VYplot || B == VZplot) isVelocity=true;
   else if(B == AXplot || B == AYplot || B == AZplot) isAcceleration=true;

   if(isPosition) {
        GenericP->SetMarkerColor(2);
	label_ = "x[m]";
        } 
   else if(isVelocity){
        GenericP->SetMarkerColor(3);
	label_ = "v[m/s]";
	} 
   else if(isAcceleration){
        GenericP->SetMarkerColor(1);
	label_ = "a[m/s^{2}]";
	}  

   RemovePostPoints(Counter);

   if(B->IsOn()){

   if(B == Xplot || B == VXplot || B == AXplot ) {
   GenericP->SetPoint(Counter,TIME,V->x());
   SetStyle(&GenericP, "t[s]",label_.c_str(), 2);     
   GenericP->Draw("AP");
   }
   else if(B == Yplot || B == VYplot || B == AYplot) {
   GenericP->SetPoint(Counter,TIME,V->y());
   SetStyle(&GenericP, "t[s]", label_.c_str(), 2);
   GenericP->Draw("AP");
   }
   else if(B == Zplot || B == VZplot || B == AZplot ) {
   GenericP->SetPoint(Counter,TIME,V->z());
   SetStyle(&GenericP, "t[s]", label_.c_str(), 2);
   GenericP->Draw("AP");
   } 
   

   }

}

bool Evolution::isEqual(Double_t t0, Double_t t1){
Double_t epsilon = 0.00001; 
return TMath::Abs(t0-t1) < epsilon;
}


void Evolution::RemovePrePoints(Int_t Counter){

 for(Int_t i = 0; i <= Counter+1; i++)
 GenericP->RemovePoint(i);

}

void Evolution::RemovePostPoints(Int_t Counter){

 for(Int_t i = Counter+1; i <= 10000; i++)
 GenericP->RemovePoint(i);

}

void Evolution::SetValues(TVector3 *V, Int_t i){

  if(i == 0){
  sprintf(GenericChar,"%.4f", V->x());
  SPosition->SetText(GenericChar,0);
  sprintf(GenericChar,"%.4f", V->y());
  SPosition->SetText(GenericChar,1);
  sprintf(GenericChar,"%.4f", V->z());
  SPosition->SetText(GenericChar,2);
  }
  else if(i == 1){
  sprintf(GenericChar,"%.4f", V->x());
  SVelocity->SetText(GenericChar,0);
  sprintf(GenericChar,"%.4f", V->y());
  SVelocity->SetText(GenericChar,1);
  sprintf(GenericChar,"%.4f", V->z());
  SVelocity->SetText(GenericChar,2);
  }
  else if(i == 2){
  sprintf(GenericChar,"%.4f", V->x());
  SAcceleration->SetText(GenericChar,0);
  sprintf(GenericChar,"%.4f", V->y());
  SAcceleration->SetText(GenericChar,1);
  sprintf(GenericChar,"%.4f", V->z());
  SAcceleration->SetText(GenericChar,2);
  }

}

void Evolution::SetStyle(TGraph **g1, string x_, string y_, Int_t index){

  (*g1)->SetTitle("");
  (*g1)->GetXaxis()->SetTitle(x_.c_str());
  (*g1)->GetXaxis()->SetTitleSize(0.05);
  (*g1)->GetXaxis()->SetTitleOffset(1.0);
  (*g1)->GetXaxis()->SetLabelSize(0.05);
  (*g1)->GetXaxis()->SetLabelOffset(0.01);

  (*g1)->GetYaxis()->SetTitle(y_.c_str());
  (*g1)->GetYaxis()->SetTitleSize(0.05);
  (*g1)->GetYaxis()->SetTitleOffset(1.0);
  (*g1)->GetYaxis()->SetLabelSize(0.05);
  (*g1)->GetYaxis()->SetLabelOffset(0.01);

  (*g1)->SetMarkerStyle(20);
  (*g1)->SetLineColor(0);

  if(index == 0){
  (*g1)->SetMarkerSize(0);
  (*g1)->SetMarkerColor(0);
  }
  else if(index == 1){
  (*g1)->SetMarkerSize(1.5);
  (*g1)->SetMarkerColor(4);
  }
  else if(index == 2){
  (*g1)->SetMarkerSize(0.5);
  (*g1)->SetMarkerColor(1);
  }

}

void Evolution::SetArrowStyle(TArrow **A1, Int_t index){
  
   (*A1)->SetLineWidth(1);
   if(index == 0) (*A1)->SetFillColor(2);
   else if(index == 1) (*A1)->SetFillColor(3);
   else if(index == 2) (*A1)->SetFillColor(5);


}

void Evolution::PlotArrow(Particle *p){


   if(PaintPArrow->IsOn()) 
	PositionArrow->DrawArrow(0.,0.,
		p->GetPosition()->x(),p->GetPosition()->y(),0.03,"|>");
   if(PaintVArrow->IsOn()) 
	VelocityArrow->DrawArrow(p->GetPosition()->x(),p->GetPosition()->y(), 
		p->GetPosition()->x()+p->GetVelocity()->x(),p->GetPosition()->y()+p->GetVelocity()->y(), 0.03,"|>");
   if(PaintAArrow->IsOn()) 
	AccelerationArrow->DrawArrow(EPosition->x(),EPosition->y(), 
		p->GetPosition()->x()+p->GetAcceleration()->x(),p->GetPosition()->y()+p->GetAcceleration()->y(), 0.03,"|>");
}


Evolution::~Evolution(){
}
