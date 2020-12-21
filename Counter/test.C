
#include <TROOT.h>
#include <TGButton.h>
#include <TGFrame.h>
#include <TTimer.h>
#include <TThread.h>
#include <Riostream.h>
#include <TGClient.h>

#include <iostream>

class MyFrame : public TGMainFrame {

  public:
 	MyFrame(const TGWindow *p, UInt_t w, UInt_t h);
	virtual ~MyFrame();
        void Plot();
	void EnableTimer();
        void ReStartTimer();
        void DisableTimer();
        void Run();
        float Refresh(float &t);

  private:

	TGMainFrame *TMF1;
	TGCompositeFrame *cframe1;
	TGVerticalFrame *vframe1;
	TGVerticalFrame *vframe2;
      

       TGTextButton *TStart;
       TGTextButton *TRestart;
       TGTextButton *TStop; 
       TGTextButton *TExit;   

       TGNumberEntry *Time;
	TGStatusBar *StatusBar;

       TTimer *Count;
       float iter;

       char Tvalue[20];

       ClassDef(MyFrame,0);	
       
};


MyFrame::MyFrame(const TGWindow *p, UInt_t w, UInt_t h): Count(nullptr), iter(0.){
   

    TMF1 = new TGMainFrame(p,h,w);     
   // Frame
   cframe1 = new TGCompositeFrame(TMF1, 170, 20, kHorizontalFrame | kFixedWidth);
   // Buttons
   TStart = new TGTextButton(cframe1,"&Start ");
   TStart->Connect("Clicked()","MyFrame",this,"EnableTimer()");

   TRestart = new TGTextButton(cframe1,"&Restart ");
   TRestart->Connect("Clicked()","MyFrame",this,"ReStartTimer()");

   TStop = new TGTextButton(cframe1, "S&top");
   TStop->Connect("Clicked()","MyFrame",this,"DisableTimer()");


   cframe1->AddFrame(TStart, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 2));
   cframe1->AddFrame(TRestart, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 2));
   cframe1->AddFrame(TStop, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 2, 2, 2));

   TMF1->AddFrame(cframe1, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));


   vframe1 = new TGVerticalFrame(TMF1, 170, 50, kFixedWidth);   
   TExit = new TGTextButton(vframe1, "&Exit ","gApplication->Terminate(0)");
   vframe1->AddFrame(TExit, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 0, 2, 2));

   TMF1->AddFrame(vframe1, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));

   vframe2 = new TGVerticalFrame(TMF1, 170, 50, kFixedWidth);

   Time = new TGNumberEntry(vframe2,0);
  // Time->SetNumStyle(TGNumberFormat::kNESInteger);

   StatusBar = new TGStatusBar(vframe2);
   StatusBar->SetParts(2);

   vframe2->AddFrame(Time, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 0, 2, 2));
   vframe2->AddFrame(StatusBar, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 2, 0, 2, 2));


   TMF1->AddFrame(vframe2, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));

  // TMF1->AddFrame(TStart, new TGLayoutHints(kLHintsCenterY,5,5,3,4));

   TStop->SetEnabled(false); 
   TRestart->SetEnabled(false); 

}

void MyFrame::Plot(){
 
 if(TMF1){
    TMF1->SetWindowName("Control Buttons");
    TMF1->SetWMSizeHints(200, 150, 320, 320, 1, 1);
    TMF1->MapSubwindows(); 
    TMF1->Resize(GetDefaultSize()); 
    TMF1->Layout();
    TMF1->MapWindow(); 
 }

}

void MyFrame::EnableTimer(){


  if (!Count) {
  std::cout << " --- Starting simulation --- " << std::endl;
   
  Count = new TTimer(this, 50, kTRUE);
  Count->Connect("Timeout()","MyFrame",this,"Run()");  
  Count->Reset();
  Count->TurnOn();

  TStart->SetEnabled(false); 
  TRestart->SetEnabled(true); 
  TStop->SetEnabled(true); 

  }

  else{
   std::cout << " --- Starting simulation --- " << std::endl;
   Count->TurnOn();
   TStart->SetEnabled(false); 
   TStop->SetEnabled(true); 

  }

}

void MyFrame::ReStartTimer(){

  if(Count) {
   Count->TurnOff();
   Count->Reset();
   iter=0.; 
   Count->TurnOn();
   TStart->SetEnabled(false);
   TStop->SetEnabled(true); 
  }

}

void MyFrame::DisableTimer(){

  if(Count){   
   std::cout << " --- Stopping simulation --- " << std::endl;
   Count->TurnOff();
   TStart->SetEnabled(true);
   TStop->SetEnabled(false); 

  }

}

MyFrame::~MyFrame(){

  TMF1->Cleanup();
  delete TMF1;

  if(Count){
  Count->TurnOff();
  delete Count;
  }

}

void MyFrame::Run(){
 
   float time = Refresh(iter);
   if(time == 0.1) DisableTimer();

}

float MyFrame::Refresh(float &t){

  t += 1e-2;

/*
  if(t > 0.12 && t < 0.13){ 
   cout << " time: "; 
   cout << std::setprecision(10) << t << endl;
   DisableTimer();
  }
*/

  sprintf(Tvalue,"Time: %.4f", t);
  StatusBar->SetText(Tvalue,0);

  return 0;

}

void test(){


MyFrame *frame = new MyFrame(gClient->GetRoot(),1000,400);
frame->Plot();
return 0;
}
