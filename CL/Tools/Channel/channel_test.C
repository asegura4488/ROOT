#ifndef CHANNEL_H
#define CHANNEL_H

#include <TF1.h>

class channel{

public:

	channel();
	channel(double Ndata_, double Nbkg_, double Nsignal_, double Xmin, double Xmax_);
	~channel();

	void Plot();
	void SetPOI(double mu_);

private:

	double Xmin;
	double Xmax;

	double Ndata;
	double Nbkg;
	double Nsignal;

	double mu;

	// Functions
	TF1 *FH0;
	TF1 *FH1;

};

#endif

channel::channel(){

}

channel::channel(double Ndata_, double Nbkg_, double Nsignal_, double Xmin_, double Xmax_): 
Ndata(Ndata_), Nbkg(Nbkg_), Nsignal(Nsignal_), Xmin(Xmin_), Xmax(Xmax_){

	mu = 0.;

	FH0 = new TF1("FH0", "TMath::Poisson(x,[0])",Xmin,Xmax);
	FH0->SetLineColor(2);
	FH0->SetParameter(0,Nbkg);

	FH1 = new TF1("FH1", "TMath::Poisson(x,[0])",Xmin,Xmax);
	FH1->SetLineColor(4);
	FH1->SetParameter(0,Nbkg + mu*Nsignal);


}

channel::~channel(){}

void channel::Plot(){
	FH0->Draw("l");
	FH1->Draw("l,same");
}



void channel::SetPOI(double mu_){
	mu = mu_;
	FH1->SetParameter(0,Nbkg + mu*Nsignal);
}

void channel_test(){

	channel *ch1 = new channel(7.,4.,11.,-1.,30.);
	ch1->SetPOI(1.0);
	ch1->Plot();

}




int main(){
	channel_test();
	return 0;
}


