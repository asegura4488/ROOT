#ifndef CHANNEL_H
#define CHANNEL_H

#include <TF1.h>
#include <TLine.h>
#include <TGraph.h>
#include <TH1F.h>

class Channel{

public:

	Channel();
	Channel(double Ndata_, double Nbkg_, double Nsignal_, double Xmin, double Xmax_);
	~Channel();

	void Plot();
	void FillGraph();
	void SetPOI(double mu_);
	void CheckLimits();
	double GetCLs();

	double GetAlpha();
	double GetBeta();
	

private:

	double Xmin;
	double Xmax;

	double Ndata;
	double Nbkg;
	double Nsignal;

	double mu;

	double alpha;
	double beta;

	// Functions
	TF1 *FH0;
	TF1 *FH1;

	TGraph *alpha_;
	TGraph *beta_;

	TH1F *h;

	TLine *line;

};

#endif

Channel::Channel(){

}

Channel::Channel(double Ndata_, double Nbkg_, double Nsignal_, double Xmin_, double Xmax_): 
Ndata(Ndata_), Nbkg(Nbkg_), Nsignal(Nsignal_), Xmin(Xmin_), Xmax(Xmax_){

	mu = 0.;

	h = new TH1F("h","h", 100, Xmin,Xmax);

	FH0 = new TF1("FH0", "TMath::Poisson(x,[0])",Xmin,Xmax);
	FH0->SetLineColor(2);
	FH0->SetLineWidth(2);
	FH0->SetParameter(0,Nbkg);

	FH1 = new TF1("FH1", "TMath::Poisson(x,[0])",Xmin,Xmax);
	FH1->SetLineColor(4);
	FH1->SetLineWidth(2);
	FH1->SetParameter(0,Nbkg + mu*Nsignal);

	alpha_ = new TGraph(1);
	alpha_->SetFillColor(2);
	beta_ = new TGraph(1);
	beta_->SetFillColor(4);

	line = new TLine();
	line->SetLineWidth(3);

}

Channel::~Channel(){}

void Channel::Plot(){

	Channel::FillGraph();
	h->SetMaximum(FH0->GetMaximum());

	h->Draw();

	alpha_->Draw("lf,same");
	beta_->Draw("lf,same");

	FH0->Draw("l,same");
	FH1->Draw("l,same");
	line->DrawLine(Ndata,0.,Ndata,FH0->GetMaximum());

	gPad->RedrawAxis();
}

void Channel::FillGraph(){

	for (int i = 0; i <= 100; ++i){
		double a = Ndata + (Xmax-Ndata)*(double)i/100.;
		double b = Ndata * (1. - (double)i/100.);

		alpha_->SetPoint(i,a,FH0->Eval(a));
		beta_->SetPoint(i,b,FH1->Eval(b));
	}

   alpha_->SetPoint(102,Ndata,0);
   alpha_->SetPoint(101,Xmax,0);
   
   beta_->SetPoint(102,Ndata,0);
   beta_->SetPoint(101,Xmin,0);
  
}

void Channel::SetPOI(double mu_){
	mu = mu_;
	FH1->SetParameter(0,Nbkg + mu*Nsignal);
}

void Channel::CheckLimits(){

	double I0 = FH0->Integral(Xmin,Xmax);
	double I1 = FH1->Integral(Xmin,Xmax);

	if(I0 < 1.0 || I1 < 1.0){
		std::cout << " Change limits: " << I0 << " " << I1 << std::endl;
		//exit(1);
	}

}

double Channel::GetCLs(){

 	double CLs = 0.;

 	double CLsb = FH1->Integral(Xmin,Ndata)/FH1->Integral(Xmin,Xmax);
 	double CLb = FH0->Integral(Xmin,Ndata)/FH0->Integral(Xmin,Xmax);

 	

 	alpha = 1.-CLb;
 	beta = CLsb;

// 	CLs = CLsb/(1.-CLb);
 	CLs = CLsb/CLb;

    //cout << alpha << " " << beta << endl;

	return CLs;
}

double Channel::GetAlpha(){ return alpha; }
double Channel::GetBeta(){ return beta; }

/////////////////////// upper limit

double GetUpperLimit(Channel *ch, double CL){

	double upper_mu = 2.;
	double mu = 0.;
	double dmu = 0.001;

	while(upper_mu >= CL){

		ch->SetPOI(mu);
		upper_mu = ch->GetCLs();

		mu += dmu;

	}

	std::cout << " Reach " << upper_mu << std::endl;

	return mu;

}


////////////////////////////// main class

void channel_test(){

	gStyle->SetOptStat(0);
	

	Channel *ch1 = new Channel(9.,7,10.,0.,30.);
	ch1->SetPOI(1.0);
	ch1->CheckLimits();
	//std::cout << ch1->GetCLs() << std::endl;
	

	std::cout << GetUpperLimit(ch1, 0.05) << std::endl;
	std::cout << ch1->GetAlpha() << " " << ch1->GetBeta() << std::endl;
	ch1->Plot();



	delete ch1;

}




int main(){
	channel_test();
	return 0;
}


