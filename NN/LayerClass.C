
#include <TRandom3.h>

#ifndef Neurona_H
#define Neurona_H

class Neurona{

public:

	Neurona();
	Neurona(int ID_, double alpha_, uint size_);
	~Neurona();
  int GetID();
	void InitWeights();
	void SetWeights(double Entries[], int Expected);
	void SwapWeights();
	void ShowWeights();
    int Activation(double x);
    double Propagation(double Entries[]);
	int Output(double Entries[]);

	double *Weights;
	double *PWeights;
	double Threshold;
	double PThreshold;

	TH1D *h1;

private:

	TRandom3 *rnd; 
    // peso = ppeso + tasa aprendizaje*error*entrada
	double alpha;
	uint size;
  int ID;

};

#endif

Neurona::Neurona(){

	rnd = new TRandom3();
	rnd->SetSeed(0);

	Weights = new double[size];
	PWeights = new double[size];

}

Neurona::Neurona(int ID_, double alpha_,uint size_): ID(ID_), alpha(alpha_), size(size_){

	rnd = new TRandom3();
	rnd->SetSeed(0);

	Weights = new double[size];
	PWeights = new double[size];

}

Neurona::~Neurona(){}

int Neurona::GetID(){return ID;}

void Neurona::InitWeights(){

   for( uint i = 0; i < size; i++ ){
   	Weights[i]  = rnd->Gaus(0.,2.);
   	PWeights[i] = rnd->Gaus(0.,2.);
   }

   Threshold  = rnd->Uniform(-1.,1.);
   PThreshold = rnd->Uniform(-1.,1.);

}

void Neurona::SetWeights(double Entries[], int Expected){

	for( uint i = 0; i < size; i++ ){
		Weights[i] = PWeights[i] + alpha*(Expected-Output(Entries))*Entries[i];
	
		//cout << i << " " << Weights[i] << " " << PWeights[i] << endl;  
	}
	    Threshold = PThreshold + alpha*(Expected-Output(Entries));
	    //cout << Threshold << " " << PThreshold << endl;

}

void Neurona::SwapWeights(){
	for( uint i = 0; i < size; i++ ){
		PWeights[i] = Weights[i];
	}

	    PThreshold = Threshold;
}

void Neurona::ShowWeights(){
	for( uint i = 0; i < size; i++ ){
		std::cout << Weights[i] << std::endl;
	}
	std::cout << " Threshold: " << Threshold << std::endl;
}


int Neurona::Activation(double x){
	return x > 0 ? 1 : 0;
}

double Neurona::Propagation(double Entries[]){

	double sum = 0.;

	for( uint i = 0; i < size; i++ ){
		sum += Entries[i]*Weights[i];
	}

	sum += Threshold;

	return sum;
}

int Neurona::Output(double Entries[]){
	return Activation(Neurona::Propagation(Entries));
}


//////////////////////////////////////////////////////////////////
/// Layer class
#ifndef Layer_H
#define Layer_H

class Layer{

  public:

    Layer();
    Layer(int Entries, uint NumberN);
    ~Layer();
    Neurona *GetNeurona(int id);

    Neurona **Neuronas;

    double Output(double Entries[], int id);

  private:

    

};

#endif

Layer::Layer(){}

Layer::Layer(int Entries, uint NumberN){

  Neuronas = new Neurona*[NumberN];

  for (uint i = 0; i < NumberN; i++){
    Neurona *N = new Neurona(i,0.1,Entries);
    N->InitWeights();
    Neuronas[i] = N;
  }


}

Layer::~Layer(){}

Neurona* Layer::GetNeurona(int id){
  return Neuronas[id];
}

double Layer::Output(double Entries[], int id){
  return Layer::GetNeurona(id)->Neurona::Output(Entries);
}

//////////////////////////////////////////////////////////////////
/// Perceptron class
#ifndef Perceptron_H
#define Perceptron_H

class Perceptron{

  public:

    Perceptron();
    Perceptron(int EEntries, uint NeuronasbyLayers[], int NumberLayers);
    ~Perceptron();
    

    Layer **Layers;

    double Output(double EEntries[],int NumberLayers);

  private:

    double *Salida;

    

};

#endif

Perceptron::Perceptron(){}

Perceptron::Perceptron(int EEntries, uint NeuronasbyLayers[], int NumberLayers){

  Layers = new Layer*[NumberLayers];

  Layers[0] = new Layer(EEntries,NeuronasbyLayers[0]);

  for (uint i = 1; i < NumberLayers; i++){
    Layer *L = new Layer(NeuronasbyLayers[i-1],NeuronasbyLayers[i]); 
    Layers[i] = L;
  }

  // array para salidas del perceptron
  Salida = new double[NumberLayers];

}

double Perceptron::Output(double EEntries[],int NumberLayers){

  Salida[0] = Layers[0]->Output(EEntries,0);

  for (uint i = 1; i < NumberLayers; i++){
    Salida[i] = Layers[i]->Output(&Salida[i-1],i);
  }

  return 0;
}

Perceptron::~Perceptron(){}





/////////////////// Main function /////////////////////////

void LayerClass(){

  Layer *L1 = new Layer(2,2); 
  cout << L1->GetNeurona(0)->GetID() << endl;
  L1->GetNeurona(0)->ShowWeights();

  Neurona *N1 = new Neurona(1,0.05,2);
  //cout << N1->GetID() << endl;
  N1->InitWeights();

  bool control = false;

  double Entry1[2] = {1.,1.};
  double Entry2[2] = {0.,1.};
  double Entry3[2] = {1.,0.};
  double Entry4[2] = {0.,0.};

  cout << L1->Output(Entry1,0) << endl;


  int it = 0;

  while(!control and it < 10000){
  	control = true;

    //N1->InitWeights();
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
  	if(N1->Output(Entry2) != 0){
  		N1->SetWeights(Entry2,0);
  		control = false;
  	}
  	if(N1->Output(Entry3) != 0){
  		N1->SetWeights(Entry3,0);
  		control = false;
  	}
  	if(N1->Output(Entry4) != 0){
  		N1->SetWeights(Entry4,0);
  		control = false;
  	}

  	N1->SwapWeights();
  	it++;
 
  }

  if(it == 10000){
  	cout << " No alcanzado " << endl;
  	exit(1); 
  }

  //cout << it << endl;
  //N1->ShowWeights();


}


int main(){
	LayerClass();
	return 0;
}
