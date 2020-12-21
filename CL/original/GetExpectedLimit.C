Double_t GetExpectedLimit(Double_t cl,Double_t b) {
  /* calculate the expected signal limit, given the confidence level
     and the background b. Note: does not work for very large b */
  Int_t n0=(int)b;
  Int_t n1=n0+1;
  Double_t p0=1.0;
  if(b>0.0) p0=TMath::Exp(n0*TMath::Log(b)-b-TMath::LnGamma(n0+1.));
  Double_t p1=p0*b/n1;
  Double_t sum=0.0;
  // sum up poisson terms from n0 to infinity
  //  (stop as the contribution vanishes)
  while((p0>0.)&&(n0>=0)) {
    Double_t muLimit=0.5*TMath::ChisquareQuantile(cl,2*(n0+1));
    Double_t signal=muLimit-b;
    sum += p0*signal;
    p0 *= n0/b;
    n0--;
  }
  // sum up poisson terms from n1 down to zero
  //  (stop earlier if teh contribution vanishes)x
  while(p1>0.0) {
    Double_t muLimit=0.5*TMath::ChisquareQuantile(cl,2*(n1+1));
    Double_t signal=muLimit-b;
    sum += p1*signal;
    n1++;
    p1 *= b/n1;
  }
  cout<<"Given the background b="<<b<<" the expected limit on the signal is "
      <<sum<<"\n";
  return sum;
}
