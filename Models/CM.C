Double_t theta = 15.*TMath::Pi()/180.;
Double_t phi = 15.*TMath::Pi()/180.;

Double_t u = 20.;
Double_t masa = 10.;

Double_t MagCM(Double_t u, Double_t theta, Double_t phi){

  Double_t Mag = 0.;
  
  Mag = u*TMath::Sqrt(  pow(0.5*sin(theta-phi)/sin(theta+phi), 2.)+ pow(sin(theta)*sin(phi)/sin(theta+phi) , 2) );
  
  return Mag;

}

Double_t AngleCM(Double_t theta, Double_t phi){

  Double_t Angle = 0.;
  Angle = TMath::ATan2( sin(theta)*sin(phi), sin(theta)*cos(phi) - 0.5*sin(theta+phi) );
  Angle *= 180./TMath::Pi();
  return Angle;

}

Double_t LossEnergy(Double_t theta, Double_t phi){

  Double_t Energy=0.;

  Energy = (pow(sin(theta), 2) + pow(sin(phi), 2))/( pow(sin(theta+phi),2.) ) -1.;
  
  return Energy;

}

void CM(){

TVector3 VCM(0.,0.,0.);

TVector3 U1(0.,0.,0.);
TVector3 U2(0.,0.,0.);

TVector3 U1CM(0.,0.,0.);
TVector3 U2CM(0.,0.,0.);

TVector3 V1(0.,0.,0.);
TVector3 V2(0.,0.,0.);

TVector3 V1CM(0.,0.,0.);
TVector3 V2CM(0.,0.,0.);

U1.SetXYZ(u,0.,0.);
U2.SetXYZ(0.,0.,0.);

V1.SetXYZ(u*sin(theta)*cos(phi)/sin(theta+phi),  u*sin(theta)*sin(phi)/sin(theta+phi) , 0.);
V2.SetXYZ(u*sin(phi)*cos(theta)/sin(theta+phi), -u*sin(phi)*sin(theta)/sin(theta+phi) , 0.);

VCM=0.5*(U1+U2);

cout << " Magnitud of the final vectors: Lab frame " << V1.Mag() << " " << V2.Mag() << endl;
cout << " Vector CM " << VCM.Mag() << endl;

// Transforming to the CM reference frame
U1CM = U1 - VCM;
U2CM = U2 - VCM;

V1CM = V1 - VCM;
V2CM = V2 - VCM;

cout << " Magnitud of the final vectors: CM frame " << V1CM.Mag() << " " << V2CM.Mag() << endl;

Double_t phiprime = V1CM.Phi()*180./TMath::Pi();
Double_t thetaprime = V2CM.Phi()*180./TMath::Pi();

cout << " Angles of the final vectors: CM frame " << phiprime << " " << thetaprime << endl;

cout << " Using Atan2 function: " <<  TMath::ATan2(V1CM.y(),V1CM.x())*180./TMath::Pi() << endl;

Double_t otherphi =  AngleCM(theta, phi);

cout << " Angles using the explicit function: " << otherphi << " "  << otherphi-180.  << endl;

// Calculating the magnitud in the CM reference frame.

Double_t VCMMag = MagCM(u,theta, phi);
cout  << " Magnitude of the vector (with formula) from the CM frame: " << VCMMag << endl; 	

Double_t Energia0 = 0.5*masa*U1.Dot(U1)+0.5*masa*U2.Dot(U2);
Double_t Energia1 = 0.5*masa*V1.Dot(V1)+0.5*masa*V2.Dot(V2);

Double_t EnergiaCM0 =  0.5*(2.*masa)*VCM.Dot(VCM) + 0.5*masa*U1CM.Dot(U1CM)+0.5*masa*U2CM.Dot(U2CM);
Double_t EnergiaCM1 =  0.5*(2.*masa)*VCM.Dot(VCM) + 0.5*masa*V1CM.Dot(V1CM)+0.5*masa*V2CM.Dot(V2CM);



cout << " Energia laboratory: " << Energia0 << " " <<  Energia1 << " DeltaK " <<  Energia1-Energia0 << endl; 
cout << " Energia CM: " << EnergiaCM0 << " " <<  EnergiaCM1 << " DeltaK " <<  EnergiaCM1-EnergiaCM0 << endl; 

cout << " Fraccion de energía perdida: " << (Energia1-Energia0)/Energia0 << endl; 
cout << " Fraccion de energía perdida (formula): " << LossEnergy(theta, phi) << endl;

}

int main(){
CM();
return 0;
}
