using namespace RooFit;


void Model_comparison(){

 Int_t NData = 1000;
 Int_t Ntoys = 1000;

 gRandom = new TRandom3();
 gRandom->SetSeed(2);  

 RooRealVar mass("mass","mass[GeV]", -5.0, 5.0);   //RooRealVar = variable
 
 RooDataSet *data = new RooDataSet("data","data",RooArgSet(mass));
 RooDataSet *MC = new RooDataSet("MC","MC",RooArgSet(mass));

/*  
 RooArgSet *ValueP = new RooArgSet(mass); 

 for(UInt_t i = 0; i < NData; i++){
    mass = gRandom->Gaus(1., 1.);
  //  std::cout << ValueP->getRealValue("mass") << std::endl;
    data->add(RooArgSet(mass)); 
  }
*/
 //Other way
 RooRealVar mean_("mean_","mean_", 0.0 ,-2.0, 2.0);  // mean , min , max
 RooRealVar sigma_("sigma_","sigma_", 0.5, 0.,2.);
 RooGaussian G1("G1","G1",mass, mean_, sigma_);
 data = G1.generate(mass,NData); 

 RooPlot *massframe = mass.frame(Name("massframe"),Title("Model 1"),Bins(20));
 

 //creating work space
 RooWorkspace *w = new RooWorkspace();
 w->import(*data);
 w->factory("RooGaussian::Gaus_(mass_[-5.0,5.0], mean[1,-2,2], sigma[1.,0.,2.])");
 w->defineSet("mean_","mean");
 w->defineSet("sigma_", "sigma");
 w->defineSet("observable_", "mass_");
 MC=w->pdf("Gaus_")->generate(*w->set("observable_"),Ntoys);
 w->import(*MC);
 w->Print();
 
 //Fitting to data 
 w->pdf("Gaus_")->fitTo(*data); 


 
 //Model
 RooArgSet Parameters(*w->set("mean_"), *w->set("sigma_"));
 RooStats::ModelConfig *Mymodel = new RooStats::ModelConfig("Gaus(x|a0,a1)");
 Mymodel->SetWorkspace(*w);
 Mymodel->SetPdf( *w->pdf("Gaus_") );  
 Mymodel->SetParametersOfInterest ( Parameters );
 Mymodel->SetObservables( *w->set("observable_") );

 
 RooPlot *MCframe = w->var("mass_")->frame(Name("MCframe"),Title("Model 2"),Bins(20));
 
 MC->plotOn(MCframe, MarkerColor(4),LineColor(4),LineStyle(kDashed));
 w->pdf("Gaus_")->plotOn(MCframe, MarkerColor(3),LineColor(3),LineStyle(kDashed));
 
 w->data("G1Data")->plotOn(massframe, MarkerColor(2),LineColor(1));


  // ProfileLikelihoodCalculator
  //RooStats::ProfileLikelihoodCalculator PLC(*w->data("G1Data"), *Mymodel);
   RooStats::ProfileLikelihoodCalculator PLC(*w->data("Gaus_Data"), *Mymodel);

  PLC.SetConfidenceLevel(0.95);
  RooStats::LikelihoodInterval *interval = PLC.GetInterval();

  std::cout << "  The interval for mean is: [" << 
	interval->LowerLimit(*w->var("mean")) << " , " << 
	interval->UpperLimit(*w->var("mean"))  << " ] " <<
  std::endl;   

  std::cout << "  The interval for sigma is: [" << 
	interval->LowerLimit(*w->var("sigma")) << " , " << 
	interval->UpperLimit(*w->var("sigma"))  << " ] " <<
  std::endl; 
 
  RooStats::LikelihoodIntervalPlot Likeplot(interval);


  //Ploting 
  TCanvas* c1 = new TCanvas("c1","Likelihood",900,500);
  c1->Divide(2,2);
  c1->cd(1);
  gPad->SetLeftMargin(0.15); 
  massframe->GetYaxis()->SetTitleOffset(1.6); 
  MCframe->Draw();
  massframe->Draw("same");
  c1->cd(2);
  gPad->SetLeftMargin(0.15); 
  Likeplot.Draw();
  c1->cd(3);
  gPad->SetLeftMargin(0.15); 

}


int main(){
Model_comparison();
return 0;
}
