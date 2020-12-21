
std::vector<string> Input;
std::vector<string> Input_;
std::vector<string> Directory;
std::vector<string> Histo;
std::vector<string> Histo2D;


TFile *File_[6];
TH1D *Jet_[50];
TH1D *HEl_[50];
TH1D *HMu_[50];
TH1D *HTau_[50];
TH2D *HCor_[50];

TList *LElectron[6];   
TList *LMuon[6];
TList *LTau[6];
TList *LJet[6];
TList *LH2D[6];

TLegend *leg = new TLegend(0.50501,0.6394293,0.8767535,0.8845655,NULL,"brNDC");

void fill(){

 string background = "/home/UANDES/ma.segura10/Software/Languages/plotter/data/background/";
 string signal = "/home/UANDES/ma.segura10/Software/Languages/plotter/data/signal/";
 
 Input.push_back(background+"W+Jets.root");
 Input.push_back(background+"DY+Jets.root");
 Input.push_back(background+"ttbar.root");
 Input.push_back(background+"VV.root");

  Input.push_back(signal+"chargino180_stau155_lsp150.root");
  Input.push_back(signal+"chargino300_stau155_lsp150.root");

 Input_.push_back("W+Jets_");
 Input_.push_back("DY+Jets_");
 Input_.push_back("ttbar_");
 Input_.push_back("VV_");
 Input_.push_back("chargino180_stau155_lsp150_");
 Input_.push_back("chargino300_stau155_lsp150_");


   for(UInt_t i = 0 ; i < Input.size(); i++){
//  std::cout << Input[i] << endl;
  } 

 Directory.push_back("electron_cuts");
 Directory.push_back("muon_cuts");
 Directory.push_back("tau_cuts");
 ////////////// Histos
 
 Histo.push_back("electron_pt");
 Histo.push_back("electron_met_phi");
 Histo.push_back("tr_mass_el");

 Histo.push_back("muon_pt");
 Histo.push_back("muon_met_phi");
 Histo.push_back("tr_mass_mu");

 Histo.push_back("tau_pt");
 Histo.push_back("tau_met_phi");
 Histo.push_back("tr_mass_tau");

 Histo.push_back("jet_pt");
 Histo.push_back("MET");


 Histo2D.push_back("Pt_lead_jet_vs_MET");
 Histo2D.push_back("MET_vs_Dphi_sleadjet_met");
 Histo2D.push_back("MET_vs_Dphi_leadjet_el");
 Histo2D.push_back("MET_vs_Dphi_leadjet_mu");
 Histo2D.push_back("MET_vs_Dphi_leadjet_tau");

 
 
}

void fillFile(){
 
  for(UInt_t i = 0 ; i < Input.size(); i++){
  File_[i] = TFile::Open((Input[i]).c_str(),"READ");
  if(!File_[i]) exit(1);
  }
 
}

void Scale1D(TH1D **h1){

  Double_t Integral = 0.;
  Integral = (*h1)->Integral();
 // cout << Integral << endl;
  if(Integral != 0.)(*h1)->Scale(1.0/Integral);

}

void Scale2D(TH2D **h2){

  Double_t Integral = 0.;
  Integral = (*h2)->Integral();
//  cout << Integral << endl;
  if(Integral != 0.)(*h2)->Scale(1.0/Integral);

}

void SetHisto(Int_t i, TH1D **h1, string label){

  (*h1)->SetStats(kFALSE);
  (*h1)->GetYaxis()->SetTitle("a.u.");
  (*h1)->SetTitle("");
  (*h1)->SetLineWidth(1);
 
  if(i==0) (*h1)->SetLineColor(1);
  else if(i==1) (*h1)->SetLineColor(2);
  else if(i==2) (*h1)->SetLineColor(4); 
  else if(i==3) (*h1)->SetLineColor(3);


  else if(i==4 || i==5) {
   (*h1)->SetLineColor((kViolet+10));
   (*h1)->SetLineWidth(3);
   (*h1)->SetLineStyle(2);
   if(i==5)(*h1)->SetLineColor((kCyan-
4)); 
  
   }
  
  
  if(label == "muon_pt") {
     (*h1)->GetXaxis()->SetTitle("p_{T}(#mu)[GeV]");
     (*h1)->GetXaxis()->SetRangeUser(10.,100);
     (*h1)->GetYaxis()->SetRangeUser(0.0001,0.3);
     }
  if(label == "tau_pt"){
    (*h1)->GetXaxis()->SetTitle("p_{T}(#tau)[GeV]");
    (*h1)->GetXaxis()->SetRangeUser(10.,100);
    (*h1)->GetYaxis()->SetRangeUser(0.0001,0.3);
    }
  if(label == "electron_pt"){
     (*h1)->GetXaxis()->SetTitle("p_{T}(e)[GeV]"); 
     (*h1)->GetXaxis()->SetRangeUser(10.,100);
     (*h1)->GetYaxis()->SetRangeUser(0.0001,0.3); 
    }

  if(label == "tr_mass_mu" || label == "tr_mass_el" || label == "tr_mass_tau"){
   (*h1)->GetXaxis()->SetRangeUser(0.,300);
   (*h1)->GetYaxis()->SetRangeUser(0.0001,0.4); 
  
  if(label == "tr_mass_mu") (*h1)->GetXaxis()->SetTitle("m_{T}(#mu, p_{T}^{miss})[GeV]");  
  if(label == "tr_mass_el") (*h1)->GetXaxis()->SetTitle("m_{T}(e, p_{T}^{miss})[GeV]");  
  if(label == "tr_mass_tau") (*h1)->GetXaxis()->SetTitle("m_{T}(#tau, p_{T}^{miss})[GeV]");

  }

  if(label == "jet_pt"){
     (*h1)->GetXaxis()->SetTitle("p_{T}(j)[GeV]");
     (*h1)->GetXaxis()->SetRangeUser(90.,500);
     (*h1)->GetYaxis()->SetRangeUser(0.0001,0.2); 
     }
  if(label == "MET"){
    (*h1)->GetXaxis()->SetTitle("p_{T}^{miss}[GeV]");
     (*h1)->GetXaxis()->SetRangeUser(100.,500);
     (*h1)->GetYaxis()->SetRangeUser(0.0001,0.2); 
   }
}



void SetHisto2D(Int_t i, TH2D **h2, string label){

  (*h2)->SetStats(kFALSE);
  (*h2)->SetTitle("");

  if(label == "Pt_lead_jet_vs_MET"){
    (*h2)->GetXaxis()->SetTitle("p_{T}(j)[GeV]");
    (*h2)->GetYaxis()->SetTitle("p_{T}^{miss}[GeV]");
  }
  if(label == "MET_vs_Dphi_sleadjet_met"){
   (*h2)->GetXaxis()->SetTitle("#Delta #phi (j, p_{T}^{miss})");
   (*h2)->GetYaxis()->SetTitle("p_{T}^{miss}[GeV]");
  }
  if(label == "MET_vs_Dphi_leadjet_el"){
   (*h2)->GetXaxis()->SetTitle("#Delta #phi (e, p_{T}^{miss})");
   (*h2)->GetYaxis()->SetTitle("p_{T}^{miss}[GeV]");
  }
   if(label == "MET_vs_Dphi_leadjet_mu"){
   (*h2)->GetXaxis()->SetTitle("#Delta #phi (#mu, p_{T}^{miss})");
   (*h2)->GetYaxis()->SetTitle("p_{T}^{miss}[GeV]");
  }
   if(label == "MET_vs_Dphi_leadjet_tau"){
   (*h2)->GetXaxis()->SetTitle("#Delta #phi (#tau, p_{T}^{miss})");
   (*h2)->GetYaxis()->SetTitle("p_{T}^{miss}[GeV]");
  }


}

void SetLegend(TH1D *h1, string Label){
 
 leg->SetBorderSize(0);
 leg->SetLineColor(1);
 leg->SetLineStyle(1);
 leg->SetLineWidth(1);
 leg->SetFillColor(0);
 leg->SetFillStyle(1001);
 TLegendEntry *entry=leg->AddEntry(h1,Label.c_str(),"l");
 entry->SetTextFont(42);

}


void fillHistos(){


 for(UInt_t i = 0 ; i < Input.size(); i++){

 LElectron[i] = new TList();
 LMuon[i] = new TList();
 LTau[i] = new TList();
 LJet[i] = new TList();


 Int_t Direc_jet = 0;
 for(UInt_t j = 0 ; j < Histo.size(); j++){
 if(j==0 || j==1 || j==2){
 HEl_[j] = (TH1D*)File_[i]->Get((Directory[0]+"/"+Histo[j]).c_str());
 Scale1D(&HEl_[j]); 
 SetHisto(i,&HEl_[j], Histo[j]); 
 if(j==0) SetLegend(HEl_[j], Input_[i]);
 LElectron[i]->Add(HEl_[j]); 
 }
 else if(j==3 || j==4 ||j==5){ 
    HMu_[j] = (TH1D*)File_[i]->Get((Directory[1]+"/"+Histo[j]).c_str());
    if(!HMu_[j]) exit(1);
    Scale1D(&HMu_[j]);
    SetHisto(i,&HMu_[j], Histo[j]);
    LMuon[i]->Add(HMu_[j]); 
 }
 else if(j==6 || j==7 ||j==8){
   HTau_[j] = (TH1D*)File_[i]->Get((Directory[2]+"/"+Histo[j]).c_str()); 
   if(!HTau_[j]) exit(1);
   Scale1D(&HTau_[j]); 
   SetHisto(i,&HTau_[j], Histo[j]);
   LTau[i]->Add(HTau_[j]);
  }
 else if(j==9 || j==10){
   Jet_[j] = (TH1D*)File_[i]->Get((Directory[Direc_jet]+"/"+Histo[j]).c_str()); 
   if(!Jet_[j]) exit(1);
   Scale1D(&Jet_[j]); 
   SetHisto(i,&Jet_[j], Histo[j]); 
   LJet[i]->Add(Jet_[j]);
 }

 } // loop 1D
   
 // For 2D
 LH2D[i] = new TList();
 Int_t Direc_i = 0;
 for(UInt_t j = 0 ; j < Histo2D.size(); j++){
  HCor_[j] = (TH2D*)File_[i]->Get((Directory[Direc_i]+"/"+Histo2D[j]).c_str()); 
  if(!HCor_[j]) exit(1);
 // Scale2D(&HCor_[j]);  
  SetHisto2D(i,&HCor_[j], Histo2D[j]);
  LH2D[i]->Add(HCor_[j]);
 }
  

 } // For loop over input files

  
}

void Plot(TList *List[6], string label){

 TCanvas* c1 = new TCanvas("c1","Plotting",1000,800);
 c1->SetLogy(); 

 for(UInt_t i = 0 ; i < Input.size(); i++){
 //List[i]->Print();
 if(i==0)((TH1D*)(List[i]->FindObject(label.c_str())))->Draw("hist");
 else ((TH1D*)(List[i]->FindObject(label.c_str())))->Draw("hist, same"); 
 }
 leg->Draw();
 c1->SaveAs(("plots/"+label+".eps").c_str());
}

void Plot2D(TList *List[6], string label){
  
 TCanvas* c1 = new TCanvas("c1","Plotting",800,800);

 for(UInt_t i = 0 ; i < Input.size(); i++){
 ((TH2D*)(List[i]->FindObject(label.c_str())))->Draw("colz");
 c1->SaveAs(("plots/2D/"+Input_[i]+label+".eps").c_str());
 }
 

 
}


void PlotListPheno(){
fill();
fillFile();
fillHistos();

  for(UInt_t j = 0 ; j < Histo.size(); j++){
    if(j==0 || j==1 || j==2) Plot(LElectron, Histo[j]);
    else if(j==3 || j==4 ||j==5) Plot(LMuon, Histo[j]);
    else if(j==6 || j==7 ||j==8) Plot(LTau, Histo[j]);
    else if(j==9 || j==10) Plot(LJet, Histo[j]);
  }

   for(UInt_t j = 0 ; j < Histo2D.size(); j++){
  // Plot2D(LH2D, Histo2D[j]);  
   }
 
}


int main(){
PlotListPheno();
return 0;
}
