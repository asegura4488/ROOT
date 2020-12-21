#include "include/Particle.h"
#include "include/Evolution.h"

Particle *p1;
Evolution *myevol;

TGraph *PX;
TGraph *PY;
TGraph *VX;
TGraph *VY;
TGraph *A;


void Kinematics(){

p1 = new Particle(0.0,0.0,0.0,0.0);
p1->SetGravity(-9.81);
p1->Showr0();

PX = p1->GenericG("t[s]","X[m]");
PY = p1->GenericG("t[s]","Y[m]");
VX = p1->GenericG("t[s]","Vx[m/s]");
VY = p1->GenericG("t[s]","Vy[m/s]");
A = p1->GenericG("t[s]","a[m/s^{2}]");

myevol = new Evolution(0.01);
myevol->Start();
//myevol->Stop();
//delete myevol;

}


int main(){
Kinematics();
return 0;
}
