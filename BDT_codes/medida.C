void medida()
{
  int n = 3000000;  //numero de dardos a lanzar en el area del cuadrado
 
  Double_t error=0.2;
  Double_t c=0.011/0.259;
  Double_t cmas=c*(1+error)*1;
  Double_t cmen=c*(1-error)*1;
  Double_t r=0.011/0.013;
  Double_t rmas=r*(1+error)*1;
  Double_t rmen=r*(1-error)*1;
  Double_t x;
  Double_t y;


  Float_t xi[2] = {0.053,0.053};
  Float_t yi[2] = {1,1};
  Float_t ex[2] = {0.003,0.003};
  Float_t ey[2] = {0.1,0.1};  

  TCanvas *c1 = new TCanvas("c1","Montecarlo",200,100,400,400);
  c1->Divide(1,1);
  c1->SetGrid();
  gRandom->SetSeed();  //semilla de Montecarlo, siempre diferente
  TH2F *h1=new TH2F("h1","Medida del fraccion de los factores de forma",100,0,1,100,0,2);
  TH2F *h2=new TH2F("h2","Medida del fraccion relativa",100,0,1,100,0,2);
  
  
  for(int i=1; i <= n; i++)
			{
  			x = gRandom->Uniform(0.0,2); //generación uniforme  
                        y = gRandom->Uniform(0.0,2);
  			
			if(y<=cmas/x && y>=cmen/x)
			{
             		h1->Fill(x,y);	
			}
			
			
			if(y<=rmas/x && y>=rmen/x){h2->Fill(-x+1,y);}}
                          
  gr = new TGraphErrors(2,xi,yi,ex,ey);
  
  c1->cd(1);
  gr->SetMarkerColor(1);
  gr->SetMarkerStyle(20);
  
  h1->GetXaxis()->SetTitle("#frac{FB_{s}}{FB_{d}}");
  h1->GetYaxis()->SetTitle("#frac{V_{cd}^{2}}{V_{cs}^{2}}");
  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(0.3);
  h1->SetMarkerColor(4);  //llenado histogramas
  h1->Draw();
   
//  c1->Update();
  h2->GetXaxis()->SetTitle("#frac{FB_{s}}{FB_{d}}");
  h2->GetYaxis()->SetTitle("#frac{FB_{s}}{FB_{d}}");
  h2->SetMarkerStyle(20);
  h2->SetMarkerSize(0.3);
  h2->SetMarkerColor(5);
  h2->Draw("same");
  gr->Draw("same");
}
