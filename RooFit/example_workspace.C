

void example_workspace(){

  Int_t Ntoys = 100;

  RooWorkspace *w = new RooWorkspace();
  w->factory("RooGaussian::Normal_(mass[-10,10], mean[-4,4], sigma[0.01, 2.])");
  w->defineSet("mean_","mean");
  w->defineSet("sigma_", "sigma");
  w->defineSet("observable_", "mass");
  w->Print();
 
  // specify components of model for statistical tool.
  RooArgSet Parameters(*w->set("mean_"), *w->set("sigma_"));
  RooStats::ModelConfig *Mymodel = new RooStats::ModelConfig("G(x|mean,1)");
  Mymodel->SetWorkspace(*w);
  Mymodel->SetPdf( *w->pdf("Normal_") );  
  Mymodel->SetParametersOfInterest ( Parameters );
  Mymodel->SetObservables( *w->set("observable_") );

  //Create toy dataset
  RooDataSet *data_ = w->pdf("Normal_")->generate(*w->set("observable_"),Ntoys);
  w->import(*data_);
 
  w->Print();
 
  RooPlot* massframe = w->var("mass")->frame();
  w->data("Normal_Data")->plotOn(massframe) ;
  w->pdf("Normal_")->plotOn(massframe);
  massframe->Draw();

  //Construction profile 
  RooNLLVar nll("nll", "nll", *w->pdf("Normal_"), *w->data("Normal_Data"));
  RooProfileLL pll("pll", "pll", nll, *w->var("mean"));
 // RooProfileLL plls("plls", "plls", nll, *w->var("sigma"));

  RooPlot* meanframe = w->var("mean")->frame();
  pll.plotOn(meanframe);

  RooPlot* sigmaframe = w->var("sigma")->frame();
 // plls.plotOn(sigmaframe);


  //Plotting

  TCanvas* c1 = new TCanvas("c1","Likelihood",900,500);
  c1->Divide(2,2);
  c1->cd(1);
  gPad->SetLeftMargin(0.15); 
  massframe->GetYaxis()->SetTitleOffset(1.6); 
  massframe->Draw();
  c1->cd(2);
  gPad->SetLeftMargin(0.15); 
  meanframe->GetYaxis()->SetTitleOffset(1.6); 
  meanframe->Draw();
  c1->cd(3);
  gPad->SetLeftMargin(0.15); 
  sigmaframe->GetYaxis()->SetTitleOffset(1.6); 
  sigmaframe->Draw();
  
}



int main(){
example_workspace();
return 0;
}
