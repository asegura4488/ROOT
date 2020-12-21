
#define RED "\033[31m"
#define BLUE "\033[34m"

vector<string> files;

void fill_info(){
  files.push_back("allData");
  files.push_back("output");
}

void readhistos_2(TDirectory *target){
  
  TFile *Input = TFile::Open(("data/"+files[0]+".root").c_str());

  TString path( (char*)strstr( target->GetPath(), ":")); //returns first occurrence in str1, specified in str2
  path.Remove(0, 2); //remove the :/
  cout << " Folder: " << RED << path << endl;
  
  //List of normalized histos
  
  
  TList* list_histos;
  list_histos = new TList(); 
  
  Input->cd( path );
  TDirectory *current_dir = gDirectory;
  Bool_t status = TH1::AddDirectoryStatus();
  TH1::AddDirectory(kFALSE);
  //gDirectory->pwd();
  
  string foldername;
  string histname;
  
  TIter nextkey(current_dir->GetListOfKeys());
  TKey *key;
  while((key=(TKey*)nextkey())){
    
    TObject *obj = key->ReadObj();
    
    // verify whether it is histo
    if ( obj->IsA() ==  TH1D::Class() || obj->IsA() ==  TH1F::Class() ) {
      TH1* readObj = (TH1*)obj;
      //cout << readObj->GetTitle() << BLUE << endl;

      //Drawing canvas
      target->cd();
      TCanvas *c = new TCanvas(readObj->GetName(), readObj->GetName());
      c->cd();
      c->Write(c->GetName());
      c->Close();
      
    }  
    // it is sub-directory     
    else if(obj->IsA()->InheritsFrom( TDirectory::Class())){
      target->cd();
      TDirectory *newdir = target->mkdir(obj->GetName(), obj->GetTitle());
      readhistos_2( newdir );
    
    }
       
  }

  target->SaveSelf(kTRUE);
  TH1::AddDirectory(status);
  
}
void read(){
  fill_info();
  TFile *output = new TFile(("data/"+files[1]+".root").c_str(), "RECREATE");  
  readhistos_2(output);
}
