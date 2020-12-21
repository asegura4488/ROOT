Double_t GetValue(Double_t n, Double_t b, Double_t mu){

  Double_t qm = 0.;
  Double_t mup = n - b; // This maximizes the likelihood function.
  if( mu >= mup ) qm = 2*(mu - n + b  - n*TMath::Log( (mu+b)/n )); 
  return qm;
}

void qm(){
  
  Double_t n0 = 160.;  // Esto es lo unica que cambia con el observed
  Double_t b = 140.;
  Double_t mu = 0.;
  Double_t muH = 0.;

  Double_t qm = 0.;
  Int_t Ntoys = 1e+4;
 
  TRandom3 *rnd = new TRandom3();

  TH1D *Eqm = new TH1D("Eqm","Eqm", 500, 0., 100.); 
  TH1D *qmH2 = new TH1D("qmH2","qmH2", 500, 0., 100.); 
  TH1D *h1 = new TH1D("h1","h1", 500, 0., 100.); 
  TH1D *h2 = new TH1D("h2","h2", 500, 0., 100.); 
  h1->SetFillColor(1);
  h1->SetLineColor(1);
  h2->SetFillColor(1);
  h2->SetLineColor(1);

  Eqm->Sumw2();
  qmH2->Sumw2();
  Eqm->SetLineColor(4);
  qmH2->SetLineColor(2);

  TH1D *U = new TH1D("U","U", 100, 0., 100.); 
 

  for(Int_t i = 1; i <= Ntoys; i++ ){
  if(i % 100000 == 0) 
		std::cout << " Ntoys generated: " << i << " --- " << std::endl; 
 	// background fluctuates following poisson distribution
	qm = GetValue(n0, rnd->PoissonD(b)+ rnd->Gaus(0.,0.01), mu);
        //qm = GetValue(rnd->PoissonD(n0)+ rnd->Gaus(0.,0.01), b, mu);
     	Eqm->Fill(qm);
 	qm = GetValue(n0, rnd->PoissonD(b)+ rnd->Gaus(0.,0.01), muH);
        //qm = GetValue(rnd->PoissonD(n0)+ rnd->Gaus(0.,0.01), b, muH); 
        qmH2->Fill(qm);
	U->Fill(rnd->Poisson(b));

  }  
  
  Eqm->SetStats(kFALSE);
  qmH2->SetStats(kFALSE);
  qmH2->GetXaxis()->SetTitle("q_{#mu}"); 
  Eqm->SetFillStyle(3001);
  Eqm->SetTitle("");
  Eqm->Scale(1.0/Eqm->Integral());
  qmH2->Scale(1.0/qmH2->Integral());
  qmH2->SetTitle("");
  Eqm->SetFillColor(4);
  qmH2->SetFillColor(2);
  qmH2->SetFillStyle(3001);

 // qmH2->Draw("HIST");
 // Eqm->Draw("HIST,same");
  
 
  TF1 *f1 = new TF1("f1","1.0/sqrt(2*TMath::Pi()*x)*TMath::Exp(-0.5*x)", 0.,20.);
 // f1->Draw("same");

  // for q upper limit
  Double_t Xmax;
  Double_t AXmax;
 
  Double_t Xmedian;
  Double_t XmedianH;
  Double_t qmax = 0.95;
  Double_t qmedian = 0.5;

  Eqm->GetQuantiles(1,&Xmax,&qmax);
  Eqm->GetQuantiles(1,&Xmedian,&qmedian);
  qmH2->GetQuantiles(1,&XmedianH,&qmedian);
  qmH2->GetQuantiles(1,&AXmax,&qmax);

  std::cout << " Median: " << Xmedian << " Qmax: " <<  Xmax <<std::endl; 
  std::cout << " Median H1: " << XmedianH << " Significance: " << TMath::Sqrt(XmedianH) << std::endl; 
  std::cout << " Qmax alternative H " << AXmax << std::endl; 

  double newmu = 0.;

  double upper = 0.;  

  double newcounter  = 21.;
  for(Int_t j = 0; j < 10000.;j++){
  newcounter += 0.01;
  upper = newcounter;
  
  for(Int_t i = 1; i <= 100000; i++ ){
 // if(i % 100000 == 0) 
		//std::cout << " Ntoys generated: " << i << " --- " << std::endl;  
                
                qm = GetValue(n0, rnd->PoissonD(b)+ rnd->Gaus(0.,0.01), newcounter);
                qmH2->Fill(qm);
                 
  }
  qmH2->Scale(1.0/qmH2->Integral());
 
  
  Double_t pvalue = 0.; 

  Int_t Nbins = qmH2->GetXaxis()->GetNbins();
  for (Int_t k = 0; k < Nbins; k++){
      Double_t lowedge = qmH2->GetXaxis()->GetBinLowEdge(k);
      Double_t Content = qmH2->GetBinContent(k);
    //  cout<< lowedge << " " << Xmedian << endl;
      if(lowedge < Xmedian) continue;
      else pvalue += Content;
  }

  cout << newcounter <<" "  << pvalue   << endl;

  if(1.0 - pvalue < 0.05){
  break;
  } 
  else qmH2->Reset(); 

  }
  cout << Xmedian << " " << newcounter/muH << " " << GetValue(n0, b, newcounter) << endl;
 
  qmH2->Draw("HIST");
  Eqm->Draw("HIST,same");

  Int_t Nbins = Eqm->GetXaxis()->GetNbins();

  h1->Fill(Xmedian);
  h1->Draw("HIST, same");
 

/*
  Double_t test = 0.;

  double counter2 = 15.;
  double cl = 1.;
  for(Int_t i = 0; i < 1000000.;i++){
  counter2 += 0.0001;
  if( abs(cl - 0.050) < 0.00001 || cl < 0.05) break;

  Double_t pvalue = 0.; 
  for (Int_t i = 0; i < Nbins; i++){
      Double_t lowedge = Eqm->GetXaxis()->GetBinLowEdge(i);
      Double_t Content = Eqm->GetBinContent(i);
      
      if(lowedge < GetValue(n0, b, counter2)) continue;
      else 
      pvalue += Content;
  }

  Double_t pvalue2 = 0.; 
  for (Int_t i = 0; i < Nbins; i++){
      Double_t lowedge = qmH2->GetXaxis()->GetBinLowEdge(i);
      Double_t Content = qmH2->GetBinContent(i);
      if(lowedge < GetValue(n0, b, counter2)) continue;
      else 
	pvalue2 += Content;
    }
  cl = pvalue/(pvalue2);
  //std::cout << GetValue(n0, b, counter2) <<  " "  << counter2 << " " << " p-value: " << pvalue <<  " " << " p-value2 "  << pvalue2 << " " << cl << std::endl;  // Mirar los valores Z de la distribución normal
  
  }

  Double_t qmobs = GetValue(n0, b, counter2); 
  h2->Fill(qmobs);
  h2->Draw("HIST, same");
*/
 double counter = 0.;
 double mutemp = 0.;
 double mufinal = 0.;
 double mufinalH = 0.;

 for(Int_t i = 0; i < 100000.;i++){
 counter += 0.001;
 if( abs(Xmax - mutemp) < 0.001 ) break;
 mutemp = GetValue(n0, b, counter); 
 }
 mufinal = counter;
 std::cout << " Final mu: " << mufinal << " " << mufinal/muH <<  Xmax   << std::endl;   
 

 counter = 0.;
 for(Int_t i = 0; i < 100000.;i++){
 counter += 0.001;
 if( abs(AXmax - mutemp) < 0.001 ) break;
 mutemp = GetValue(n0, b, counter); 
 }
 mufinalH = counter;
 std::cout << " Final mu: " << mufinalH << " " << mufinalH/muH <<  std::endl;   

}


int main(){

qm();
return 0;

}
