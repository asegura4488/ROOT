void RunAll(Int_t compile = 0){

gROOT->Reset();

if(compile == 1) gROOT->ProcessLine(".x compile_classes.C");

gSystem->Load("src/Methods_cc.so");


gROOT->ProcessLine(".L Confidence.C");
gROOT->ProcessLine("Confidence()");

}