//********************************************************************************************
//This macro generate a toy model for a dsitribution signal+background
//For each dataset created the mu (signal strenght) value is fitted and pull are calculated
//From the mu_fitted distribution one obtain the MU fitted value and a 95%CL is computed
//The same process is reapeted for a sample with an increased number of events

//N.B Create a directory named "Figures" where the images will be saved
//*********************************************************************************************

///////////////////////////////////
//TO RUN THE MACRO
//1. create directory Figures
//2. run root -b toy_model.C
////////////////////////////////

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooUniform.h"
#include "RooAbsPdf.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#include "TH1.h"
#include "TRandom3.h"
#include "RooAddPdf.h"
#include "stdio.h"

using namespace RooFit ;
using namespace std;


void toy_model(){

  const int dim=10;
  
  Double_t alpha[dim] = {1,2,5,10,20,30,50,70,90,100};  //scaling factor for events
  Double_t N_toy =100; //number of toy generated
  TString title[dim]={"alpha=1","alpha=2","alpha=5","alpha=10","alpha=20","alpha=30","alpha=50","alpha=70","alpha=90","alpha=100"};//correcting the string if alpha values are changed
 
  Double_t up_mu[dim], down_mu[dim];
  Double_t alpha_low[dim], alpha_high[dim];
  Double_t mu_low[dim],mu_high[dim];
  Double_t MU_obs[dim],MU_obs_err[dim]; 
  Double_t pvalue_up,pvalue_down;
  
  Double_t CL=0.025;
    
  TRandom3 a,b;
  
  Double_t pull,mu_fit, mu_fit_err;
  Double_t mu_th=1; //theoretical value of mu
  
  
  gStyle->SetOptStat("MR");  //print mean and RMS values with their errors on the histos
  
  //Declaring signal variables
  RooRealVar x("x","x",115,130) ;
  RooRealVar mean("mean","mean ",125.) ;
  RooRealVar sigma("sigma","width of gaussian",2.) ;
  
  
  // Build gaussian p.d.f in terms of x,mean and sigma
  RooGaussian sig("sig","Signal shape",x,mean,sigma); 
  RooUniform bkg("bkg","Background shape",x);   
  
  //Creating histograms
  TH1F *h_mu_pull = new TH1F("h_mu_pull","pulls of mu",50,-3,3);
  TH1F *h_mu_fit = new TH1F("h_mu_fit","Fitted mu",50,0,2.5);
  TH1F *h_mu_err = new TH1F("h_mu_err","Error on fitted mu",25,0,1);
  TCanvas *mu_results = new TCanvas("mu_results","mu_results",1300,1300);

  RooDataSet *data;
  

  for(int i=0;i<dim;i++){ //loop alpha
    
    MU_obs[i]=0;
    MU_obs_err[i]=0;
    alpha_low[i]=0;
    alpha_high[i]=0;
    
    for(int j=0;j<N_toy;j++){
      
      //Number of signal and background events (according to a Poisson Distribution)
      //alpha is a scaling factor to increase number of observed events
      Double_t N_s=(alpha[i])*(a.Poisson(17.35));
      Double_t N_b=(alpha[i])*(b.Poisson(15.78));
      
       
      //Setting Nsig, Nbkg,mu and n_s
      RooRealVar Nsig("Nsig","signal events",N_s);
      RooRealVar Nbkg("Nbkg","bkg events",N_b);
      RooRealVar mu("mu","signal strenght",mu_th,0,5);
      RooFormulaVar n_s("n_s","@0*@1",RooArgList(Nsig,mu)); //n_s = N_sig*mu
      
      
      //Creating model: n_s*sig + Nbkg*bkg
      RooAddPdf model("model","model",RooArgList(sig,bkg),RooArgList(n_s,Nbkg));
      
      //Creating dataset
      //if number events not specified creates ev=sig+bkg
      RooDataSet *data = model.generate(x);
      
      //Fit pdf to data and getting parameters
      model.fitTo(*data,PrintLevel(-1)); //do not print all fit information
      mu_fit = mu.getVal();
      mu_fit_err=mu.getError();
      pull=(mu_fit - mu_th)/mu_fit_err;

      
      //Filling Histogram
      h_mu_pull->Fill(pull);
      h_mu_fit->Fill(mu_fit);
      h_mu_err->Fill(mu_fit_err);
      

    }//end for on toy number
    
   
    
    //Creating pdf to fit on MU distribution
    RooRealVar MU("MU","MU",0,2.5);
    RooRealVar MU_mean("MU_mean","mean ",0,2.5) ;
    RooRealVar MU_sigma("MU_sigma","width of gaussian",0,2.5) ;
    RooGaussian MU_sig("MU_sig","Signal shape",MU,MU_mean,MU_sigma); 
    
    //Importing MU distribution to RooDataHist
    h_mu_fit->Scale(1/N_toy);
    RooDataHist H_MU("H_MU","H_MU",MU,h_mu_fit);
    MU_sig.fitTo(H_MU,PrintLevel(-1),SumW2Error(kTRUE));
   
    //Drawing mu results
    RooPlot* frame = x.frame(Title("Model Gaus+Uniform"));
   // data->plotOn(frame);
   // model.plotOn(frame,Normalization(1.0,RooAbsReal::RelativeExpected));
   // model.plotOn(frame, Components(bkg),LineStyle(kDashed)) ;

      
    RooPlot *frame2 = MU.frame(Title("MU fitted"));
    H_MU.plotOn(frame2);
    MU_sig.plotOn(frame2);

   
    mu_results->Divide(2,2);
    mu_results->cd(1);  frame->Draw();
    mu_results->cd(2);  frame2->Draw(); 
    mu_results->cd(3);  h_mu_err->Draw();
    mu_results->cd(4);  h_mu_pull->Draw();
    mu_results->Print("Figures/Mu_results_"+title[i]+".eps");
    mu_results->Clear();
    
    //variables for p-value
    MU_obs[i]=MU_mean.getVal();
    MU_obs_err[i]=MU_sigma.getVal();
    up_mu[i]=0.1;
    down_mu[i]=0.1;
    Double_t pvalue_up=0;
    Double_t pvalue_down=0;
 
    //calculating p-values
    while (pvalue_down<=CL) {
      MU.setRange("range_down",0.1,down_mu[i]);
      RooAbsReal *integral_down = MU_sig.createIntegral(MU,NormSet(MU),Range("range_down")) ;
      pvalue_down=integral_down->getVal(); 
      down_mu[i] += 0.001 ;
    }
    while(  pvalue_up<=(1-CL)){
      MU.setRange("range_up",0.1,up_mu[i]);
      RooAbsReal *integral_up = MU_sig.createIntegral(MU,NormSet(MU),Range("range_up")) ;
      pvalue_up=integral_up->getVal(); 
      up_mu[i] += 0.001 ;
    }
    
    h_mu_pull->Reset();
    h_mu_fit->Reset();
    h_mu_err->Reset();
  }//end loop alpha
  

  
  for(int n=0;n<dim;n++){
    cout<<"alpha: "<<alpha[n]<<"  "<<down_mu[n]<<" < "<<MU_obs[n]<<" < "<<up_mu[n]<<endl;
    cout<<"          "<<MU_obs[n]<<"+/-"<<MU_obs_err[n]<<endl; //mean +/- sigma (68% C.L)      
    mu_low[n]=MU_obs[n]-down_mu[n];
    mu_high[n]=up_mu[n]-MU_obs[n];
    
  }

  TCanvas *c =new TCanvas("c","c");
  TF1* th = new TF1("th","1",0,100);
  th->SetLineColor(2);
  th->SetLineStyle(2);
  th->SetLineWidth(3);
  TGraphAsymmErrors *gr = new TGraphAsymmErrors(10,alpha,MU_obs,alpha_low,alpha_high,mu_low,mu_high);
  gr->SetTitle("Signal strenght 95% C.L vs number of events observed");
  gr->GetXaxis()->SetTitle("scaling factor");
  gr->GetYaxis()->SetTitle("95% C.L. on mu");
  gr->SetMarkerColor(4);
  gr->SetMarkerStyle(21);
  gr->SetLineColor(4);
  gr->Draw("ALP");
  th->Draw("same");
  c->Print("Figures/mu_95%CL.eps");
  
  
} //end void

