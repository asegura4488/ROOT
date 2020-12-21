void compile_classes(){
  
  gROOT->ProcessLine(".x src/Particle.cc++");
  gROOT->ProcessLine(".x src/Evolution.cc++");

}
