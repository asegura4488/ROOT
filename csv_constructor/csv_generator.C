#include <vector>
#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

using namespace std;

std::vector<string> input;
std::vector<string> Digis_Pt;
std::vector<string> Digis;

std::vector<string> features;
std::vector<string> target;

void fill(){
  input.push_back("BDT_CPPF_train_30");
  
  Digis_Pt.push_back("Pt_Muon_Matched");
  Digis_Pt.push_back("IPt_Muon");
  
  
  Digis.push_back("phi1");
  Digis.push_back("phi2");
  Digis.push_back("phi3");
  Digis.push_back("phi4");
  Digis.push_back("theta1");
  Digis.push_back("theta2");
  Digis.push_back("theta3");
  Digis.push_back("theta4");
  Digis.push_back("deltaphi12");
  Digis.push_back("deltaphi23");
  Digis.push_back("deltaphi34");
  Digis.push_back("deltatheta12");
  Digis.push_back("deltatheta23");
  Digis.push_back("deltatheta34");
  Digis.push_back("deltatheta14");
  Digis.push_back("cluster1");
  Digis.push_back("cluster2");
  Digis.push_back("cluster3");
  Digis.push_back("cluster4");
  //Digis.push_back("NMuons");
  //Digis.push_back("NRechits");
  //Digis.push_back("type");
  Digis.push_back("NCPPF");
  
  features.push_back("bdt_features.csv");
  features.push_back("bdt_features_1.csv");
  //features.push_back("bdt_features_2.csv");

  target.push_back("bdt_muon_pt.csv");
  target.push_back("bdt_inverse_muon_pt.csv");
}

void csv_generator(){
  fill();
  
  TString Name = input[0]+".root";
  TFile *FILE = TFile::Open(Name,"READ");
  TTree* tree_ = (TTree*)FILE->Get("BDTCPPF/bdt_cppf");

  Float_t *DIGIS_Pt;
  DIGIS_Pt = new Float_t[Digis_Pt.size()]; 
  //Float_t DIGIS_Pt[2] = {0};
  for(int i = 0; i < Digis_Pt.size() ; i++ ){
    tree_->SetBranchAddress( Digis_Pt[i].c_str(), &DIGIS_Pt[i]);
  }
  Short_t *DIGIS;
  DIGIS = new Short_t[Digis.size()];
  //Short_t DIGIS[22] = {0};   
  for(int i = 0; i < Digis.size() ; i++ ){
    tree_->SetBranchAddress( Digis[i].c_str(), &DIGIS[i]);
  }
  //Map for name branches and array index
  std::cout << "Set of features for saving: " << std::endl;
  std::map<std::string, int> map_branches;
  for(int i = 0; i < Digis.size(); i++){
    map_branches[Digis[i]] = i;  
    std::cout << Digis[i] << " " << i << std::endl;
  }
  
  //output files
  ofstream *Features;
  Features = new ofstream[features.size()];
  //ofstream Features[2];
  for(int i = 0; i < features.size(); i++){
    Features[i].open(features[i], std::ofstream::trunc);
  }
  ofstream *Target;
  Target = new ofstream[target.size()];
  for(int i = 0; i < target.size(); i++){
    Target[i].open(target[i], std::ofstream::trunc);
  }

  //Saving string in files
  for(int i = 0; i < features.size(); i++){  
    for(int j = 0; j < Digis.size(); j++){
      Features[i] <<  Digis[j]; 
      if(j != Digis.size()-1) Features[i] << ",";
      else Features[i] << endl;
    }
  }

  for(int i = 0; i < target.size(); i++){
    for(int j = 0; j < Digis_Pt.size(); j++){
      if(i!=j) continue;
      Target[i] << Digis_Pt[j]; 
      Target[i] << endl;
    }
  }
  
  // close and opening the file without erase their content
  for(int k = 0; k < features.size(); k++){
    Features[k].close();
    Features[k].open(features[k], std::ios_base::app);
  }
  for(int k = 0; k < target.size(); k++){
    Target[k].close();
    Target[k].open(target[k], std::ios_base::app);   
  }
    
  //Loop over the tree entries  
  Long64_t Nentries =  tree_->GetEntries();  
  std::cout << "--- Processing: " << tree_->GetEntries() << " events" << std::endl;
  int counter = 0;
  for (Long64_t ievt=0; ievt < Nentries; ievt++) {
    tree_->GetEntry(ievt);
    if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;
    //Posible cuts
    if(DIGIS[map_branches["NCPPF"]] < 4) continue; 
    //if(DIGIS[map_branches["type"]] != -1) continue;
    //cout << DIGIS_Pt[0] << DIGIS[map_branches["type"]] << endl;

 
    //Saving features
    for(int i = 0; i < features.size(); i++){  
      for(int j = 0; j < Digis.size(); j++){
	Features[i] <<  DIGIS[j];
	if(j != Digis.size()-1) Features[i] << ",";
	else Features[i] << endl; 
      }
    }  
    //Saving targets
    for(int i = 0; i < target.size(); i++){  
      for(int j = 0; j < Digis_Pt.size(); j++){
    	if(i!=j) continue;
	Target[i] << DIGIS_Pt[j]; 
	Target[i] << endl;
      }
    }
    counter++;
    if(counter==20000) break;
 
  } 
  
  for(int k = 0; k < features.size(); k++){
    Features[k].close();
  }
  for(int k = 0; k < target.size(); k++){
    Target[k].close();   
  } 

  delete[] DIGIS_Pt;
  delete[] DIGIS;
  delete[] Features;
  delete[] Target;
}


int main(){
  csv_generator();
  return 0;
}


