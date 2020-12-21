using namespace RooFit;

void argus_background(){

RooRealVar mass("mass","mass", 0,10.);                      //RooRealVar = variable

RooRealVar mean_("mean","mean", 5.28 ,5.20, 5.30);  // mean , min , max
RooRealVar sigma_("sigma","sigma", 0.3, 0.,1.);

RooRealVar a0("a0","a0",0.1,0,1);
RooRealVar a1("a1","a1",0.5,0,1);

//pdf
RooGaussian g1("g1","g1",mass, mean_, sigma_); 
RooPolynomial Argus("Argus","Argus",mass, RooArgSet(a0,a1));

RooRealVar nsig("nsig","nsig",2,0,10000.);
RooRealVar nbkg("nbkg","nsig",200,0,10000.);  // Fraction of events of s and b

RooAddPdf Sumg1Argus("Sumg1Argus","s+b", RooArgList(g1,Argus), RooArgList(nsig, nbkg));

RooDataSet *data= Sumg1Argus.generate(mass,10000);
Sumg1Argus.fitTo(*data, Extended()); // To generate pseudodata.


RooPlot *massframe = mass.frame();

Sumg1Argus.plotOn(massframe, LineColor(1));
Sumg1Argus.plotOn(massframe, Components(g1), LineStyle(kDashed), LineColor(kRed));
Sumg1Argus.plotOn(massframe, Components(Argus),  LineStyle(kDashed), LineColor(kBlue));

data->plotOn(massframe);
Sumg1Argus.plotOn(massframe);

massframe->Draw();

}

int main(){
argus_background();
return 0;
}
