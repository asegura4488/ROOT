/////////////////
// PDG id numbers
/////////////////

const int pid_pt      = 2212;             // Target. As same as proton
const int pid_g       = 22;               // photon
const int pid_p       = 2212;             // proton
const int pid_kp      = 321;              // kaon+
const int pid_km      = -321;             // kaon-
const int pid_pp      = 211;              // pion+
const int pid_pm      = -211;             // pion-
const int pid_phi     = 333;              // phi meson (1020)
const int pid_rho     = 113;              // rho meson (770)

const char *file_name = "";    // data outfile name
char file_dat[50];                       // dat outfile
char file_root[50];                       // root outfile
const int DIGIT       = 6;                // number of decimals in outfile




///////////////////////////////////////////////////////////////
// HEAD bank stuff (BOS file). Please see CLAS bank definitions
///////////////////////////////////////////////////////////////

const int v_ev            = 1;            // version of event format (Head bank BOS file)
const int ev_type         = -3;           // event type
const int ev_weigth       = 1;            // event weigth 
const int ev_class        = 11;           // evet class
const int trig            = 0;            // trigger bits 


/////////////////////
// Physical constants
/////////////////////

const double TARGET   = 40.0;             // target Length in cm
const double q        = 1.0;              // 1 means "|e|" electric charge.
const double c        = 299.792428;       // speed of light in mm/ns
const double PI       = 3.141592654;
const double ZERO     = 0.0;
const double PHI_MAX  = 6.283185307;
const double PHI_MIN  = 0.0;
const double TH_MAX   = 6.283185307;
const double TH_MIN   = 0.0;
const double MP       = 0.93827;
const double MN       = 0.93957;
const double MK       = 0.49368;     
const double MPI      = 0.13957;     
const double MPHI     = 1.01946;
const double MRHO     = 0.7755;

//At Lab frame (lab = l)

const double PT_X     = 0.0;               // Proton (target) x-momentum
const double PT_Y     = 0.0;               // Proton (target) y-momentum
const double PT_Z     = 0.0;               // Proton (target) z-momentum
const double EPT      = MP;                // Proton Energy (target)
const double XPT       = 0;                // target x-position 
const double YPT       = 0;                // target x-position 
const double ZPT       = 0;                // target x-position 




/////////////////////
// 4-momentum vectors
/////////////////////

// at lab frame
TLorentzVector aux;
TLorentzVector aux1;
TLorentzVector pgl;                        // pg   = 4-momentum photon
TLorentzVector pptl;                       // pt   =   " "      proton (target)
TLorentzVector ppl;                        // p    =   " "      proton (outgoing)
TLorentzVector pphil;                      // pphi =   " "      phi
TLorentzVector prhol;                       // prho =   " "      rho
TLorentzVector pkpl;                       // pkp  =   " "      kaon+
TLorentzVector pkml;                       // pkm  =   " "      kaon-
TLorentzVector pppl;                       // ppp  =   " "      pion+
TLorentzVector ppml;                       // ppm  =   " "      pion-

//at cm frame
TLorentzVector pgcm;
TLorentzVector pptcm;
TLorentzVector ppcm;
TLorentzVector pphicm;
TLorentzVector prhocm;
TLorentzVector pkpcm;
TLorentzVector pkmcm;
TLorentzVector pppcm;
TLorentzVector ppmcm;

//at rest frame
TLorentzVector pgrest;
TLorentzVector pptrest;
TLorentzVector pprest;
TLorentzVector pphirest;
TLorentzVector prhorest;
TLorentzVector pkprest;
TLorentzVector pkmrest;
TLorentzVector ppprest;
TLorentzVector ppmrest;

// at Helicity Frame
TLorentzVector pghel;
TLorentzVector ppthel;
TLorentzVector pphel;
TLorentzVector pphihel;
TLorentzVector prhohel;
TLorentzVector pkphel;
TLorentzVector pkmhel;
TLorentzVector ppphel;
TLorentzVector ppmhel;





////////////////////
// Lorentz Rotations
////////////////////

TLorentzRotation I;
TLorentzRotation CM_LAB;                   // Lorentz trans. from CM of gamma and target to LAB frame
TLorentzRotation REST_LAB;                 // Lorentz trans. from phi REST frame to LAB frame
TLorentzRotation LAB_CM;                   // LAB to CM of gamma and target
TLorentzRotation LAB_REST;                 // LAB to phi REST frame
TLorentzRotation CM_REST;                  // CM to phi REST frame
TLorentzRotation REST_CM;                  // REST to phi CM frame
TLorentzRotation HEL_REST;                  // HEL to phi REST frame
TLorentzRotation REST_HEL;                  // REST to phi HEL frame

TLorentzRotation HEL_CM;                  // HEL to phi REST frame
TLorentzRotation CM_HEL;                  // REST to phi HEL frame



////////////////
// Lorentz Boots
////////////////

TVector3 BCM;
TVector3 BHEL;
TVector3 bphil;                            //velocity of phi in lab frame
TVector3 brhol;                            //velocity of rho in lab frame
TVector3 bpl;                              // "           proton  "



///////////////////
// GLOBAL VARIABLES
///////////////////

// integer variables

//command options
int meson;                                  // default meson option (phi)
int ppev;                                   // default print option
int NEVENT;                                 // Number of events to be generated
int run;                                    // Run number

// double variables

//Director cosines
double dcx_phil;
double dcx_rhol;
double dcx_pl;
double dcx_gl;
double dcx_kpl;
double dcx_kml;
double dcx_ppl;
double dcx_pml;

double dcy_phil;
double dcy_rhol;
double dcy_pl;
double dcy_gl;
double dcy_kpl;
double dcy_kml;
double dcy_ppl;
double dcy_pml;

double dcz_phil;
double dcz_rhol;
double dcz_pl;
double dcz_gl;
double dcz_kpl;
double dcz_kml;
double dcz_ppl;
double dcz_pml;


// kinematical variables 
double EG;                 // Photon beam energy
double EPHIcm;             // Phi meson energy at cm frame 
double EPcm;               // proton energy at cm frame 
double ERHOcm;             // Rho meson energy at cm frame 
double EKPrest;            // Kaon plus energy in phi rest frame (rest)
double EKMrest;            //  "   minus  "        "   "     "     "
double EPPrest;            // pion plus energy in phi rest frame (rest)
double EPMrest;            //  "   minus  "        "   "     "     "
double EPhel;              // Proton Energy in Helicity Frame

double theta_cm;           // theta in cm for phi particle. It must be generated
double phi_cm;             // phi in cm        """        .  ""
double p_phicm;            // phi meson momentum at cm frame (p_ stands for momentum)
double p_rhocm;            // rho meson momentum at cm frame (p_ stands for momentum)
double p_pcm;              // proton momentum at cm frame    ("                "    )
double theta_rest;         // theta in rest frame for kaon+
double phi_rest;           // phi "     "        "
double p_kprest;           // kaon+ momentum at rest frame (p_ stands for momentum)
double p_kmrest;           // kaon- momentum at rest frame (p_ stands for momentum)
double p_pprest;           // pion+ momentum at rest frame (p_ stands for momentum)
double p_pmrest;           // pion- momentum at rest frame (p_ stands for momentum)


double p_kphel;            // kaon+ momentum at rest frame (p_ stands for momentum)
double p_kmhel;            // kaon- momentum at rest frame (p_ stands for momentum)
double p_pphel;            // pion+ momentum at rest frame (p_ stands for momentum)
double p_pmhel;            // pion- momentum at rest frame (p_ stands for momentum)
double p_phel;             // proton momentum at rest frame (p_ stands for momentum)
double costh;              //costh random variable
//vertex at target

double xxl;                // random variables  
double yyl;
double zzl;

double xl;                 // vertex reaction coordinates at lab frame
double yl;
double zl;
