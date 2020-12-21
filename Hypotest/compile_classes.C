void compile_classes(){
  
  gROOT->ProcessLine(".x src/LoadFiles.cxx++");
  gROOT->ProcessLine(".x src/Pseudo.cxx++");
  gROOT->ProcessLine(".x src/Workspace.cxx++");
  gROOT->ProcessLine(".x src/HMethods.cxx++");

}
