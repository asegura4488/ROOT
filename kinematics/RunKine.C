void RunKine(Int_t compile=0){

 gROOT->Reset();
 if(compile ==1) gROOT->ProcessLine(".x compile_classes.C"); 

 gSystem->Load("src/Particle_cc.so");

 gROOT->ProcessLine(".L Kinematics.C");
 gROOT->ProcessLine("Kinematics()");

}
