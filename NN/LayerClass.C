
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
  // cout << Threshold << endl;

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
    Layer(int Entries, int NumberN_);
    ~Layer();

    Neurona *GetNeurona(int id);

    int GetNumberN();

    double *Output(double Entries[], double Salida[]);

    void SwapWeightsLayer();

    void SetWeights();

    void ShowWeights();

    Neurona **Neuronas;

  private:

    int NumberN;
    

};

#endif

Layer::Layer(){}

Layer::Layer(int Entries, int NumberN_): NumberN(NumberN_){

  Neuronas = new Neurona*[NumberN_];

  for (uint i = 0; i < NumberN_; i++){
    Neurona *N = new Neurona(i,0.1,Entries);
    N->InitWeights();
    Neuronas[i] = N;
  }


}

Layer::~Layer(){}

Neurona* Layer::GetNeurona(int id){
  return Neuronas[id];
}

int Layer::GetNumberN(){
  return NumberN;
}

// Esto devuelve un apuntador al array.
// Una solucion es llenar un apuntador doble para
// tener arrays con diferentes dimensiones

double *Layer::Output(double Entries[], double Salida[]){

  for(int i = 0; i < NumberN; i++){
   // cout << i << " iterando la neurona " << endl;
    Salida[i] = Layer::GetNeurona(i)->Neurona::Output(Entries);
  }

    return Salida;

}

void Layer::SetWeights(){

	for(int i = 0; i < NumberN; i++)
	Layer::GetNeurona(i)->Neurona::InitWeights();
}

void Layer::ShowWeights(){

	for(int i = 0; i < NumberN; i++)
	Layer::GetNeurona(i)->Neurona::ShowWeights();
}

void Layer::SwapWeightsLayer(){
	for(int i = 0; i < NumberN; i++){
		Layer::GetNeurona(i)->Neurona::SwapWeights();
	}
}

//////////////////////////////////////////////////////////////////
/// Perceptron class
#ifndef Perceptron_H
#define Perceptron_H

class Perceptron{

  public:

    Perceptron();
    Perceptron(double EEntries, int NeuronasbyLayers[], int NumberLayers);
    ~Perceptron();
    

    Layer **Layers;

    double Output(double EEntries[],int NumberLayers);
    void PrintOutput(int Layers[], int NumberLayers);

    void SetWeights(int NumberLayers);
    void ShowWeights(int NumberLayers);
    void SwapWeights(int NumberLayers);

  private:

    double **OutputByLayer;

  	

    

};

#endif

Perceptron::Perceptron(){}

Perceptron::Perceptron(double EEntries, int NeuronasbyLayers[], int NumberLayers){

  Layers = new Layer*[NumberLayers];
  OutputByLayer = new double*[NumberLayers];

  Layers[0] = new Layer(EEntries,NeuronasbyLayers[0]);
  //cout << Layers[0]->GetNumberN() << " numero neuronas " <<endl;

  for (uint i = 1; i < NumberLayers; i++){
    Layer *L = new Layer(NeuronasbyLayers[i-1],NeuronasbyLayers[i]); 
    Layers[i] = L;
   // cout << Layers[i]->GetNumberN() << " numero de neuronas " <<endl;
  }

  
  // Create the output arrays
  for(int i = 0; i < NumberLayers; i++){

  	int size = Layers[i]->GetNumberN();
  //	cout << size << " dolores " <<endl;
  	double *out = new double[size];

  	OutputByLayer[i] = out;

  	//delete[] out;

  }

}

double Perceptron::Output(double EEntries[],int NumberLayers){

  // LLenamos la primera capa con la entrada inicial
  OutputByLayer[0] = Layers[0]->Output(EEntries,OutputByLayer[0]);

  //cout << OutputByLayer[0][0] << " primera  " << OutputByLayer[0][1] <<endl;

  for(int i = 1; i < NumberLayers; i++){
  	OutputByLayer[i] = Layers[i]->Output(OutputByLayer[i-1],OutputByLayer[i]);
  }
  //cout << OutputByLayer[1][0] << " final" <<endl;


  return OutputByLayer[1][0];
}

void Perceptron::PrintOutput(int Layers[], int NumberLayers){

    std::cout << " ----------------- " << std::endl; 
   for(int i = 0; i < NumberLayers; i++){
  	std::cout << " Capa: " << i << std::endl; 
  	for(int j = 0; j < Layers[i]; j++){
  		std::cout << " Salida: " << OutputByLayer[i][j] << std::endl; 
  	}
   }

}

void Perceptron::SetWeights(int NumberLayers){
	for(int i = 0; i < NumberLayers; i++){
		Layers[i]->Layer::SetWeights();
	}
}

void Perceptron::ShowWeights(int NumberLayers){
	for(int i = 0; i < NumberLayers; i++){
		std::cout << " ************* " << std::endl; 
		std::cout << " Layer: " << i << std::endl;
		Layers[i]->Layer::ShowWeights();
	}
}

void Perceptron::SwapWeights(int NumberLayers){
	for(int i = 0; i < NumberLayers; i++){
		Layers[i]->Layer::SwapWeightsLayer();
	}
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

  double out[2] = {0};
  L1->Output(Entry1,out);
  //cout << out[0] << " que paso " << out[1] << endl;

  int capas[2] = {3,1};
  int NCapas = 2;
  Perceptron *p1 = new Perceptron(2,capas,NCapas);
  p1->Output(Entry1,NCapas);
  //p1->PrintOutput(capas,2);


  int it = 0;

  while(!control and it < 10000){
  	control = true;

    
  	if(p1->Output(Entry1,NCapas) != 0){
  		p1->SetWeights(NCapas);
  		control = false;
  	}
  	if(p1->Output(Entry2,NCapas) != 1){
  		p1->SetWeights(NCapas);
  		control = false;
  	}
  	if(p1->Output(Entry3,NCapas) != 1){
  		p1->SetWeights(NCapas);
  		control = false;
  	}
  	if(p1->Output(Entry4,NCapas) != 0){
  		p1->SetWeights(NCapas);
  		control = false;
  	}
  	

  	p1->SwapWeights(NCapas);
  	it++;
    //cout << it << endl;
  }

  if(it == 10000){
  	cout << " No alcanzado " << endl;
  	exit(1); 
  }

  cout << it << endl;
  p1->Output(Entry1,NCapas);
  p1->PrintOutput(capas,NCapas);
  p1->Output(Entry2,NCapas);
  p1->PrintOutput(capas,NCapas);
  p1->Output(Entry3,NCapas);
  p1->PrintOutput(capas,NCapas);
  p1->Output(Entry4,NCapas);
  p1->PrintOutput(capas,NCapas);

  p1->ShowWeights(NCapas);

}


int main(){
	LayerClass();
	return 0;
}
