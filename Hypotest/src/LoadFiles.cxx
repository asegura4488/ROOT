#include "../include/LoadFiles.h"

LoadFiles::LoadFiles():
ConFolder(""){
}

void LoadFiles::SetConfig(string path){
ConFolder= path;
}

void LoadFiles::InitData(string path){
 
 Input[0].open(ConFolder+"/"+path+".in");
 if(!Input[0]) {
    std::cout << "could not open file config/" << path+".in" << std::endl;
    exit(1);
  }
  string files_=""; 
  while(!Input[0].eof()){
   Input[0] >> files_;
   Data_F.push_back(files_);
  }
  Data_F.pop_back();
  Data_s = Data_F.size();
  Input[0].close();
}

void LoadFiles::InitBackground(string path){
 
 Input[1].open(ConFolder+"/"+path+".in"); 
 if(!Input[1]) {
    std::cout << "could not open file config/" << path+".in" << std::endl;
    exit(1);
  }
  string files_=""; 
  while(!Input[1].eof()){
   Input[1] >> files_;
   Bkg_F.push_back(files_);
  }
  Bkg_F.pop_back();
  MC_s = Bkg_F.size(); 
  Input[1].close();
}

void LoadFiles::InitSignal(string path){
 
 Input[2].open(ConFolder+"/"+path+".in");
 if(!Input[2]) {
    std::cout << "could not open file config/" << path+".in" << std::endl;
    exit(1);
  }
  string files_=""; 
  while(!Input[2].eof()){
   Input[2] >> files_;
   Sig_F.push_back(files_);
  }
  Sig_F.pop_back();
  Sig_s = Sig_F.size();
  Input[2].close(); 
}

void LoadFiles::InitSignalB(string path){
 
 Input[3].open(ConFolder+"/"+path+".in");
 if(!Input[3]) {
    std::cout << "could not open file config/" << path+".in" << std::endl;
    exit(1);
  }
  string files_=""; 
  while(!Input[3].eof()){
   Input[3] >> files_;
   SigB_F.push_back(files_);
  }
  SigB_F.pop_back();
  Sigb_s = SigB_F.size(); 
  Input[3].close();
}


void LoadFiles::Show(){
  if(Data_F.size() == 0) std::cout << " No data files ... " << std::endl;

  for(UInt_t i = 0; i < Data_F.size(); i++){
    cout << " Data: " << Data_F[i] << endl;
  }
  for(UInt_t i = 0; i < Bkg_F.size(); i++){
    cout << " Background: " << Bkg_F[i] << endl;
  }
  for(UInt_t i = 0; i < Sig_F.size(); i++){
    cout << " Signal: " << Sig_F[i] << " S+B histos -> " << SigB_F[i] << endl;
  }
}

void LoadFiles::ShowSizes(){
std::cout << " Data: " << Data_s << " MC: " << MC_s << " Signal: " << Sig_s << " Signalb " << Sigb_s << std::endl;   
}

void LoadFiles::LoadFile_(){

  for(UInt_t i = 0; i < Data_F.size(); i++){
    Data[i] = TFile::Open(("histos/data/"+Data_F[i]+".root").c_str(),"READ");
  }
   for(UInt_t i = 0; i < Bkg_F.size(); i++){
    Bkg[i] = TFile::Open(("histos/background/"+Bkg_F[i]+".root").c_str(),"READ");
  }
   // Total MC
    Total_Bkg[0] = TFile::Open("histos/background/MC.root","READ");

   for(UInt_t i = 0; i < Sig_F.size(); i++){
    Sig[i] = TFile::Open(("histos/signal/"+Sig_F[i]+".root").c_str(),"READ");
  }
   for(UInt_t i = 0; i < SigB_F.size(); i++){
    SigB[i] = TFile::Open(("histos/Sbhistos/"+SigB_F[i]+".root").c_str(),"READ");
  }
}

TH1D* LoadFiles::GetDataHisto(Int_t index, string path, string label){
  TH1D *h1 = (TH1D*)Data[index]->Get(path.c_str());
  if(!h1) { cout << "No found: " << path << endl;  
    exit(1);
  }
  h1->Sumw2();
  h1->SetTitle(Data_F[index].c_str());
  h1->GetXaxis()->SetTitle(label.c_str());
  return h1;  
}

TH1D* LoadFiles::GetMCHisto(Int_t index, string path, string label){
  TH1D *h1 = (TH1D*)Bkg[index]->Get(path.c_str());
  if(!h1) { cout << "No found: " << path << endl;  
    exit(1);
  }
  h1->Sumw2();
  h1->SetTitle(Bkg_F[index].c_str());
  h1->GetXaxis()->SetTitle(label.c_str());
  return h1;  
}

TH1D* LoadFiles::GetTotalMCHisto(string path, string label){
  TH1D *h1 = (TH1D*)Total_Bkg[0]->Get(path.c_str());
  if(!h1) { cout << "No found: " << path << endl;  
    exit(1);
  }
  h1->Sumw2();
  h1->SetTitle("MC");
  h1->GetXaxis()->SetTitle(label.c_str());
  return h1;  
}

TH1D* LoadFiles::GetSignalHisto(Int_t index, string path, string label){
  TH1D *h1 = (TH1D*)Sig[index]->Get(path.c_str());
  if(!h1) { cout << "No found: " << path << endl;  
    exit(1);
  }
  h1->Sumw2();
  h1->SetTitle(Sig_F[index].c_str());
  h1->GetXaxis()->SetTitle(label.c_str()); 
  return h1;  
}

TH1D* LoadFiles::GetSignalBHisto(Int_t index, string path, string label){
  TH1D *h1 = (TH1D*)SigB[index]->Get(path.c_str());
  if(!h1) { cout << "No found: " << path << endl;  
    exit(1);
  }
  h1->Sumw2();
  h1->SetTitle(SigB_F[index].c_str());
  h1->GetXaxis()->SetTitle(label.c_str());
  return h1;  
}

LoadFiles::~LoadFiles(){
}
