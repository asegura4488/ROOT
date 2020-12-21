using namespace RooFit;

void sum_gauss(){

RooRealVar mass("mass","mass",-2.0,2.0);                      //RooRealVar = variable

RooRealVar mean_("mean","mean",0 ,-1, 1);  // mean , min , max
RooRealVar sigma_("sigma","sigma", 0.3, 0.,1.);

RooRealVar mean2_("mean2","mean2", 1,-1, 2);  // mean , min , max
RooRealVar sigma2_("sigma2","sigma2", 0.4, 0.,1.);


//pdf
RooGaussian g1("g1","g1",mass, mean_, sigma_); 
RooGaussian g2("g2","g2",mass, mean2_, sigma2_); 

RooRealVar nsig("nsig","nsig",10,0,10000.);
RooRealVar nbkg("nbkg","nsig",500,0,10000.);  // Fraction of events of s and b

RooAddPdf Sumg1g2("Sumg1g2","s+b", RooArgList(g1,g2), RooArgList(nsig, nbkg));


RooPlot *massframe = mass.frame();

Sumg1g2.plotOn(massframe, LineColor(1));
Sumg1g2.plotOn(massframe, Components(g1), LineStyle(kDashed), LineColor(kRed));
Sumg1g2.plotOn(massframe, Components(g2),  LineStyle(kDashed), LineColor(kBlue));

massframe->Draw();

}

int main(){
sum_gauss();
return 0;
}
