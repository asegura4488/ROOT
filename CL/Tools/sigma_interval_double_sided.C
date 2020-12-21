void sigma_interval_double_sided(){
  gStyle->SetOptStat(0);
  TH1F * h = new TH1F( "h_work",";x;f(x)",200,-100, 100.);
  TF1* fga  = new TF1( "f_work","gaus", -100, 100);
  fga->SetLineColor(3);
  fga->SetParameter( 0, 1.);
  fga->SetParameter( 1, 0.);
  fga->SetParameter( 2, 20.);
  
  TCanvas* c1 = new TCanvas("gauss","gauss",800,400);
  h->SetMaximum(1);
  h->Draw();
  double gauss_integral = fga->Integral(-100,100);
  double mean  = fga->GetParameter(1);
  double sigma = fga->GetParameter(2);
  for( int i = 0; i <= 1000; ++i){
    double tmp_integral = fga->Integral( mean-(double)i/200.*sigma, 
					mean+(double)i/200.*sigma);
    //tmp_integral += (gauss_integral-tmp_integral);
    //cout<<(double)i/10.<<" sigma corresponds to "
	//<<tmp_integral/gauss_integral*100<<" % double-sided interval"<<endl;
    printf("sigma %.3f %.9f \n", (double)i/200., 1-tmp_integral/gauss_integral);
  }  

  fga->Draw("same");

}

