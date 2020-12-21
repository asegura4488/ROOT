#include "include/Evolution.h"

void MainCode(){

//Creating frame for buttons
Evolution *Evol = new Evolution(gClient->GetRoot(),800,800);
Evol->DrawF();

Particle *p1 = new Particle(0.,20.,0.,5.,7.,0.,0.,-9.81,0.);
Evol->SetParticle(p1);

}

int main(){

MainCode();
return 0;

}
