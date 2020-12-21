#ifndef BINNER_H
#define BINNER_H

#include <iostream>
#include <vector>
#include <fstream>

#include <TH1.h>
#include <TFile.h>
#include <TROOT.h>
#include <TMath.h>

class binner{
  
 public:
  
  binner();
  ~binner();
 void InitBins(string file); 
 void SetConfig(string path);
 void InitFiles(string file); 
 void LoadTFile(string path_, string label_);
 TH1D* GetHisto(TFile* Source ,string path, string label_);
 void Rebinner(TH1D **h_old);
 void GetRebin();
 void CreateFiles(string histoN);

 Double_t *BINS;
 UInt_t N_bins;

 UInt_t Data_s;
 UInt_t MC_s;
 UInt_t Sig_s;

 private:
 std::string ConFolder;

 std::ifstream Input[5]; 
 std::vector<Double_t> bins;

 std::vector<string> Data_F;
 std::vector<string> Bkg_F;
 std::vector<string> Sig_F;

 TFile *Data[50];
 TFile *Bkg[50];
 TFile *Sig[50];

 TH1D *HData[50];
 TH1D *HBkg[50];
 TH1D *HSig[50];

 TH1D *h_new;

 TFile *NData[50];
 TFile *NBkg[50];
 TFile *NSig[50];

};

#endif
