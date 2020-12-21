void RunAll(Int_t compile=0){

 gROOT->Reset();
 if(compile==1) gROOT->ProcessLine(".x compile_classes.C"); 

 gSystem->Load("src/binner_cxx.so");
 gROOT->ProcessLine(".L Binner.C");
 gROOT->ProcessLine("Binner()"); 
  

}
