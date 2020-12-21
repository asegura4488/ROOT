Double_t GetLimit(Double_t cl, Double_t b) {
  
  Double_t p0=1.0;
  Double_t sum=0.0;
  Int_t n0 = 0;
  while(p0 > 0.){
  p0=TMath::Exp(n0*TMath::Log(b)-b-TMath::LnGamma(n0+1.)); //likelihood
  Double_t muLimit=0.5*TMath::ChisquareQuantile(cl, 2*(n0+1)); 
  Double_t signal=muLimit-b;
  sum += p0*signal;
  n0++;
  } 

  return sum;
}

void GetExpectedLimit(){
  
  Double_t Data = 2.;
  Double_t bkg = 2.; 
  Double_t Signal = 5.;
  
  Int_t Ntoys = 5000;
  Double_t limit = 0.;

  TRandom3 *rnd = new TRandom3();
  
  TH1D *Pois = new TH1D("Pois","Pois", 100, 0., 200.); 
  Pois->Sumw2();
  TH1D *HSig = new TH1D("HSig","HSig", 100, 0., 10.); 
  HSig->Sumw2();
  TH1D *HMu = new TH1D("HMu","HMu", 300, 0., 3.); 
  HMu->Sumw2();

  for(Int_t i = 1; i <= Ntoys; i++){ 
        if(i % 1000 == 0) 
		std::cout << " Ntoys generated: " << i << " --- " << std::endl; 

  	Double_t ExBack = rnd->PoissonD(bkg);  
  	limit = GetLimit(0.95, ExBack);
    	Pois->Fill(ExBack);
        HSig->Fill(limit);   
	HMu->Fill(limit/Signal);
  	//std::cout << limit << std::endl;
  }
 
  // observed
  
  Double_t muLimit=0.5*TMath::ChisquareQuantile(0.95, 2*(Data+1)); 
  limit=muLimit-bkg;
  std::cout << " Observed limit " <<  limit << "  "  << limit/Signal << std::endl; 

  TF1 *gaus = new TF1("gaus", "gaus", 0, 3.);
  HMu->Fit(gaus, "R");
  Double_t Mean = gaus->GetParameter(1);
  Double_t sigma = gaus->GetParameter(2);
  Double_t plus_1sigma = Mean + sigma;
  Double_t plus_2sigma = Mean + 2*sigma;
  Double_t minus_1sigma = Mean - sigma;
  Double_t minus_2sigma = Mean - 2*sigma;
 
  std::cout << minus_2sigma << " " 
	    << minus_1sigma << " " 
	    << Mean << " " 
	    << plus_1sigma << " " 
	    << plus_2sigma << " " 	
	    << std::endl;

 // Pois->Draw();
 // HSig->Draw();
  HMu->Draw();
 // gaus->Draw();

}

int main(){
  GetExpectedLimit();
  return 0;
}
