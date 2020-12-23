#include<TMath.h>

Double_t interes_A = 0.;
Double_t interes_M = 0.;
Double_t Capital_I = 0.;
Double_t Valor_Cuota = 0.;
Double_t Cuotas_totales = 0.;

Double_t anual_to_mensual(Double_t interes_A){
  Double_t interes_M = TMath::Power(1+interes_A, 30./360.)-1.;
  //(1+x)^{a/x}=exp{a}
  return interes_M;
}

Double_t anual_to_mensual_2(Double_t interes_A){
  //(1+a/x)^{x}=exp{a}
  Double_t interes_M = TMath::Power(1+interes_A/12, 12)-1.;
  return interes_M;
}

Double_t mensual_to_anual(Double_t interes_M){
  Double_t interes_A = TMath::Power(1+interes_A, 360./30.)-1.;
  return interes_A;
}

Double_t peso_interes(Double_t Interes, Double_t N_Cuotas){
  Double_t peso = Interes/(1.-TMath::Power(1.+Interes,-N_Cuotas)); 
  return peso;
}


void calculo(){
  cout << "Simulador de cuotas de prestamo: " << " --------- " << endl;
  
  //interes efectivo anual
  interes_A = 20.1;
  interes_A /= 100.;
  // para calcular el efectivo anual a partir del mensual, se calcula (1+interes_M/100.)^(360.30.)-1
  interes_M = anual_to_mensual(interes_A);
  double interes_M_2 = anual_to_mensual_2(interes_A);
  
  //interes_M = 0.025;
  
  std::cout << "Interes Anual: " << interes_A*100. << " Interes Mensual: " << interes_M*100. << " otra formula: " << interes_M*100. << std::endl;
  //Ajustando el capital inicial
  Capital_I = 9000000.;
  
  std::cout << " El Capital es: " << int(Capital_I) << std::endl;
  
  Cuotas_totales = 36.;
  
  std::cout << " El numero de cuotas: " << Cuotas_totales << std::endl;
  
  //propagacion interes compueto
  Valor_Cuota = Capital_I*peso_interes(interes_M, Cuotas_totales);
  std::cout << " Valor de cuota: " << Valor_Cuota << std::endl;

  Double_t total_pagado = Valor_Cuota*Cuotas_totales;

  std::cout << " Total pagado: " << int(total_pagado)
	    << " Perdido: " << int(total_pagado-Capital_I)
            << " En: " << Cuotas_totales << " meses " 
            << int((total_pagado-Capital_I)/Cuotas_totales)  
	    << std::endl;
    
   Double_t cuota[50]={0};
   Double_t meses[50]={0}; 
   Double_t dinero_p[50]={0};
   Double_t abono_pp[50]={0};
   Double_t interes_pp[50]={0};

  for(int i = 0; i < 40; i++){
   meses[i] = i+6;
   cuota[i] = Capital_I*peso_interes(interes_M, i+6);
   dinero_p[i] = Capital_I*(peso_interes(interes_M, i+6)*(i+6)-1);
   abono_pp[i] = Capital_I*(peso_interes(interes_M, i+6)-interes_M);
   interes_pp[i] = Capital_I*interes_M;
   }

  std::vector<double> capital_por_pagar;
  std::vector<double> abono_capital;
  std::vector<double> interes_capital;

  Double_t Capital_M = Capital_I;
  Double_t interes_p = 0.;
  Double_t abono_p = 0.;

  Double_t abono_a_capital = 1000000;
  int mes_abonado = 4;
  bool hay_abono = false;
  //Toca restar el pago de cuota del mes y la comision del banco por cancelacion previa 2.5% mas o menos
  Double_t penal = (abono_a_capital-Valor_Cuota)*0.025; 
  abono_a_capital -= penal;

  if(hay_abono) std::cout << " Abono a capital: " << abono_a_capital << std::endl;
  
  for(int i = 0; i < Cuotas_totales ; i++ ){
    //Interes en el periodo
    interes_p = Capital_M*interes_M;
    interes_capital.push_back(interes_p);
    //El abono a capital en el periodo
    abono_p = Valor_Cuota-interes_p;
    abono_capital.push_back(abono_p); 
    //El nuevo capital se calcula
    Capital_M -= abono_p;
    if(hay_abono && i == mes_abonado-1) Capital_M -= abono_a_capital; 
    capital_por_pagar.push_back(Capital_M);
    
  }


  //Viendo la information
  for(int i = 0; i < Cuotas_totales ; i++ ){

    double interes_i = 0.;
    if(i==0) interes_i = interes_capital[i]/Capital_I;
    else interes_i = interes_capital[i]/capital_por_pagar[i-1];

    
    std::cout << " Mes: " << i+1
	      << " Abono a capital: " << abono_capital[i] 
	      << " Interes pagado: " << interes_capital[i]
	      << " Nuevo Capital " << int(capital_por_pagar[i])
              << " Interes del mes " << interes_i*100
	      << std::endl;

    if(hay_abono && i == mes_abonado-1)
      std::cout << " Se abono: " << int(abono_a_capital)
		<< " en el mes: " << mes_abonado
		<< std::endl;
  }
 

  TCanvas * c1 = new TCanvas("c", "c", 700, 500);
  TGraph *gr1 = new TGraph(40,meses,cuota);
  TGraph *gr2 = new TGraph(40,meses,dinero_p);
  TGraph *gr3 = new TGraph(40,meses,abono_pp);
  TGraph *gr4 = new TGraph(40,meses,interes_pp);
   gr1->SetLineColor(1);
   gr2->SetLineColor(2);
   gr3->SetLineColor(4);
   gr4->SetLineColor(3);
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr1);
  mg->Add(gr2);
  mg->Add(gr3);
  mg->Add(gr4);
  mg->Draw("AC*");
}

int main(){
  
  calculo();
  return 0;
}
