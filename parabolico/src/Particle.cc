#include "../include/Particle.h"

Particle::Particle(){
}

Particle::Particle(Double_t x0_,  Double_t y0_, Double_t z0_, 
		   Double_t vx0_, Double_t vy0_, Double_t vz0_,
		   Double_t ax0_, Double_t ay0_, Double_t az0_):
 	Position0(x0_,y0_,z0_),
	Velocity0(vx0_,vy0_,vz0_),
	Acceleration0(ax0_,ay0_,az0_),
	Deltat(0.){

   Position.SetXYZ(0.,0.,0.);
   Velocity.SetXYZ(0.,0.,0.);
   Acceleration.SetXYZ(0.,0.,0.);

   ResetPosition0 = Position0;
   ResetVelocity0 = Velocity0;
   ResetAcceleration0 = Acceleration0;

}

void Particle::SetPosition(Double_t x_, Double_t y_, Double_t z_){
Position.SetXYZ(x_,y_,z_);
}

TVector3* Particle::GetPosition(){
return &Position;
}

void Particle::SetVelocity(Double_t vx_, Double_t vy_, Double_t vz_){
Velocity.SetXYZ(vx_,vy_,vz_);
}

TVector3* Particle::GetVelocity(){
return &Velocity;
}

void Particle::SetAcceleration(Double_t ax_, Double_t ay_, Double_t az_, Double_t TIME){

 Acceleration0.SetXYZ(ax_,ay_,az_);
 Position0 = Position;
 Velocity0 = Velocity;
 Deltat = TIME;

}

TVector3* Particle::GetAcceleration(){
return &Acceleration;
}

void Particle::ChangeVectors(Double_t t){

  t -= Deltat;
  Position = Position0 + Velocity0*t + Acceleration0*0.5*TMath::Power(t,2);
  Velocity = Velocity0 + Acceleration0*t;
  Acceleration = Acceleration0;
  
}

void Particle::Reset(){
 
  Position0 = ResetPosition0;
  Velocity0 = ResetVelocity0;
  Acceleration0 = ResetAcceleration0;
  Deltat=0.;

}

Particle & Particle::operator = (const Particle & p) {
    Position0 = p.Position0;
    Velocity0 = p.Velocity0;
    Acceleration0 = p.Acceleration0;
    return *this;
}

Particle::~Particle(){
}

