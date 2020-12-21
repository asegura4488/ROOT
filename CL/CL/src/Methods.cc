#include "../include/Methods.h"

Methods::Methods(){
}

Methods::Methods(Double_t Ndata_, Double_t Nbkg_, Double_t Nsignal_): 
Ndata(Ndata_), Nbkg(Nbkg_), Nsignal(Nsignal_){
rnd = new TRandom3();


  Int_t Nbins = 20000;
  Double_t Min = -1000.;
  Double_t Max = 1000.;

  Hbkg = new TH1D("Hbkg","", Nbins, Min, Max);
  Hsbkg = new TH1D("Hsbkg","", Nbins, Min, Max);
  HObs = new TH1D("HObs","", Nbins, Min, Max);

  Nbins = 2000;
  Hq0b = new TH1D("Hq0b","", Nbins, 0, 20);
  Hq0sb = new TH1D("Hq0sb","", Nbins, 0, 20);
  Hq0median = new TH1D("Hq0median","", Nbins, 0, 20);

  HGenb = new TH1D("HGenb","", 5000, 0, 5000);
  HGensb = new TH1D("HGensb","", 5000, 0, 5000);

  Hqm0 = new TH1D("Hqm0","", 20000, 0, 1000);
  Hqm1 = new TH1D("Hqm1","", 20000, 0, 1000); 
  Hqmm = new TH1D("Hqmm","", 20000, 0, 1000); 

  BNorm = new TH1D("Bnorm","", 1000, 0., 2.0);
  BPosterior = new TH1D("BPosterior", "", 1000 , 0. , 2.0);
  mup = new TH1D("mup", "", 1000 , 0. , 2.0);



  SetHistos(&Hbkg,  4, "-2ln(Q)");
  SetHistos(&Hsbkg, 2, "-2ln(Q)");
  SetHistos(&HObs,  1, "-2ln(Q)");

  SetHistos(&Hqm0, 4, "q_{#mu}");
  SetHistos(&Hqm1, 2, "q_{#mu}");
  SetHistos(&Hqmm, 1, "q_{#mu}");


  SetHistos(&Hq0b,  4, "q_{0}");
  SetHistos(&Hq0sb, 2, "q_{0}");
  SetHistos(&Hq0median, 1, "q_{0}");

  SetHistos(&HGenb,  4, "b");
  SetHistos(&HGensb, 2, "s+b");

  SetHistos(&BNorm, 4, "#mu");
  SetHistos(&BPosterior, 2, "#mu");
  SetHistos(&mup, 1, "#mu");

  c1 = new TCanvas("c1", "",165,113,1015,547);
  c1->UseCurrentStyle(); 
  c1->Divide(2,2);

}

void Methods::SetHistos(TH1D **h1, Double_t index, string label){
  (*h1)->SetStats(kFALSE);
  (*h1)->Sumw2();
  (*h1)->SetLineColor(index);
  (*h1)->SetFillColor(index); 
  (*h1)->SetFillStyle(3001);
  (*h1)->GetXaxis()->SetTitle(label.c_str());
 // (*h1)->GetYaxis()->SetTitle(label.c_str());
}

void Methods::NormHistos(TH1D **h1){
  if((*h1)->Integral() != 0.) (*h1)->Scale(1.0/ (*h1)->Integral());
  else std::cout << " --- fail normalization --- " << std::endl;  
}

void Methods::PlotHistos(TH1D *h1, Double_t index){
  if(index == 0) h1->Draw("HIST");
  else h1->Draw("HIST,same");
}

void Methods::SetNtoys(Double_t Ntoys_){
  Ntoys = Ntoys_;
}

void Methods::GetExpected(){
	Ndata = Nbkg;
}

 Double_t Methods::GetPvalue(TH1D *h1, Double_t Val){

  Double_t integral = 0.;
  Int_t Nbins = h1->GetXaxis()->GetNbins();

  
  for (Int_t b = 1; b <= Nbins; b++ ){
      if(h1->GetXaxis()->GetBinLowEdge(b) >= Val){
        integral += h1->GetBinContent(b);
      }
   }
 
  return integral;
 }


Double_t Methods::GetFrequestist(Double_t mu){

  Double_t Clsb = 0.;
  Clsb = TMath::Prob(2.*(mu+Nbkg), 2.*(Ndata+1.));
  return Clsb;

}

Double_t Methods::GetFrequestistCls(Double_t mu){

  Double_t Cls = 0.;
  Double_t Clsb = 0.;
  Double_t Clb = 0.;
  Clsb = TMath::Prob(2.*(mu+Nbkg), 2.*(Ndata+1.));
  Clb = TMath::Prob(2.*Nbkg, 2.*(Ndata+1.));
 
  if(Clb != 0.) Cls = Clsb/Clb;
  else Cls = -1;

  return Cls;

}

Double_t Methods::GetModifiedFrequestist(Double_t mu){

  Double_t Cls = 0.;
  Double_t Clsb = 0.;
  Double_t Clb = 0.;
  Clsb = TMath::Prob(2.*(mu+Nbkg), 2.*(Ndata+1.));
  Clb = TMath::Prob(2.*Nbkg, 2.*(Ndata+1.));
 
  if(Clb != 1.) Cls = Clsb/(1.-Clb);
  else Cls = -1;

  return Cls;

}

Double_t Methods::GetFrequestistLnQ(Double_t mu){


 // Normalp = false;
  
  double Ndata1 = 100., Nbkg1 = 90. , Nsignal1 = 150.;
  Nsignal2 = Nsignal1;

  ObsLnQ = GetLnQ(Ndata, Nbkg, mu);
  double ObsLnQ2 = GetLnQ2(Ndata1, Nbkg1, mu) ;
   
  //ObsLnQ += ObsLnQ2;

   Hbkg->Reset();
   Hsbkg->Reset();
   HObs->Reset();
   HGenb->Reset();
   HGensb->Reset() ;
   
   
   
   for(Int_t i = 1; i <= Ntoys; i++){
   	if(i % 1000000 == 0)
   		std::cout << " Ntoys generated: " << i << " --- " << std::endl;

    //rnd->SetSeed(i);

   // 
    Double_t temp = Nbkg;
    Double_t templ = Lumi;
    
    do{
    // temp = rnd->Uniform( Nbkg*(1.-0.06), Nbkg*(1.+0.06));
   // temp = rnd->Gaus( Nbkg , Nbkg*0.1 );  
     templ = rnd->Gaus( Lumi, Lsigma );
    // temp = rnd->PoissonD( Nbkg );
   // cout << temp << " previous " << endl; 

    }while(temp <= 0. || templ <= 0.);

 
    GenDb = rnd->PoissonD(temp*templ);
    GenDb += rnd->Gaus(0., 0.05);
    GenDsb = rnd->PoissonD(   (temp + mu*Nsignal) *templ );
    GenDsb += rnd->Gaus(0., 0.05);


    HGenb->Fill(GenDb);
    HGensb->Fill(GenDsb);
    /*
    double GenDb1 = rnd->PoissonD(Nbkg1);
    GenDb1 += rnd->Gaus(0., 1.0);
    double GenDsb1 = rnd->PoissonD(Nbkg1 + mu*Nsignal1);
    GenDsb1 += rnd->Gaus(0., 1.0);
    */
    

    double p1 = GetLnQ(GenDb, Nbkg, mu);
    //p1 += GetLnQ2(GenDb1, Nbkg1, mu);
    
    double p2 = GetLnQ(GenDsb, Nbkg, mu);
    //p2 += GetLnQ2(GenDsb1, Nbkg1, mu);

    Hbkg->Fill(p1);
    Hsbkg->Fill(p2);

   // Hbkg->Fill(GetLnQ(GenDb, Nbkg, mu));
   // Hsbkg->Fill(GetLnQ(GenDsb, Nbkg, mu));
 	  HObs->Fill(ObsLnQ);

  
   }

    NormHistos(&Hbkg);
    NormHistos(&Hsbkg);
    NormHistos(&HObs);
   

    Double_t Cls = 0.;

    Double_t Clsb =  GetPvalue(Hsbkg, ObsLnQ);
    Double_t Clb =   GetPvalue(Hbkg, ObsLnQ);
  
    
      if(Clb != 0.)  Cls = Clsb/Clb;
      else Cls = +1;

      //if(Clb != 1.)  Cls = Clsb/(1.-Clb);
      //else Cls = +1;
       
  
     std::cout << " Cls(Q): " <<  Cls << " " << mu << endl;

    return Cls;

}

Double_t Methods::GetFrequestistqm(Double_t mu){

  rnd->SetSeed(2000);
  
  Hqm0->Reset();
  Hqm1->Reset();
  Hqmm->Reset();


  Double_t templ = Lumi;
  Double_t temp = Nbkg;
   

  ObsLnQ = Getqm(Ndata, Nbkg, mu);
  //Systematic
 
  double lumi = Lumi;
  //ObsLnQ = GetqmSysL(Ndata, Nbkg, mu, GetDoublehatl(Ndata, Nbkg, mu, lumi), lumi);

  double m_ = Nbkg;
  ObsLnQ = GetqmSys(Ndata, GetDoublehatb(Ndata, mu, m_), mu, m_);


  
  double p1 = 0.;    
  double p2 = 0.; 

  for(Int_t i = 1; i <= Ntoys; i++){

    if(i % 1000000 == 0)
      std::cout << " Ntoys generated: " << i << " --- " << std::endl;



   

    // Get systematic,
    Double_t m = rnd->PoissonD( Nbkg );
    Double_t Newlm = rnd->Gaus(Lumi, Lsigma);
  
   // m = rnd->Uniform(Nbkg*0.94,Nbkg*1.06);
    //m = Nbkg;
    //Newlm  = Lumi;

    GenDb = rnd->PoissonD( m * Newlm );
    GenDsb = rnd->PoissonD( (m + mu*Nsignal) * Newlm );


    HGenb->Fill(GenDb);
    HGensb->Fill(GenDsb);


    //p1 = Getqm(GenDb,  temp, mu);    
   // p2 = Getqm(GenDsb, temp, mu);

    //  cout << GetDoublehatl(Ndata, Nbkg, mu, Newlm) << endl;

   // p1 = GetqmSysL(GenDb,  Nbkg, mu, GetDoublehatl(Ndata, Nbkg, mu, Newlm), Newlm);    
   // p2 = GetqmSysL(GenDsb, Nbkg, mu, GetDoublehatl(Ndata, Nbkg, mu, Newlm), Newlm);

    p1 = GetqmSys(GenDb,  GetDoublehatb(Ndata, mu, m), mu, m);
    p2 = GetqmSys(GenDsb, GetDoublehatb(Ndata, mu, m), mu, m);
    
    
   // if(p2 > 0. && p1 > 0.){ // for bacgkroundd
      Hqm0->Fill(p1);
      Hqm1->Fill(p2);
    //}

   }


    NormHistos(&Hqm0);
    NormHistos(&Hqm1);

    
 
    double Clsb = GetPvalue(Hqm1, ObsLnQ);
    double Clb = GetPvalue(Hqm0, ObsLnQ); 



    Hqm0->GetQuantiles(1,&qmedian,&quantile);
    
    //Hqmm->Fill(qmedian);
    Hqmm->Fill(ObsLnQ);
    
    double Pvalue = GetPvalue(Hqm1, qmedian); // Cowan article

     //   std::cout << " Cls(qm): " <<  Pvalue << " " << mu << " qm " << qmedian << " Z " << sqrt(qmedian) << endl; 
    //    Double_t Cls = 0.05;

    Double_t Cls = 0.;
    if(Clb != 0.) Cls = Clsb/Clb;
    else Cls = 1.0;

    cout << std::setprecision(6) << Clsb << "  " << Clb << " " << Cls << "  " << Pvalue/0.5 << " qobs "
     << ObsLnQ << " " << mu << endl;
  //  cout << std::setprecision(6) << Clb << " Z(p0)mu=0 " << -TMath::NormQuantile(1.-Clb) << endl;
    
  //  Cls = 0.04;
    return Cls;

}


Double_t Methods::GetLnQ(Double_t Ndata_, Double_t Nbkg_, Double_t mu_){
	Double_t LnQ = 0.;
	if(Nbkg_ != 0.) LnQ = 2.*(mu_*Nsignal - Ndata_*TMath::Log(1.+ (mu_*Nsignal/Nbkg_)));
	else exit(1);
	return LnQ;
}

Double_t Methods::GetLnQ2(Double_t Ndata_, Double_t Nbkg_, Double_t mu_){
  Double_t LnQ = 0.;
  if(Nbkg_ != 0.) LnQ = 2.*(mu_*Nsignal2 - Ndata_*TMath::Log(1.+ (mu_*Nsignal2/Nbkg_)));
  else exit(1);
  return LnQ;
}

Double_t Methods::Getqm(Double_t Ndata_, Double_t Nbkg_, Double_t mu_){

  Double_t qm = 0.;
  Double_t mup = (Ndata_ - Nbkg_)/Nsignal; // This maximizes the likelihood function.
  if( mu_ >= mup) 
    qm = 2*(mu_*Nsignal + Nbkg_ - Ndata_*(1.0 + TMath::Log( (mu_*Nsignal + Nbkg_)/Ndata_ ))); 
  return qm;

}

Double_t Methods::GetqmSys(Double_t Ndata_, Double_t Nbkg_, Double_t mu_, Double_t m){

  Double_t qm = 0.;
  Double_t mup = 0.;
 
  mup = (Ndata_ - m)/Nsignal;
/*
  if(mup < 0.){
    qm = 2*(mu_*Nsignal + 2*Nbkg_- Ndata_*TMath::Log(mu_*Nsignal + Nbkg_) - m*TMath::Log(Nbkg_) );
    qm += 2*( (Ndata_+m)*TMath::Log(Ndata_+m) -2*(Ndata_+m) );  

  }
*/

  if(mup > 0. &&  mu_ >= mup){
    qm += 2*(mu_*Nsignal + Nbkg_ - Ndata_*(1.0 + TMath::Log( (mu_*Nsignal + Nbkg_)/Ndata_ ))); 
    qm += 2*(Nbkg_ - m*(1.0 + TMath::Log( Nbkg_/m )));
  }

  return qm;

}

Double_t Methods::GetqmSysL(Double_t Ndata_, Double_t Nbkg_, Double_t mu_, Double_t lhat, Double_t lm){

  Double_t qm = 0.;
  Double_t mup = 0.;
 
  mup = (Ndata_ - lm*Nbkg_) /(lm*Nsignal);

  if(mu_ >= mup){
    qm  = 2*( lhat*(mu_*Nsignal + Nbkg_) - Ndata_*(1.0 + TMath::Log( (lhat*(mu_*Nsignal + Nbkg_)) / Ndata_ ))); 
    qm += pow( (lhat-lm)/Lsigma, 2 );
  }
  return qm;

}


Double_t Methods::GetDoublehatb(Double_t Ndata_, Double_t mu, Double_t m){

  Double_t doublehatb = 0.;
  Double_t NN = Ndata_ + m - mu*Nsignal;
  doublehatb = 0.5*( NN + sqrt( pow(NN,2) + 4.*mu*Nsignal*m  ) );
  return doublehatb;

}

Double_t Methods::GetDoublehatl(Double_t Ndata_, Double_t Nbkg_, Double_t mu, Double_t lm){

  Double_t doublehatl = 0.;
  Double_t K = mu*Nsignal + Nbkg_;
  doublehatl = 0.5*(lm - pow(Lsigma,2)*K + sqrt(  pow(lm - pow(Lsigma,2)*K,2) + 4*pow(Lsigma,2)*Ndata_ ) );

  return doublehatl;
}


Double_t Methods::GetPrior(Double_t mu){

  Double_t weight = 1.0;
 // weight = mu;

  Double_t mup = (Ndata-Nbkg)/Nsignal;

  if(mu < mup) weight = 0.;
  return weight; 
}

Double_t Methods::GetBayes(Double_t mu){

  
  Double_t w = 0.;
  Double_t mu_ = 0.;
  Double_t probU = 0.;
  Double_t probAcep = 0.;

  BNorm->Reset();
  BPosterior->Reset();
  mup->Reset();

  double numerator1 = 0.;
  double denominator1 = 0.;

    Double_t LnGammaNdata=TMath::LnGamma(Ndata+1.); //n! 

  // Calculating the maximum of the L(mu) distribution
    Double_t mumin = (Ndata - Nbkg)/Nsignal;
    Double_t Max = 0.;
    Max = TMath::Exp( -(mumin*Nsignal + Nbkg) + Ndata*TMath::Log(mumin*Nsignal + Nbkg) - LnGammaNdata);
    Max *= GetPrior(mumin);

    Double_t NewLumi = Lumi;

  for(Int_t i = 1; i <= Ntoys; i++){

    if(i % 10000000 == 0)
      std::cout << " Ntoys generated: " << i << " --- " << std::endl;
    
    mu_ =   rnd->Uniform(0., 5.0);

    //NewLumi = rnd->Gaus(Lumi, Lumi*0.025); 
    
    w=TMath::Exp( -NewLumi*(mu_*Nsignal + Nbkg) + Ndata*TMath::Log(NewLumi*(mu_*Nsignal + Nbkg)) - LnGammaNdata);
    //w *= ( TMath::Exp(  - pow(NewLumi - Lumi, 2) / (2*pow(Lsigma,2))  ) )  /  ( Lsigma*sqrt(2*TMath::Pi()) );  

    w *= GetPrior(mu_);


    
    probAcep = w/Max;
    probU = rnd->Uniform(0., 1.0);

    
    if( (w > 0.) && (probU <= probAcep) ){
     BNorm->Fill(mu_);
     if(mu_ < mu) BPosterior->Fill(mu_);
    }  

    denominator1 += w;
    if(mu_ < mu)     
      numerator1 += w;  // Second method to estimate the integral
   }

    Double_t Numerator = BPosterior->Integral();
    Double_t Denominator =  BNorm->Integral();

    NormHistos(&BPosterior);
    NormHistos(&BNorm);

    mup->Fill(mu);
  
  //  cout << Numerator/Denominator << " " << numerator1/denominator1 << endl;

   Double_t Cls = 0.;
   if(Denominator != 0.) Cls = 1. - (Numerator/Denominator);
   // if(denominator1 != 0.) Cls = 1. - (numerator1/denominator1);

   else Cls = 1.;

   cout << " Cls: " << Cls <<  " mu " <<  mu << endl;

   return Cls;

}

Double_t Methods::GetSignificance(Double_t mu){



  Hq0b->Reset();
  Hq0sb->Reset(); 
  Hq0median->Reset();

  Ntoys = 1E+7;

  Normalp = true;

  std::cout << " --- Calculating Significance --- "  << std::endl;

  for(Int_t i = 1; i <= Ntoys; i++){
    if(i % 1000000 == 0)
      std::cout << " Ntoys generated for significance: " << i << " --- " << std::endl;

    Double_t temp = Nbkg;
    Double_t templ = Lumi;
    
    do{
   //  temp = rnd->Uniform( Nbkg*(1.-0.1), Nbkg*(1.+0.1));
   //  temp = rnd->Gaus( Nbkg , Nbkg*0.05);  
     templ = rnd->Gaus( Lumi, Lumi*0.025 );
   // temp = rnd->PoissonD( Nbkg );
   // cout << temp << " previous " << endl; 

    }while(temp <= 0. || templ <= 0.);


    GenDb = rnd->PoissonD(temp*templ);
    GenDb += rnd->Gaus(0., 0.5);
    GenDsb = rnd->PoissonD((temp+mu*Nsignal)*templ);
    GenDsb += rnd->Gaus(0., 0.5);

    Hq0b->Fill(Getq0(GenDb, Nbkg));
    Hq0sb->Fill(Getq0(GenDsb, Nbkg));

  }

  NormHistos(&Hq0b);
  NormHistos(&Hq0sb);
  

  Hq0sb->GetQuantiles(1,&qmedian,&quantile);

  Hq0median->Fill(qmedian);

  cout << " PValue: " << GetPvalue(Hq0b, qmedian) << endl;
  if(GetPvalue(Hq0b, qmedian) != 0. || GetPvalue(Hq0b, qmedian) >= 1.0){
    significance = -TMath::NormQuantile(abs(GetPvalue(Hq0b, qmedian)));    
  } else std::cout << " --- It is not possible to find the significance --- " << std::endl;

  return significance;
}

Double_t Methods::Getq0(Double_t Ndata_, Double_t Nbkg_){

  Double_t q0 = 0.;
  if(Nbkg_ != 0.) q0 = sqrt(2.*( Ndata_* TMath::Log(Ndata_/Nbkg_) + Nbkg_ - Ndata_ ));
  else exit(0);
  return q0;

}

Double_t Methods::GetLimit(Double_t CL, Int_t method_, Double_t mu){

    CL = 1.0 - CL;
    limit = 1.0;
    do{
        
        if(method_ == 1) limit = GetFrequestist(mu);
        else if(method_ == 2) limit = GetFrequestistCls(mu);
        else if(method_ == 3) limit = GetModifiedFrequestist(mu);
        else if(method_ == 4) limit = GetFrequestistLnQ(mu);
        else if(method_ == 5) limit = GetFrequestistqm(mu);
        else if(method_ == 6) limit = GetBayes(mu);

        mu += h;

    }	while (limit > 0.05);

    if(method_ == 4 ||  method_ == 5 || method_ == 6){

    //significance =  GetSignificance(1.0); 
    cout << significance << endl;
    Plotter();
   

    }
 
    return mu-h;
}

void Methods::Plotter(){

 // c1->Clear();

  c1->cd(1);
  /*
  PlotHistos(Hbkg, 0);
  PlotHistos(Hsbkg, 1);
  PlotHistos(HObs, 2);
*/

  c1->Modified();
  c1->Update(); 

  c1->cd(2);
/*
  PlotHistos(Hq0b, 0);
  PlotHistos(Hq0sb, 1);
  PlotHistos(Hq0median, 2);
*/
  PlotHistos(BNorm,0);
  PlotHistos(BPosterior,1);
  PlotHistos(mup,2);

  c1->Modified();
  c1->Update(); 
 
  c1->cd(3);
  
  PlotHistos(HGenb, 0);
  PlotHistos(HGensb, 1);

  c1->Modified();
  c1->Update(); 

  c1->cd(4);

   
  PlotHistos(Hqm0, 0);
  PlotHistos(Hqm1, 1); 
  PlotHistos(Hqmm,2);

  c1->Modified();
  c1->Update(); 

  c1->SaveAs("Likelihood.pdf");

}

void Methods::SetNdata(Double_t Ndata_){
Ndata = Ndata_;
}
Double_t Methods::GetNdata(){
return Ndata;
}

void Methods::SetNbkg(Double_t Nbkg_){
Nbkg = Nbkg_;
}
Double_t Methods::GetNbkg(){
return Nbkg;
}

void Methods::SetNsignal(Double_t Nsignal_){
Nsignal = Nsignal_;
}
Double_t Methods::GetNsignal(){
return Nsignal;
}


Methods::~Methods(){
 delete c1;
}