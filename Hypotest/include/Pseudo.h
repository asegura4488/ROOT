#ifndef Hypotest_include_PSEUDO_H
#define Hypotest_include_PSEUDO_H

#include "TH1D.h"
#include "TMath.h"
#include "TFile.h"


#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooAbsPdf.h" 
#include "RooGenericPdf.h"
#include "RooWorkspace.h"
#include "RooGlobalFunc.h"
#include "RooFitResult.h"
#include "RooRandom.h"
#include "RooPlot.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <stdio.h>

class Pseudo{
  
 public:
  Pseudo();
  Pseudo(string path);
  void InitBins(string file);
  ~Pseudo();
  void SetConfig(string path);
  TH1D* CreatePseudoHisto(TH1D *h1, Int_t Ntoys);
  void SaveFile(TH1D *h1);

  Double_t *BINS;
  UInt_t N_bins;
 private:
  std::string ConFolder; 

  std::ifstream Input[5]; 
  std::vector<Double_t> bins;

  RooWorkspace *w; 
  char namePdf[50];
  Double_t Mean;
  Double_t Sigma;
  Int_t Mean_I;

  TFile* Output;
  std::ofstream outpseudo;
  TH1D *h1_pseudo;
};

#endif
