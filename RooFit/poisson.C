using namespace RooFit;

void poisson(){

RooRealVar mass("mass","mass", 0.,500.0);   //RooRealVar = variable

RooRealVar mean_("mean","mean", 30 ,0, 50);  // mean , min , max

RooRealVar mean2_("mean2","mean2", 140 ,0, 200);  // mean , min , max
RooRealVar mean3_("mean2","mean2", 171. ,0, 200);  // mean , min , max

//pdf
RooPoisson P1("P1","P1",mass, mean2_);
RooPoisson P2("P2","P2",mass, mean3_);
 
RooDataSet *data= P1.generate(mass,10000);
RooDataSet *data2= P2.generate(mass,10000);

RooRealVar range("range","range",0.,500.);   //RooRealVar = variable
RooRealVar range2("range2","range2",0.,147.0);   //RooRealVar = variable

mass.setMin(147.);
mass.setMax(500.);

RooAbsReal *Integral = P1.createIntegral(mass);
Integral->Print();

mass.setMin(0.);
mass.setMax(147.);

RooAbsReal *Integral2 = P2.createIntegral(mass);
Integral2->Print();

Double_t CL = Integral2->getVal()/Integral->getVal();

std::cout << CL << std::endl;

mass.setMin(0.);
mass.setMax(500.);
RooPlot *massframe = mass.frame(Name("massframe"),Title("Poisson distribution"),Bins(100));

P1.plotOn(massframe, LineColor(kBlue));
P2.plotOn(massframe, LineColor(kRed));

//data->plotOn(massframe);
//data2->plotOn(massframe);

massframe->Draw();



}

int main(){
poisson();
return 0;
}
