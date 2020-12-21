void test(){

  TFile *file = TFile::Open("workspaces/chargino100_stau_75_lsp50.root");
  RooWorkspace *w = (RooWorkspace*) file->Get("combined");
  w->Print();

  RooAbsData* data = w->data("obsData"); 
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
  double poiValue = -1.;
    if (!sbModel->GetSnapshot() || poiValue > 0) {
      Info("StandardHypoTestDemo","Model %s has no snapshot  - make one using model poi",sbModel->GetName());
      RooRealVar * var = dynamic_cast<RooRealVar*>(sbModel->GetParametersOfInterest()->first());
      if (!var) return;
      double oldval = var->getVal();
      if (poiValue > 0)  var->setVal(poiValue);
      //sbModel->SetSnapshot( RooArgSet(*var, *w->var("lumi") ) );
      sbModel->SetSnapshot( RooArgSet(*var) );
      if (poiValue > 0) var->setVal(oldval);
      //sbModel->SetSnapshot( *sbModel->GetParametersOfInterest() );
   }

  int nEvents = data->numEntries();
  std::cout << nEvents << std::endl;

  RooStats::SimpleLikelihoodRatioTestStat *slrts = new RooStats::SimpleLikelihoodRatioTestStat(*bModel->GetPdf(), *sbModel->GetPdf());
  RooArgSet nullParams(*bModel->GetSnapshot());
  RooStats::ProfileLikelihoodTestStat * profll = new RooStats::ProfileLikelihoodTestStat(*bModel->GetPdf());

  RooStats::RatioOfProfiledLikelihoodsTestStat *
      ropl = new RooStats::RatioOfProfiledLikelihoodsTestStat(*bModel->GetPdf(), *sbModel->GetPdf(), sbModel->GetSnapshot());
   ropl->SetSubtractMLE(false);
  profll->SetPrintLevel(0);


  RooStats::HypoTestCalculatorGeneric *hypoCalc = new RooStats::FrequentistCalculator(*data, *sbModel, *bModel);
  ((RooStats::FrequentistCalculator*)hypoCalc)->SetToys(100, 2); 

  RooStats::HypoTestResult *htr = hypoCalc->GetHypoTest();
  htr->SetPValueIsRightTail(true);
  htr->SetBackgroundAsAlt(false);
  htr->Print();
  std::cout << htr->NullPValue() << " " << 
               htr->Significance() << " " <<
               htr->CLb() << " " <<
	       htr->CLsplusb() << " " << 
	       htr->CLs() <<
  std::endl;

  RooStats::ToyMCSampler * sampler = (RooStats::ToyMCSampler *)hypoCalc->GetTestStatSampler();
  
  
  sampler->SetNEventsPerToy(nEvents);
  sampler->SetGenerateBinned(true);
  sampler->SetTestStatistic(slrts);


  RooStats::HypoTestPlot *plot = new RooStats::HypoTestPlot(*htr,100);
  plot->SetLogYaxis(true);
  plot->Draw();
}
