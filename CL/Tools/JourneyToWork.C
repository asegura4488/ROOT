void JourneyToWork(){
  gStyle->SetOptStat(0);
   TCanvas * c1 = new TCanvas("","",600,600);
   TH1F * h = new TH1F( "h_work",";x;f(x)",20,7,8.5);
   TF1* fga  = new TF1( "f_work","gaus",7,8.5);
   fga->SetLineColor(3);
   fga->SetParameter( 0, 0.85);
   fga->SetParameter( 1, 7.65);
   fga->SetParameter( 2, 0.167);
 
   h->SetMaximum(1);
   h->Draw();

   TLatex text;
   text.SetTextSize(0.035);
   text.SetTextColor(4);
   text.DrawLatex(8.0,0.1, "#alpha = 1 - CL = 0.005");
   text.SetTextColor(1);
   text.SetTextSize(0.04);
   text.DrawLatex(8,0.7, "#mu = t + 0.5 h");
   text.DrawLatex(8,0.63, "#sigma = 1/6 h");

   TGraph * g = new TGraph(1);
   g->SetPoint(0,8,0);
   for (int i=1; i<=100; ++i){
     g->SetPoint(i, 8.+0.5*(double)i/100., fga->Eval(8.+0.5*(double)i/100.));
   }  
   g->SetPoint(101,8.5,0);
   //g->SetPoint(102,-3,0);
   g->SetFillColor(4);

   cout<<"fga->Integral(-1s,1s)"<<fga->Integral(fga->GetParameter(1)-3*fga->GetParameter(2), fga->GetParameter(1)+3*fga->GetParameter(2))<<endl;
   cout<<"fga->Integral()"<<fga->Integral(7, 8.5)<<" "<<
       fga->Integral(fga->GetParameter(1)-3*fga->GetParameter(2), fga->GetParameter(1)+3*fga->GetParameter(2))/fga->Integral(7, 8.5)<<endl;
   cout<<"fga->Integral()"<<fga->Integral(8, 8.5)<<" "<<
     fga->Integral(8.,8.5)/fga->Integral(7, 8.5)<<endl;
   g->Draw("lf,same");
   fga->Draw("l,same");
   gPad->RedrawAxis();
   c1->SaveAs( "journeytowork.pdf" );
}

