void limits_CLs_TLimit(){
  gStyle->SetOptStat(0);

  const double   bkgd =5;
  const double   signal = 11;
  const unsigned data = 7;

  TCanvas * c1 = new TCanvas("","",600,900);
 
  TH1F* cl_vs_s_CL = new TH1F("clvss_CL",";signal yield s;confidence level CL_{s}",150,0,15);
  TH1F* cl_90 = new TH1F("cl90","",1,0,15);
  TH1F* cl_95 = new TH1F("cl95","",1,0,15);
  TH1F* cl_99 = new TH1F("cl99","",1,0,15);
  cl_90->SetBinContent(1,0.1);
  cl_95->SetBinContent(1,0.05);
  cl_99->SetBinContent(1,0.01);
  cl_vs_s_CL->SetMarkerStyle(8);
  cl_vs_s_CL->SetMaximum(1);
  cl_vs_s_CL->SetMinimum(0.0011);

  double upper_limit_signal_CLs = 0;
  for (unsigned entries=0; entries<150; ++entries){
    float i_signal = 15.*entries/150.;
    TConfidenceLevel* myconfidence = TLimit::ComputeLimit( i_signal, bkgd, data, 500);
    cl_vs_s_CL->SetBinContent(entries, myconfidence->CLs());
    if( myconfidence->CLs() < 0.05 && upper_limit_signal_CLs == 0){
      cout << "  CLs    : " << myconfidence->CLs()  << endl;
      cout << "  CLsb   : " << myconfidence->CLsb() << endl;
      cout << "  CLb    : " << myconfidence->CLb()  << endl;
      cout << "< CLs >  : " << myconfidence->GetExpectedCLs_b()  << endl;
      cout << "< CLsb > : " << myconfidence->GetExpectedCLsb_b() << endl;
      cout << "< CLb >  : " << myconfidence->GetExpectedCLb_b()  << endl;
      cout << "i_signal:"<<i_signal<<endl;
      upper_limit_signal_CLs = i_signal;
    }
  }
 
  TLine line;
  line.SetLineWidth(4);
  TLatex text;
  text.SetTextSize(0.04);
  text.SetTextColor(1);

  gPad->SetLogy(1);
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
  line.DrawLine( upper_limit_signal_CLs, 0.14, upper_limit_signal_CLs, 0.0);  

  c1->SaveAs("limits_CLs_TLimit.png");
}
