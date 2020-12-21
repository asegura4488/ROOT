{
  TH2F *h2 = new 
  TH2F("h2","Densidad de part#acute{i}culas en una atm#acute{o}sfera est#acute{a}ndar",200,0,10,200,0,10); 
  TCanvas *c1=new TCanvas("c1","Densidad de particulas",200,10,700,500);
  c1->Divide(1,1);  // Declaración del histograma y del entorno grafico
  gRandom->SetSeed(); // Semilla de Montecarlo, siempre es diferente 
  Float_t r;
  Float_t x;
  Float_t y;
  for(Int_t i=1;i<=1000;i++) // Ciclo sobre i
  {
  r=gRandom->Uniform(0,1);   // Generación de una variable uniforme  
  x=gRandom->Uniform(0,10);  // Generación de una variable uniforme  
  y=-2*log(1-r);         // Generación de una distribución exponencial
  h2->Fill(x,y);
  }
  c1->cd(1); 
  h2->Draw();		//Dibujar histograma	
}
