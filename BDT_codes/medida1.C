void medida1()
{
  int n = 3000;  //numero de dardos a lanzar en el area del cuadrado
 
  Double_t error=0.2;
  Double_t c=0.01365;
  Double_t cmas=c*(1+error);
  Double_t cmen=c*(1-error);
  Double_t cdosmas=c*(1+2*error);
  Double_t cdosmen=c*(1-2*error);
  Double_t r=0.045;
  Double_t rmas=r*(1+error);
  Double_t rmen=r*(1-error);
  Double_t rdosmas=r*(1+2*error);
  Double_t rdosmen=r*(1-2*error);
  Double_t x;
  Double_t y;


  Float_t xi[2] = {0.256,0.256};
  Float_t yi[2] = {0.053,0.053};
  Float_t ex[2] = {0.021,0.021};
  Float_t ey[2] = {0.006,0.006};  

  TCanvas *c1 = new TCanvas("c1","Montecarlo",200,100,400,400);
  c1->Divide(1,1);
  c1->SetGrid(1);
  c1->SetTickx(1);
  c1->SetTicky(1);
   gRandom->SetSeed();  //semilla de Montecarlo, siempre diferente
 // TH2F *h1=new TH2F("h1","Medida del fraccion de los factores de forma",100,0,1,100,0,2);
 // TH2F *h2=new TH2F("h2","Medida del fraccion relativa",100,0,1,100,0,2);
  TF1 *f0 = new TF1("f0", "[11]", 0.0001,1);
  f0->SetTitle("#frac{#tau_{B_{s}}}{#tau_{B_{d}}}");
  f0->SetParameter(11, 0.053);
  f0->SetLineColor(0);
  f0->GetXaxis()->SetTitle("");
  f0->GetYaxis()->SetTitle("");
 
  TF1 *f1 = new TF1("f1","[0]/x", 0.001,1);
  f1->SetParameter(0, c);
  f1->SetLineColor(2);
  f1->SetLineStyle(1);
 
  TF1 *f2 = new TF1("f2","[1]/x", 0.001,1);
  f2->SetParameter(1, cmen);
  f2->SetLineColor(6);
  f2->SetLineStyle(2);
  TF1 *f3 = new TF1("f3","[2]/x", 0.001,1);
  f3->SetLineColor(6);
  f3->SetParameter(2, cmas);
  f3->SetLineStyle(2);

  TF1 *f4 = new TF1("f4","[4]/x", 0.001,1);
  f4->SetParameter(4, cdosmas);
  f4->SetLineColor(14);
  f4->SetLineStyle(10);
  TF1 *f5 = new TF1("f5","[5]/x", 0.001,1);
  f5->SetParameter(5, cdosmen);
  f5->SetLineColor(14);
  f5->SetLineStyle(10);
 
  TF1 *f6 = new TF1("f6","-[6]/(x-1)", 0.001,1);
  f6->SetParameter(6, r);
  f6->SetLineColor(4);

  TF1 *f7 = new TF1("f7","-[7]/(x-1)", 0.001,1);
  f7->SetParameter(7, rmen);
  f7->SetLineColor(9);
  f7->SetLineStyle(2);

  TF1 *f8 = new TF1("f8","-[8]/(x-1)", 0.001,1);
  f8->SetParameter(8, rmas);
  f8->SetLineColor(9); 
  f8->SetLineStyle(2);
   
  TF1 *f9 = new TF1("f9","-[9]/(x-1)", 0.001,1);
  f9->SetParameter(9, rdosmas);
  f9->SetLineColor(7); 
  f9->SetLineStyle(10);

  TF1 *f10 = new TF1("f10","-[10]/(x-1)", 0.001,1);
  f10->SetParameter(10, rdosmen);
  f10->SetLineColor(7); 
  f10->SetLineStyle(10);
  
  gr = new TGraphErrors(2,xi,yi,ex,ey);
  
  c1->cd(1);
  c1->SetGrid(1);
  c1->SetTickx(1);
  c1->SetTicky(1);
  gr->SetMarkerColor(4);
  gr->SetMarkerStyle(20);
  
  f0->GetXaxis()->SetTitle("#frac{f_{s}}{f_{d}}");
  f0->GetYaxis()->SetTitle("#frac{V_{cd}^{2}}{V_{cs}^{2}}");
//  h1->SetMarkerStyle(20);
//  h1->SetMarkerSize(0.3);
//  h1->SetMarkerColor(4);  //llenado histogramas
//  h1->Draw();
   
  c1->Update();
//  h2->GetXaxis()->SetTitle("#frac{FB_{s}}{FB_{d}}");
 // h2->GetYaxis()->SetTitle("#frac{F_{B_{s}}^{2}}{F_{B_{d}}^{2}}");
 // h2->SetMarkerStyle(20);
  //h2->SetMarkerSize(0.3);
  //h2->SetMarkerColor(5);
  //h2->Draw("same");
  f0->Draw();
  f1->Draw("same");
  f2->Draw("same");
  f3->Draw("same");
  f4->Draw("same");
  f5->Draw("same");
  f6->Draw("same");
  f7->Draw("same");
  f8->Draw("same");
  f9->Draw("same");
  f10->Draw("same");
  gr->Draw("same");
   c1->Update();
}
