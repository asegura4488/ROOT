using namespace RooFit;

void poly(){

RooRealVar mass("mass","mass",-2.0,10.0);   //RooRealVar = variable
RooRealVar a0("a0","a0",0.1,0,1);
RooRealVar a1("a1","a1",2,0,3);

//pdf
RooPolynomial Poly("Poly","Poly",mass, RooArgSet(a0,a1)); 

RooPlot *massframe = mass.frame();

Poly.plotOn(massframe, LineColor(kBlack));

massframe->Draw();

}

int main(){
poly();
return 0;
}
