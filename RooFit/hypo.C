using namespace RooFit;

void hypo(){

  RooWorkspace *w = new RooWorkspace("w");
  w->factory("x[0,0,1]");
  w->factory("ex[0,0,1]");
  w->factory("Uniform::signal(x)");
  w->factory("Uniform::back(x)");
  w->factory("SUM::Model(S[50,0,100]*signal,B[100,0,200]*back)");
  //side band for 100 background events
  w->factory("Poisson::sideband(backEstimated[100], B)");
  w->factory("PROD::ModelConstraint(Model, sideband)");
  w->defineSet("S_","S");
  w->defineSet("B_","B");
  w->defineSet("ex_","ex");
  w->defineSet("Observable","x");
  w->Print();

  RooArgSet Parameters(*w->set("S_"), *w->set("B_"));
  RooArgSet NParameters(*w->set("ex_"));

  RooStats::ModelConfig *Alternative = new RooStats::ModelConfig("Alternative");
  Alternative->SetWorkspace(*w);
  Alternative->SetPdf( *w->pdf("ModelConstraint") );
 // Alternative->SetPdf( *w->pdf("priorNuisance") );
  Alternative->SetParametersOfInterest ( Parameters );
 // Alternative->SetNuisanceParameters ( NParameters );
  Alternative->SetObservables( *w->set("Observable") );
  w->loadSnapshot( "alternative" );
  Alternative->SetSnapshot( Parameters );

  RooStats::ModelConfig *Null = new RooStats::ModelConfig(*Alternative);
  w->loadSnapshot( "null" );
  Null->SetSnapshot( Parameters );



  RooDataSet *data = new RooDataSet("data","data",RooArgSet(*w->set("Observable")));
  RooDataSet *MC = new RooDataSet("MC","MC",RooArgSet(*w->set("Observable")));

  Int_t Ntoy = 20000000;
  data=w->pdf("ModelConstraint")->generate(*w->set("Observable"), Ntoy);
  MC=w->pdf("Model")->generate(*w->set("Observable"), Ntoy);

  // Likelihood
  RooStats::ProfileLikelihoodCalculator PLC(*data, *Alternative);
  PLC.SetAlternateParameters ( *Alternative->GetSnapshot() );
  PLC.SetNullParameters ( *Null->GetSnapshot() );  

  RooStats::HypoTestResult *plcresult=PLC.GetHypoTest();
  double significance = plcresult->Significance();

  std::cout << significance << std::endl;

  // Plotting

  RooPlot *massframe = w->var("x")->frame(RooFit::Name("massframe"),RooFit::Title("Model 1"),RooFit::Bins(20));
  RooPlot *massframe1 = w->var("x")->frame(RooFit::Name("massframe"),RooFit::Title("Model 1"),RooFit::Bins(20));
  w->pdf("Model")->plotOn(massframe, LineColor(2));
  w->pdf("ModelConstraint")->plotOn(massframe, LineColor(4));

  data->plotOn(massframe1, LineColor(1));
  MC->plotOn(massframe1, LineColor(2));

  TCanvas* c1 = new TCanvas("c1","Likelihood",900,500);
  c1->Divide(2,2);
  c1->cd(1);
  gPad->SetLeftMargin(0.15); 
  massframe->GetYaxis()->SetTitleOffset(1.6); 
  massframe->Draw();
  c1->cd(2);
  gPad->SetLeftMargin(0.15); 
  massframe1->Draw();
  c1->cd(3);
  gPad->SetLeftMargin(0.15); 


}


int main(){
hypo();
return 0; 
}
