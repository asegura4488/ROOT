#include "ROOT.h"

//Directorios


TDirectoryFile *Kaon;
TDirectoryFile *Lambda;
TDirectoryFile *Invariantes;
TDirectoryFile *Comparasiones;
///////////////
//Histogramas 1D
///////////////


TH1F* masak;			//Masa del kaon

TH1F* dkcos;                    //Distribucion angular de coseno theta del kaon
TH1F* dkteta;			//Distribucion angular de theta del kaon
TH1F* dkphi;			//Distribucion angular de phi del kaon
TH1F* masald;			//Masa del lambda
TH1F* dldteta;                  //Distribucion angular de theta del lambda
TH1F* dldcos;                   //Distribucion angular del cos(theta) del lambda
TH1F* dldphi;			//Distribucion angular de phi del lambda

TH1F* dktetacm;			//Distribucion angular de theta del kaon en CM
TH1F* dkcoscm;			//Distribucion angular del coseno de theta del kaon en CM
TH1F* dkphicm;			//Distribucion angular de phi del kaon en CM
TH1F* dldtetacm;                //Distribucion angular de theta del lambda CM
TH1F* dldcoscm;                 //Distribucion angular del cos(theta) del lambda CM
TH1F* dldphicm;			//Distribucion angular de phi del Lambda en CM


TH1F* SLabi;                    //Canal s Lab, Estado inicial
TH1F* SLabf;			//Canal s Lab, Estado final
TH1F* SCmi;			//Canal s Cm, Estado inicial
TH1F* SCmf;		        //Canal s Cm, Estado final

TH1F* canalt1;			//canal t1 a->c
TH1F* canalt2;			//canal t2 b->d
TH1F* canalu1;			//canal t1 a->d
TH1F* canalu2;			//canal t2 b->c

TH1F* canalt1cm;		//canal t1cm 
TH1F* canalt2cm;		//canal t2cm 
TH1F* canalu1cm;		//canal u1cm 
TH1F* canalu2cm;		//canal u2cm 

TH1F* Energiagcm;               //Energia del Beam y el Target en el Cm
TH1F* Energiapcm;

TH2F* betald;			//Beta del lambda en funcion del momentum 
TH2F* betak;			//Beta del kaon en funcion del momentum
TH2F* enminld;			//Energia mínima para producir Lambdas
TH2F* enminkp;			//Energia mínima para producir Kaones

TH1F* PxC;			// Momentun en X del kaon
TH1F* PyC;			// Momentun en Y del kaon
TH1F* PzC;			// Momentun en Z del kaon
TH1F* EC;			// Energia del kaon
TH1F* PxcmC;			// Momentun en X del kaon
TH1F* PycmC;			// Momentun en Y del kaon
TH1F* PzcmC;			// Momentun en Z del kaon
TH1F* EcmC;			// Energia del kaon
TH1F* PtcmC;			// Momentum total del kaon centro de masas

TH1F* PxD;			// Momentun en X del lambda
TH1F* PyD;			// Momentun en Y del lambda
TH1F* PzD;			// Momentun en Z del lambda
TH1F* ED;			// Energia del lambda
TH1F* PxcmD;			// Momentun en X del lambda
TH1F* PycmD;			// Momentun en Y del lambda
TH1F* PzcmD;			// Momentun en Z del lambda
TH1F* EcmD;			// Energia del lambda
TH1F* PtcmD;			// Momentum total del lambda centro de masas
