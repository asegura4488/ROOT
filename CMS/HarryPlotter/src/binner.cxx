#include "binner.h"

binner::binner(): 
  N_bins(0){
}

void binner::Init(string file){
  
  Input[0].open(("config/Bins/"+file+".in").c_str());
  if(!Input[0]) {
    std::cout << "could not open file config bin file" <<std::endl;
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
  
  //Histogram to rebinning
  
  
  
}

void binner::Weight_Init(string file){

   Input[1].open(("config/Weights/"+file+".in").c_str());
   if(!Input[1]) {
    std::cout << "could not open file weights file" <<std::endl;
    exit(1);
  } 

  Double_t weights_ = 0;
  Double_t errors_ = 0;

  while(!Input[1].eof()){
    Input[1] >> weights_;
    Input[1] >> errors_;
    weights.push_back(weights_);    
    errors.push_back(errors_);    

  }
  weights.pop_back();
  errors.pop_back();

 
}



void binner::ApplyWeight(TH1D **h1){
  
  
  Int_t NbinsX =  (*h1)->GetXaxis()->GetNbins();
  
 //Fill the maps of weights
  for(Int_t i = 1; i <= NbinsX; i++){
  Weight[i] = weights[i-1];
  Error[i] = errors[i-1]; 
  cout <<  i << " " <<Weight[i] <<  " " << Error[i] <<endl;
 
  }
 
  
  Double_t value=0.;
  Double_t error=0.;
  Double_t ratio=0.;
 	 for(Int_t i = 1; i <=  NbinsX; i++){
         if((*h1)->GetBinContent(i) != 0.) 
		ratio = (*h1)->GetBinError(i)/(*h1)->GetBinContent(i);
         else ratio = 0.;

         value = Weight[i]*(*h1)->GetBinContent(i);
	 error = (pow(value,2))*(pow(ratio,2)+pow(Error[i]/Weight[i],2));

       //  error += value; //poissonian error      
         
         if(sqrt(error) > value) error = TMath::Power(value,2); 
  
         if(error > 0.) cout << i << " new "  << sqrt(error) << " old " << (*h1)->GetBinError(i) <<  " ratio  "<< ratio << " ratio_H " <<  Error[i]/Weight[i] << " entry " << (*h1)->GetBinContent(i) << " value " << value << endl; 
         
          (*h1)->SetBinContent(i, value);
          (*h1)->SetBinError(i, sqrt(error));
         
         }
  
}



void binner::Rebinner(TH1D **h_old, UInt_t key){
  
  string name = static_cast<std::ostringstream*>(&(std::ostringstream() << key))->str();
  h_new = new TH1D(name.c_str(), (*h_old)->GetName(), N_bins, BINS);
  
  Int_t old_nbins = (*h_old)->GetXaxis()->GetNbins(); 
  Int_t new_nbins = h_new->GetXaxis()->GetNbins();
  
  for (int b = 1; b <= new_nbins; b++ ){
    Double_t Right_edge_new = h_new->GetXaxis()->GetBinLowEdge(b)+h_new->GetXaxis()->GetBinWidth(b);
    Double_t Edge_new = h_new->GetXaxis()->GetBinLowEdge(b);
    Double_t Num_back = 0.;
    Double_t error_back = 0.;
    
    for (int i = 1; i <= old_nbins; i++ ){
      Double_t Right_edge_old = (*h_old)->GetXaxis()->GetBinLowEdge(i)+(*h_old)->GetXaxis()->GetBinWidth(i);
      
  if((Right_edge_old <= Right_edge_new) && (Right_edge_old > Edge_new)){ //Relevant Condition
    
    Num_back += (*h_old)->GetBinContent(i);
    error_back += TMath::Power( (*h_old)->GetBinError(i), 2 ) ;
    
  }
  else continue;
  
  h_new->SetBinContent(b, Num_back);
  h_new->SetBinError(b, TMath::Sqrt(error_back));
  
    } // loop over the old hist
  } // loop over the new hist
  
 h_new->Sumw2(); 
 (*h_old) = h_new;
 
 
}


void binner::BinWidth(TH1D **h1){

  UInt_t bins = (*h1)->GetXaxis()->GetNbins();
  UInt_t BinWidth = 0; 
  for (UInt_t b = 1; b <= bins; b++ ){
  BinWidth = BINS[b]-BINS[b-1];
  //BinWidth = (*h1)->GetXaxis()->GetBinWidth(b);   
  (*h1)->SetBinContent(b,(*h1)->GetBinContent(b)/BinWidth); 
  (*h1)->SetBinError(b,(*h1)->GetBinError(b)/BinWidth); 
  }
 
}


void binner::Poisson_error(TH1D **h1, bool binW){
  
 UInt_t Nbins = (*h1)->GetXaxis()->GetNbins(); 
 
 Double_t bincontent = 0.;
 UInt_t binwidth = 0;
 for(UInt_t i = 0; i < Nbins ; i++){
 
 bincontent = (*h1)->GetBinContent(i+1);
 binwidth = (*h1)->GetXaxis()->GetBinWidth(i+1);

 if(bincontent <= 0.){  

   if(binW){
   cout << " bin empty for Data: " << i+1 << " --- Calculating the error in this bin --- " << 1.84/binwidth << endl;  
   (*h1)->SetBinError(i+1, 1.84/binwidth);
   }
   else{
   cout << " bin empty for Data: " << i+1 << " --- Calculating the error in this bin --- " << 1.84 << endl;  
   (*h1)->SetBinError(i+1, 1.84);
   }
 
 }

 }

}





binner::~binner(){ 
  //delete[] BINS;
}

