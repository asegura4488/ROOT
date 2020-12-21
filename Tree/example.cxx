#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"

#ifndef __CINT__

int main(int argc, char **argv){

TFile hfile("htree.root","RECREATE");

TH1F *hpx = new TH1F("hpx","px distribution", 100, -4 , 4);
TH2F *hpxpy = new TH2F("hpxpy", "2D transverse",40, -4, 4,40,-4,4);
TProfile *hprof = new TProfile("hprof", "Profile", 100, -4, 4, 0, 20);


 


//Some structures
typedef struct {Float_t x,y,z;} SPoint;
typedef struct {
	Int_t ntrack, nseg, nvertex;
	UInt_t flag;
	Float_t Temperature; 
} SEvent;

static SPoint Point;
static SEvent Event;

TTree *tree = new TTree("T","New_Tree");
 tree->Branch("Point", &Point, "x:y:z");
 tree->Branch("Event", &Event, "ntrack/I:nseg/I:nvertex/I:flag/i:Temperature/F");
 tree->Branch("hpx","TH1F",&hpx,128000,0);

Float_t px,py,pz;
static Float_t p[3];

for ( Int_t i=0; i<1000; i++) {
       gRandom->Rannor(px,py);
       pz = px*px + py*py;
       Float_t random = gRandom->Gaus(0,1);

hpx->Fill(px);
hpxpy->Fill(px,py,1);
hprof->Fill(px,pz,1);

Point.x= 10*(random-1);
Point.y= 5*random;
Point.z= 20*random;

       Event.ntrack  = Int_t(100*random);
       Event.nseg    = Int_t(2*Event.ntrack);
       Event.nvertex = 1;
       Event.flag    = Int_t(random+0.5);
       Event.Temperature = 20+random;


p[0] = px;
p[1] = py;
p[2] = pz;


 tree->Fill();

}

tree->Print();
hfile.Write();
hfile.Close();

}
#endif
