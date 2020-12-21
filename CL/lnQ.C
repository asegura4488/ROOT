std::map<Double_t, Double_t> MAP;
std::map<Double_t, Double_t> MAPmu;

TH1D *OnlyBack;
TH1D *SplusBack;
TH1D *Observed;
TRandom3 *rnd;

void PlotHistos(TH1D *h1, Double_t index){
  
  if(h1->Integral() != 0.) h1->Scale(1.0/h1->Integral());
  else std::cout << " --- fail normalization --- " << std::endl;

  if(index == 0) h1->Draw("HIST");
  else h1->Draw("HIST,same");

}

void SetHistos(TH1D **h1, Double_t index){

  (*h1)->SetStats(kFALSE);
  (*h1)->Sumw2();
  (*h1)->SetLineColor(index);
  (*h1)->SetFillColor(index); 
  (*h1)->SetFillStyle(3001);
  (*h1)->GetXaxis()->SetTitle("-2ln(Q)");

}

Double_t GetVal(Double_t s, Double_t b, Double_t n){
  
  Double_t estimator = 0.;
 
  if(b != 0.) estimator =  2*(s - n*TMath::Log(1+s/b)) ;
  else 
    exit(1); 
  
  return estimator;
 
}

Double_t pvalue(TH1D *h1, Double_t obs){
  
  Int_t Nbins = h1->GetXaxis()->GetNbins();
 
  Double_t integral = 0.;   
  for (int b = 1; b <= Nbins; b++ ){

   if(h1->GetXaxis()->GetBinLowEdge(b) >= obs){
       // std::cout <<  h1->GetXaxis()->GetBinLowEdge(b) << " " <<  obs << " " << integral << endl;
	integral += h1->GetBinContent(b);
   }
    
  }
  return integral;
}



Double_t  ln2Q(Double_t s_){

  bool observelimit = true;

  Double_t n = 100.;
  Double_t b = 90.;
  Double_t s = s_;

  Int_t Ntoys = 1e+5;


  Double_t ObslnQ = 0.;
  if(observelimit) ObslnQ = GetVal(s,b,n);
  else ObslnQ = GetVal(s,b,b);
 
  rnd->SetSeed(36000);

  for(Int_t i = 1; i <= Ntoys; i++){ 
    //    if(i % 10000 == 0) 
	//	std::cout << " Ntoys generated: " << i << " --- " << std::endl; 
 // ; 
  
  //Double_t trial = rnd->Poisson(b);
  Double_t trial = rnd->PoissonD(b);
 // cout << trial << endl;
  trial += rnd->Gaus(0., 2.5);
 // cout << trial << endl;

 // cout << trial << endl;
  if(observelimit){  
  OnlyBack->Fill(GetVal(s,trial,n));
  SplusBack->Fill(GetVal(s,trial,s+b));

  } else{
  OnlyBack->Fill(GetVal(s,trial,b));
  SplusBack->Fill(GetVal(s,trial,s+b));

  }

  Observed->Fill(ObslnQ);
//  Observed->Fill(GetVal(s,b,n));

  }

  OnlyBack->Scale(1.0/OnlyBack->Integral());
  SplusBack->Scale(1.0/SplusBack->Integral());
  Observed->Scale(1.0/Observed->Integral());

 // std::cout << " Signal Test: " << s <<  " Observed: " << ObslnQ << std::endl; 

  Double_t clb = pvalue(OnlyBack, ObslnQ);
  Double_t clsb = pvalue(SplusBack, ObslnQ);

  Double_t CL = clsb/clb;

 // std::cout << clb << " "  << clsb << " CL " << CL << std::endl;


  return CL;
}

void lnQ(){

 OnlyBack = new TH1D("OnlyBack","", 1000, -50., 50.); 
 SplusBack = new TH1D("SplusBack","",1000, -50., 50.); 
 Observed = new TH1D("Observed","",1000, -50., 50.); 

 rnd = new TRandom3();

 SetHistos(&OnlyBack, 4);
 SetHistos(&SplusBack, 2);
 SetHistos(&Observed, 1);


 Double_t stheorico = 10.;

 Double_t s=20.;
 for(int i = 0; i < 1000; i++){
 OnlyBack->Reset();
 SplusBack->Reset(); 
 Observed->Reset();	
// if(i != 0) continue;
 s += 0.0001;
 if(ln2Q(s) > 0.051) s += 1.0;

 cout << s <<" " << ln2Q(s) << endl;
// MAP[s] = ln2Q(s); 
 MAPmu[s/stheorico] = ln2Q(s); 
 //cout << OnlyBack->GetEntries() << endl;

 if(abs(ln2Q(s) - 0.050) < 0.0001) break;
 if(ln2Q(s) <= 0.05) break; 

 }
 
 
 for(auto&it : MAP){ 
 	std:cout << it.first << " " << it.second << std::endl;}

 for(auto&iter : MAPmu){ 
	std::cout << iter.first << " " << iter.second << std::endl;}

  PlotHistos(OnlyBack, 0);
  PlotHistos(SplusBack, 1);
  PlotHistos(Observed, 2);
 
}


int main(){

 lnQ();
  

return 0;

}
