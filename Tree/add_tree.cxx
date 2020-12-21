#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "THStack.h"
#include "TLegend.h"
#include "TTreePlayer.h"
#include "TStyle.h"
#include "TGaxis.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TEfficiency.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iostream>
#include <TNamed.h>
#include <vector>
#include "math.h"
#include <TBufferFile.h>
#include <TMultiGraph.h>

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"

#ifndef __CINT__

void add_tree(){

//TFile hfile("htree.root","UPDATE");

TFile *hfile = TFile::Open("htree.root","UPDATE");

 Float_t new_v=1;

  TTree *t3 = (TTree*)hfile->Get("T");
//  TBranch *newBranch = t3->Branch("new_v", &new_v, "new_v/F");

//  Long64_t nentries = t3->GetEntries();

//  for(Long64_t i = 0; i< nentries;i++) {
////  new_v = gRandom->Uniform(-2,2);
//  newBranch->Fill();
//  }  

//t3->Write("", TObject::kOverwrite);
//hfile->Write("", TObject::kOverwrite);
hfile->Close();
}

#endif

int main(){
add_tree();
return 0;
}
