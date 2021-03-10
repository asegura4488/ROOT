
void CLs(){

   TFile *file = TFile::Open("workspace.root");


  RooWorkspace *w = (RooWorkspace *)file->Get("combined");
   if (!w) {
      cout << "workspace not found" << endl;
      return -1.0;
   }

   RooAbsData *data = w->data("obsData");
   RooStats::ModelConfig *mc = (RooStats::ModelConfig *)w->obj("ModelConfig");

   if (!data || !mc) {
      w->Print();
      cout << "data or ModelConfig was not found" << endl;
      return -1.0;
   }


   RooStats::ModelConfig* bModel = (RooStats::ModelConfig*) mc->Clone("BonlyModel");
   RooRealVar* poi = (RooRealVar*) bModel->GetParametersOfInterest()->first();
   poi->setVal(0.);
   bModel->SetSnapshot( *poi  );

   RooStats::FrequentistCalculator  freqCalc(*data, *bModel, *mc);
   RooStats::ProfileLikelihoodTestStat* plr = new RooStats::ProfileLikelihoodTestStat(*mc->GetPdf());
   plr->SetOneSided(true);
   RooStats::ToyMCSampler* toymcs = (RooStats::ToyMCSampler*) freqCalc.GetTestStatSampler();
   toymcs->SetTestStatistic(plr);

   
   if (!mc->GetPdf()->canBeExtended()) {
    toymcs->SetNEventsPerToy(1);
    }

   
    freqCalc.SetToys(3000,3000) ;

    RooStats::HypoTestInverter inverter(freqCalc);
    inverter.SetConfidenceLevel(0.95);
    inverter.UseCLs(true);
    inverter.SetVerbose(false);
    inverter.SetFixedScan(20.0,0.0,1.0);
    RooStats::HypoTestInverterResult* result =  inverter.GetInterval();

   
    RooStats::HypoTestInverterPlot* plot = new RooStats::HypoTestInverterPlot("HTI_Result_Plot","HypoTest Scan Result",result);
    plot->Draw("CLb 2CL");

   RooStats::HypoTestResult *result_;
   result_ = freqCalc.GetHypoTest();
   double Significance_ = result_->Significance();

    cout << "Significance_ "<< Significance_ << endl;

    cout << 100*inverter.ConfidenceLevel() << "%  upper limit : " << result->UpperLimit() << endl;
    cout << " expected limit (median) " << result->GetExpectedUpperLimit(0) << std::endl;


}

int main(){

  CLs();
  return 0;
   

}
