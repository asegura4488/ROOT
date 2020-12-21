void sigma_interval_single_sided(){
  gStyle->SetOptStat(0);
  TH1F * h = new TH1F( "h_work",";x;f(x)",100,-50, 50.);
  TF1* fga  = new TF1( "f_work","gaus", -50, 50);
  fga->SetLineColor(3);
  fga->SetParameter( 0, 1.);//normalisation
  fga->SetParameter( 1, 0.);//mean
  fga->SetParameter( 2, 5.);//width
  
  TCanvas* c1 = new TCanvas("gauss","gauss",800,400);
  h->SetMaximum(1);
  h->Draw();
  float gauss_integral = fga->Integral(-500,500);
  cout << gauss_integral << endl;
  float mean  = fga->GetParameter(1);
  float sigma = fga->GetParameter(2);
  for( int i = 0; i < 50; ++i){
    float tmp_integral = fga->Integral( mean-(double)i/10.*sigma, 
					mean+(double)i/10.*sigma);
    tmp_integral += (gauss_integral-tmp_integral)/2.;
    cout<<(double)i/10.<<" sigma corresponds to "
	<<tmp_integral/gauss_integral*100<<" % single-sided interval"<<endl;
  }  

  fga->Draw("same");

}

