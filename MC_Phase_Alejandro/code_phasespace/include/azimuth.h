

#define PI 3.141592654

float azimuth(TLorentzVector p)
{
  
  float ffi = 0;
  
  if(p.Px() != 0){
    ffi = atan(p.Py()/p.Px());
    if(p.Px() < 0)
      ffi = PI + ffi;
  }

  else{ 
    if(p.Py() > 0)
      ffi = PI/2;
    else if(p.Py() == 0)
      ffi = 0;
    else
      ffi = -PI/2;
  }

  
  if(ffi < 0)
    ffi = ffi + 2*PI;
  
  
  return ffi;
  
}
