TH1D* ScaleHisto(TH1D *h1, Double_t Events, Double_t xsec, Double_t lumi){

  TH1D* hnew;
  
  hnew =h1;
  hnew->Sumw2();
  
  Double_t scale_ = (1.0/Events) * xsec * lumi ; 
  hnew->Scale(scale_);

  return hnew;
}


void Normalizer(){

 
 TFile *f1 = TFile::Open("DY+Jets.root","READ");
 TH1D *h1 = (TH1D*)f1->Get("tau_cuts/tr_mass_tau");
 TH1D *Events = (TH1D*)f1->Get("tau_cuts/Nevents");
 Double_t Events_ = Events->GetBinContent(1); 
 h1->Draw();
 
 TH1D *HNorm;
 HNorm = ScaleHisto(h1, Events_, 43120., 100000); 
 HNorm->Draw();
 std::cout << " Expected events: " << HNorm->Integral() << endl; 

}

int main(){
Normalizer();
return 0;

}
