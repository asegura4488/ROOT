#include "RooRandom.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooPolynomial.h"
#include "RooArgSet.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooExtendPdf.h"
#include "RooConstVar.h"
#include "RooStats/HybridCalculatorOriginal.h"
#include "RooStats/HybridResult.h"
#include "RooStats/HybridPlot.h"

void hypo_1(){
 
 Int_t Ntoys = 5000;

 RooRandom::randomGenerator()->SetSeed(3007);
 //Observable
 RooRealVar mass("mass","mass",0.01,10);
 RooArgList observables(mass);

//Signal model
 RooRealVar lumi("lumi","luminosity",1);
 RooRealVar sr("sr","Cross Section Ratio", 3.8, 1., 50.);
 //RooFormulaVar ns("ns","1*sr*lumi",RooArgList(lumi,sr));

 //RooConstVar sigma("simga","simga", 1.0);
 //RooRealVar mean("mean","mean", 5.0 ,0., 10.0);
 RooGaussian SigPdf("SigPdf","",mass,RooFit::RooConst(3.0),RooFit::RooConst(0.8));  
 RooRealVar ns("ns","",20,0,300.);
 ns.setConstant(kTRUE);


  //Background only pdf
// RooRealVar slope("slope","slope",2);
// RooPolynomial BkgPdf("BkgPdf", "B-only model", mass,slope); 
 RooRealVar nb("nb","",40,0,300);
 RooPolynomial BkgPdf("BkgPdf", "", mass,RooFit::RooConst(0));
 RooExtendPdf Bkg_extPdf("BkgPdf","",BkgPdf,nb); 
 

 
 
 //Total Model
 RooAddPdf TotalPdf("TotalPdf","", RooArgList(SigPdf,BkgPdf),RooArgList(ns,nb));
 

 //Create data toys
 

// RooDataSet *MC = BkgPdf.generate(observables, RooFit::Extended());
 RooDataSet *data = TotalPdf.generate(observables,RooFit::Extended());
  
   RooGaussian bkg_yield_prior("bkg_yield_prior","",nb,RooFit::RooConst(nb.getVal()),RooFit::RooConst(10.));

   RooArgSet nuisance_parameters(nb); // variables to be integrated

   // prepare the calculator

   RooStats::HybridCalculatorOriginal Myhypo(*data, TotalPdf, Bkg_extPdf, &nuisance_parameters, &bkg_yield_prior);
   Myhypo.SetTestStatistic(1);
   Myhypo.SetNumberOfToys(Ntoys);
   Myhypo.UseNuisance(true);
   Myhypo.SetGenerateBinned(false);

   RooStats::HybridResult* myHybridResult = Myhypo.GetHypoTest();

   if (! myHybridResult) {
     std::cerr << "\nError returned from Hypothesis test" << std::endl;
     return;
   }

/*
   RooStats::HypoTestInverterOriginal myInverter(Myhypo,ns);
   myInverter.SetTestSize(0.10);
   myInverter.SetConfidenceLevel(0.95);
   myInverter.UseCLs(true);
   myInverter.RunAutoScan(3.,5,myInverter.Size()/2,0.005);  
*/
 

/*
   RooStats::HypoTestInverterResult* results = myInverter.GetInterval();

   
   RooStats::HypoTestInverterPlot *Plot = new RooStats::HypoTestInverterPlot("plot","HypoTest Scan Result",results);
   TGraphErrors* gr1 = Plot->MakePlot();


   double upperLimit = results->UpperLimit();
   double ulError = results->UpperLimitEstimatedError();
   double CL = 100*myInverter.ConfidenceLevel();
   std::cout << "The computed upper limit is: " << upperLimit << "+-" <<  ulError <<std::endl;
   std::cout << "CL_s: " << CL << std::endl;


   std::cout << " expected limit (median) " << results->GetExpectedUpperLimit(0) << std::endl;
   std::cout << " expected limit (-1 sig) " << results->GetExpectedUpperLimit(-1) << std::endl; 
   std::cout << " expected limit (+1 sig) " << results->GetExpectedUpperLimit(1) << std::endl; 
   std::cout << " expected limit (-2 sig) " << results->GetExpectedUpperLimit(-2) << std::endl;
   std::cout << " expected limit (+2 sig) " << results->GetExpectedUpperLimit(2) << std::endl;
*/
 //////////////////////////////////////////
 //Plotting pdf
 RooPlot *massframe = mass.frame(RooFit::Name("massframe"),RooFit::Title("Models"),RooFit::Bins(20));
 TotalPdf.plotOn(massframe, RooFit::LineColor(3), RooFit::LineStyle(kDashed));
 BkgPdf.plotOn(massframe, RooFit::LineColor(2));
 SigPdf.plotOn(massframe, RooFit::LineColor(1));
 //Ploting datasets
 RooPlot *dataframe = mass.frame(RooFit::Name("dataframe"),RooFit::Title("dataset"),RooFit::Bins(20)); 
// MC->plotOn(dataframe, RooFit::LineColor(4), RooFit::MarkerColor(4));
 data->plotOn(dataframe, RooFit::LineColor(1), RooFit::MarkerColor(1));


  TCanvas* c1 = new TCanvas("c1","Likelihood",900,500);
  c1->Divide(2,2);
  c1->cd(1);
  gPad->SetLeftMargin(0.15); 
  massframe->GetYaxis()->SetTitleOffset(1.6); 
  massframe->Draw();
  c1->cd(2);
  gPad->SetLeftMargin(0.15); 
  dataframe->GetYaxis()->SetTitleOffset(1.6); 
  dataframe->Draw();
  c1->cd(3);
  gPad->SetLeftMargin(0.15);  
//  Plot->Draw("CLb 2CL");
 // gr1->Draw("ALP, same");

}

int main(){
hypo_1();
return 0;
}
