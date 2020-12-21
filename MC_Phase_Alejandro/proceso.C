/******************************************************************
 *                                                                 *
 *                                                                 *
 *                                                                 *
 *   Programa de procesos de dispersión 	                   *
 *                                                                 *
 *                                                                 *
 *                                                                 *
 *   Este programa genera eventos A+B -> C+D  	                   *
 *                       					   *
 *                          					   *
 *                                                                 *
 *   Autor:       Manuel Alejandro Segura D                        *
 *                Universidad Distrital FJC                        *
 *                Proyecto de Licenciatura en Física               *   	 
 *                Grupo de investigación FISINFOR                  *
 ******************************************************************/ 

using namespace std;
#include <time.h>
#include <iostream>
#include <fstream>
#include "include/ROOT.h"
#include "include/booking.h"
#include "include/abs_d.h"      
#include "include/azimuth.h"    
#include "include/polar.h"
#include "include/gstyle.h"
#include "TRandom3.h"
#include "TRandom2.h"
#include "TGenPhaseSpace.h"
#include "TF1.h"
#include "TF2.h"
#include "TF3.h"

void usage(){                          //Funcion de opciones de comando
  cerr << "Este programa tiene opciones de comando, aqui se da un ejemplo:\n" << '\n';
  cout << "./proceso -[opcion] " << '\n';
  cout << "-E<Energia del foton>    :  Energia del foton -E2.0  (Significa 2.0GeV)" << '\n';
  cout << "-e<Numero de eventos>    :  Numero de eventos para ser generados -e20000" << '\n';
  cout << "-o<Archivo de salida>    :  Nombre del archivo de datos -omisdatos" << '\n';
  cout << "                            La extension esta hecha por el codigo" << '\n';
  cout << "-l<Distribucion-energia> :  Eventos de energia por eventos generados" << '\n';
  cout << "                            Por defecto se tiene un beam de energia EG unica"<< '\n';
  exit(8);
}

 
 
/****************
 *Programa Main *
 ***************/

int main(int argc, char *argv[])
{

       
  if(argc == 1){
  usage();
  }
  
  while((argc > 1) && (argv[1][0] == '-')){
    switch (argv[1][1]){
    
    //Energia del haz de fotones
    case 'E':
      EG = atof(&argv[1][2]);
      break;
  
    //Numero de eventos procesados
    case 'e':
      NEVENT = atoi(&argv[1][2]);
      break;
      
    //Loop sobre la energia del beam
    case 'l':
      loope = atoi(&argv[1][2]);
      break;
    
    //Archivo de salida 
    case 'o':
      file_name = &argv[1][2];
      break;
      
    default:
    cerr << "Por favor, verifique sus opciones y pruebe nuevamente .... " << '\n' <<'\n';
   // usage();
    }
    
      
    ++argv;
    --argc;
    
  }
		
  if(EG==-1){usage();}
  if(NEVENT==0){usage();}     
 						
  sprintf(file_dat,"%s_%d.dat",file_name,run);
  sprintf(file_root,"%s_%d.root",file_name,run);
  TFile *f = new TFile(file_root,"RECREATE");		//Creando los archivos Dat y Root
  ofstream outfile(file_dat);
  outfile.precision(DIGIT);  
  outfile << NEVENT << endl;              
  
  gstyle();
  booking(); 						//Haciendo los histogramas
  
  // LOOP DE EVENTOS!!!!!!!!!!!!!!!!!!!!
    
    gRandom->SetSeed();

    TLorentzVector ppl(0.0, 0.0, 0.0, MP);  		// Cuadrimomento del Target
    	
    
     for(int j = 0; j<loope; j++){
     if(loope==1){					//condicion para distribucion de energia
     n=EG;
     }else{n=gRandom->Uniform(0,EG);}
  
     TLorentzVector pgl(0.0, 0.0, n, n);    		// Cuadrimomento de Beam
     w=(ppl+pgl);    					// Suma de cuadrimomentos
    	
     Double_t masses[2] = { ML, MK};
     TGenPhaseSpace event;				// Generador de eventos
     event.SetDecay(w, 2, masses);   
     
     
     for(int i = 0; i< NEVENT; i++){

     
     weight=event.Generate();
     TLorentzVector *ppldl = event.GetDecay(0);
     TLorentzVector *ppkpl = event.GetDecay(1);
     pldl = *ppldl;					//Momentum de lambda en el laboratorio
     pkpl = *ppkpl;					//Momentum de Kaon en el laboratorio    
   
     //Boost sobre el centro de masas
     
     beta = w.Rho()/w.E();			//Calculando la velocidad del centro de masas
      
     beta_w.SetZ(-beta);
      
     TLorentzRotation LAB_CM;

     LAB_CM.Boost(beta_w);                      //Boost sobre el centro de masas  

      
     gcm   = 1/sqrt(1-beta*beta);             	// Gamma cm
     Ebcm  = gcm*(1-beta)*EG;                	// Energia del foton C.M
     Etcm  = gcm*MP;                       	// Energia del target in C.M

     pkpcm = LAB_CM*pkpl;                       //Cuadrimomento del Kaon en el centro de masas
     pldcm = LAB_CM*pldl;                       //Cuadrimomento del Lambda en el centro de masas
     pptcm = LAB_CM*ppl;                       //Cuadrimomento del target en el centro de masas
     pbcm =  LAB_CM*pgl;                        //Cuadrimomento del beam en el centro de masas
 
     Slabi = (ppl+pgl);                         // Canal s Lab, estado inicial
     Slabf = (pldl+pkpl);                       // Canal s Lab, estado final 
     Scmi  = (pptcm+pbcm);                      // Canal s Cm, estado inicial  
     Scmf  = (pkpcm+pldcm);                     // Canal s Cm, estado final
     		            
     T1l=(ppl-pldl);		                //Canal T1 laboratorio
     T2l=(pgl-pkpl);			        //Canal T2 laboratorio
     U1l=(ppl-pkpl);		                //Canal U1 laboratorio
     U2l=(pgl-pldl);			        //Canal U2 laboratorio	
	
     T1cm=(pptcm-pldcm);			//canal T1 en el centro de masas
     T2cm=(pbcm-pkpcm);				//canal T2 en el centro de masas
     U1cm=(pptcm-pkpcm);			//Canal U1 en el centro de masas	
     U2cm=(pbcm-pldcm);				//canal U2 en el centro de masas

    //llenando Histogramas
    
    masak->Fill(pkpl.M()); 				//Masa del kaon
    dkcos->Fill(pkpl.CosTheta());    			 //Distribucion en coseno theta del kaon
    dkteta->Fill(pkpl.Theta()*180.0/TMath::Pi()); 	//Distribucion en theta del kaon   
    dkphi->Fill(pkpl.Phi()*180.0/TMath::Pi()); 		//Distribucion en phi del kaon 
    mld= gRandom->BreitWigner(pldl.M(),0.0156);
    masald->Fill(mld); 					//Masa del lambda
    dldteta->Fill(pldl.Theta()*180.0/TMath::Pi()); 	//Distribucion en theta del lambda
    dldcos->Fill(pldl.CosTheta());		 	//Distribucion en cos(theta) del lambda
    dldphi->Fill(pkpl.Phi()*180.0/TMath::Pi());         //Distribucion en phi del kaon
    dktetacm->Fill(pkpcm.Theta()*180.0/TMath::Pi());     //Distribucion en theta del kaon en CM
    dkcoscm->Fill(pkpcm.CosTheta());  			//Distribucion en cos(theta) del kaon en CM
    dkphicm->Fill(pkpcm.Phi()*180.0/TMath::Pi());       //Distribucion en phi del kaon en CM
    dldtetacm->Fill(pldcm.Theta()*180.0/TMath::Pi());    //Distribucion en theta del Lambda en CM
    dldcoscm->Fill(pldcm.CosTheta());   	 //Distribucion en cos(theta) del Lambda en CM
    dldphicm->Fill(pldcm.Phi()*180.0/TMath::Pi());      //Distribucion en Phi del Lambda en CM

    //Canal s, Laboratorio.

    SLabi->Fill(Slabi.M2());                            //Estado inicial                            
    SLabf->Fill(Slabf.M2());                            //Estado final
 
    //Canal s, Centro de masas  

    SCmi->Fill(Scmi.M2());                              //Estado inicial                              
    SCmf->Fill(Scmf.M2());                              //Estado final 
    

  
    canalt1->Fill(T1l.M2());				//canal t1 laboratorio
    canalt2->Fill(T2l.M2());				//canal t2 laboratorio
    canalu1->Fill(U1l.M2());				//canal u1 laboratorio
    canalu2->Fill(U2l.M2());				//canal u2 laboratorio

    canalt1cm->Fill(T1cm.M2());				//canal t1 centro de masas
    canalt2cm->Fill(T2cm.M2());				//canal t2 centro de masas
    canalu1cm->Fill(U1cm.M2());				//canal u1 centro de masas
    canalu2cm->Fill(U2cm.M2());				//canal u2 centro de masas	

    //Variables Cinematicas y energia minima

    Energiagcm->Fill(pbcm.E());
    Energiapcm->Fill(pptcm.E());	 

       
    betald->Fill(pldl.Rho(), pldl.Rho()/pldl.E());      // momentum y beta del lambda
    betak->Fill(pkpl.Rho(), pkpl.Rho()/pkpl.E());       // momentum y beta del kaon  
    
    enminld->Fill(pgl.E(),pldl.Rho());			//Energia minima para producir un lambda
    enminkp->Fill(pgl.E(),pkpl.Rho());			//Energia minima para producir un kaon

    //variables cinematicas del Kaon

    PxC->Fill(pkpl.Px());				//Momentun en x del kaon
    PyC->Fill(pkpl.Py());				//Momentun en y del kaon
    PzC->Fill(pkpl.Pz());				//Momentun en z del kaon
    EC->Fill(pkpl.E());					//Energia del kaon
    PxcmC->Fill(pkpcm.Px());				//Momentun en x del kaon cm
    PycmC->Fill(pkpcm.Py());				//Momentun en y del kaon cm
    PzcmC->Fill(pkpcm.Pz());				//Momentun en z del kaon cm
    PtcmC->Fill(pkpcm.Rho());				//Momentum total del kaon cm	
    EcmC->Fill(pkpcm.E());				//Energia del kaon cm

    //variables cinematicas del lambda

    PxD->Fill(pldl.Px());				//Momentun en x del lambda
    PyD->Fill(pldl.Py());				//Momentun en y del lambda
    PzD->Fill(pldl.Pz());				//Momentun en z del lambda
    ED->Fill(pldl.E());					//Energia del lambda
    PxcmD->Fill(pldcm.Px());				//Momentun en x del lambda cm
    PycmD->Fill(pldcm.Py());				//Momentun en y del lambda cm
    PzcmD->Fill(pldcm.Pz());				//Momentun en z del lambda cm
    PtcmD->Fill(pldcm.Rho());				//Momentum total del lambda cm	
    EcmD->Fill(pldcm.E());				//Energia del lambda cm

   
    // Escribiendo la informacion en los archivos de salida
    
     	outfile << masak << " ";    
	outfile << dkcos << " ";
        outfile << dkteta << " ";                       
     	outfile << dkphi << " "; 
	outfile << masald << " ";
        outfile << dldteta << " ";              
	outfile << dldcos << " ";                  
     	outfile << dldphi << " "; 
	outfile << dkcoscm << " "; 
	outfile << dktetacm << " "; 
	outfile << dkphicm << " "; 
        outfile << dldtetacm << " "; 
	outfile << dldcoscm << " "; 
	outfile << dldphicm << " "; 
	outfile << SLabi << " ";
	outfile << SLabf << " ";
        outfile << SCmi << " ";
        outfile << SCmf << " ";
	outfile << canalt1 << " "; 
        outfile << canalt2 << " ";
	outfile << canalu1 << " "; 
        outfile << canalu2 << " ";
	outfile << canalt1cm << " ";
        outfile << canalt2cm << " ";
	outfile << canalu1cm << " ";
	outfile << canalu2cm << " ";
        outfile << betald << " "; 
        outfile << betak << " ";  
	outfile << enminld << " "; 
        outfile << enminkp << " "; 
        outfile << Energiagcm << " ";
	outfile << Energiapcm << " ";
	outfile << PxC << " ";
	outfile << PyC << " ";
	outfile << PzC << " ";
        outfile << EC << " ";
	outfile << PxcmC << " ";
	outfile << PycmC << " ";	 
	outfile << PzcmC << " ";
	outfile << EcmC << " ";
        outfile << PtcmC << " ";
	outfile << PxD << " ";
	outfile << PyD << " ";
	outfile << PzD << " ";
        outfile << ED << " ";
	outfile << PxcmD << " ";
	outfile << PycmD << " ";	 
	outfile << PzcmD << " ";
	outfile << PtcmD << " ";
        outfile << EcmD << " ";
}
}  
 
        
	f->Write();              	// escribiendo sobre el archivo de histogramas
  	f->Close();
     
     
}    				 			// Final de programa

