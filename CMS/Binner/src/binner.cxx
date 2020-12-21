#include "../include/binner.h"

binner::binner(): ConFolder(""){
}

void binner::SetConfig(string path){
ConFolder = path;
}

void binner::InitBins(string file){

  Input[0].open((ConFolder+"/bins/"+file+".in").c_str());
  if(!Input[0]) {
    std::cout << "could not open file config bin file: " << file << std::endl;
    exit(1);
  } 

  Double_t bins_ = 0;
  while(!Input[0].eof()){
    Input[0] >> bins_;
    bins.push_back(bins_);    
  }
  bins.pop_back();

  BINS = new Double_t[bins.size()];
  N_bins = bins.size()-1;
  int i=0;
  for(std::vector<Double_t>::iterator it = bins.begin(); it != bins.end(); it++, i++){
    BINS[i] = (*it);
  }

  Input[0].close();
} 

void binner::InitFiles(string file){

  Input[1].open((ConFolder+"/"+file+".in").c_str());
  if(!Input[1]) {
    std::cout << "could not open file config file: " << file << std::endl;
    exit(1);
  } 

  string files_=""; 
  while(!Input[1].eof()){
   Input[1] >> files_;
   if(file == "data") Data_F.push_back(files_);
   else if(file == "background") Bkg_F.push_back(files_);
   else if(file == "signal") Sig_F.push_back(files_);
  }

   if(file == "data"){
    Data_F.pop_back(); Data_s = Data_F.size(); 
    }
   else if(file == "background"){
    Bkg_F.pop_back(); MC_s = Bkg_F.size(); 
    }
   else if(file == "signal"){
    Sig_F.pop_back(); Sig_s = Sig_F.size(); 
    }

  Input[1].close();
}

void binner::LoadTFile(string path_, string label_){

 for(UInt_t i = 0; i < Data_F.size(); i++){
    Data[i] = TFile::Open(("histos/data/"+Data_F[i]+".root").c_str(),"READ");
    HData[i] = GetHisto(Data[i] , path_, label_);
    HData[i]->SetTitle(Data_F[i].c_str());
 }
 for(UInt_t i = 0; i < Bkg_F.size(); i++){
    Bkg[i] = TFile::Open(("histos/background/"+Bkg_F[i]+".root").c_str(),"READ");
    HBkg[i] = GetHisto(Bkg[i] , path_, label_);
    HBkg[i]->SetTitle(Bkg_F[i].c_str());  
 }
 for(UInt_t i = 0; i < Sig_F.size(); i++){
    Sig[i] = TFile::Open(("histos/signal/"+Sig_F[i]+".root").c_str(),"READ");
    HSig[i] = GetHisto(Sig[i] , path_, label_);
    HSig[i]->SetTitle(Sig_F[i].c_str());  
 }
    

}

TH1D* binner::GetHisto(TFile* Source ,string path, string label){

  TH1D *h1 = (TH1D*)Source->Get(path.c_str());
  if(!h1) { cout << "No found: " << path << endl;  
    exit(1);
  }
  h1->Sumw2();
  h1->GetXaxis()->SetTitle(label.c_str());
  return h1;  
}

void binner::GetRebin(){

  for(UInt_t i = 0; i < Data_F.size(); i++){
    Rebinner(&HData[i]);
    std::cout << " Rebinning Data: " << Data_F[i] << std::endl; 
  }
  for(UInt_t i = 0; i < Bkg_F.size(); i++){
    Rebinner(&HBkg[i]);
    std::cout << " Rebinning Background: " << Bkg_F[i] << std::endl;   
  }
  for(UInt_t i = 0; i < Sig_F.size(); i++){
    Rebinner(&HSig[i]);
    std::cout << " Rebinning Signal: " << Sig_F[i] << std::endl;   
  }
   
}

void binner::CreateFiles(string histoN){
  

   for(UInt_t i = 0; i < Data_F.size(); i++){
    NData[i] = TFile::Open(("Final/data/"+Data_F[i]+".root").c_str(),"RECREATE"); 
    HData[i]->SetTitle(histoN.c_str());
    HData[i]->SetName(histoN.c_str());
    HData[i]->Write();
    NData[i]->Close();
    }
   for(UInt_t i = 0; i < Bkg_F.size(); i++){
    NBkg[i] = TFile::Open(("Final/background/"+Bkg_F[i]+".root").c_str(),"RECREATE");
    HBkg[i]->SetTitle(histoN.c_str());
    HBkg[i]->SetName(histoN.c_str());
    HBkg[i]->Write();
    NBkg[i]->Close(); 
   }
   for(UInt_t i = 0; i < Sig_F.size(); i++){
    NSig[i] = TFile::Open(("Final/signal/"+Sig_F[i]+".root").c_str(),"RECREATE");
    HSig[i]->SetTitle(histoN.c_str());
    HSig[i]->SetName(histoN.c_str());
    HSig[i]->Write();
    NSig[i]->Close(); 
   }
}

void binner::Rebinner(TH1D **h_old){
  
  h_new = new TH1D((*h_old)->GetTitle(), (*h_old)->GetName(), N_bins, BINS);
  
  Int_t old_nbins = (*h_old)->GetXaxis()->GetNbins(); 
  Int_t new_nbins = h_new->GetXaxis()->GetNbins();
  
  for (int b = 1; b <= new_nbins; b++ ){
    Double_t Right_edge_new = h_new->GetXaxis()->GetBinLowEdge(b)+h_new->GetXaxis()->GetBinWidth(b);
    Double_t Edge_new = h_new->GetXaxis()->GetBinLowEdge(b);
    Double_t Num_back = 0.;
    Double_t error_back = 0.;
    
    for (int i = 1; i <= old_nbins; i++ ){
      Double_t Right_edge_old = (*h_old)->GetXaxis()->GetBinLowEdge(i)+(*h_old)->GetXaxis()->GetBinWidth(i);
      
  if((Right_edge_old <= Right_edge_new) && (Right_edge_old > Edge_new)){ //Relevant Condition
    
    Num_back += (*h_old)->GetBinContent(i);
    error_back += TMath::Power( (*h_old)->GetBinError(i), 2 ) ;
    
  }
  else continue;
  
  h_new->SetBinContent(b, Num_back);
  h_new->SetBinError(b, TMath::Sqrt(error_back));
  
    } // loop over the old hist
  } // loop over the new hist
  
 h_new->Sumw2(); 
 h_new->GetXaxis()->SetTitle((*h_old)->GetXaxis()->GetTitle());
 (*h_old) = h_new;
 
 
}


binner::~binner(){
}
