void calculopi()
{
  int n = 5000;  //numero de dardos a lanzar en el area del cuadrado
  double r = 5;
  double h = 5;  //centro del circulo
  double k = 5;
  Int_t nf = 0;  //numero de aciertos fuera del circulo
  Int_t nd = 0;  //        "          dentro   " 
  TCanvas *c1 = new TCanvas("c1","Montecarlo",200,100,400,400);
  c1->Divide(1,1);
  c1->SetGrid();
  gRandom->SetSeed();  //semilla de Montecarlo, siempre diferente
  TH2F *h1=new 
  TH2F("h1","Circulo generado a trav#acute{e}s de Montecarlo",100,0,2.0*r,100,0,2.0*r);
  TH2F *h2=new TH2F("h2","h2",100,0,2.0*r,100,0,2.0*r);
  double x,y;
  double lado =2.0*r;
  for(int i=1; i <= n; i++){
  x = gRandom->Uniform(0.0,lado); //generación uniforme  
  y = gRandom->Uniform(0.0,lado); //generación uniforme  
  h1->Fill(x,y);
  x=x-h;
  y=y-k;
  if((x*x + y*y) > (r*r))  //condicion de acierto-error
  nf++;
  if((x*x + y*y) <= (r*r))
  nd++;
  if(((x*x+y*y)>=((r-0.1)*(r-0.1)))&&((x*x+y*y)<=((r+0.1)*(r+0.1))))    
  h2->Fill(x+h,y+k);   
 }
  double pi_num;
  pi_num = ((double)nd)*4/((double)n);
  cout << pi_num << endl;
  cout << nf << endl;
  cout << nd << endl;   // calculo del número pi
  c1->cd(1);
  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(0.3);
  h1->SetMarkerColor(1);  //llenado histogramas
  h1->Draw();
  h2->SetMarkerStyle(20);
  h2->SetMarkerSize(0.5);
  h2->SetMarkerColor(4);
  h2->Draw("same");
}
