#include "TString.h"
#include "TInterpreter.h"
#include <fstream>
#include "TH1.h"
#include "TGraphSmooth.h"
#include "TCanvas.h"
#include "TSystem.h"


TCanvas *vC1;

void DrawSmooth(Int_t pad, const char *title, const char *xt, const char *yt)
{
   vC1->cd(pad);
   TH1F *vFrame = gPad->DrawFrame(0,-130,60,70);
   vFrame->SetTitle(title);
   vFrame->SetTitleSize(0.2);
   vFrame->SetXTitle(xt);
   vFrame->SetYTitle(yt);
   grin->Draw("P");
   grout->DrawClone("LPX");
}



void volados()
{
   TRandom3 rand;
// read file and add to fit object
   Double_t *x = new Double_t[11000];
   Double_t *y = new Double_t[11000];
   Double_t vX, vY;
   Double_t exitosos = 0;
   Double_t vNData = 0;
   Int_t Eventos;
   Double_t r;
   for(Int_t N;N<10000; N++){   
      for(Int_t j = 0; j<= N; j++)
      {
         r = rand.Uniform(0,1);
         if(r > 0.5){
            exitosos++;
         }   
         vNData++;
      //cout<<j<<" ciclo"<<endl;
      }
      x[N] = N;
      y[N] = exitosos/vNData;
      //cout<<"Exitosos: "<<exitosos<<", Vdata: "<<vNData<<", N: "<<N<<endl;
      exitosos = 0;
      vNData = 0;
   }
  TGraph *grin = new TGraph(N,x,y);
   
// draw graph
   vC1 = new TCanvas("vC1","Smooth Regression",200,10,900,700);
   grin->Draw("AC");


// cleanup
   delete [] x;
   delete [] y;
}

