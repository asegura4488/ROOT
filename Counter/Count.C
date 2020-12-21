// root -l 
// Correr usando .x Count.C++


#include <TTimer.h> 
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>

#include <iostream>

int i=0;
TCanvas *c1;
TH1D *h1;
TF1 *f1;
TTimer *counter;

void Init();
void Destructor();
void Count();
void Update(int &);
void Print(TH1D *);


// Methods

void Init(){
  c1 = new TCanvas("c1","Example", 200,100,600,400 );
  h1 = new TH1D("h1","Example", 11, 0.,11.);
  f1 = new TF1("f1","sin(x)",0,10); 
}
void Destructor(){
delete h1; 
delete f1;
delete counter;
}

void Count(){
  Init();
  //Timer constructor
  counter = new TTimer("Update(i)", 100);
  counter->TurnOn();
  // Usando esto el valor de i no cambia globalmente 
  
}

void Update(int &k){
  k++;
  std::cout << " Generation: " << k << std::endl;

  c1->Clear();

  h1->Fill(k);
  Print(h1);
    
  c1->Modified();
  c1->Update();
  
  h1->Reset();
  

  if( k == 10 ){
    counter->TurnOff();
    Destructor(); 
  }  
}

void Print(TH1D *h){
h->Draw();
}



int main(){
Count();
return 0;
}






