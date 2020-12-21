void test(){ 
 Int_t nh=5000;
   TH1D *h = new TH1D("h", 
      "Fitted gaussian with .95 conf.band", 100, -3, 3);
   h->FillRandom("gaus", nh);
   TF1 *f = new TF1("fgaus", "gaus", -3, 3);
   f->SetLineWidth(2);
   f->SetLineColor(1);
   f->SetLineStyle(2); 
   h->Fit(f, "Q");
   h->Draw("e3");
   
   //Create a histogram to hold the confidence intervals
   TH1D *hint = new TH1D("hint", 
      "Fitted gaussian with .95 conf.band", 400, -3, 3); // <---
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(h, 0.95);
   TH1D *hint1 = new TH1D("hint1", 
      "Fitted gaussian with .95 conf.band", 400, -3, 3); // <---
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint1, 0.68);
   //Now the "hint" histogram has the fitted function values as the 
   //bin contents and the confidence intervals as bin errors
   hint->SetStats(kFALSE);
   hint->SetFillColor(5);
   hint1->SetFillColor(3);
    
    h->SetFillColor(5);
    h->Draw("e3, same");
 //  hint->Draw("e3 same");
 //  hint1->Draw("e3 same");
   

  
}
