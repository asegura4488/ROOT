using namespace RooFit;

void gauss(){

RooRealVar mass("mass","mass",-2.0,2.0);   //RooRealVar = variable
RooRealVar mean_("mean","mean",0 ,-1, 1);  // mean , min , max
RooRealVar sigma_("sigma","sigma", 0.1, 0.,1.); // sigma , min , max 

//pdf
RooGaussian g1("g1","g1",mass, mean_, sigma_); 

RooPlot *massframe = mass.frame();

g1.plotOn(massframe, LineColor(kRed));

massframe->Draw();

}

int main(){
gauss();
return 0;
}
