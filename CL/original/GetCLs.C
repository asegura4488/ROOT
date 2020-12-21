Double_t GetCLs(Double_t signal,Double_t bgr,Int_t nobs) {
  /* calculate CLs for the given
     signal, background , nobs. Does not work for high nobs. */
  Double_t cl_b=TMath::Prob(2.*bgr,2.*(nobs+1));
  Double_t cl_sb=TMath::Prob(2.*(signal+bgr),2.*(nobs+1));
  Double_t cl_s=cl_sb/cl_b;
  cout<<"signal="<<signal<<" bgr="<<bgr<<" CL_SB="<<cl_sb
      <<" cl_b="<<cl_b<<" cl_s="<<cl_s<<"\n";
  return cl_s;
}
