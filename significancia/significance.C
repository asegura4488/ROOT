
Double_t GetSignificance(Double_t Ns, Double_t Nb){

  Double_t sig = 0.;

  if(Ns+Nb != 0.) sig = Ns/(TMath::Sqrt(Ns+Nb));
 
  return sig;

}

void significance(){
 
// TFile *s1 = TFile::Open("/home/alejandro/Libros/Data/PhenoISRMultiChannel/Normalized_100/chargino180_stau155_lsp150.root");
 TFile *s1 = TFile::Open("/home/alejandro/Libros/Data/PhenoISRMultiChannel/Normalized_100/chargino300_stau155_lsp150.root");
 TFile *bkg1 = TFile::Open("/home/alejandro/Libros/Data/PhenoISRMultiChannel/Normalized_100/DY+Jets.root"); 
 TFile *bkg2 = TFile::Open("/home/alejandro/Libros/Data/PhenoISRMultiChannel/Normalized_100/W+Jets.root"); 
 TFile *bkg3 = TFile::Open("/home/alejandro/Libros/Data/PhenoISRMultiChannel/Normalized_100/ttbar.root");  
 TFile *bkg4 = TFile::Open("/home/alejandro/Libros/Data/PhenoISRMultiChannel/Normalized_100/WW.root"); 
 TFile *bkg5 = TFile::Open("/home/alejandro/Libros/Data/PhenoISRMultiChannel/Normalized_100/WZ.root"); 
 TFile *bkg6 = TFile::Open("/home/alejandro/Libros/Data/PhenoISRMultiChannel/Normalized_100/ZZ.root"); 
 
 if(!s1) {
   std::cout << " No encontrado " << std::endl;
   exit(1);  
   }

 string histo = "electron_cuts/tr_mass_el";
// string histo = "muon_cuts/tr_mass_mu";
// string histo = "tau_cuts/tr_mass_tau";

 TH1D *sh1 = (TH1D*)s1->Get(histo.c_str());
 TH1D *bh1 = (TH1D*)bkg1->Get(histo.c_str()); 
 TH1D *bh2 = (TH1D*)bkg2->Get(histo.c_str()); 
 TH1D *bh3 = (TH1D*)bkg3->Get(histo.c_str()); 
 TH1D *bh4 = (TH1D*)bkg4->Get(histo.c_str()); 
 TH1D *bh5 = (TH1D*)bkg5->Get(histo.c_str());
 TH1D *bh6 = (TH1D*)bkg6->Get(histo.c_str());
 sh1->Sumw2();

 Double_t Ns = 0.;
 Double_t Nb = 0.;

 Ns = sh1->Integral();
 Nb += bh1->Integral();
 Nb += bh2->Integral();
 Nb += bh3->Integral();
 Nb += bh4->Integral();
 Nb += bh5->Integral();
 Nb += bh6->Integral();

 Double_t Significance = 0.;
 Significance = GetSignificance(Ns,Nb);

 std::cout << Ns << " " << Nb <<  " Significance Global " << Significance << endl;
 
 UInt_t Nbins = sh1->GetXaxis()->GetNbins();
 TH1D *HSig = (TH1D*)sh1->Clone();
 HSig->SetTitle("");
 HSig->GetXaxis()->SetTitle("m_{T}(e, p_{T}^{miss})");
 HSig->GetYaxis()->SetTitle("S/#sqrt{S+B}/bin");
 HSig->Reset();

  for( UInt_t i = 1; i <= Nbins; i++ ){

    Double_t Ns_ = 0.;
    Double_t Nb_ = 0.;
    
    Ns_ = sh1->GetBinContent(i);
    Nb_ += bh1->GetBinContent(i);
    Nb_ += bh2->GetBinContent(i);
    Nb_ += bh3->GetBinContent(i); 
    Nb_ += bh4->GetBinContent(i);
    Nb_ += bh5->GetBinContent(i);
    Nb_ += bh6->GetBinContent(i);  
  //  std::cout << Ns_ << " " << Nb_ << endl; 
    
    Double_t SigbyBin = GetSignificance(Ns_,Nb_);
   // std::cout << SigbyBin << endl;
    HSig->SetBinContent(i,SigbyBin);
//    HSig->SetBinError(i,TMath::Sqrt(SigbyBin));
    HSig->SetBinError(i,0.);

  }

 
 HSig->Draw();


// sh1->Draw();
// std::cout << sh1->Integral() << std::endl;


}

int main(){

significance();
return 0;

}
