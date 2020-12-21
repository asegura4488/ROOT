using namespace RooFit;

void firstLikelihood(){
  
  RooWorkspace w("myWorkspace", true);
  w.factory("Gaussian::g1(mass[-20.0,20.0],mean[0,-10.,10.],width[2,2,5])");
  w.factory("Gaussian::g2(mass,mean2[3,-10.,10.],width2[1,0,6])");
  
  RooRealVar *mass = w.var("mass");
  
  //Adding models
  w.factory("SUM::model(frac[0.3,0,1]*g1,g2)");
  auto model = w.pdf("model"); 
  RooRealVar *frac = w.var("frac");
  RooRealVar *sigma2 = w.var("width2");
  
  w.Print();
  
  
  //Generate pseudo-data
  RooDataSet *data = model->generate(*mass, 5000);
  // Create likelihood function
  RooAbsReal* nll = model->createNLL(*data, NumCPU(4));
  // Minimize likelihood
  RooMinuit(*nll).migrad();
  
  
  
  RooPlot *frac_frame = frac->frame(Bins(10), Range(0.01,0.95));
  RooPlot *sigma_frame = sigma2->frame(Bins(10), Range(0.01,5.95));
  RooPlot *massframe = mass->frame(Bins(20));
  RooPlot *massframeP = mass->frame(Bins(20));
  
  
  nll->plotOn(frac_frame, ShiftToZero(), LineColor(kBlue));
  
  RooAbsReal *pll_frac = nll->createProfile(*frac);
  RooAbsReal *pll_sigma2 = nll->createProfile(*sigma2); 
  
  
  pll_frac->plotOn(frac_frame, LineColor(kRed));
  pll_sigma2->plotOn(sigma_frame, LineColor(kGreen));
  
  model->plotOn(massframe, LineColor(kBlack));
  model->plotOn(massframe, Components(*w.pdf("g1")), LineStyle(kDashed), LineColor(kRed));
  model->plotOn(massframe, Components(*w.pdf("g2")), LineStyle(kDashed), LineColor(kBlue));
  //PseudoData
  data->plotOn(massframeP);
  
  TCanvas* c1 = new TCanvas("c1","Likelihood",800,800);
  c1->Divide(2,2);
  c1->cd(1); 
  gPad->SetLeftMargin(0.15); 
  frac_frame->GetYaxis()->SetTitleOffset(1.6); 
  frac_frame->Draw();
  c1->cd(2); 
  gPad->SetLeftMargin(0.15); 
  sigma_frame->GetYaxis()->SetTitleOffset(1.6); 
  sigma_frame->Draw();
  c1->cd(3); 
  gPad->SetLeftMargin(0.15); 
  massframe->GetYaxis()->SetTitleOffset(1.6); 
  massframe->Draw();
  c1->cd(4); 
  gPad->SetLeftMargin(0.15); 
  massframeP->GetYaxis()->SetTitleOffset(1.6); 
  massframeP->Draw();
  
}

int main(){	
  firstLikelihood();
  return 0;
}
