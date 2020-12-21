#include <iostream>
#include  <vector>
#include "TVector3.h"
#include "TFile.h"
#include "DataBd.C"
#include "TTree.h"
#include "DataWork.C"
#include "TMVA/Reader.h"
#include "TMVA/MethodBDT.h"


{
//------ Plotting
 using namespace RooFit;
 using namespace std;


gStyle->SetCanvasColor(kWhite);     // background is no longer mouse-dropping white
gStyle->SetPalette(1,0);            // blue to red false color palette. Use 9 for b/w
gStyle->SetCanvasBorderMode(0);     // turn off canvas borders
gStyle->SetPadBorderMode(0);
gStyle->SetFrameBorderMode(0);
gStyle->SetFrameBorderSize(0);
gStyle->SetOptTitle(0);
gStyle->SetLineWidth(1.0);
//gStyle->SetMarkerSize(0.5);
gStyle->SetMarkerSize(1.4);
//gStyle->SetLabelSize(0,"X");
//gStyle->SetLabelSize(0,"Y");
//gStyle->SetTitleSize(0,"Y");

//---- Fit and global options

 TCanvas *c1 = new TCanvas("c1","",550,550);


 Double_t Mmin = 5.2;
 Double_t Mmax = 5.5;


 TChain *ch = new TChain("treeS","");
 ch->Add("ROOTSlimDataBd-BDT.root");

 gROOT->ProcessLine(".L DataWork.C+");
 TTree *tree = (TTree*) ch;
 DataWork t(tree);

 Long64_t nentries = t.fChain->GetEntries();

 cout<<" Entries : "<<nentries<<endl;
  
 //------------------------------
 RooRealVar M("M","Invariant Mass (GeV/c^{2})",Mmin,Mmax);

 RooDataSet data("data","data",RooArgSet(M));

 Int_t nTen = nentries/10;
 TLorentzVector Jpsi,Xi;
 Int_t k=0;
 Int_t nbytes = 0, nb = 0;
 for(Long64_t jentry=0; jentry<nentries;jentry++) 
    {
      Long64_t ientry = t.LoadTree(jentry);
      if (ientry < 0) break;
      nb = t.fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%nTen==0) cout<<10*(jentry/nTen)<<"%-"<<flush;
      if(jentry==nentries-1) cout<<endl;

      //Mass windows cuts
      if(t.mB<=Mmin || t.mB>=Mmax) continue;
     if(t.Bdl<0.05) continue;
      //if(t.mf0<=0.95 || t.mf0>=1.05) continue;
      if(t.Bpt<=18.) continue;
      if(t.bdt<=-0.7) continue;

      M=t.mB;

      data.add(RooArgSet(M)); 

    }

cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
data.Print("v");

//return;
//dataWS.Print("v");



//---- Mass model -------
Double_t supM = Mmax;
Double_t infM = Mmin;
Double_t mi = supM - infM;
Double_t m1m2 = supM*supM - infM*infM;
Double_t m3 = supM*supM*supM - infM*infM*infM;

//RooPlot* Mframe = M.frame(infM,supM,25);

//data.plotOn(Mframe,DataError(RooAbsData::SumW2));
//Mframe->Draw();

//return;

 RooRealVar a0("a0","a0",-20.0,20.0);
 RooRealVar a1("a1","a1",-20.0,20.0);
 RooRealVar a2("a2","a2",-20.0,20.0);
RooRealVar a3("a3","a3",-20.0,20.0);
 //RooPolynomial bkg1("bkg1","Background",M,RooArgList(a0,a1,a2)); 
 RooPolynomial bkg1("bkg1","Background",M,RooArgList(a0,a1)); 

 RooRealVar mean("mean"," Mass mean",5.2,5.4,"GeV");
 RooRealVar width("width"," Mass width",0.01324,0.01324,"GeV");
 RooGaussian Sig("Sig"," Signal PDF",M,mean,width);

 RooRealVar meanB("meanB"," Mass mean B",5.2,5.5,"GeV");
 RooRealVar widthB("widthB"," Mass width B",0.0,0.2,"GeV");
 RooGaussian SigB("SigB"," Signal PDF B",M,meanB,widthB);

 RooRealVar meanB2("meanB2"," Mass mean B2",5.2,5.5,"GeV");
 RooRealVar widthB2("widthB2"," Mass width B2",0.0103,0.0103,"GeV");
 RooGaussian SigB2("SigB2"," Signal PDF B2",M,meanB2,widthB2);


 RooRealVar Ns("Ns","Ns",0.,100000);
 RooRealVar Nbs("Nbs","Nbs",0.,100000);
 RooRealVar Nb("Nb","Nb",0.,100000);
 RooRealVar fs("fs","fs",0.,1.);
 RooRealVar fs2("fs2","fs2",0.,1.);
 
RooRealVar fb("fb","fb",0.,1.);

 //RooRealVar c("c","c",1000.0,1000.0);
 //c.setVal(-2.0);
 //RooExponential expB("expB","Exp. Background",M,c);

 //RooAddPdf bkg("Bkg model","Bkg model",RooArgList(expB,bkg1),RooArgList(fb));
 //RooAddPdf SignalBd("Signal model","Signal model",RooArgList(Sig,SigB),RooArgList(fs));
 //RooAddPdf SignalBd("Signal model","Signal model",RooArgList(Sig,SigB),RooArgList(N));
 //RooAddPdf Signal("Signal model","Signal model",RooArgList(SignalBd,SigB2),RooArgList(fs2));
 //RooAddPdf Signal("Signal model","Signal model",RooArgList(Sig,SigB2),RooArgList(fs2));

 //RooAddPdf MassModel("MassModel","MassModel",RooArgList(Sig,expB),RooArgList(Ns,Nb));
 //RooAddPdf MassModel("MassModel","MassModel",RooArgList(Sig,bkg),RooArgList(Ns,Nb));
 //RooAddPdf MassModel("MassModel","MassModel",RooArgList(Signal,bkg1),RooArgList(Ns,Nb));
RooAddPdf MassModel("MassModel","MassModel",RooArgList(Sig,SigB2,bkg1),RooArgList(Ns,Nbs,Nb));

 //RooAddPdf sigb("sigb","sigb",RooArgList(SigB2,Sig),fs);
 //RooAddPdf MassModel("MassModel","MassModel",RooArgList(bkg1,sigb),fb,kTRUE);                 // Este es el bueno


//-------------- End Mass model definition ---------------------------


//------------ Fit procedure -------------------

//Setting Mass model parameter
 fs.setVal(0.8);
 fs2.setVal(0.95);
 Ns.setVal(10000);
 Nbs.setVal(30);
 Nb.setVal(100);
 mean.setVal(5.3);
 width.setVal(0.02);
 meanB.setVal(5.2);
 widthB.setVal(0.04);
 meanB2.setVal(5.3);
 meanB2.setConstant(kTRUE);
 widthB2.setVal(0.02);
 //widthB2.setConstant(kTRUE);
 a0.setVal(0.);
 a1.setVal(0.);
 a2.setVal(0.);
 a3.setVal(0.);
 
 RooFitResult* fitres = MassModel.fitTo(data,Extended(),Minos(kFALSE),Save(kTRUE));
 
meanB2.setConstant(kFALSE);
 
 fitres = MassModel.fitTo(data,Extended(),Minos(kFALSE),Save(kTRUE));

//Calculating S/srt(B)
Double_t mVal = mean.getVal();
Double_t wVal = width.getVal();
Double_t ns = 3.;
Double_t xmin = mVal - ns*wVal;
Double_t xmax = mVal + ns*wVal;

TString cut;
cut="M>";
cut+=xmin;
cut+=" && ";
cut+="M<";
cut+=xmax;

cout<<cut<<endl;
RooDataSet* dataSignal = (RooDataSet*)data.reduce(cut);

Int_t nevt = dataSignal->numEntries();

cout<<" --> "<<nevt<<endl;

Double_t NsVal = Ns.getVal();
Double_t NsEVal = Ns.getError();


cout<<" Results : "<<endl;
Nb.Print();
Ns.Print();

//dataSignal->Print();
//RooPlot* Mframe = M.frame(infM,supM,28);
//RooPlot* Mframe = M.frame(infM,supM,44);


RooPlot* Mframe = M.frame(infM,supM,25);
//RooPlot* Mframe = M.frame(infM,supM,22);
//RooPlot* Mframe = M.frame(infM,supM,20);
//RooPlot* Mframe = M.frame(5.11,5.8,23);
data.plotOn(Mframe,DataError(RooAbsData::SumW2));
MassModel.plotOn(Mframe);
// Double_t chi2tmp = Mframe->chiSquare();
MassModel.plotOn(Mframe,DrawOption("F"),FillColor(2));
//MassModel.plotOn(Mframe,Components(bkg),DrawOption("F"),FillColor(18));
MassModel.plotOn(Mframe,Components(bkg1),DrawOption("F"),FillColor(20));
data.plotOn(Mframe,DataError(RooAbsData::SumW2));
MassModel.plotOn(Mframe);
//dataWS->plotOn(Mframe,DataError(RooAbsData::SumW2));
//dataJS->plotOn(Mframe,DataError(RooAbsData::SumW2));
//dataXiS->plotOn(Mframe,DataError(RooAbsData::SumW2));
//dataAllS->plotOn(Mframe,DataError(RooAbsData::SumW2));
MassModel.paramOn(Mframe, Format("NELU", AutoPrecision(2)));
Mframe->Draw();
//chi2tmp = Mframe->chiSquare();

//fitres->Print("v");

//return;





//Calculating S/srt(B)
mVal = mean.getVal();
wVal = width.getVal();
ns = 3.;
xmin = mVal - ns*wVal;
xmax = mVal + ns*wVal;

//TString cut;
cut="M>";
cut+=xmin;
cut+=" && ";
cut+="M<";
cut+=xmax;

cout<<cut<<endl;
//RooDataSet* dataSignal = (RooDataSet*)data.reduce(cut);

nevt = dataSignal->numEntries();
cout<<" --> "<<nevt<<endl;

 NsVal = Ns.getVal();
 NsEVal = Ns.getError();

fitres->Print("v");

cout<<" Results : "<<endl;
Nb.Print();
Ns.Print();

dataSignal->Print();


  Double_t minNLLAll = fitres->minNll();
  mean.setConstant(kTRUE);
  width.setConstant(kTRUE);
  Nbs.setVal(0.0);
  Nbs.setConstant(kTRUE);
  meanB2.setConstant(kTRUE);
  widthB2.setConstant(kTRUE);
  a0.setConstant(kTRUE);
  a1.setConstant(kTRUE);
  Ns.setConstant(kTRUE);
  Nb.setConstant(kTRUE);
  RooFitResult* fitres1 = MassModel.fitTo(data,Extended(),Minos(kFALSE),Save(kTRUE));
  Double_t minNLLBkg = fitres1->minNll();


fitres->Print("v");
 
fitres1->Print("v");

  Double_t L1 = TMath::Exp(minNLLBkg);
  Double_t L2 = TMath::Exp(minNLLAll);
  cout<<endl;
  cout<<" Likelihood values : "<<minNLLAll<<"  "<<minNLLBkg<<endl;
  cout<<" Likelihood ratio : "<<minNLLBkg - minNLLAll<<endl;
  cout<<" 1/LR : "<<1/TMath::Exp(minNLLBkg - minNLLAll)<<endl;
  
  Double_t sigLL = sqrt(2.*(minNLLBkg - minNLLAll));
  cout<<" sfsdfsdfsddsd Significance from LR : "<<sigLL<<endl;


Double_t significance = NsVal/sqrt(1.*nevt - NsVal);
Double_t significance1 = NsVal/sqrt(1.*nevt);


cout<<" Significance S/sqrt(B):   "<<significance<<endl;
cout<<" Significance S/sqrt(S+B): "<<significance1<<endl;
//cout<<" Plot chi2 :               "<<chi2tmp<<endl;
//cout<<" Probability :             "<<TMath::Prob(16.*chi2tmp,16)<<endl;
cout<<" Number of events :        "<<NsVal<<" +/- "<<NsEVal<<endl;

}//End analysis
