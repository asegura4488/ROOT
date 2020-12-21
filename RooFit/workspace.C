using namespace RooFit;

void workspace(){

RooWorkspace w("myWorkspace", true);
w.factory("Gaussian::g1(mass[-2.0,2.0],mean[0,-1.,1.],width[0.03,0.001,1])");
RooRealVar *mass = w.var("mass");


// import other pdf to workspace
RooRealVar a0("a0","a0",0.1,0,1);
RooRealVar a1("a1","a1",0.1,0,3);
RooPolynomial Poly("Poly","Poly", *mass, RooArgSet(a0,a1)); 
w.import(Poly);

// Adding the pdf 
w.factory("SUM::sum(nsig[200,0,10000]*g1,nbkg[800,0,10000]*Poly)");
auto sum = w.pdf("sum"); // Returns as RooAbspdf*
w.Print();

RooPlot *massframe = mass->frame();

sum->plotOn(massframe, LineColor(kBlack));
sum->plotOn(massframe, Components(*w.pdf("g1")), LineStyle(kDashed), LineColor(kRed));
sum->plotOn(massframe, Components(*w.pdf("Poly")), LineStyle(kDashed), LineColor(kBlue));
  
massframe->Draw();

//w.writeToFile("Test.root"); // to import from input files later

}

int main(){
workspace();
return 0;
}
