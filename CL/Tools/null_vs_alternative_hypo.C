void null_vs_alternative_hypo(){
  gStyle->SetOptStat(0);
  TH1F * h = new TH1F( "h_work",";Nev.;arbitrary", 60, 0, 30.);
  // null hypothesis
  TF1* fgh0  = new TF1( "f_h0","gaus", -50, 50);
  fgh0->SetLineColor(kGreen+2);
  fgh0->SetParameter( 0, 0.2);//normalisation
  fgh0->SetParameter( 1, 4.);//mean
  fgh0->SetParameter( 2, TMath::Sqrt(4.));
  // alternative hypothesis
  TF1* fga  = new TF1( "f_a","gaus", -50, 50);
  fga->SetLineColor(kRed);
  fga->SetParameter( 0, 0.1);//normalisation
  fga->SetParameter( 1, 15.);//mean
  fga->SetParameter( 2, TMath::Sqrt(15.));//width
  
  TCanvas* c1 = new TCanvas("gauss","gauss",800,400);
  h->SetMaximum(0.25);
  h->Draw();
  float gauss_h0_integral = fgh0->Integral(-50,50);
  float gauss_a_integral = fga->Integral(-50,50);
  float mean  = fgh0->GetParameter(1);
  float sigma = fgh0->GetParameter(2);

  float alpha = fgh0->Integral( 7, 50);
  float beta  = fga->Integral( -50, 7); 

  cout<<"alpha:"<<alpha/gauss_h0_integral*100
      <<" beta:"<<beta/gauss_a_integral*100<<endl;

  // for( int i = 0; i < 50; ++i){
  //   float tmp_integral = fgh0->Integral( mean-(double)i/10.*sigma, 
  // 					mean+(double)i/10.*sigma);
  //   tmp_integral += (gauss_h0_integral-tmp_integral)/2.;
  //   cout<<(double)i/10.<<" sigma corresponds to "
  // 	<<tmp_integral/gauss_h0_integral*100<<" % single-sided interval"<<endl;
  // }  

  fgh0->Draw("same");
  fga->Draw("same");
  TLine* line_data = new TLine( 7, 0, 7, 0.23);
  line_data->SetLineColor(kBlack);
  line_data->Draw();
}

