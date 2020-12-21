using namespace std;
#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>

//===============================================

float f(float x, float y)
{
  float f=((1+x)/((1+y)));      
  return(f);
    
}

float* rk4(float x0,float xf,float y0,float n)
{
  
  float h=0;
  h= (xf - x0)/n;
  int delta = 0;
  delta =n+1;
  float *rk = new float[2*(delta+1)];

  float x=x0,y=y0; 
  rk[0]=x0;
  rk[delta]=y0;


  float k1,k2,k3,k4;
  int cont=0;
  while(x<xf)
    {
      cout<< cont << "Here " << rk[cont] << " " << rk[cont+delta] <<endl;
      
      cont++;
      k1=h*f(x,y);
      k2=h*f(x+h/2.0,y+k1/2.0);
      k3=h*f(x+h/2.0,y+k2/2.0);
      k4=h*f(x+h,y+k3);
      y+=(k1+2*k2+2*k3+k4)/6.0;
      x+=h;
      rk[cont]=x;
      rk[cont+delta]=y;
      
    }
  
  cout << rk[cont]<< " " << rk[cont + delta] <<endl;
  return  rk;
  
}

void runge44(){
  
  TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
  
  c1->Divide(1,1);
  
  cout << "here"<< endl;
  float x0,y0,xf,n;
  
  cout<<" METODO DE RUNGE KUTTA (ORDEN 4)" << " " << endl;
  
  cout<<"Here"<< "X" << " Y " << endl;
  x0 = -50;
  xf = 50;
  y0 = 1;
  n  = 1000;
  
  float h=0;
  h= (xf - x0)/n;
  const int npar = n+1;
  
  float *rk=0;
  
  rk = rk4(x0,xf,y0,n);
  
  Double_t x[npar], y[npar];
  
  for (Int_t i=0;i<npar;i++) {
    
    x[i] = rk[i]; 
    y[i] = rk[i+npar]; 
    
    cout << x[i] << " h  " << y[i] << endl;
    
  }
  
  TGraph *gr = new TGraph(npar,x,y);
  
  c1->cd(1);
  gr->GetYaxis()->SetRangeUser(0.0,3.0); 
  gr->GetXaxis()->SetRangeUser(-50.0,50.0); 
  gr->Draw("ACP");
  
  delete [] rk;
}
