void set_histo_style( TH1F *h, int marker_style, Color_t marker_color, 
		      float min=1, float max=0.0011){
  h->SetMarkerStyle(marker_style);
  h->SetMarkerColor(marker_color);
  h->SetMaximum(min);
  h->SetMinimum(max);
}

void limits_CLs_combination_pro(){
  gStyle->SetOptStat(0);
  TCanvas * c1 = new TCanvas("","",600,900);
  c1->Divide(2,1);

  unsigned nbins = 100;

  // TH1F h("h","; event yield;arbitrary",nbins,0,30);
  // h.GetYaxis()->SetTitleOffset(1.4);

  //category 1
  const double bkgd_c1 = 4;
  const double sgnl_c1 = 11;
  const unsigned data_c1 = 7;

  //category 2
  const double bkgd_c2 = 6;
  const double sgnl_c2 = 12;
  const unsigned data_c2 = 9;
  
  TF1* fnull  = new TF1("fnull","TMath::Poisson(x,[0])",0,30);
  TF1* falt   = new TF1("falt","TMath::Poisson(x,[0])",0,30);
  fnull->SetLineColor(3);
  falt->SetLineColor(2);

  TH1F* cl_vs_s_CL_c1 = new TH1F("clvss_CL_c1",";signal yield s;confidence level CL_{s}",150,0,15);
  TH1F* cl_vs_s_CL_c2 = new TH1F("clvss_CL_c2",";signal yield s;confidence level CL_{s}",150,0,15);
  TH1F* cl_vs_s_CL_comb = new TH1F("clvss_CL_comb",";signal yield s;confidence level CL_{s}",150,0,15);

  set_histo_style( cl_vs_s_CL_c1, 8, kBlue+2);
  set_histo_style( cl_vs_s_CL_c2, 8, kBlue);
  set_histo_style( cl_vs_s_CL_comb, 8, kBlack);

  TH1F* cl_90 = new TH1F("cl90","",1,0,15);
  TH1F* cl_95 = new TH1F("cl95","",1,0,15);
  TH1F* cl_99 = new TH1F("cl99","",1,0,15);
  cl_90->SetBinContent(1,0.1);
  cl_95->SetBinContent(1,0.05);
  cl_99->SetBinContent(1,0.01);

  double upper_limit_signal_CLs_c1 = 0;
  double upper_limit_signal_CLs_c2 = 0;
  double upper_limit_signal_CLs_comb = 0;
  fnull->SetParameter(  0, bkgd_c1);
  double CLb_c1 = fnull->Integral(0, data_c1);
  fnull->SetParameter(  0, bkgd_c2);
  double CLb_c2 = fnull->Integral(0, data_c2);

  for (unsigned entries=0; entries<150; ++entries){
    float signal = 15.*entries/150.;
    falt->SetParameter(  0, bkgd_c1 + signal);
    double CLsb_c1 = falt->Integral(0, data_c1);
    falt->SetParameter(  0, bkgd_c2 + signal);
    double CLsb_c2 = falt->Integral(0, data_c2);

    double CL_c1 = 1 - CLsb_c1/CLb_c1;
    double CL_c2 = 1 - CLsb_c2/CLb_c2;
    double CL_comb = 1 - CLsb_c1/CLb_c1*CLsb_c2/CLb_c2;
    
    cout<<"signal:"<<signal<<" CL_c1:"<<CL_c1
	<<" CL_c2:"<<CL_c2
	<<" CL_comb:"<<CL_comb
	<<endl;

   if(CLsb_c1/CLb_c1 < 0.05 && upper_limit_signal_CLs_c1 == 0){
      upper_limit_signal_CLs_c1 = signal;
      cout<<"c1 CLs signal:"<<signal<<endl;
    }
    if(CLsb_c2/CLb_c2 < 0.05 && upper_limit_signal_CLs_c2 == 0){
      upper_limit_signal_CLs_c2 = signal;
      cout<<"c2 CLs signal:"<<signal<<endl;
    }
    if(CLsb_c1/CLb_c1*CLsb_c2/CLb_c2 < 0.05 && 
       upper_limit_signal_CLs_comb == 0){
      upper_limit_signal_CLs_comb = signal;
      cout<<"comb. CLs signal:"<<signal<<endl;
    }
 
    cl_vs_s_CL_c1->SetBinContent(entries, CLsb_c1/CLb_c1);
    cl_vs_s_CL_c2->SetBinContent(entries, CLsb_c2/CLb_c2);
    cl_vs_s_CL_comb->SetBinContent(entries, CLsb_c1/CLb_c1*CLsb_c2/CLb_c2);
  }

  TLine line;
  line.SetLineWidth(4);
  TLatex text;
  text.SetTextSize(0.04);
  text.SetTextColor(1);

  gPad->SetLogy(1);
  cl_vs_s_CL_c1->Draw("p");
  cl_vs_s_CL_c2->Draw("p,same");
  cl_vs_s_CL_comb->Draw("p,same");
  cl_90->Draw("h,same");
  cl_95->Draw("h,same");
  cl_99->Draw("h,same");
  text.SetTextColor(1);
  text.DrawLatex(1,0.1005, "90%");  
  text.DrawLatex(1,0.0505, "95%");  
  text.DrawLatex(1,0.0105, "99%"); 
  line.SetLineColor(kBlue+2);
  line.SetLineStyle(2);
  line.DrawLine( upper_limit_signal_CLs_c1, 0.14, upper_limit_signal_CLs_c1, 0.0);
  line.SetLineColor(kBlue);
  line.SetLineStyle(2);
  line.DrawLine( upper_limit_signal_CLs_c2, 0.14, upper_limit_signal_CLs_c2, 0.0);  
  line.SetLineColor(kBlack);
  line.SetLineStyle(2);
  line.DrawLine( upper_limit_signal_CLs_comb, 0.14, upper_limit_signal_CLs_comb, 0.0);  
  c1->SaveAs("limits_CLs_combination.png");
}
