


const char *file_name = "";              // Nombre del archivo de datos de salida
char file_dat[50];                       // Archivo de salida Dat 
char file_root[50];                      // Archivo de salida Root
const int DIGIT       = 6;               // Numero de decimales del archivo de salida


/////////////////////
// Constantes Fisicas
/////////////////////

const double TARGET   = 40.0;            
const double q        = 1.0;              
const double c        = 299.792428;       
const double PI       = 3.141592654;
const double ZERO     = 0.0;
const double PHI_MAX  = 6.283185307;
const double PHI_MIN  = 0.0;
const double TH_MAX   = 6.283185307;
const double TH_MIN   = 0.0;
const double MP       = 0.93827;              //Masa del proton en Gev/c^2
const double ML       = 1.15195;	      //Masa del Lambda en Gev/c^2     
const double MK       = 0.493679;     	      //Masa del Kaon en Gev/c^2	


TVector3 beta_w(0,0,0);	       		      //Vector centro de masas	


/////////////////////
//Cuadri-momentos ///
/////////////////////


TLorentzVector pkpl;			     //Cuadrimomento del Lambda en el laboratorio
TLorentzVector pldl;                         //Cuadrimomento del kaon en el laboratorio	 
TLorentzVector pptcm;			     //Cuadrimomento del target en el centro de masas
TLorentzVector pbcm;                         //Cuadrimomento del beam en el centro de masas
TLorentzVector pkpcm;			     //Cuadrimomento del Lambda en el CM
TLorentzVector pldcm;                        //Cuadrimomento del kaon en el CM	
TLorentzVector w;			     //Cuadrimomento Total	
TLorentzVector Slabi;                        //Cuadrimomento Estado inicial Lab
TLorentzVector Slabf;                        //Cuadrimomento Estado final Lab  
TLorentzVector Scmi;                                 
TLorentzVector Scmf;			     //Cuadrimomento Total en centro de 

TLorentzVector T1l;			     //canal T A->C	
TLorentzVector T2l;		             //Canal T B->D
TLorentzVector U1l;			     //canal U A->D	
TLorentzVector U2l;		             //Canal U B->C	
TLorentzVector T1cm;                         //Canal T en el centro de masas   
TLorentzVector T2cm;                         //Canal T en el centro de masas 
TLorentzVector U1cm;                         //Canal U en el centro de masas 
TLorentzVector U2cm;                         //Canal U en el centro de masas 


///////////////////
// GLOBAL VARIABLES
///////////////////
double n;
Double_t weight = 0;
int ppev;                                   
int loope=1;
int NEVENT;                                 
int run;                                    
double delta=0.1;
double central;
double xmin;
double xmax;

double mk;			
double mld;                     //masa con breitwigner
double Il;
double Icm;
//Variables Cinematicas
double EG    = 0.0;             // Energia del haz de fotones
double gcm   = 0.0;             // Gamma cm
double Ebcm  = 0.0;             // Energia del foton en el C.M
double Etcm  = 0.0;             // Energia del target en el C.M   
double beta  = 0.0;			
