{
  TH1F *h1 = new TH1F("h1","Histograma de una distribuci#acute{o}n uniforme",200,0,10);
  TCanvas *c1=new TCanvas("c1","Histograma distribucion uniforme",200,10,700,500);
  c1->Divide(1,1);            // Declaración del histograma y del entorno grafico
  gRandom->SetSeed();         // Semilla de Montecarlo para que siempre sea diferente   
  Float_t r;
  for(Int_t i=1;i<=5000;i++)  // Ciclo sobre i 
  {
  r=gRandom->Uniform(0,10);   // Generación de una variable uniforme   
  h1->Fill(r);                // llenado del histograma
  }
  c1->cd(1);
  h1->Draw();
  h1->GetXaxis()->SetTitle("V. Aleatoria"); // Parámetros del histograma
  h1->GetYaxis()->SetTitle("Frecuencia");  
}  
