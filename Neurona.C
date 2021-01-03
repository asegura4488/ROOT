
double weight1 = 0.;
double weight2 = 0.;
double Threshold = 0.;

TRandom3 *rnd = new TRandom3();

int Activacion(double x){
	return x > 0 ? 1 : 0;
}

double GetNeurona(double in1, double in2, double weight1, double weight2, double Threshold){
	return Threshold + weight1*in1 + weight2*in2; 
}


void Neurona(){

  rnd->SetSeed(0);

  cout << Activacion(-6) << " " <<  rnd->Rndm()  << endl;

  /* AND	E1	E2
      1		1	1
      0		1 	0
      0		0	1	
      0		0	0 
  */
  bool control = false;
  while(!control){

  	// Esto calcula los pesos para que la neurona funcione 
  	// como una compuerta AND
  	control = true;

    weight1 = rnd->Uniform(-1.,1.);
    weight2 = rnd->Uniform(-1.,1.);
    Threshold = rnd->Uniform(-1.,1.);

    cout << "Weight1: " << weight1 << endl;
    cout << "Weight2: " << weight2 << endl;
    cout << "Threshold: " << Threshold << endl; 

 	cout << " 1  1 " << Activacion(GetNeurona(1,1,weight1,weight2,Threshold)) << endl;
    cout << " 1  0 " << Activacion(GetNeurona(1,0,weight1,weight2,Threshold)) << endl;
   	cout << " 0  1 " << Activacion(GetNeurona(0,1,weight1,weight2,Threshold)) << endl;
    cout << " 0  0 " << Activacion(GetNeurona(0,0,weight1,weight2,Threshold)) << endl;
  
    if(Activacion(GetNeurona(1,1,weight1,weight2,Threshold)) != 1){
    	control = false;
    }

    if(Activacion(GetNeurona(1,0,weight1,weight2,Threshold)) != 0){
    	control = false;
    }

    if(Activacion(GetNeurona(0,1,weight1,weight2,Threshold)) != 0){
    	control = false;
    }
    if(Activacion(GetNeurona(0,0,weight1,weight2,Threshold)) != 0){
    	control = false;
    }

    // El umbral en general debe ser un número negativo

   }

    /* OR	E1	E2
      1		1	1
      1		1 	0
      1		0	1	
      0		0	0 
  */
  control = false;
  while(!control){

  	// Esto calcula los pesos para que la neurona funcione 
  	// como una compuerta AND
  	control = true;

    weight1 = rnd->Uniform(-1.,1.);
    weight2 = rnd->Uniform(-1.,1.);
    Threshold = rnd->Uniform(-1.,1.);

    cout << "Weight1: " << weight1 << endl;
    cout << "Weight2: " << weight2 << endl;
    cout << "Threshold: " << Threshold << endl; 

 	cout << " 1  1 " << Activacion(GetNeurona(1,1,weight1,weight2,Threshold)) << endl;
    cout << " 1  0 " << Activacion(GetNeurona(1,0,weight1,weight2,Threshold)) << endl;
   	cout << " 0  1 " << Activacion(GetNeurona(0,1,weight1,weight2,Threshold)) << endl;
    cout << " 0  0 " << Activacion(GetNeurona(0,0,weight1,weight2,Threshold)) << endl;
  
    if(Activacion(GetNeurona(1,1,weight1,weight2,Threshold)) != 1){
    	control = false;
    }

    if(Activacion(GetNeurona(1,0,weight1,weight2,Threshold)) != 1){
    	control = false;
    }

    if(Activacion(GetNeurona(0,1,weight1,weight2,Threshold)) != 1){
    	control = false;
    }
    if(Activacion(GetNeurona(0,0,weight1,weight2,Threshold)) != 0){
    	control = false;
    }




  }
   // La suma de pesos deben ser positivos 


   // Como la neurona es una funcion lineal, no es posible descrbir esas compuertas
   // con una solo necesitamos más de una neurona

  // Compuertas mas interesante
  // XNOR: ambas entradas iguales
    /* XNOR	E1	E2
      1		1	1
      0		1 	0
      0		0	1	
      1		0	0 
  */


  // XOR: ambas entradas diferentes 
   /* XOR	E1	E2
      0		1	1
      1		1 	0
      1		0	1	
      0		0	0 
  */
  /*
  control = false;
  while(!control){

  	// Esto calcula los pesos para que la neurona funcione 
  	// como una compuerta AND
  	control = true;

    weight1 = rnd->Uniform(-1.,1.);
    weight2 = rnd->Uniform(-1.,1.);
    Threshold = rnd->Uniform(-1.,1.);

    cout << "Weight1: " << weight1 << endl;
    cout << "Weight2: " << weight2 << endl;
    cout << "Threshold: " << Threshold << endl; 

 	cout << " 1  1 " << Activacion(GetNeurona(1,1,weight1,weight2,Threshold)) << endl;
    cout << " 1  0 " << Activacion(GetNeurona(1,0,weight1,weight2,Threshold)) << endl;
   	cout << " 0  1 " << Activacion(GetNeurona(0,1,weight1,weight2,Threshold)) << endl;
    cout << " 0  0 " << Activacion(GetNeurona(0,0,weight1,weight2,Threshold)) << endl;
  
    if(Activacion(GetNeurona(1,1,weight1,weight2,Threshold)) != 0){
    	control = false;
    }

    if(Activacion(GetNeurona(1,0,weight1,weight2,Threshold)) != 1){
    	control = false;
    }

    if(Activacion(GetNeurona(0,1,weight1,weight2,Threshold)) != 1){
    	control = false;
    }
    if(Activacion(GetNeurona(0,0,weight1,weight2,Threshold)) != 0){
    	control = false;
    }

  }
  */


}


int main(){
	Neurona();
	return 0;
}