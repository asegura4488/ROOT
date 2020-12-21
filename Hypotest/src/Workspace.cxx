#include "../include/Workspace.h"

Workspace::Workspace():
ConFolder(""),
Data_s(0),
MC_s(0),
Sig_s(0),
Sigb_s(0),
Pseudo_s(0){

}
void Workspace::SetConfig(string path){
ConFolder = path;
}

void Workspace::Init(string path){
  
  Input[0].open(ConFolder+"/"+path+".in");
  if(!Input[0]) {
    std::cout << "could not open file config/" << path+".in" << std::endl;
    exit(1);
  } 

  string files_=""; 
  while(!Input[0].eof()){
   Input[0] >> files_;
   if(path == "data") Data_F.push_back(files_);
   else if(path == "background") Bkg_F.push_back(files_);
   else if(path == "signal") Sig_F.push_back(files_);
   else if(path == "signalb") Sigb_F.push_back(files_);
   else if(path == "pseudodata") Pseudo_F.push_back(files_); 
  }

   if(path == "data"){
    Data_F.pop_back(); Data_s = Data_F.size(); 
    }
   else if(path == "background"){
    Bkg_F.pop_back(); MC_s = Bkg_F.size(); 
    }
   else if(path == "signal"){
    Sig_F.pop_back(); Sig_s = Sig_F.size(); 
    }
   else if(path == "signalb"){
    Sigb_F.pop_back(); Sigb_s = Sigb_F.size(); 
    }
   else if(path == "pseudodata"){
    Pseudo_F.pop_back(); Pseudo_s = Pseudo_F.size(); 
    }

  Input[0].close();
}

void Workspace::ShowSizes(){
std::cout << " Data: " << Data_s << 
	     " MC: "   << MC_s   << 
             " Signal: " << Sig_s << 
	     " Signalb " << Sigb_s << 
	     " Pseudodata " << Pseudo_s << 
std::endl;   
}


void Workspace::Load(string path_, string label_){

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
   // Total MC
   Total_Bkg[0] = TFile::Open("histos/background/MC.root","READ");
   HTotal_Bkg[0] = GetHisto(Total_Bkg[0],  path_, label_);

   for(UInt_t i = 0; i < Sig_F.size(); i++){
    Sig[i] = TFile::Open(("histos/signal/"+Sig_F[i]+".root").c_str(),"READ");
    HSig[i] = GetHisto(Sig[i] , path_, label_);
    HSig[i]->SetTitle(Sig_F[i].c_str());
   
  }
   for(UInt_t i = 0; i < Sigb_F.size(); i++){
    SigB[i] = TFile::Open(("histos/Sbhistos/"+Sigb_F[i]+".root").c_str(),"READ"); 
    HSigB[i] = GetHisto(SigB[i] , path_, label_);
    HSigB[i]->SetTitle(Sigb_F[i].c_str());
  
  }
    for(UInt_t i = 0; i < Pseudo_F.size(); i++){
    Pseudo[i] = TFile::Open(("histos/pseudodata/"+Pseudo_F[i]+".root").c_str(),"READ");
    HPseudo[i] = GetHisto(Pseudo[i] , path_, label_);
    HPseudo[i]->SetTitle(Pseudo_F[i].c_str());
  
  
  }
/*
  HPseudo[0]->Draw();
  HData[0]->Draw("same");
  HTotal_Bkg[0]->Draw("same");
  HSigB[0]->Draw("same");
  HSig[0]->Draw("same");
  

*/
}
TH1D* Workspace::GetHisto(TFile* Source ,string path, string label){

  TH1D *h1 = (TH1D*)Source->Get(path.c_str());
  if(!h1) { cout << "No found: " << path << endl;  
    exit(1);
  }
  h1->Sumw2();
  h1->GetXaxis()->SetTitle(label.c_str());
  return h1;  
}

void Workspace::GetChannel(Int_t index, string label_){

  Measure_ = new RooStats::HistFactory::Measurement(label_.c_str(),label_.c_str());
  Measure_->SetOutputFilePrefix( label_.c_str() );
  Measure_->SetPOI("SigXsecOverSM");	
  Measure_->SetLumi(1.0);
  Measure_->SetLumiRelErr(0.025);
  Measure_->AddConstantParam("Lumi");

   
  Data_ = new RooStats::HistFactory::Data();
  //Data_->SetHisto(HData[0]);
 // Data_->SetHisto(HPseudo[index]); // Data or Pseudo-Data S+B hypothesis
  Data_->SetHisto(HTotal_Bkg[0]); // Data or Pseudo-Data S+B hypothesis
 
  Signal_ = new RooStats::HistFactory::Sample("Signal_") ;
  Signal_->SetNormalizeByTheory(false);
  Signal_->ActivateStatError();
  Signal_->AddNormFactor("SigXsecOverSM",4,0.5,10);
  Signal_->AddOverallSys("AccSys", 0.95, 1.05);
  Signal_->SetHisto(HSig[index]);


  TMC_ = new RooStats::HistFactory::Sample("TMC_");
  TMC_->ActivateStatError();
  TMC_->AddOverallSys("BkgSys",0.95,1.05);	
  TMC_->SetHisto(HTotal_Bkg[0]);
 
  //Create channel 
    Channel_ = new RooStats::HistFactory::Channel(("Channel"+label_).c_str()) ;
    Channel_->SetStatErrorConfig(0.05, "Poisson");
    Channel_->SetData(*Data_) ;   // Add the DATA to the channel
    Channel_->AddSample(*Signal_) ; // Add the SIGNAL to the channel
    Channel_->AddSample(*TMC_) ;    // Add the BACKGROUND to the channel
    Measure_->AddChannel(*Channel_);

    H1 = new RooStats::HistFactory::HistoToWorkspaceFactoryFast(*Measure_);
    w = H1->MakeCombinedModel(*Measure_);
    w->writeToFile(("workspaces/"+Sig_F[index]+".root").c_str());

}

void Workspace::GetWorkspace(){

   for(UInt_t i = 0; i < Sig_F.size(); i++){ 
    std::cout << " Getting workspace for " << Sig_F[i] <<endl; 
    GetChannel(i, Sig_F[i]);
  }

}


Workspace::~Workspace(){
    }
