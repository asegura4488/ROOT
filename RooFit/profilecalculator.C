

void profilecalculator(){

  Int_t Ntoys = 1000;

  RooWorkspace *w = new RooWorkspace();
  w->factory("RooGaussian::Normal_(mass[-10,10], mean[-1,2], sigma[0.5, 1.0])");
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

  // ProfileLikelihoodCalculator
  RooStats::ProfileLikelihoodCalculator PLC(*w->data("Normal_Data"), *Mymodel);
  PLC.SetConfidenceLevel(0.95);
  RooStats::LikelihoodInterval *interval = PLC.GetInterval();

  std::cout << "  The interval is: [" << 
	interval->LowerLimit(*w->var("mean")) << " , " << 
	interval->UpperLimit(*w->var("mean"))  << " ] " <<
  std::endl;  

  // Set to 0 the value of mean
  
//  w->var("mean")->setVal(0.1);
  std::cout << " Is mean = " << 0.1 << 
         interval->IsInInterval(*w->var("mean")) << 
  std::endl;   

  std::cout << "  The interval is: [" << 
	interval->LowerLimit(*w->var("sigma")) << " , " << 
	interval->UpperLimit(*w->var("sigma"))  << " ] " <<
  std::endl; 

  //markov chain calculator  // esto debe ser revisado.

  RooStats::MCMCCalculator MCC(*w->data("Normal_Data"), *Mymodel);
  MCC.SetConfidenceLevel(0.95);
  
  //Special
  MCC.SetNumBins(100);
  //MCC.SetIntervalType(RooStats::MCMCInterval::kShortest);
  //MCC.SetLeftSideTailFraction(0.);
  MCC.SetNumBurnInSteps(10);
  MCC.SetNumIters(100000);

  RooStats::MCMCInterval *intervalMC = MCC.GetInterval();
   std::cout << "  The markov interval is: [" << 
	intervalMC->LowerLimit(*w->var("mean")) << " , " << 
	intervalMC->UpperLimit(*w->var("mean"))  << " ] " <<
   std::endl;  
  
   std::cout << "  The markov interval is: [" << 
	intervalMC->LowerLimit(*w->var("sigma")) << " , " << 
	intervalMC->UpperLimit(*w->var("sigma"))  << " ] " <<
   std::endl; 


  RooStats::LikelihoodIntervalPlot Likeplot(interval);
  RooStats::MCMCIntervalPlot *MCplot = new RooStats::MCMCIntervalPlot(*intervalMC);
  //Plotting

  TCanvas* c1 = new TCanvas("c1","Likelihood",900,500);
  c1->Divide(2,2);
  c1->cd(1);
  gPad->SetLeftMargin(0.15); 
  massframe->GetYaxis()->SetTitleOffset(1.6); 
  massframe->Draw();
  c1->cd(2);
  gPad->SetLeftMargin(0.15); 
  Likeplot.Draw();
  MCplot->SetLineColor(kBlue);
  MCplot->Draw("same");
  c1->cd(3);
  gPad->SetLeftMargin(0.15); 
 // sigmaframe->GetYaxis()->SetTitleOffset(1.6); 
 //  sigmaframe->Draw();
  
}



int main(){
profilecalculator();
return 0;
}
