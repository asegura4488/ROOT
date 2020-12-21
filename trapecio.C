Double_t f(Double_t x){      //Definimos la funciÃn


Double_t s = x*sin(x);

return s;

}

Double_t E(Double_t n){

Double_t a = -1;
Double_t b = 1;

Double_t t = -(1./12.)*(2.*cos(n)-n*sin(n))*TMath::Power(b-a,3);

return t;

}

void trapecio(){


Double_t a = -1.;                //Definimos la integral por regla taprezoidal
Double_t b = 1.;

Double_t n = 1000.;

Double_t h = (b-a)/n;
cout << " paso " <<  h <<endl;

Double_t p = 0.5*h*(f(a)+f(b));
Double_t l = 0.;

for(Int_t i = 1; i <= n; i++){
l += h*f(a+double(i)*h);
cout << l << endl;
}

std::cout << " Integral: " << p+l << std::endl;

std::cout << " Error: " << E(gRandom->Uniform(-1,1)) << std::endl;

}                                                        
