#ifndef Particle_h
#define Particle_h

#include "TVector3.h"

class Particle{

 public:
	Particle();
        Particle(Double_t x0_,  Double_t y0_, Double_t z0_, 
		 Double_t vx0_, Double_t vy0_, Double_t vz0_,
		 Double_t ax0_, Double_t ay0_, Double_t az0_);

	virtual ~Particle();

        void SetPosition(Double_t x_, Double_t y_, Double_t z_);
        TVector3* GetPosition();
        void SetVelocity(Double_t vx_, Double_t vy_, Double_t vz_);
        TVector3* GetVelocity(); 
        void SetAcceleration(Double_t ax_, Double_t ay_, Double_t az_, Double_t TIME);
        TVector3* GetAcceleration();

        void ChangeVectors(Double_t);
        void Reset();

        Particle & operator = (const Particle &);
        
 private:
  
   TVector3 Position0; 
   TVector3 Velocity0;
   TVector3 Acceleration0;

   TVector3 ResetPosition0; 
   TVector3 ResetVelocity0;
   TVector3 ResetAcceleration0;


   TVector3 Position; 
   TVector3 Velocity;
   TVector3 Acceleration;

   Double_t Deltat;   

};

#endif
