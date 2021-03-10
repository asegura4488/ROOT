void Creator(){

   TFile *File1 = TFile::Open("data.root","READ");
   TFile *File2 = TFile::Open("bkg.root","READ");

   

   TFile *File3 = TFile::Open("chargino100_stau90_lsp80.root","READ");
 //  TFile *File3 = TFile::Open("chargino400_stau380_lsp360.root","READ");
  
/*
   TH1D *hdata = (TH1D*)File1->Get("Tau1MetMt");
   TH1D *hbkg = (TH1D*)File2->Get("Tau1MetMt");
   TH1D *hsignal = (TH1D*)File3->Get("Tau1MetMt");
*/


   TH1D *hdata = new TH1D("hdata","hdata", 1, 0. , 20.);
   hdata->Sumw2();
   TH1D *hbkg = new TH1D("hbkg","hbkg", 1, 0. , 20.);
   hbkg->Sumw2();
   TH1D *hsignal = new TH1D("hsignal","hsignal", 1, 0. , 20.);
   hsignal->Sumw2();


   for(int i = 0; i < 10; i++){
 	 hdata->Fill(1);
         }
   for(int i = 0; i < 8; i++) { 
         hbkg->Fill(2);
	 }
   for(int i = 0; i < 20; i++) {
 	 hsignal->Fill(4);
	 }
/*
   for(int i = 0; i < 100; i++){
 	 hdata->Fill(11);
         }
   for(int i = 0; i < 90; i++) { 
         hbkg->Fill(12);
	 }
   for(int i = 0; i < 150; i++) {
 	 hsignal->Fill(15);
	 }
*/

   hdata->Draw();
   hdata->GetYaxis()->SetRangeUser(0.,320.);
   hdata->SetLineColor(1);

   hbkg->Draw("same");
   hbkg->SetLineColor(2);

   hsignal->Draw("same");
   hsignal->SetLineColor(4);

   TFile *MyFile = new TFile("histos.root","RECREATE");
   TDirectory *histos = MyFile->mkdir("histos");  
   histos->cd();

   hdata->Write();
   hbkg->Write();
   hsignal->Write(); 

   MyFile->cd();


   RooWorkspace *w; 
   RooStats::HistFactory::Measurement *Measure_ = new RooStats::HistFactory::Measurement("measure","measure");
   Measure_->SetOutputFilePrefix( "measure" );
   Measure_->SetPOI("mu");	
   Measure_->SetLumi(1.0);
   Measure_->SetLumiRelErr(0.0);
   Measure_->AddConstantParam("Lumi");

   RooStats::HistFactory::Data *Data_ = new RooStats::HistFactory::Data();
   Data_->SetHisto(hdata);

   RooStats::HistFactory::Sample *TMC_ = new RooStats::HistFactory::Sample("TMC_");
  // TMC_->AddOverallSys("BkgSys", 0.94, 1.06); 
   TMC_->SetHisto(hbkg);

   RooStats::HistFactory::Sample *Signal_ = new RooStats::HistFactory::Sample("Signal_");
   Signal_->AddNormFactor("mu",1,0.,3.);
 //  Signal_->AddOverallSys("AccSys", 0.95, 1.05);
   Signal_->SetHisto(hsignal);


    RooStats::HistFactory::Channel *Channel_;
    RooStats::HistFactory::HistoToWorkspaceFactoryFast *H1;

    Channel_ = new RooStats::HistFactory::Channel("Channel");
  //  Channel_->SetStatErrorConfig(0.05, "Poisson");

    Channel_->SetData(*Data_) ;   // Add the DATA to the channel
    Channel_->AddSample(*Signal_) ; // Add the SIGNAL to the channel
    Channel_->AddSample(*TMC_) ;    // Add the BACKGROUND to the channel
    Measure_->AddChannel(*Channel_);

    H1 = new RooStats::HistFactory::HistoToWorkspaceFactoryFast(*Measure_);
    w = H1->MakeCombinedModel(*Measure_);
    w->writeToFile("workspace.root");

    w->Print("t");


    MyFile->Close(); 

}

int main(){

	Creator();
	return 0;
}
