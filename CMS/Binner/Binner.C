#include "include/binner.h"

void Binner(string histo="NRecoTau1/Tau1MetMt"){
//void Binner(string histo="transverse_mass_lumi"){

binner *B1 = new binner();

B1->SetConfig("config");
//B1->SetConfig("PhenoConfig");


//B1->InitBins("bins");
B1->InitBins("original");

B1->InitFiles("data");
B1->InitFiles("background");
B1->InitFiles("signal");

string label="m_{#font[12]{T}}(#tau_{#font[12]{h}}, p_{#font[12]{T}}^{miss})";
B1->LoadTFile(histo, label);
B1->GetRebin(); 

  const TString cmd = "mkdir -p Final";
  const TString cmd_data = "mkdir -p Final/data";
  const TString cmd_bkg = "mkdir -p Final/background";
  const TString cmd_signal = "mkdir -p Final/signal";
  gSystem->GetFromPipe(cmd); 
  gSystem->GetFromPipe(cmd_data); 
  gSystem->GetFromPipe(cmd_bkg);
  gSystem->GetFromPipe(cmd_signal); 

  B1->CreateFiles("Tau1MetMt");


}

int main(){
Binner();
return 0;
}
