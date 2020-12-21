void RunAll(Int_t compile=0){

 gROOT->Reset();
 if(compile ==1) gROOT->ProcessLine(".x compile_classes.C"); 

 //Load Cargar classes
 gSystem->Load("src/LoadFiles_cxx.so");
 gSystem->Load("src/Pseudo_cxx.so");
 gSystem->Load("src/Workspace_cxx.so");
 gSystem->Load("src/HMethods_cxx.so"); 
 //Run
 gROOT->ProcessLine(".L MakeWorkspaces.C");
 gROOT->ProcessLine(".L Hypothesis.C"); 

 Int_t control=0;
 std::cout << " Create Rooworkspace: 0 " << " Run Hypothesis methods: 1" << std::endl;  
 std::cin >> control;
 //control = 1;
 if(control==0){
 gROOT->ProcessLine("MakeWorkspaces()");
 }
 else if(control==1){
 gROOT->ProcessLine("Hypothesis()");
 }
 else{ 
 std::cout << " No valid option " << std::endl; 
 exit(1);  
 }
 
}


