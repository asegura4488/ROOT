void rotacion(){

  double w0 = TMath::Pi()/6.;
  double w1 = 0.; 

  double r0 = 1.3;
  double r1 = 0.7;

  double M = 10.;
  double m = 25.;

  double I0 = 0.;
  double I1 = 0.;


  I0 = 0.5*M*pow(r0,2) + 2.*m*pow(r0,2);
  I1 = 0.5*M*pow(r0,2) + 2.*m*pow(r1,2);

  double Idisk = 0.5*M*pow(r0,2); 

  std::cout << " I0 " << I0 << " I1 " << I1 << endl;   
  
  // Angular momentum

  double L0 = w0*I0;
  w1 = w0*I0/I1;


  std::cout << " Total Angular momentum: " << L0  << " New omega " << w1 << " "  << L0/(Idisk + 2.*m*pow(r1,2)) <<  endl;  

  // Delta kinetic energy

  double E0 = 0.5*I0*pow(w0,2); 
  double E1 = 0.5*I1*pow(w1,2);

  std::cout << " Delta E " <<  E1 - E0 << endl; 

  // Work of the centripetal force

  double alpha = sqrt(2.0*m/Idisk);


  
  double W = (0.5*m* pow(L0/Idisk, 2))* ( ( pow(r0,2) - pow(r1,2) ) / ( (1+pow(alpha*r1,2)) * (1+pow(alpha*r0,2) ) ));
 
  W *= 2.0;

  std::cout << " Work: " << W << std::endl;

}
