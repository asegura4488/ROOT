Double_t GetCLsSys(Double_t signal,Double_t bgr,
		   Double_t dBgrRel,Double_t dLumiRel,Int_t nObs) {
  /* calculate CLs for the given signal, background, errors
     and observed number of events, using Monte Carlo methods */
  TH1D *Hbkg;
  TH1D *Hsbkg;

  Int_t Nbins = 3000;
  Double_t Min = 0.;
  Double_t Max = 300.;

  
  Hbkg = new TH1D("Hbkg","", Nbins, Min, Max);
  Hsbkg = new TH1D("Hsbkg","", Nbins, Min, Max);
  

  TRandom *rnd=new TRandom3();
  Int_t nTry=300000;
  Double_t nexp_sb=0.0;
  Double_t nexp_b=0.0;
  Double_t lumi=1.0;
  for(Int_t iTry=0;iTry<nTry;iTry++) {
    /* get Luminosity from truncated Gaussian */
    Double_t l=lumi;
    if(dLumiRel>0.0) {
      do {
	l=rnd->Gaus(lumi,dLumiRel*lumi);
      } while(l<=0.0);
    }
    /* get Background from truncated Gaussian */
    Double_t b=bgr;
    if(dBgrRel>0.0) {
      do {
	b = rnd->Uniform(bgr*(1-dBgrRel), bgr*(1+dBgrRel)); 
        //b = rnd->Gaus(bgr,dBgrRel*bgr);
      } while(b<=0.0);
    }
   
   // cout << b <<  " "  << l << endl;
    // background-only experiments
    Int_t n_b=rnd->Poisson(l*b);
    // signal plus background experiment
    Int_t n_sb=rnd->Poisson(l*(signal+b));

    Hbkg->Fill(n_b);
    Hsbkg->Fill(n_sb);
    

    if(n_b<=nObs) nexp_b += 1.0;
    if(n_sb<=nObs) nexp_sb += 1.0;
  }
  delete rnd;
  Double_t cl_s=nexp_sb/nexp_b;
  Double_t dcl_s= TMath::Sqrt(nexp_sb+nexp_b*cl_s*cl_s)/nexp_b;
  Double_t dcl2 = TMath::Sqrt(1.+cl_s*cl_s)/nexp_b;
//  else {
    cout<<"CLSsys="<<cl_s<<" +/- "<<dcl_s<<  " " << dcl2 <<" for B="<<bgr<<" +/- "<<dBgrRel
	<<"%, L=1 +/- "<<dLumiRel<<"%, signal="<<signal<<"\n";
//  }

  Hsbkg->SetLineColor(2);
  Hsbkg->SetFillColor(2);

  Hbkg->Draw();
  Hsbkg->Draw("same");
  return cl_s;
}
