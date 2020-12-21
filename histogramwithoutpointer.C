

void histogramwithoutpointer(){

  auto c0 = new TCanvas("Gauss","Gauss",0,0,320,240);

  c0->cd();

  TH1D h1("h1","h1", 50 , -5, 5);
  h1.SetMarkerStyle(21);
  h1.SetMarkerSize(0.8);
  h1.SetMarkerColor(kRed);

  h1.Reset();

  for ( int j = 0; j<10000; j++ ){
 	float a = gRandom->Gaus();
 	//cout << a << endl; 
    h1.Fill(a);
	}

  // Para h1 que se dibujan sin puntero
  h1.DrawClone();

  c0->Update();

}

int main(){
	histogramwithoutpointer();
	return 0;
}
