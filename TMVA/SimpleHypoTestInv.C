using namespace RooStats;
using namespace RooFit;

void SimpleHypoTestInv( const char* infile =  "CountingModel.root", 
                        const char* workspaceName = "w",
                        const char* modelConfigName = "ModelConfig",
                        const char* dataName = "data" )
{
  TFile *file = TFile::Open(infile);
  if (!file) return;
  RooWorkspace* w = (RooWorkspace*) file->Get(workspaceName);
  RooStats::ModelConfig* mc = (RooStats::ModelConfig*) w->obj(modelConfigName);
  RooAbsData* data = w->data(dataName);
  ModelConfig*  sbModel = (RooStats::ModelConfig*) w->obj(modelConfigName);
  RooRealVar* poi = (RooRealVar*) sbModel->GetParametersOfInterest()->first();
  ModelConfig * bModel = (ModelConfig*) sbModel->Clone();
  bModel->SetName(TString(sbModel->GetName())+TString("_with_poi_0"));      
  poi->setVal(0);
  bModel->SetSnapshot( *poi  );
  FrequentistCalculator  fc(*data, *bModel, *sbModel);
  fc.SetToys(10000,5000);  
  AsymptoticCalculator  ac(*data, *bModel, *sbModel);
  ac.SetOneSided(true);  // for one-side tests (limits)
  AsymptoticCalculator::SetPrintLevel(-1);
  HypoTestInverter calc(ac);    // for asymptotic 
  calc.SetConfidenceLevel(0.95);
  bool useCLs = true;
  calc.UseCLs(useCLs);
  calc.SetVerbose(false);
  ToyMCSampler *toymcs = (ToyMCSampler*)calc.GetHypoTestCalculator()->GetTestStatSampler();
  ProfileLikelihoodTestStat profll(*sbModel->GetPdf());
  if (useCLs) profll.SetOneSided(true);
  toymcs->SetTestStatistic(&profll);
  if (!sbModel->GetPdf()->canBeExtended())
     toymcs->SetNEventsPerToy(1);
  int npoints = 50;  // number of points to scan
  double poimin = poi->getMin();
  double poimax = poi->getMax();
  poimin = 0; 
  poimax = 10;
  calc.SetFixedScan(npoints,poimin,poimax);
  HypoTestInverterResult * r = calc.GetInterval();
  double upperLimit = r->UpperLimit();


ofstream fout;fout.open("expected.log");
//  std::cout << "Expected upper limits, using the B (alternate) model : " << std::endl;
  std::cout << " expected limit (+2 sig) " << r->GetExpectedUpperLimit(2) << std::endl;
  std::cout << " expected limit (+1 sig) " << r->GetExpectedUpperLimit(1) << std::endl;
  std::cout << " expected limit (median) " << r->GetExpectedUpperLimit(0) << std::endl;
  std::cout << " expected limit (-1 sig) " << r->GetExpectedUpperLimit(-1) << std::endl;
  std::cout << " expected limit (-2 sig) " << r->GetExpectedUpperLimit(-2) << std::endl;

  fout << r->GetExpectedUpperLimit(2) <<"E-04"<<"  "<< r->GetExpectedUpperLimit(1) <<"E-04"<<"  "<< r->GetExpectedUpperLimit(0) <<"E-04"<<"  "<< r->GetExpectedUpperLimit(-1) <<"E-04"<<"  "<< r->GetExpectedUpperLimit(-2) <<"E-04"<< std::endl;


  HypoTestInverterPlot *plot = new HypoTestInverterPlot("HTI_Result_Plot","HypoTest Scan Result",r);
  auto c1 = new TCanvas(); 
  c1->SetLogy(false);

  plot->Draw("CLb 2CL");  // plot also CLb and CLs+b  

  const int n = r->ArraySize();
  if (n> 0 &&  r->GetResult(0)->GetNullDistribution() ) { 
     auto c2 = new TCanvas(); 
     if (n > 1) {
        int ny = TMath::CeilNint( sqrt(n) );
        int nx = TMath::CeilNint(double(n)/ny);
     }
     for (int i=0; i<n; i++) {
        if (n > 1) c2->cd(i+1);
        SamplingDistPlot * pl = plot->MakeTestStatPlot(i);
        pl->SetLogYaxis(true);
        pl->Draw();
     }
  }


}
