
void asym(){

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

   RooRealVar* poi1 = (RooRealVar*) mc->GetParametersOfInterest()->first();
   mc->SetSnapshot( *poi1  );
 
   RooStats::ModelConfig* bModel = (RooStats::ModelConfig*) mc->Clone("BonlyModel");
   RooRealVar* poi = (RooRealVar*) bModel->GetParametersOfInterest()->first();
   poi->setVal(0.);
   bModel->SetSnapshot( *poi  );

   RooStats::AsymptoticCalculator  asympCalc(*data, *bModel, *mc);
   asympCalc.SetOneSided(true);


   RooStats::HypoTestInverter inverter(asympCalc);
   inverter.SetConfidenceLevel(0.95);
   inverter.UseCLs(true);
   inverter.SetVerbose(true);
   inverter.SetFixedScan(40,0.0,1.0);
   RooStats::HypoTestInverterResult* result =  inverter.GetInterval();


   RooStats::HypoTestInverterPlot* plot = new RooStats::HypoTestInverterPlot("HTI_Result_Plot","HypoTest Scan Result",result);
   plot->Draw("CLb 2CL"); 

   RooStats::HypoTestResult *result_;
   result_ = asympCalc.GetHypoTest();
   double Significance_ = result_->Significance();

   double errorS = result_->SignificanceError();

   double Pvalue = result_->NullPValue();

   cout << 100*inverter.ConfidenceLevel() << "  upper limit : " << result->UpperLimit() << endl;
   std::cout << " expected limit (median) " << result->GetExpectedUpperLimit(0) << std::endl;

   cout << "Significance_ "<< Significance_ << "+-" << errorS <<  endl;
   cout << " Pvalue "  << Pvalue << " " << TMath::NormQuantile(1.-Pvalue) << endl;


}

int main(){

  asym();
  return 0;
   

}
