#ifndef include_Methods_h
#define include_Methods_h


#include <iostream>
#include <TMath.h>
#include <TRandom3.h>
#include <TH1D.h>
#include <TCanvas.h>

class Methods{

public:
	Methods();
	~Methods();
	Methods(Double_t Ndata_, Double_t Nbkg_, Double_t Nsignal_);
    
    void SetNdata(Double_t Ndata_);
    Double_t GetNdata();
    void SetNbkg(Double_t Nbkg_);
    Double_t GetNbkg();
    void SetNsignal(Double_t Nsignal_);
    Double_t GetNsignal();

    void SetNtoys(Double_t Ntoys_);

    void GetExpected();
    Double_t GetPvalue(TH1D *h1, Double_t Val);

    void SetHistos(TH1D **h1, Double_t index, string label);
    void NormHistos(TH1D **h1);
    void PlotHistos(TH1D *h1, Double_t index);

    Double_t GetFrequestist(Double_t mu);
    Double_t GetFrequestistCls(Double_t mu);
    Double_t GetModifiedFrequestist(Double_t mu); 

    Double_t GetFrequestistLnQ(Double_t mu);
    Double_t GetFrequestistqm(Double_t mu);

    Double_t GetLnQ(Double_t Ndata_, Double_t Nbkg_, Double_t mu_);
    Double_t GetLnQ2(Double_t Ndata_, Double_t Nbkg_, Double_t mu_);
    Double_t Getqm(Double_t Ndata_, Double_t Nbkg_, Double_t mu_);
    Double_t GetqmSys(Double_t Ndata_, Double_t Nbkg_, Double_t mu_, Double_t m);
    Double_t GetqmSysL(Double_t Ndata_, Double_t Nbkg_, Double_t mu_, Double_t lhat, Double_t lm);

    Double_t GetDoublehatb(Double_t Ndata_, Double_t mu, Double_t m);
    Double_t GetDoublehatl(Double_t Ndata_, Double_t Nbkg_, Double_t mu, Double_t lm);

    Double_t Getq0(Double_t Ndata_, Double_t Nbkg_);

    Double_t GetLimit(Double_t CL, Int_t method_, Double_t mu);
    Double_t GetSignificance(Double_t mu);
 
    Double_t GetPrior(Double_t mu);
    Double_t GetBayes(Double_t mu);

    void Plotter();

private:

  Double_t Ndata;
  Double_t Nbkg;
  Double_t Nsignal;
  Double_t Nsignal2;

  Double_t Lumi = 1.0;
  Double_t Lsigma = Lumi*0.025;

  bool Normalp = true;
  Double_t epsilon = 1E-3;
  Double_t h = 1E-2;

  Double_t limit = 0.;

  Double_t quantile = 0.5;
  Double_t qmedian = 0;
  Double_t significance = 0.;

  Int_t Ntoys = 1E+5;
  Double_t GenDb = 0.;
  Double_t GenDsb = 0.;

  Double_t ObsLnQ=0.;

  Double_t doublehatb1 = 0.;
  Double_t doublehatl = 0.;

  TRandom3 *rnd;

  TH1D *Hbkg;
  TH1D *Hsbkg;
  TH1D *HObs;

  TH1D *Hqm0;
  TH1D *Hqm1;
  TH1D *Hqmm;

  TH1D *HGenb;
  TH1D *HGensb; 

  TH1D *Hq0b;
  TH1D *Hq0sb;
  TH1D *Hq0median;

 
  TH1D *mup;
  TH1D *BNorm;
  TH1D *BPosterior;

  TCanvas *c1;  


};

#endif

