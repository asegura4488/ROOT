void limits_95CL_s_b(){
  gStyle->SetOptStat(0);
  TCanvas * c1 = new TCanvas("","",900,600);
  c1->Divide(2,1);

  unsigned nbins = 100;
  double min = -0., max = 1000;

  TH1F* h  = new TH1F("h","; event yield;arbitrary",nbins,0,30);
  h->GetYaxis()->SetTitleOffset(1.4);
   
  double bkgd = 4, sgnl = 11;
  unsigned data = 7;
  
  TF1* fnull  = new TF1("null","TMath::Poisson(x,[0])",0,30);
  TF1* falt   = new TF1("falt","TMath::Poisson(x,[0])",0,30);
  fnull->SetLineColor(3);
  fnull->SetParameter( 0, bkgd);
  falt->SetLineColor(2);
  falt->SetParameter( 0, bkgd+sgnl);

  TH1F* cl_vs_s = new TH1F("clvss",";signal yield s;confidence level CL_{s+b}",100,0,15);
  TH1F* cl_90 = new TH1F("cl90","",1,0,15);
  TH1F* cl_95 = new TH1F("cl95","",1,0,15);
  TH1F* cl_99 = new TH1F("cl99","",1,0,15);
  cl_90->SetBinContent(1,0.1);
  cl_95->SetBinContent(1,0.05);
  cl_99->SetBinContent(1,0.01);
  cl_vs_s->SetMarkerStyle(8);
  cl_vs_s->SetMaximum(1);
  cl_vs_s->SetMinimum(0.0011);

  double upper_limit_signal = 0;
  for (unsigned entries=0; entries<100; ++entries){
    float signal = 15.*entries/100.;
    falt->SetParameter(  0, bkgd+signal);
    double CLsb=falt->Integral(0,data);
    if(CLsb < 0.05 && upper_limit_signal == 0){
      upper_limit_signal = signal;
      cout<<"signal:"<<signal<<endl;
    }
    cl_vs_s->SetBinContent(entries, CLsb);
  }

  TLine line;
  line.SetLineWidth(4);
  TLatex text;
  text.SetTextSize(0.04);
  text.SetTextColor(1);


  c1->cd(1);
  gPad->SetLogy(0);
  h->GetYaxis()->SetRangeUser(0,  0.21 );
  h->Draw("h");
  fnull->SetParameter(  0, 6);
  fnull->Draw("same");
  falt->SetParameter(  0, 18);
  falt->Draw("same");
  text.SetTextSize(0.04);   
  text.SetTextColor(1);
  text.DrawLatex(7.6,0.144, "Observation d = 7 ev.");   
  text.SetTextColor( kGreen - 6);
  text.DrawLatex(5., 0.18, "#lambda_{b} = 4 ev.");
  text.SetTextColor(kRed);
  text.DrawLatex(20., 0.09, "#lambda_{s+b} = 15 ev.");
  line.DrawLine(7,0.14,7,0.0);

  c1->cd(2);
  gPad->SetLogy(1);
  cl_vs_s->Draw("p");
  cl_90->Draw("h,same");
  cl_95->Draw("h,same");
  cl_99->Draw("h,same");
  text.SetTextColor(1);
  text.DrawLatex(1,0.1005, "90%");  
  text.DrawLatex(1,0.0505, "95%");  
  text.DrawLatex(1,0.0105, "99%"); 
  line.SetLineStyle(2);
  line.SetLineWidth(2);
  line.DrawLine( upper_limit_signal, 0.14, upper_limit_signal, 0.0);  

  c1->SaveAs("limits_95CL_s_b.png");
}
