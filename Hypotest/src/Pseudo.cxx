#include "../include/Pseudo.h"

Pseudo::Pseudo(){}

Pseudo::Pseudo(string path): ConFolder(""), Mean(0.), Sigma(0.), Mean_I(0){
SetConfig(path);
outpseudo.open(ConFolder+"/pseudodata.in", std::ofstream::trunc);
}

void Pseudo::SetConfig(string path){
ConFolder=path;
}

void Pseudo::InitBins(string file){

  Input[0].open((ConFolder+"/bins/"+file+".in").c_str());
  if(!Input[0]) {
    std::cout << "could not open file config bin file: " << file << std::endl;
    exit(1);
  } 

  Double_t bins_ = 0;
  while(!Input[0].eof()){
    Input[0] >> bins_;
    bins.push_back(bins_);    
  }
  bins.pop_back();

  BINS = new Double_t[bins.size()];
  N_bins = bins.size()-1;
  int i=0;
  for(std::vector<Double_t>::iterator it = bins.begin(); it != bins.end(); it++, i++){
    BINS[i] = (*it);
  }

  Input[0].close();
} 

TH1D* Pseudo::CreatePseudoHisto(TH1D *h1, Int_t Ntoys){
  bool rebin = false;
  

  if(!rebin) {
  h1_pseudo = (TH1D*)h1->Clone();
  N_bins =h1->GetXaxis()->GetNbins();
  }
  else h1_pseudo = new TH1D(h1->GetName(), h1->GetTitle(), N_bins, BINS);

  w = new RooWorkspace();
  w->factory("Gaussian::gaus(x[0,10000],mean[100000],sigma[10000])");
  
  
  for (UInt_t i=1; i<=N_bins; i++) {
    
    Double_t BinCont = h1->GetBinContent(i);
    if (BinCont < 0.) BinCont *= -1;    

    if(BinCont != 0){
      
      w->var("x")->setMax(5.0*BinCont);
      w->var("mean")->setVal(BinCont);
      w->var("sigma")->setVal(TMath::Sqrt(BinCont));
      // Create pseudoData   
      RooDataSet* Odata = w->pdf("gaus")->generate(*w->var("x"), Ntoys);
      Mean = Odata->mean(*w->var("x"));  
      Sigma = Odata->sigma(*w->var("x"));
      Mean_I = TMath::Nint(Mean); 
      delete Odata;
      
      h1_pseudo->SetBinContent(i,Mean_I);
      h1_pseudo->SetBinError(i,Sigma);
      
      
    } else{
      h1_pseudo->SetBinContent(i,0.);
      h1_pseudo->SetBinError(i,0.); 
      // Set O bin content
    }
    
    
  } // loop
  
  delete w;
  std::cout << " Pseudo data generated for: " << h1->GetTitle() << std::endl; 
  return h1_pseudo;
}

void Pseudo::SaveFile(TH1D *h1){

 string hname=h1->GetTitle();
 Output = new TFile(("./histos/pseudodata/"+hname+".root").c_str(),"RECREATE");
 h1->Write();
 Output->Close(); 
 
 outpseudo << hname;
 outpseudo << endl;
  
}

Pseudo::~Pseudo(){
}
