
#include <TRandom3.h>

#ifndef Neurona_H
#define Neurona_H

class Neurona{

public:

	Neurona();
	Neurona(double Threshold_);
	~Neurona();
	void GetWeights();
	void SetWeights(double Entries[], int Eout);
	void Swap();
	void ShowWeights();
    int Activation(double x);
    double Propagation(double Entries[]);
	int Output(double Entries[]);

	double Weights[2];
	double PWeights[2];
	double Threshold;
	double PThreshold;

private:
	TRandom3 *rnd; 

    // peso = ppeso + tasa aprendizaje*error*entrada
	double alpha = 0.3;

};

#endif

Neurona::Neurona(){
	rnd = new TRandom3();
	rnd->SetSeed(0);

	for( uint i = 0; i < 2; i++ ){
		PWeights[i] = rnd->Uniform(-1.,1.);	
	}

    PThreshold = rnd->Uniform(-1.,1.);
}

Neurona::Neurona(double Threshold_): Threshold(Threshold_){
	rnd = new TRandom3();
	rnd->SetSeed(0);

	for( uint i = 0; i < 2; i++ ){
		PWeights[i] = rnd->Uniform(0.,1.);	
	}

	PThreshold = rnd->Uniform(0.,1.);
}

Neurona::~Neurona(){

}

void Neurona::GetWeights(){

   for( uint i = 0; i < 2; i++ ){
   	Weights[i] = rnd->Uniform(-1.,1.);
   }
   Threshold = rnd->Uniform(-1.,1.);


}

void Neurona::SetWeights(double Entries[], int Eout){

	for( uint i = 0; i < 2; i++ ){
		Weights[i] = PWeights[i] + alpha*(Eout-Output(Entries))*Entries[i];
	
		//cout << i << " " << Weights[i] << " " << PWeights[i] << endl;  
	}
	    Threshold = PThreshold + alpha*(Eout-Output(Entries));
	    //cout << Threshold << " " << PThreshold << endl;

}

void Neurona::Swap(){
	for( uint i = 0; i < 2; i++ ){
		PWeights[i] = Weights[i];
	}

	    PThreshold = Threshold;
}

void Neurona::ShowWeights(){
	for( uint i = 0; i < 2; i++ ){
		std::cout << Weights[i] << std::endl;
	}
}


int Neurona::Activation(double x){
	return x > 0 ? 1 : 0;
}

double Neurona::Propagation(double Entries[]){

	float sum = 0.;

	for( uint i = 0; i < 2; i++ ){
		sum += Entries[i]*Weights[i];
	}

	sum += Threshold;

	return sum;
}

int Neurona::Output(double Entries[]){
	return Activation(Neurona::Propagation(Entries));
}




void NeuronaClass(){

  int Nneu = 2;
  Neurona *AllNeuronas[Nneu];

  Neurona *N1 = new Neurona(0.);

  bool control = false;

  double Entry1[2] = {1.,1.};
  double Entry2[2] = {0.,1.};
  double Entry3[2] = {1.,0.};
  double Entry4[2] = {0.,0.};

  N1->GetWeights();

  int it = 0;

  while(!control and it < 10000){
  	control = true;

    //N1->GetWeights();
    //N1->ShowWeights();
  	
  	/*
  	std::cout << N1->Output(Entry1) << std::endl;
  	std::cout << N1->Output(Entry2) << std::endl;
  	std::cout << N1->Output(Entry3) << std::endl;
  	std::cout << N1->Output(Entry4) << std::endl;
*/
  	if(N1->Output(Entry1) != 1){
  		N1->SetWeights(Entry1,1);
  		control = false;
  	}
  	if(N1->Output(Entry2) != 1){
  		N1->SetWeights(Entry2,0);
  		control = false;
  	}
  	if(N1->Output(Entry3) != 1){
  		N1->SetWeights(Entry3,0);
  		control = false;
  	}
  	if(N1->Output(Entry4) != 0){
  		N1->SetWeights(Entry4,0);
  		control = false;
  	}

  	N1->Swap();
  	it++;
 
  }

  if(it == 10000){
  	cout << " No alcanzado " << endl;
  	exit(1); 
  }

  cout << it << " Threshold: " << N1->Threshold << endl;
  N1->ShowWeights();


}


int main(){
	NeuronaClass();
	return 0;
}
