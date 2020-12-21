
void Frequentist(){

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


   RooStats::ProfileLikelihoodCalculator plCalc(*data,*mc);
   plCalc.SetConfidenceLevel(0.95);
   RooStats::LikelihoodInterval* interval = plCalc.GetInterval();

   RooRealVar *firstPOI = (RooRealVar *)mc->GetParametersOfInterest()->first();
   std::cout << " GetVal() " << firstPOI->getVal() << std::endl;

   double lowerLimit = interval->LowerLimit(*firstPOI);
   double upperLimit = interval->UpperLimit(*firstPOI);
   cout << lowerLimit << " " << upperLimit << endl;

   
   RooStats::LikelihoodIntervalPlot *plot = new RooStats::LikelihoodIntervalPlot(interval);
   plot->Draw("TF1");

    /*RooStats::HypoTestResult *result_;
    result_ = plCalc.GetHypoTest();
    double Significance_ = result_->Significance();
    cout << "Significance_ "<< Significance_ << endl;
*/
}

int main(){

  Frequentist();
  return 0;
   

}