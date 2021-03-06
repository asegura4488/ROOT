#include "include/LoadFiles.h"
#include "include/Pseudo.h"
#include "include/Workspace.h"

void MakeWorkspaces(string Distribution="transverse_mass_lumi"){
//void MakeWorkspaces(string Distribution="Tau1MetMt"){
 string label="m_{#font[12]{T}}(#tau_{#font[12]{h}}, p_{#font[12]{T}}^{miss})";
 gROOT->Reset();
 gSystem->Load("src/LoadFiles_cxx.so"); 
 gSystem->Load("src/Pseudo_cxx.so"); 
 gSystem->Load("src/Workspace_cxx.so"); 

// Loading file paths
LoadFiles *F1 = new LoadFiles();
F1->SetConfig("config");
//F1->SetConfig("ISRconfig");
F1->InitData("data");
F1->InitBackground("background");
F1->InitSignal("signal");
F1->InitSignalB("signalb");
//F1->Show();
F1->LoadFile_();
//F1->ShowSizes();

// Loading histograms locally

UInt_t Data_s = F1->Data_s;
TH1D* Data_[Data_s];
for(UInt_t i = 0 ; i < Data_s ; i++) Data_[i] = F1->GetDataHisto(i,Distribution, label);

UInt_t MC_s = F1->MC_s;
TH1D* MC_[MC_s];

// Create signal and signal + back plus the pseudo values for both.
//Pseudo *Pseudo_ = new Pseudo("ISRconfig");
Pseudo *Pseudo_ = new Pseudo("config");
//Pseudo_->InitBins("bins");
Pseudo_->InitBins("original");
Int_t Ntoys = 10.;

for(UInt_t i = 0 ; i < MC_s ; i++){
    MC_[i] = F1->GetMCHisto(i,Distribution, label);
     //  Pseudo_->SaveFile(Pseudo_->CreatePseudoHisto(MC_[i],Ntoys));
    }

UInt_t Sig_s = F1->Sig_s;
TH1D* Sig_[Sig_s];

for(UInt_t i = 0 ; i < Sig_s ; i++) {
	Sig_[i] = F1->GetSignalHisto(i,Distribution, label);
        //Pseudo_->SaveFile(Pseudo_->CreatePseudoHisto(Sig_[i],Ntoys));
	}

UInt_t Sigb_s = F1->Sigb_s;
TH1D* Sigb_[Sigb_s];

for(UInt_t i = 0 ; i < Sigb_s ; i++) {
	Sigb_[i] = F1->GetSignalBHisto(i,Distribution, label);
        Pseudo_->SaveFile(Pseudo_->CreatePseudoHisto(Sigb_[i],Ntoys));        
	}

// Setting the workspace for each signal point

Workspace *W = new Workspace();
W->SetConfig("config");
//W->SetConfig("ISRconfig");
W->Init("data");
W->Init("background");
W->Init("signal");
W->Init("signalb");
W->Init("pseudodata");
W->ShowSizes();
W->Load(Distribution, label);
W->GetWorkspace();


// it is just for testing
/*
TH1D *h4 = F1->GetTotalMCHisto(Distribution, label);

TH1D *h2 = F1->GetSignalHisto(2,Distribution, label);
TH1D *ph1 = Pseudo_->CreatePseudoHisto(h2,3);

h2->Draw();
ph1->SetLineColor(2);
ph1->Draw("same");
*/

}


int main(){
MakeWorkspaces();
return 0;
}
