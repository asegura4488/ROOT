void limits_CLs_category2(){
  gStyle->SetOptStat(0);
  TCanvas * c1 = new TCanvas("","",900,600);
  c1->Divide(2,1);

  unsigned nbins = 100;
  double min = -0., max = 1000;

  TH1F* h  = new TH1F("h","; event yield;arbitrary",nbins,0,30);
  h->GetYaxis()->SetTitleOffset(1.4);
   
  double bkgd = 6, sgnl = 12;
  unsigned data = 9;
  
  TF1* fnull  = new TF1("fnull","TMath::Poisson(x,[0])",0,30);
  TF1* falt   = new TF1("falt","TMath::Poisson(x,[0])",0,30);
  fnull->SetLineColor(3);
  fnull->SetParameter( 0, bkgd);
  falt->SetLineColor(2);
  falt->SetParameter( 0, bkgd+sgnl);

  TH1F* cl_vs_s = new TH1F("clvss",";signal yield s;confidence level CL_{s+b}",100,0,15);
  TH1F* cl_vs_s_CL = new TH1F("clvss_CL",";signal yield s;confidence level CL_{s}",100,0,15);
  TH1F* cl_90 = new TH1F("cl90","",1,0,15);
  TH1F* cl_95 = new TH1F("cl95","",1,0,15);
  TH1F* cl_99 = new TH1F("cl99","",1,0,15);
  cl_90->SetBinContent(1,0.1);
  cl_95->SetBinContent(1,0.05);
  cl_99->SetBinContent(1,0.01);
  cl_vs_s->SetMarkerStyle(8);
  cl_vs_s->SetMaximum(1);
  cl_vs_s->SetMinimum(0.0011);
  cl_vs_s_CL->SetMarkerStyle(8);
  cl_vs_s_CL->SetMarkerColor(kBlue);
  cl_vs_s_CL->SetMaximum(1);
  cl_vs_s_CL->SetMinimum(0.0011);

  double upper_limit_signal_CLsb = 0;
  double upper_limit_signal_CLs = 0;
  fnull->SetParameter(  0, bkgd);
  double CLb=fnull->Integral(0,data);

  for (unsigned entries=0; entries<100; ++entries){
    float signal = 15.*entries/100.;
    falt->SetParameter(  0, bkgd+signal);
    double CLsb=falt->Integral(0,data);

    double CL = 1 - CLsb/CLb;
    cout<<"signal:"<<signal<<" CL:"<<CL
	<<" CLsb:"<<1-CLsb
	<<endl;

    if(CLsb/CLb < 0.05 && upper_limit_signal_CLs == 0){
      upper_limit_signal_CLs = signal;
      cout<<"CLs signal:"<<signal<<endl;
    }
 
    if(CLsb < 0.05 && upper_limit_signal_CLsb == 0){
      upper_limit_signal_CLsb = signal;
      cout<<"CLsb signal:"<<signal<<endl;
    }
 
    cl_vs_s->SetBinContent(entries, CLsb);
    cl_vs_s_CL->SetBinContent(entries, CLsb/CLb);
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
  text.DrawLatex(8.6,0.144, "Observation d = 9 ev.");   
  text.SetTextColor( kGreen - 6);
  text.DrawLatex(5., 0.18, "#lambda_{b} = 6 ev.");
  text.SetTextColor(kRed);
  text.DrawLatex(20., 0.09, "#lambda_{s+b} = 18 ev.");
  line.DrawLine(9,0.14,9,0.0);

  c1->cd(2);
  gPad->SetLogy(1);
  cl_vs_s->Draw("p");
  cl_vs_s_CL->Draw("p,same");
  cl_90->Draw("h,same");
  cl_95->Draw("h,same");
  cl_99->Draw("h,same");
  text.SetTextColor(1);
  text.DrawLatex(1,0.1005, "90%");  
  text.DrawLatex(1,0.0505, "95%");  
  text.DrawLatex(1,0.0105, "99%"); 
  line.SetLineStyle(2);
  line.SetLineWidth(2);
  line.DrawLine( upper_limit_signal_CLsb, 0.14, upper_limit_signal_CLsb, 0.0);  
  line.SetLineColor(kBlue);
  line.SetLineStyle(2);
  line.DrawLine( upper_limit_signal_CLs, 0.14, upper_limit_signal_CLs, 0.0);  

  TF1 *flog=new TF1("flog","log10(x)",0.0011,1);
  TGaxis *A_CLs = new TGaxis(-1.75,0.0011,-1.75,1,"flog",505,"G");
  A_CLs->SetTitle("confidence level CL_{s}");
  A_CLs->SetLabelSize(0.0375);
  A_CLs->SetTitleSize(0.0375);
  A_CLs->SetLineColor(kBlue);
  A_CLs->SetTextColor(kBlue);
  A_CLs->SetLabelColor(kBlue);
  A_CLs->SetTitleOffset(1.5); // Axis title automatically placed
  A_CLs->Draw();
  c1->SaveAs("limits_CLs_category2.png");
}
