#include <iostream>
#include  <vector>
#include "TVector3.h"
#include "TFile.h"
#include "DataBd.C"
#include "TMVA/Reader.h"
#include "TMVA/MethodBDT.h"

using namespace std;

void SlimDatav3()
{


  TChain * ch = new TChain("ntuple","");

 // ch->Add("/home/alejandro/Bd/datos_ks0/recofinalBs.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Bd/datos_ks0/crab2_ks0.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Bd/datos_ks0/crab3_ks0.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Bd/datos_ks0/crab4_ks0.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Bd/datos_ks0/crab5_ks0_1000.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Bd/datos_ks0/crab5_ks0_1200.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Bd/datos_ks0/crab5_ks0_1400.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Bd/datos_ks0/crab5_ks0_1600.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Bd/datos_ks0/crab5_ks0_1800.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Bd/datos_ks0/crab5_ks0_200.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Bd/datos_ks0/crab5_ks0_400.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Bd/datos_ks0/crab5_ks0_600.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Bd/datos_ks0/crab5_ks0_800.root/mkcands/ntuple");

  TTree *tree = (TTree*)ch;

  DataBd t(tree);

  Long64_t nentries = t.fChain->GetEntries();
  
  cout<<" Entries : "<<nentries<<endl;

  
  t.fChain->SetBranchStatus("*",0);  // disable all branches
  t.fChain->SetBranchStatus("B_mass",1); 
  t.fChain->SetBranchStatus("B_J_mass",1); 
  t.fChain->SetBranchStatus("B_Ks0_mass",1); 
  t.fChain->SetBranchStatus("B_Ks0_charge1",1); 
  t.fChain->SetBranchStatus("B_Ks0_charge2",1); 
  t.fChain->SetBranchStatus("B_px",1); 
  t.fChain->SetBranchStatus("B_py",1); 
  t.fChain->SetBranchStatus("B_pz",1); 
  t.fChain->SetBranchStatus("B_J_px1",1); 
  t.fChain->SetBranchStatus("B_J_py1",1); 
  t.fChain->SetBranchStatus("B_J_pz1",1); 
  t.fChain->SetBranchStatus("B_Ks0_px1",1); 
  t.fChain->SetBranchStatus("B_Ks0_py1",1); 
  t.fChain->SetBranchStatus("B_Ks0_pz1",1); 
  t.fChain->SetBranchStatus("B_J_px2",1); 
  t.fChain->SetBranchStatus("B_J_py2",1); 
  t.fChain->SetBranchStatus("B_J_pz2",1); 
  t.fChain->SetBranchStatus("B_Ks0_px2",1); 
  t.fChain->SetBranchStatus("B_Ks0_py2",1); 
  t.fChain->SetBranchStatus("B_Ks0_pz2",1); 
  t.fChain->SetBranchStatus("bctau2D",1); 
  t.fChain->SetBranchStatus("bctau2DE",1); 
  t.fChain->SetBranchStatus("B_chi2",1); 
  t.fChain->SetBranchStatus("B_J_chi2",1); 
  t.fChain->SetBranchStatus("B_Ks0_chi2",1); 
  t.fChain->SetBranchStatus("nB",1); 
  


  TMVA::Reader *reader = new TMVA::Reader("!Color");    
  string dir = "/home/alejandro/Bd/TMVA/weights/";
  string prefix = "BDTAnalysisv4-test";

  Float_t var[35];

   reader->AddVariable("v0", &var[0]);
   reader->AddVariable("v1", &var[1]);
   reader->AddVariable("v2", &var[2]);
   reader->AddVariable("v3", &var[3]);
   //reader->AddVariable("v4", &var[4]);
   reader->AddVariable("v5", &var[5]);
   //reader->AddVariable("v6", &var[6]);
  //reader->AddVariable("v7", &var[7]);
   //reader->AddVariable("v8", &var[8]);
   reader->AddVariable("v9", &var[9]);
   reader->AddVariable("v10", &var[10]);
   reader->AddVariable("v11", &var[11]);
   //reader->AddVariable("v12", &var[12]);
   reader->AddVariable("v13", &var[13]);
   reader->AddVariable("v14", &var[14]);
   //reader->AddVariable("v15", &var[15]);
   reader->AddVariable("v16", &var[16]);
   //   reader->AddVariable("v17", &var[17]);
   //   reader->AddVariable("v18", &var[18]);
   //   reader->AddVariable("v19", &var[19]);
   //   reader->AddVariable("v20", &var[20]);
   //   reader->AddVariable("v21", &var[21]);
   //   reader->AddVariable("v22", &var[22]);
   //   reader->AddVariable("v23", &var[23]);
//    reader->AddVariable("v24", &var[24]);
//    reader->AddVariable("v25", &var[25]);


   reader->BookMVA( "BDT method", dir + prefix + "_BDT.weights.xml" );

   cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
   cout<<" Reading data ..."<<nentries<<endl;


   Double_t mass,massJ,massKs0,bdt,Bdl,Bdlxy,Bpt,mf0,Pi1pt,Pi2pt,Jlxy,JlxyE,calpha;

   TString outfileName( "ROOTSlimDataBd-BDT.root" );

   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   TTree *treeS =  new TTree("treeS","signal");
   treeS->Branch("mB",&mass,"mB/D");
   treeS->Branch("mJ",&massJ,"mJ/D");
   treeS->Branch("mKs0",&massKs0,"mKs0/D");
   treeS->Branch("bdt",&bdt,"bdt/D");
   treeS->Branch("Bdl",&Bdl,"Bdl/D");
   //treeS->Branch("Bdlxy",&Bdlxy,"Bdlxy/D");
   treeS->Branch("Bpt",&Bpt,"Bpt/D");
   //treeS->Branch("Pi1pt",&Pi1pt,"Pi1pt/D");
   //treeS->Branch("Pi2pt",&Pi2pt,"Pi2pt/D");
   //treeS->Branch("Jlxy",&Jlxy,"Jlxy/D");
   //treeS->Branch("JlxyE",&JlxyE,"JlxyE/D");
   //treeS->Branch("calpha",&calpha,"calpha/D");

   Int_t nTen = nentries/10;

   Int_t nbytes = 0, nb = 0;
   for(Long64_t jentry=0; jentry<nentries;jentry++) 
     {
       Long64_t ientry = t.LoadTree(jentry);
       if (ientry < 0) break;
       nb = t.fChain->GetEntry(jentry);   nbytes += nb;
       if(jentry%nTen==0) cout<<10*(jentry/nTen)<<"%-"<<flush;
       if(jentry==nentries-1) cout<<endl;

       for(int i=0;i<t.nB;i++)
	 {
	      if(t.B_mass->at(i)<5. || t.B_mass->at(i)>5.6) continue;
	      if(t.B_J_mass->at(i)<2.9 || t.B_J_mass->at(i)>3.2) continue;
	      if(t.B_Ks0_mass->at(i)<0.49 || t.B_Ks0_mass->at(i)>0.5) continue;
	      if(t.B_Ks0_charge1->at(i)==t.B_Ks0_charge2->at(i)) continue;

	      TVector3 mu1(t.B_J_px1->at(i),t.B_J_py1->at(i),t.B_J_pz1->at(i));
	      TVector3 mu2(t.B_J_px2->at(i),t.B_J_py2->at(i),t.B_J_pz2->at(i));	      	  
	      TVector3 pi1(t.B_Ks0_px1->at(i),t.B_Ks0_py1->at(i),t.B_Ks0_pz1->at(i));
	      TVector3 pi2(t.B_Ks0_px2->at(i),t.B_Ks0_py2->at(i),t.B_Ks0_pz2->at(i));	      	      
	      TVector3 mumu = mu1+mu2;
	      TVector3 pipi = pi1+pi2;
	      
	      TVector3 B(t.B_px->at(i),t.B_py->at(i),t.B_pz->at(i));

	      if(fabs(mu1.Eta())>2.5 || fabs(mu2.Eta())>2.5) continue;
	      //if(mu1.Pt()<3. || mu2.Pt()<3.) continue;
	      //if(pi1.Pt()<0.5 || pi2.Pt()<0.5) continue;	      
	      //if(mumu.Pt()<5.) continue;
	      //if(pipi.Pt()<1.6) continue;	      
	      //if(B.Pt()<10.) continue;
	      
	      if(t.bctau2D->at(i)<-1.0 || t.bctau2D->at(i)>1.) continue;
	      if(t.B_Ks0_chi2->at(i)>26.) continue;  
	      if(t.B_J_chi2->at(i)>26.) continue;  
	      if(t.B_chi2->at(i)>26.) continue;  

	      var[0] = pi1.Pt();
	      var[1] = pi1.Eta();
	      var[2] = pi1.Phi();
	      
	      var[3] = pi2.Pt();
	      var[4] = pi2.Eta();
	      var[5] = pi2.Phi();

	      var[6] = pipi.Pt();
	      var[7] = pipi.Eta();
	      var[8] = pipi.Phi();

	      var[9] = t.B_Ks0_chi2->at(i);
	      var[10] = t.B_J_chi2->at(i);
	      var[11] = t.B_chi2->at(i);

	      if(B.DeltaR(pi1) < B.DeltaR(pi2)) 
		{
		  var[12] = B.DeltaR(pi1);
		  var[13] = B.DeltaR(pi2);
		}
	      else 
		{
		  var[12] = B.DeltaR(pi2);
		  var[13] = B.DeltaR(pi1);
		}
	      
	      var[14] = pi1.DeltaR(pi2);

	      if(B.DeltaR(mu1) < B.DeltaR(mu2)) 
		{
		  var[15] = B.DeltaR(mu1);
		  var[16] = B.DeltaR(mu2);
		}
	      else 
		{
		  var[15] = B.DeltaR(mu2);
		  var[16] = B.DeltaR(mu1);
		}

	      //var[17] = t.bctau2D->at(i)/t.bctau2DE->at(i);

	      bdt = reader->EvaluateMVA( "BDT method"); 

	      //if(bdt<-0.5) continue;
       
	      mass = t.B_mass->at(i);
	      massJ = t.B_J_mass->at(i);
	      massKs0 = t.B_Ks0_mass->at(i);
	      Bpt = B.Pt();
	      Bdl = t.bctau2D->at(i);

	      treeS->Fill();

	 }
     }

   outputFile->Write("",TObject::kOverwrite);

}
