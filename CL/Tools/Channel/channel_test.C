#ifndef CHANNEL_H
#define CHANNEL_H

class channel{

public:
	
	channel();
	channel(double Ndata_, double Nbkg_, double Nsignal_);
	~channel();

private:

	double Ndata;
	double Nbkg;
	double Nsignal;

	double mu;

};

#endif

channel::channel(){

}

channel::channel(double Ndata_, double Nbkg_, double Nsignal_): 
Ndata(Ndata_), Nbkg(Nbkg_), Nsignal(Nsignal_){

}

channel::~channel(){}

void channel_test(){

	channel ch1 = channel(7.,4.,11.);


}

int main(){
	channel_test();
	return 0;
}


