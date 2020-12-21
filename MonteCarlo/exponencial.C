{
  TH1F *h1 = new 
  TH1F("h1","Histograma de una distribuci#acute{o}n exponencial",150,0,10);
  TCanvas *c1=new
  TCanvas("c1","Histograma distribucion Exponencial",200,10,700,500);
  c1->Divide(1,1);	 // Declaración del histograma y del entorno grafico
  gRandom->SetSeed();    // Semilla de Montecarlo, siempre es diferente 
  Float_t x;
  Float_t r;
  Float_t y;
  for(Int_t i=1;i<=5000;i++)  // Ciclo sobre i
  {
  r=gRandom->Uniform(0,1);    // Generación de una variable uniforme       
  y=-2*log(1-r);              // Generación de una distribución exponencial
  h1->Fill(y);                // llenado del histograma
  }
  c1->cd(1);
  h1->Draw();		     //Dibujar histograma	
  h1->GetXaxis()->SetTitle("V. Aleatoria"); // Parámetros del histograma
  h1->GetYaxis()->SetTitle("Frecuencia");  
}
