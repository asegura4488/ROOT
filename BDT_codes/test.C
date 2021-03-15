{
  using namespace RooFit;
  double bins[3] = {0,3,10};
  TH1D* hist = new TH1D("hist","hist",2,bins);
  hist->Sumw2();
  hist->Fill(0.5,1000);hist->Fill(7,100);
  RooRealVar x("x","x",0,80);  

  RooDataHist data(hist->GetName(), hist->GetTitle(), RooArgSet(x), Import(*hist, kFALSE));

  TH1* t = data.createHistogram("t",x); //makes the internal histogram

  //the last parameter in these calls is whether or not to correct for bin width
  RooHist *h_poissonErr_corrected = new RooHist(*t,0,1,RooAbsData::Poisson,1.,true);

  RooHist *h_poissonErr_uncorrected = new RooHist(*t,0,1,RooAbsData::Poisson,1.,false);  //THIS IS THE SAME AS 'corrected'... POISSON FORCES BIN WIDTH CORRECTION

  RooHist *h_sumw2Err_corrected = new RooHist(*t,0,1,RooAbsData::SumW2,1.,true);

  RooHist *h_sumw2Err_uncorrected = new RooHist(*t,0,1,RooAbsData::SumW2,1.,false);  //This is the same as the original histogram


  //plot all these RooHist
  h_poissonErr_corrected->SetMarkerColor(kBlack);h_poissonErr_corrected->SetLineColor(kBlack);
  h_poissonErr_uncorrected->SetMarkerColor(kRed);h_poissonErr_uncorrected->SetLineColor(kRed);
    h_sumw2Err_corrected->SetMarkerColor(kBlue);h_sumw2Err_corrected->SetLineColor(kBlue);
  h_sumw2Err_uncorrected->SetMarkerColor(kGreen);h_sumw2Err_uncorrected->SetLineColor(kGreen);
  
  RooPlot* frame = x.frame();

  frame->addPlotable(h_poissonErr_corrected,"P");
  frame->addPlotable(h_poissonErr_uncorrected,"P");
  frame->addPlotable(h_sumw2Err_corrected,"P");
  frame->addPlotable(h_sumw2Err_uncorrected,"P");
  frame->Draw();
}

