void null_vs_alternative_hypo_flu_100(){
  gStyle->SetOptStat(0);
  TH1F * h = new TH1F( "h_work",";t[^{o}C];arbitrary", 100, 39, 41.);
  // null hypothesis
  TF1* g_bf  = new TF1( "g_bf","gaus", -100, 100);
  g_bf->SetLineColor(kGreen+2);
  g_bf->SetParameter( 0, 0.2);//normalisation
  g_bf->SetParameter( 1, 39.7);//mean
  g_bf->SetParameter( 2, 0.2);//sigma

  TF1* g_nf  = new TF1( "g_nf","gaus", -100, 100);
  g_nf->SetLineColor(kRed);
  g_nf->SetParameter( 0, 20.);//normalisation
  g_nf->SetParameter( 1, 39.9);//mean
  g_nf->SetParameter( 2, 0.2);//sigma

  TGraph * g = new TGraph(1);
  TGraph * a = new TGraph(1);
  for (int i=0; i<=100; ++i){
    g->SetPoint(i, 39.64+0.8*(double)i/100., g_bf->Eval(39.64+0.8*(double)i/100.));
    a->SetPoint(i, 39.64-0.8*(double)i/100., g_nf->Eval(39.64-0.8*(double)i/100.));
  }  
  g->SetPoint(101,40.6,0);
  g->SetPoint(102,39.64,0);
  g->SetFillColor(4);
  a->SetPoint(101,39,0);
  a->SetPoint(102,39.64,0);
  a->SetFillColor(5);
  
  float g_nf_integral = g_nf->Integral(37,41);
  float g_nf_mean  = g_nf->GetParameter(1);
  float g_nf_sigma = g_nf->GetParameter(2);
  float rel_cut = 0.1; //1-beta = 90%
  float cut_flu = 36.;

  for (int x=0; x<=400; ++x){
    if( g_nf->Integral(37, 37+x/100.)/g_nf_integral > rel_cut){
      cut_flu = 37+(x-1)/100.;
      cout<<"cut_flu at "<<37+(x-1)/100.<<" °C"<<endl;      
      break;
    } 
  } 

  float g_bf_integral = g_bf->Integral(37,41);
  float g_bf_cut_flu_integral = g_bf->Integral(37,cut_flu);
  //float rej_patients_bf = (g_bf_integral-g_bf_cut_flu_integral)/g_bf_integral;
  float rej_patients_bf = g_bf->Integral(cut_flu,41)/g_bf_integral;
  cout<<"rej_patients_bf:"<<rej_patients_bf*100<<"%"<<endl;

  float n_patients_bf = (1-rej_patients_bf)*g_bf_integral;
  float n_patients_nf = 0.1*g_nf_integral;

  cout <<"n_beds nf:"
       <<n_patients_nf/(n_patients_nf+n_patients_bf)*100<<"%"<<endl;
  cout <<"n_beds bf:"
       <<n_patients_bf/(n_patients_nf+n_patients_bf)*100<<"%"<<endl;

  TCanvas* c1 = new TCanvas("gauss","gauss",800,400);
  h->SetMaximum(25);
  h->Draw();

  g->Draw("lf,same");
  a->Draw("lf,same");

  g_bf->Draw("same");
  g_nf->Draw("same");

  gPad->RedrawAxis();
  c1->SaveAs("bird_vs_normal_flu.pdf");

}

