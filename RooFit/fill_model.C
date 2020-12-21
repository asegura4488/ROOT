using namespace RooFit;

void fill_model(){
  
  RooRealVar mass("mass","mass[GeV]",-2.0,2.0);   //RooRealVar = variable
  
  RooDataSet *data = new RooDataSet("data","data",RooArgSet(mass));
  
  gRandom = new TRandom3();
  
  RooArgSet *ValueP = new RooArgSet(mass);

  for(UInt_t i = 0; i < 1000; i++){
    mass = gRandom->Uniform(-2.0, 2.0);
    std::cout << ValueP->getRealValue("mass") << std::endl;
    data->add(RooArgSet(mass)); 
  }
  
  RooPlot *massframe = mass.frame();
  
  data->plotOn(massframe, LineStyle(kDashed), LineColor(1));
  
  massframe->Draw();
  
}

int main(){
  fill_model();
  return 0;
}
