Double_t GetBayesPrior(Double_t mu) {
  // prior probability, used below
  Double_t p=1.0;
  if(mu>90.) p=0;
  return p;
}

Double_t GetPosterior(Double_t muMax,Int_t nObs,Int_t nTry=200000) {
  /* calculates the Bayesian posterior probability for 0<=my<=my0
     given nObs. */
  Double_t sum[2],sum2[2];
  rnd=new TRandom3();
  sum[0]=0.; sum[1]=0.; sum2[0]=0.; sum2[1]=0.;
  /* the integral is split into two parts
     0 .. nObs               exponential distribution rising with mu
     nObs .. infinity        exponential distribution falling with mu */
  Double_t lgamNobs=TMath::LnGamma(nObs+1.);
  for(Int_t iTry=0;iTry<nTry;iTry++) {
      /* mu is drawn from an exponential distribution
	 with decay constant 1+nObs
         P(mu) = exp( -/+ (mu-nObs)/(nObs+1))
       the weight w compensates for the difference between
       the exponential distribution and the likelihood
         L(mu) = exp(-mu +ln(mu)*nObs -LnGamma(nObs+1)) 
      */
    Double_t w,mu;
    if(rnd->Uniform()>0.5) {
      mu=nObs+rnd->Exp(1.+nObs);
      w=TMath::Exp(TMath::Log(mu)*nObs-mu-lgamNobs+ (mu-nObs)/(1.+nObs));
    } else {
      mu=nObs-rnd->Exp(1.+nObs);
      if(mu>0.0) {
	w=TMath::Exp(TMath::Log(mu)*nObs-mu-lgamNobs +(nObs-mu)/(1.+nObs));
      } else {
	w=0.0;
      }
    }
    // prior probability
    w *= GetBayesPrior(mu);
    Int_t i= (mu>=muMax) ? 1 : 0;
    sum[i] += w;
    sum2[i] += w*w;
  }
  Double_t norm=sum[0]+sum[1];
  Double_t p=sum[0]/norm;
  Double_t dp=
    TMath::Sqrt(sum2[1]*sum[0]*sum[0]+sum2[0]*sum[1]*sum[1])/norm/norm;
  delete rnd;
  cout<<"The Bayesian posterior probability for 0<mu<"<<muMax
      <<", given Nobs="<<nObs<<" is "<<p<<" +/- "<<dp<<"\n";
  return p;
}

