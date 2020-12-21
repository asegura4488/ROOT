vector<string> files;

void fill_info(){
 // files.push_back("allData");
 // files.push_back("output");
  files.push_back("DQM_CPPF");
}


void readhistos(){
  fill_info();
  
  TFile *F = TFile::Open(("data/"+files[0]+".root").c_str());
  //TFile *out = new TFile(("data/"+files[1]+".root").c_str(), "RECREATE");

  //TString path( (char*)strstr( F->GetPath(), ":")); //returns first occurrence in str1, specified in str2
  
  //path.Remove(0, 2); //remove the :/
  //cout << path << endl;
  
  //List of normalized histos

  
  TList* list_histos;
  list_histos = new TList(); 

  //F->cd("METCut");
  TDirectory *current_dir = gDirectory;
  Bool_t status = TH1::AddDirectoryStatus();
  //cout << status << endl;
  //TH1::AddDirectory(kFALSE);
  //gDirectory->pwd();
  
  TIter nextkey(current_dir->GetListOfKeys());
  TKey *key;

  string foldername;
  string histname;
  
  while((key=(TKey*)nextkey())){
 
    if(key->IsFolder()){
      current_dir->cd(key->GetName());
      TDirectory *sub_current_dir = gDirectory;
      TIter nextkey2(sub_current_dir->GetListOfKeys());
      TKey *key2;
      while((key2=(TKey*)nextkey2())){
	TObject *obj2 = key2->ReadObj(); 
	histname = obj2->GetName();
	cout << histname << endl;
      }
      
    }
    
    TObject *obj = key->ReadObj();
    foldername = obj->GetName();

    cout << " Folder: " <<foldername << endl;
      
    if(!obj->IsA()->InheritsFrom( "TH1" )) continue;
    
     //  std::cout<< histname << std::endl;   
    
    //TH1 *read_obj = (TH1*)obj;
    //TH1D* fullhists = new TH1D("full", read_obj->GetTitle(), read_obj->GetXaxis()->GetNbins(), read_obj->GetXaxis()->GetXmin(), read_obj->GetXaxis()->GetXmax());

    // TKey *key2 = (TKey*)gDirectory->GetListOfKeys()->FindObject(read_obj->GetName());
    //if(key2){
    //  TH1* h2 = (TH1*)key2->ReadObj();
    //  fullhists=(TH1D*)h2;
    //  list_histos->Add(fullhists);
    //}   
    
    
  }

  // TH1D *h = (TH1D*)list_histos->At(1);
  // h->Draw();
  
  
}
int main(){
  readhistos();
  return 0;
}
