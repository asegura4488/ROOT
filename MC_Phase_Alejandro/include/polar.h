

#define PI 3.141592654

Float_t polar(TLorentzVector ppp)
{
  
  Float_t pang1 = 0;   // Polar angle
  
  Float_t ppptot = 0;  // Total momentum
  ppptot = sqrt(ppp.E()*ppp.E() - ppp.M2());   // momentum

  
  if(ppptot != 0 && (ppp.Pz()<=ppptot)){
    pang1 = acos(ppp.Pz()/ppptot);
  }
  else 
    pang1 = 0;
  
  return pang1;
}
