void FastT(){

  TFile *file = TFile::Open("workspaces/chargino100_stau_75_lsp50.root");
  RooWorkspace *w = (RooWorkspace*) file->Get("combined");
  w->Print();

  RooAbsData *data = w->data("obsData"); 
  RooStats::ModelConfig* sbModel = (RooStats::ModelConfig*) w->obj("ModelConfig");
  RooStats::ModelConfig *bModel = (RooStats::ModelConfig*) w->obj("");
 

  if (!bModel ) {
      bModel = (RooStats::ModelConfig*) sbModel->Clone();
      bModel->SetName(TString("")+TString("B_only"));
      RooRealVar * var = dynamic_cast<RooRealVar*>(bModel->GetParametersOfInterest()->first());
      if (!var) return;
      double oldval = var->getVal();
      var->setVal(0);
      //bModel->SetSnapshot( RooArgSet(*var, *w->var("lumi"))  );
      bModel->SetSnapshot( RooArgSet(*var)  );
      var->setVal(oldval);
  }
  cout << bModel->GetName() << endl;
  
  RooRealVar *X = w->var("binWidth_obs_x_Channelchargino100_stau_75_lsp50_0");
  cout << X->getVal() << endl;
  
  RooStats::ProfileLikelihoodCalculator *plc = new RooStats::ProfileLikelihoodCalculator(*data, *sbModel);
  plc->SetConfidenceLevel(0.95);
  RooStats::LikelihoodInterval *interval_ = plc->GetInterval();
 
  RooStats::LikelihoodIntervalPlot *plot = new RooStats::LikelihoodIntervalPlot();
  plot->SetLikelihoodInterval(interval_);
  plot->SetNPoints(50);
  plot->SetMaximum(10.);
  plot->Draw();

  RooRealVar *Sigma = w->var("SigXsecOverSM");
  std::cout << interval_->LowerLimit(*Sigma) << " " << interval_->UpperLimit(*Sigma) << " CL: "<< interval_->ConfidenceLevel() <<std::endl;
 

}
