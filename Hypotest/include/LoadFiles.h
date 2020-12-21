#ifndef Hypotest_include_LOADFILES_H
#define Hypotest_include_LOADFILES_H

#include <TH1.h>
#include <TFile.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

class LoadFiles{
  
 public:
  LoadFiles();
  ~LoadFiles();
 void SetConfig(string path);
 void InitData(string path);
 void InitBackground(string path);
 void InitSignal(string path);
 void InitSignalB(string path);
 void Show();
 void ShowSizes(); 
 void LoadFile_();

 TH1D* GetDataHisto(Int_t index, string path, string label);
 TH1D* GetMCHisto(Int_t index, string path, string label);
 TH1D* GetTotalMCHisto(string path, string label);
 TH1D* GetSignalHisto(Int_t index, string path, string label);
 TH1D* GetSignalBHisto(Int_t index, string path, string label);

 UInt_t Data_s;
 UInt_t MC_s;
 UInt_t Sig_s;
 UInt_t Sigb_s;

 private:
 std::string ConFolder; 
 std::ifstream Input[4];

 std::vector<string> Data_F;
 std::vector<string> Bkg_F;
 std::vector<string> Sig_F;
 std::vector<string> SigB_F;

  TFile *Data[50];
  TFile *Bkg[50];
  TFile *Sig[50];
  TFile *SigB[50];
  TFile *Total_Bkg[1];

};
#endif
