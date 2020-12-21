void Run(Int_t compile = 0){

 gROOT->Reset();
 if(compile == 0) gROOT->ProcessLine(".x compile_classes.C"); 
 
 
 gSystem->Load("src/Evolution_cc.so");

 gROOT->ProcessLine(".L MainCode.C");
 gROOT->ProcessLine("MainCode()");


}
