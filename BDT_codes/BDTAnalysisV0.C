#include <iostream>
#include  <vector>
#include "TFile.h"
#include "TVector3.h"
#include "DataBd.C"
#include "TMVAGui.C"
#include "TMVA/MethodBDT.h"
#include "TMVA/Reader.h"
#include "TMVA/Factory.h"

void BDTAnalysisV0()
{

  TChain * ch = new TChain("ntuple","");

  // ch->Add("/home/alejandro/Documentos/Bd/datos_ks0/recofinalBs.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Documentos/Bd/datos_ks0/crab2_ks0.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Documentos/Bd/datos_ks0/crab3_ks0.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Documentos/Bd/datos_ks0/crab4_ks0.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Documentos/Bd/datos_ks0/crab5_ks0_1000.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Documentos/Bd/datos_ks0/crab5_ks0_1200.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Documentos/Bd/datos_ks0/crab5_ks0_1400.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Documentos/Bd/datos_ks0/crab5_ks0_1600.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Documentos/Bd/datos_ks0/crab5_ks0_1800.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Documentos/Bd/datos_ks0/crab5_ks0_200.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Documentos/Bd/datos_ks0/crab5_ks0_400.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Documentos/Bd/datos_ks0/crab5_ks0_600.root/mkcands/ntuple");
  ch->Add("/home/alejandro/Documentos/Bd/datos_ks0/crab5_ks0_800.root/mkcands/ntuple");

  TTree *tree = (TTree*)ch;

  DataBd tB(tree);

  TChain * chS = new TChain("ntuple","");
chS->Add("/home/alejandro/Documentos/Bd/outputMC_ks0_cern.root/mkcands/ntuple");


  TTree *treeSignal = (TTree*)chS;
  DataBd t(treeSignal);

  Long64_t nentries = t.fChain->GetEntries();
  Long64_t nentriesB = tB.fChain->GetEntries();

  //nentriesB = 500000;

  cout<<" Entries signal: "<<nentries<<endl;
  cout<<" Entries background: "<<nentriesB<<endl;

  Double_t var[35];
  Int_t tp;
  Double_t mass;

  TString outfileName( "TMVAV0.root" );
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

  TTree *treeS =  new TTree("treeS","signal");
  treeS->Branch("v0",&var[0],"v0/D");
  treeS->Branch("v1",&var[1],"v1/D");
  treeS->Branch("v2",&var[2],"v2/D");
  treeS->Branch("v3",&var[3],"v3/D");
  //treeS->Branch("v4",&var[4],"v4/D");
  treeS->Branch("v5",&var[5],"v5/D");
  //treeS->Branch("v6",&var[6],"v6/D");
  //treeS->Branch("v7",&var[7],"v7/D");
  //treeS->Branch("v8",&var[8],"v8/D");
  treeS->Branch("v9",&var[9],"v9/D");
  treeS->Branch("v10",&var[10],"v10/D");
  treeS->Branch("v11",&var[11],"v11/D");
  //treeS->Branch("v12",&var[12],"v12/D");
  treeS->Branch("v13",&var[13],"v13/D");
  treeS->Branch("v14",&var[14],"v14/D");
  //treeS->Branch("v15",&var[15],"v15/D");
  treeS->Branch("v16",&var[16],"v16/D");
  //treeS->Branch("v17",&var[17],"v17/D");

  //  treeS->Branch("v18",&var[18],"v18/D");
  //  treeS->Branch("v19",&var[19],"v19/D");
  //  treeS->Branch("v20",&var[20],"v20/D");
  //  treeS->Branch("v21",&var[21],"v21/D");
  //  treeS->Branch("v22",&var[22],"v22/D");
  //  treeS->Branch("v23",&var[23],"v23/D");
//   treeS->Branch("v24",&var[24],"v24/D");
//   treeS->Branch("v25",&var[25],"v25/D");
//   treeS->Branch("v26",&var[26],"v26/D");
//   treeS->Branch("v27",&var[27],"v27/D");


  //--------------------------------------------
  //Background

  TTree *treeB =  new TTree("treeB","background");  

  treeB->Branch("v0",&var[0],"v0/D");
  treeB->Branch("v1",&var[1],"v1/D");
  treeB->Branch("v2",&var[2],"v2/D");
  treeB->Branch("v3",&var[3],"v3/D");
  //treeB->Branch("v4",&var[4],"v4/D");
  treeB->Branch("v5",&var[5],"v5/D");
  //treeB->Branch("v6",&var[6],"v6/D");
  //treeB->Branch("v7",&var[7],"v7/D");
  //treeB->Branch("v8",&var[8],"v8/D");
  treeB->Branch("v9",&var[9],"v9/D");
  treeB->Branch("v10",&var[10],"v10/D");
  treeB->Branch("v11",&var[11],"v11/D");
  //treeB->Branch("v12",&var[12],"v12/D");
  treeB->Branch("v13",&var[13],"v13/D");
  treeB->Branch("v14",&var[14],"v14/D");
  //treeB->Branch("v15",&var[15],"v15/D");
  treeB->Branch("v16",&var[16],"v16/D");
  //treeB->Branch("v17",&var[17],"v17/D");

  //  treeB->Branch("v18",&var[18],"v18/D");
  //  treeB->Branch("v19",&var[19],"v19/D");
  //  treeB->Branch("v20",&var[20],"v20/D");
  //  treeB->Branch("v21",&var[21],"v21/D");
  //  treeB->Branch("v22",&var[22],"v22/D");
  // treeB->Branch("v23",&var[23],"v23/D");
//   treeB->Branch("v24",&var[24],"v24/D");
//   treeB->Branch("v25",&var[25],"v25/D");
//   treeB->Branch("v26",&var[26],"v26/D");
//   treeB->Branch("v27",&var[27],"v27/D");

  
  cout<<" ****** Construction of signal and background  trees ***********"<<endl;  
  
  tB.fChain->SetBranchStatus("*",0);  // disable all branches
  tB.fChain->SetBranchStatus("B_mass",1); 
  tB.fChain->SetBranchStatus("B_J_mass",1); 
  tB.fChain->SetBranchStatus("B_Ks0_mass",1); 
  tB.fChain->SetBranchStatus("B_Ks0_charge1",1); 
  tB.fChain->SetBranchStatus("B_Ks0_charge2",1); 
  tB.fChain->SetBranchStatus("B_px",1); 
  tB.fChain->SetBranchStatus("B_py",1); 
  tB.fChain->SetBranchStatus("B_pz",1); 
  tB.fChain->SetBranchStatus("B_J_px1",1); 
  tB.fChain->SetBranchStatus("B_J_py1",1); 
  tB.fChain->SetBranchStatus("B_J_pz1",1); 
  tB.fChain->SetBranchStatus("B_Ks0_px1",1); 
  tB.fChain->SetBranchStatus("B_Ks0_py1",1); 
  tB.fChain->SetBranchStatus("B_Ks0_pz1",1); 
  tB.fChain->SetBranchStatus("B_J_px2",1); 
  tB.fChain->SetBranchStatus("B_J_py2",1); 
  tB.fChain->SetBranchStatus("B_J_pz2",1); 
  tB.fChain->SetBranchStatus("B_Ks0_px2",1); 
  tB.fChain->SetBranchStatus("B_Ks0_py2",1); 
  tB.fChain->SetBranchStatus("B_Ks0_pz2",1); 
  tB.fChain->SetBranchStatus("bctau2D",1); 
  tB.fChain->SetBranchStatus("bctau2DE",1); 
  tB.fChain->SetBranchStatus("B_chi2",1); 
  tB.fChain->SetBranchStatus("B_J_chi2",1); 
  tB.fChain->SetBranchStatus("B_Ks0_chi2",1); 
  tB.fChain->SetBranchStatus("nB",1); 
  

  //nentries = 10;
  Int_t nbytes = 0, nb = 0;
  for(Long64_t jentry=0; jentry<nentries;jentry++) 
    {
      Long64_t ientry = t.LoadTree(jentry);
      if (ientry < 0) break;
      nb = t.fChain->GetEntry(jentry);   nbytes += nb;

      for(int i=0;i<t.nB;i++)
	{

	  if(abs(t.B_Ks0_pId1->at(i))==211 && abs(t.B_Ks0_pId2->at(i))==211 && abs(t.B_Ks0_parentId1->at(i))==310 && abs(t.B_Ks0_parentId2->at(i))==310)
	    {

	      if(t.B_J_mass->at(i)<3.0 || t.B_J_mass->at(i)>3.2) continue;
	      if(t.B_Ks0_mass->at(i)<0.46 || t.B_Ks0_mass->at(i)>0.54) continue;
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
	      
	      if(t.bctau2D->at(i)<-1.0 || t.bctau2D->at(i)>1.0) continue;
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

	      treeS->Fill();
	    }

	}
    }
  Int_t tentries = treeS->GetEntries();
  cout<<" Entries in tree for signal : "<<tentries<<endl;

  //return;
 

  Int_t nTen = nentriesB/10;
  nb=0;nbytes=0;
  for(Long64_t jentry=0; jentry<nentriesB;jentry++) 
    {
      Long64_t ientry = tB.LoadTree(jentry);
      if (ientry < 0) break;
      nb = tB.fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%nTen==0) cout<<10*(jentry/nTen)<<"%-"<<flush;
      if(jentry==nentriesB-1) cout<<endl;

      for(int i=0;i<tB.nB;i++)
	{

	  if( (tB.B_mass->at(i)<5.05 || tB.B_mass->at(i)>5.25) && (tB.B_mass->at(i)<5.4 || tB.B_mass->at(i)>5.56) ) continue;

	  if(tB.B_J_mass->at(i)<3.0 || tB.B_J_mass->at(i)>3.2) continue;
	  if(tB.B_Ks0_mass->at(i)<0.46 || tB.B_Ks0_mass->at(i)>0.55) continue;
	  if(tB.B_Ks0_charge1->at(i)==tB.B_Ks0_charge2->at(i)) continue;

	  TVector3 mu1(tB.B_J_px1->at(i),tB.B_J_py1->at(i),tB.B_J_pz1->at(i));
	  TVector3 mu2(tB.B_J_px2->at(i),tB.B_J_py2->at(i),tB.B_J_pz2->at(i));	      	  
	  TVector3 pi1(tB.B_Ks0_px1->at(i),tB.B_Ks0_py1->at(i),tB.B_Ks0_pz1->at(i));
	  TVector3 pi2(tB.B_Ks0_px2->at(i),tB.B_Ks0_py2->at(i),tB.B_Ks0_pz2->at(i));	      	      
	  TVector3 mumu = mu1+mu2;
	  TVector3 pipi = pi1+pi2;
	      
	  TVector3 B(tB.B_px->at(i),tB.B_py->at(i),tB.B_pz->at(i));
	  
	  if(fabs(mu1.Eta())>2.5 || fabs(mu2.Eta())>2.5) continue;
	  //if(mu1.Pt()<3. || mu2.Pt()<3.) continue;
	  //if(pi1.Pt()<0.5 || pi2.Pt()<0.5) continue;	      
	  //if(mumu.Pt()<5.) continue;
	  //if(pipi.Pt()<1.6) continue;	      
	  //if(B.Pt()<10.) continue;
	  
	  if(tB.bctau2D->at(i)<-1.0 || tB.bctau2D->at(i)>1.) continue;
	  if(tB.B_Ks0_chi2->at(i)>26.) continue;  
	  if(tB.B_J_chi2->at(i)>26.) continue;  
	  if(tB.B_chi2->at(i)>26.) continue;  
	  
	  var[0] = pi1.Pt();
	  var[1] = pi1.Eta();
	  var[2] = pi1.Phi();
	  
	  var[3] = pi2.Pt();
	  var[4] = pi2.Eta();
	  var[5] = pi2.Phi();
	  
	  var[6] = pipi.Pt();
	  var[7] = pipi.Eta();
	  var[8] = pipi.Phi();
	  
	  var[9] = tB.B_Ks0_chi2->at(i);
	  var[10] = tB.B_J_chi2->at(i);
	  var[11] = tB.B_chi2->at(i);
	  
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
	  
	  //var[17] = tB.bctau2D->at(i)/tB.bctau2DE->at(i);
	  
	  treeB->Fill();
 
	}

    }

  Int_t tentriesB = treeB->GetEntries();
  cout<<" Entries in tree for background : "<<tentriesB<<endl;


  tentries = treeS->GetEntries();
  cout<<" Entries in tree for signal : "<<tentries<<endl;

  
   std::cout << "Start TMVAnalysis" << std::endl
             << "=================" << std::endl
             << std::endl;
   std::cout << "Running all standard methods may take about 10 minutes of running..." << std::endl;




   TMVA::Factory *factory = new TMVA::Factory( "BDTAnalysisv4-test", outputFile, Form("!V:!Silent:%sColor", gROOT->IsBatch()?"!":"") );
   //TMVA::Factory *factory = new TMVA::Factory( "MVAnalysis-test-new-bdt", outputFile, "" ) ;
   
   factory->AddVariable("v0", "P_{T}(K_{1}^{0})",'F');
   factory->AddVariable("v1", "#eta(K_{1}^{0})",  'F');
   factory->AddVariable("v2", "#phi(K_{1}^{0})", 'F');
   factory->AddVariable("v3", "P_{T}(K_{2}^{0})", 'F');
   //factory->AddVariable("v4", "#eta(K_{0})", 'F');
   factory->AddVariable("v5", "#phi(K_{2}^{0})",  'F');
   //factory->AddVariable("v6", "#eta(K_{0})", 'F');
   //factory->AddVariable("v7", "#eta(K_{0})", 'F');
   //factory->AddVariable("v8", "#eta(K_{0})", 'F');
   factory->AddVariable("v9", "#chi^{2}(K^{0}_{s})",  'F');
   factory->AddVariable("v10","#chi^{2}(J/ #phi)",  'F');
   factory->AddVariable("v11","#chi^{2}(B^{0})", 'F');
   //factory->AddVariable("v12", "#eta(K_{0})", 'F');
   factory->AddVariable("v13", "#Delta(B.K^{0}_{2})", 'F');
   factory->AddVariable("v14", "#Delta(K^{0}_{1}.K^{0}_{2})", 'F');
   //factory->AddVariable("v15", 'F');
   factory->AddVariable("v16","#Delta(B.#mu)",  'F');
   //  factory->AddVariable("v17", 'F');
   //  factory->AddVariable("v18", 'F');
   //  factory->AddVariable("v19", 'F');
   //  factory->AddVariable("v20", 'F');
   //  factory->AddVariable("v21", 'F');
   //  factory->AddVariable("v22", 'F');
   //  factory->AddVariable("v23", 'F');
   //  factory->AddVariable("v24", 'F');
   //  factory->AddVariable("v25", 'F');
   //  factory->AddVariable("v26", 'F');
   //  factory->AddVariable("v27", 'F');


   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;


   factory->AddSignalTree    ( treeS,     signalWeight     );
   factory->AddBackgroundTree( treeB, backgroundWeight );
   

   TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";

   //factory->PrepareTrainingAndTestTree( mycuts, mycutb, "SplitMode=Random:NormMode=NumEvents:!V" );
   factory->PrepareTrainingAndTestTree( mycuts, mycutb, "SplitMode=Random:NormMode=NumEvents:nTrain_Signal=1000:!V" );
   //factory->PrepareTrainingAndTestTree( mycuts, mycutb, "SplitMode=Random:NormMode=NumEvents:nTrain_Signal=3000:nTrain_Background=60000:!V" );

 
   // Boosted Decision Trees (second one with decorrelation)
     factory->BookMethod( TMVA::Types::kBDT, "BDT", 
			  //"!H:!V:NTrees=100:BoostType=AdaBoost:SeparationType=MisClassificationError:nCuts=-1:PruneMethod=CostComplexity:PruneStrength=-1:NEventsMin=25" );
			  "!H:!V:NTrees=200:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=-1:PruneMethod=CostComplexity:PruneStrength=-1:NEventsMin=25");
			  //		   "!H:!V:NTrees=500:BoostType=AdaBoost:SeparationType=GiniIndexWithLaplace:nCuts=30:PruneMethod=CostComplexity:PruneStrength=-1:NEventsMin=20" );
     //			   "!H:!V:NTrees=500:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=50:PruneMethod=CostComplexity:PruneStrength=4.5:NEventsMin=15" );

   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();    

   // --------------------------------------------------------------
   
   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAnalysis is done!" << std::endl;      

   delete factory;

   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVAGui( outfileName );
}
