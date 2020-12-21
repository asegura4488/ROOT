 /******************************************************************
 *                                                                 *
 *                                                                 *
 *                                                                 *
 *   Program phasespace_gen.C                                      *
 *                                                                 *
 *                                                                 *
 *                                                                 *
 *   This program generates events accordingly to:                 *
 *   1.       g p-> p + phi =====> phi->k- + k+                    *
 *   2.       g p-> p + rho =====> rho->? ?                        *
 *                                                                 *
 *   Author:      Julian Salamanca                                 *
 *                Idaho State University                           *
 *                Department of Physics                            *
 *                                                                 *
 *  Usage:        Please read README.phasespace_gen                *
 *                                                                 *
 *                                                                 *
 *                                                                 *
 ******************************************************************/


using namespace std;
#include <time.h>
#include <iostream>
#include <fstream>
#include "include/ROOT.h"
#include "include/variables.h"
//#include "include/hist_dec.h"
#include "include/booking.h"
#include "include/abs_d.h"      //absolute value for a double variable
#include "include/azimuth.h"    
#include "include/polar.h"
#include "TRandom3.h"
#include "TRandom2.h"
#include "TGenPhaseSpace.h"
#include "TF1.h"
#include "TF2.h"
#include "TF3.h"

// Parameters for the cohedge function (a "fake" one ...)

const double p = 2.1;            // where the peak starts
const double mp = 2.11;          // where the peak drops
const double norm = 1.0;         // for the arg in Exp function Exp(norm*arg)
const double frac_peak = 0.1;    // percentage from the peak to fake the flat part of the photon's spectrum
const double edge = 2.12;        // where the flat part is going to start
const Double_t max_func = 2.11;
const Double_t min_func = 1.89;

void usage(){
  cerr << " Command with no options. Here is an example:  " << '\n';
  cout << "./phasespace_gen -[options] " << '\n';
  cout << "-E<Photon energy>      :  Photon energy i.e. -E2.0  ( It means 2.0GeV)" << '\n';
  cout << " -e<Number of events>  :  Number of events to be generated i.e. -e20000  (20000 events)" << '\n';
  cout << " -o<outputfile>        :  dat file name i.e. -omyfile " << '\n';
  cout << "                          the extension is made by the code" << '\n';
  cout << " -p<processed events>  :  print events processed from the total events inthe -e option" << '\n';
  cout << " -r<run_number>        :  run number. By default is -999999" << '\n';
  cout << "                          please start from 1; the next one will we 2 and so on " << '\n';
  cout << " -P<polarization>      :  Angle of Polarization orientation in degree: " << endl;
  cout << "                           0.0: para   90.0: perp.  This is for the angle" << '\n';
  cout << "                          between polarization plane and reaction plane" << endl;
  cout << " -O<parameter file>    :  A simple dat file where 10 out of 11 parameters are for the w dist" << endl;
  exit(8);

}

/***********************
 * energy distribution *
 **********************/

Double_t expFun(Double_t *x, Double_t *par)
{
  Double_t arg = 0;
  arg = norm*par[1]*x[0];
  Double_t fun1 = 0;
  Double_t fun2 = 0;
  fun1 = TMath::Exp(par[0])*TMath::Exp(arg);
  fun2 = par[2] + par[3]*x[0];

  Double_t para = p;
  Double_t max_para = mp;
  

  if(x[0]< para)
    return fun1;
  else if((x[0]>=para)&&(x[0]<max_para))
    return fun2;
  else
    return par[4];
}


/*************************************************
 * Linear polarized Angular distibution function *
 ************************************************/

Double_t w(Double_t *x,Double_t *par)
{
  Double_t w;
  Double_t w0;
  Double_t w1;
  Double_t w2;
  Double_t th;
  
  Double_t P_g = par[9];    // degree of polarization;
  Double_t ph = x[0];    // angle between production plane and the vector polarization
  Double_t cth = x[1];
  Double_t e_ang = x[2];  // angle between production plane and the vector polarization
  
  th = acos(cth);

  w0 = 0.5*(1-par[0]) +
    0.5*(3*par[0]-1)*cos(th)*cos(th) -
    sqrt(2.0)*par[1]*sin(2*th)*cos(ph) -
    par[2]*sin(th)*sin(th)*cos(2*ph);
  w0 = 3 /(4*TMath::Pi())*w0;
  
  w1 = par[3]*sin(th)*sin(th) +
    par[4]*cos(th)*cos(th)-
    sqrt(2.0)*par[5]*sin(2*th)*cos(ph)-
    par[6]*sin(th)*sin(th)*cos(2*ph);
  w1 = 3 /(4*TMath::Pi())*w1;
  
  w2 = sqrt(2.0)*par[7]*sin(2*th)*sin(ph) +
    par[8]*sin(th)*sin(th)*sin(2*ph);
  w2= 3/(4*TMath::Pi())*w2;
  
  Double_t phase = par[10];
  w = w0 - P_g*cos(2*(e_ang + phase))*w1 - P_g*sin(2*(e_ang + phase))*w2;

  return w;
  
}

// t distribution

Double_t tFun(Double_t *x,Double_t *par)
{
  
  Double_t b = par[0];
  Double_t t = x[0];

  Double_t fun = TMath::Exp(b*t);
  
  return fun;
  
}



/****************
 * MAIN program *
 ***************/

int main(int argc, char *argv[]){
  

  double pol_ori;                // 0: para;  1: perp
  const char *par_file = "";    // data outfile name
  ppev = 0;                      // defautl print option "-p". It means no printing
  run = -99999999;               // default run number
  if(argc == 1){
    usage();
  }
  
  while((argc > 1) && (argv[1][0] == '-')){
    switch (argv[1][1]){
      // Photon Beam Energy
    case 'E':
      EG = atof(&argv[1][2]);
      break;
      
      
      //Number of events to be processed
    case 'e':
      NEVENT = atoi(&argv[1][2]);
      break;
      
      // output file 
    case 'o':
      file_name = &argv[1][2];
      break;
    
    case 'O':
      par_file = &argv[1][2];
      break;

      // print processed events
    case 'p':
      ppev = atoi(&argv[1][2]); 
      break;

    case 'P':
      pol_ori = atof(&argv[1][2]);
      break;

      // run number
    case 'r':
      run = atoi(&argv[1][2]); 
      break;
      
    default:
      cerr << " Please, check options and try again .... " << '\n';
      usage();
    }
    
    ++argv;
    --argc;
    
  }//while arg


  
  //GLOBAL VARIALES
  
  //creating  dat and root files
  sprintf(file_dat,"%s_%d.dat",file_name,run);
  sprintf(file_root,"%s_%d.root",file_name,run);
  TFile *f = new TFile(file_root,"RECREATE");
  ofstream outfile(file_dat);
  outfile.precision(DIGIT);  
  outfile << NEVENT << endl;              

  //opening par file (Here there are he parameters for w distribution)
  ifstream infile_par(par_file);

  double bcm   = 0.0;             // Beta center of mass (cm)
  double gcm   = 0.0;             // Gamma cm
  double EGcm  = 0.0;             // Photon energy in C.M
  double EPTcm = 0.0;             // Target energy in C.M
    
  // setting the target
  pptl.SetPxPyPzE(PT_X,PT_Y,PT_Z,MP);
  
  //Setting vertex distributions
  TF1 *gausFunc = new TF1("gausFunc","[0]*TMath::Exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))",-3,3);
  gausFunc->SetParameter(0,100);
  gausFunc->SetParameter(1,0.0);
  gausFunc->SetParameter(2,1.0);
  

  // setting parameters for the energy distribution  
  TF1 *func = new TF1("func",expFun, min_func, max_func, 5);
  
  Double_t par[5];
  par[0]=-12.44;
  //  par[1]=8.842;
  par[1]= 10.0;
  par[3]= -TMath::Exp(par[0])*TMath::Exp(par[1]*p)/(edge-p);
  par[2]= TMath::Exp(par[0])*TMath::Exp(par[1]*p) - par[3]*p;
  par[4]= TMath::Exp(par[0])*TMath::Exp(par[1]*p)*frac_peak;  
  func->SetParameters(par);


  // setting t distribution
  Double_t t_min = -2;
  Double_t t_max = 0.0;

  TF1 *tDist = new TF1("tDist",tFun,t_min,t_max,1);
  Double_t par_tFun[1];
  par_tFun[0] = 3.0;  // b parameter from a reference in Mibe's thesis
  
  tDist->SetParameters(par_tFun);

  // setting parameters on the angular distribution
  const int par_num = 11;
  Double_t xmin = 0.0;
  Double_t xmax = 2*TMath::Pi();
  Double_t ymin = -1.0;
  Double_t ymax = 1.0;
  
  TF3 *dsdw = new TF3("dsdw",w, xmin, xmax, ymin, ymax, xmin, xmax, par_num);

  //Pure naturally parity exchange gives p1_1-1 = - Im p2_1-1 = 0.5 (POMERON)
  //Pure UN-naturally parity exchange gives p1_1-1 = - Im p2_1-1 = -0.5 (Pion, eta)

  //i.e POMERON
  Double_t par_w[par_num];
  string sdm;
  double sdm_val;
  for(int jj = 0 ; jj < 10; jj++){
    infile_par >> sdm ;
    infile_par >> sdm_val;
    par_w[jj] = sdm_val;
    
    cout << sdm << " " << par_w[jj] << endl;
  }
  par_w[10] = pol_ori*TMath::Pi()/180.0;
  
  cout << "******************************** " << endl;
  cout << " Pol orientation : " << pol_ori << " degrees " << endl;
  cout << "******************************** " << endl;

  dsdw->SetParameters(par_w);
  
  // cos(theta), theta \phi_ang and \PSI
  Double_t cth;
  Double_t theta;
  Double_t ph;
  Double_t psi;
  
  //setting the generators
  
  TRandom3 r1(0);//time(NULL));
  TRandom3 r2(0);//time(NULL));
  TRandom3 *myRNG = new TRandom3();  //it will be the default generator
  
  int tt = time(NULL);
  int tinit = (int)tt%100000;
  
  cout << "time: " << tt << endl;
  cout << "the last 5 digits of time: " << tinit << endl;
  if(tinit > 60000){
    tinit = (int)tinit/2;
    cout << "Last 5 digits are more than 60000: " << endl;
    cout << "Maximun is 65000" << endl;
    cout << "Dividing by 2 tinit" << endl;
    cout << "New tinit: " << tinit << endl;
  }
  
  UInt_t seed = tinit;
  myRNG->SetSeed(seed);
  cout << "seed: " << seed << endl;
  gRandom = myRNG;           // setting myRNG as default one

  //  f->cd();
  booking(); //booking histograms
  
  // LOOP of EVENTS!!!!!!!!!!!!!!!!!!!!

  
  int evt_tru = 0;

  for(int i = 0; i< NEVENT; i++){
    
    // generating values for EG
    EG = func->GetRandom(1.8,2.2);
    //EG =2.1;
    //EG =r2.Uniform(1.8,2.2);
    
    bcm   = EG/(EG + MP);                  // Beta center of mass (cm)
    gcm   = 1/sqrt(1-bcm*bcm);             // Gamma cm
    EGcm  = gcm*(1-bcm)*EG;                // Photon energy in C.M
    EPTcm = gcm*MP;                        // Target energy in C.M
   
    EPHIcm = (MPHI*MPHI - MP*MP + (EGcm + EPTcm)*(EGcm + EPTcm))/(2*(EGcm + EPTcm));
    p_phicm = sqrt(EPHIcm*EPHIcm - MPHI*MPHI);           //phi meson cm momentum
        
    // Angular Distribution generates three values cos(theta): -1,1 , \phi-angle: 0,2pi ang psi-angle: 0,2pi
    
    dsdw->GetRandom3(ph,cth,psi);
    theta = acos(cth);


    // psi at this point is measured from the poarization plane to reaction one. 
    // We need it to be the other way arround
    psi = 2*TMath::Pi() - psi;
    
    //setting values in Helicity Frame
    p_kmhel = sqrt(MPHI*MPHI/4 - MK*MK);
    p_kphel = sqrt(MPHI*MPHI/4 - MK*MK);
    EPhel = (2*EG*MP - MPHI*MPHI)/(2*MPHI);
    p_phel = sqrt(EPhel*EPhel - MP*MP);
    
    //pkmhel.SetPxPyPzE(p_kmhel*cos(ph)*sin(theta), p_kmhel*sin(ph)*sin(theta), p_kmhel*cth, MPHI/2);
    //pkphel.SetPxPyPzE(-pkmhel.Px(),-pkmhel.Py(),-pkmhel.Pz(),MPHI/2);
    
    pkphel.SetPxPyPzE(p_kphel*cos(ph)*sin(theta), p_kphel*sin(ph)*sin(theta), p_kphel*cth, MPHI/2);
    pkmhel.SetPxPyPzE(-pkphel.Px(),-pkphel.Py(),-pkphel.Pz(),MPHI/2);

    pphihel.SetPxPyPzE(0,0,0,MPHI);
    pphel.SetPxPyPzE(0,0,-p_phel,EPhel);

    EPHIcm = ((pphihel + pphel).M2() + MPHI*MPHI - MP*MP)/(2*(pphihel + pphel).M());
    p_phicm = sqrt(EPHIcm*EPHIcm - MPHI*MPHI);
    
    Double_t bhel_cm = p_phicm/EPHIcm;

    BHEL.SetXYZ(0,0,bhel_cm);  // here I am boosting along the z-direction
    HEL_CM = I;
    HEL_CM.Boost(BHEL);
    ppcm  = HEL_CM*pphel;
    pphicm= HEL_CM*pphihel;
    pkpcm = HEL_CM*pkphel;
    pkmcm = HEL_CM*pkmhel;


    //ppcm.RotateY(TMath::Pi());
    //pphicm.RotateY(TMath::Pi());
    //pkpcm.RotateY(TMath::Pi());
    //pkpcm.RotateY(TMath::Pi());

    
    //now I have to make a Y-rotation because the reaction plane is actually a x-z reaction plane
    // I need to generate a 2D isotropic distribution for the azimutal angle in this plane
    
    Double_t th_rp;  // pol angle in the reaction plane
    Double_t cth_rp;  // cos(pol angle) in the reaction plane
    //cth_rp = r1.Uniform(-1,1);  // here we still are in the reaction plane Y=0
    //th_rp = acos(cth_rp);  // I have to think if the distribution should be by cos(th) or th
    //th_rp = r1.Uniform(0,2*TMath::Pi());  // here we still are in the reaction plane Y=0


    // actually what I am doing is generating the polar angle by applying a Y-axis rotation.
    // Here I can generate base on either an isotropic angular distribution, or following dsdw ~ exp(b*t).
    // Lets play with the second one. In this case th_rp will be the polar angle.

    Double_t t0, t1, sval, tval;
    
    sval = 2*EG*MP + MP*MP;

    t0 = (-MPHI*MPHI)*(-MPHI*MPHI)/(4*sval) - (EGcm - pphicm.Rho())*(EGcm - pphicm.Rho());
    t1 = (-MPHI*MPHI)*(-MPHI*MPHI)/(4*sval) - (EGcm + pphicm.Rho())*(EGcm + pphicm.Rho());

    //    cout << "EG: " << EG << endl;
    //cout << "t0: " << t0 << endl;
    //cout << "t1: " << t1 << endl;
        
    tval = tDist->GetRandom(t1,t0);
    cth_rp = (tval - MPHI*MPHI + 2*EGcm*EPHIcm)/(2*EGcm*pphicm.Rho());
    th_rp = acos(cth_rp);

    ppcm.RotateY(th_rp);
    pphicm.RotateY(th_rp);
    pkpcm.RotateY(th_rp);
    pkmcm.RotateY(th_rp);  

    pprest = ppcm;
    pphirest = pphicm;
    pkprest = pkpcm;
    pkmrest = pkmcm;


    //We have to generate an angle \PSI between pol plane and reaction plane
    
    Double_t psi_rp_pol;
    psi_rp_pol = psi;
    
    ppcm.RotateZ(psi_rp_pol);
    pphicm.RotateZ(psi_rp_pol);
    pkpcm.RotateZ(psi_rp_pol);
    pkmcm.RotateZ(psi_rp_pol); // know we are at the CM frame

    
    pptl.SetPxPyPzE(0,0,0,MP);
    pgl.SetPxPyPzE(0,0,EG,EG);
        
    BCM.SetXYZ(0,0,bcm);  // just to completness
    LAB_CM = I;
    LAB_CM.Boost(-BCM);
    pgcm  = LAB_CM*pgl;
    pptcm = LAB_CM*pptl;
       
    // the final step will be to get pp, pphi pkp and pkm to the lab frame
    BCM.SetXYZ(0,0,bcm);
    CM_LAB = I;
    CM_LAB.Boost(BCM);   // please see the sign. It is different from above
    ppl  = CM_LAB*ppcm;
    pphil = CM_LAB*pphicm;
    pkpl  = CM_LAB*pkpcm;
    pkml  = CM_LAB*pkmcm;
    
    //    aux = ppl + pkpl + pkml - pgl;                             //checking 4-momentum conservation    
    aux = ppl + pphil  - pgl;                             //checking 4-momentum conservation    

    
    //IMPORTANT
    // Here is the definition of two-body reaction in t channel
    //g + pt  -> phi + p
    //1  + 2  -> 3 + 4;
    //
    // t = (p1 - p3)^2 = (p2 - p4)^2
    
    //tmin def:
    // E. Byckling and K. Kajantie,"Particle Kinematics",pag 86-87. Wiley and Sons. 1973
    // At cm:
    // tmin = m1^2 + m3^2 - 2E1*E3 + 2P1*P3; where P1 and P3 are 3-momentum vectors
   
 
    float s12,s34,s12_cm,s34_cm;
    float t13,t24,t13_cm,t24_cm;
    float tmin_t13_cm, tmin_t24_cm;
        
    t13    = (pgl   - pphil ).M2();
    t24    = (pptl  - ppl   ).M2();
    t13_cm = (pgcm  - pphicm).M2();
    t24_cm = (pptcm - ppcm  ).M2();
    
    tmin_t13_cm = pgcm.M2() + pphicm.M2() - 2*pgcm.E()*pphicm.E() + 2*pgcm.Rho()*pphicm.Rho();
    tmin_t24_cm = pptcm.M2() + ppcm.M2() - 2*pptcm.E()*ppcm.E() + 2*pptcm.Rho()*ppcm.Rho();
    
    s12 = (pgl + pptl).M2();
    s34 = (pphil + ppl).M2();
    
    s12_cm = (pgcm + pptcm).M2();
    s34_cm = (pphicm + ppcm).M2();


    //Filling histos
    
    if(t13 < 0.00001){
      if((EG>1.89)&&(EG<2.11)){
	
	evt_tru++;

	mm_pt_l->Fill(aux.M()); // aux.M());  // checking for proton mass
	mm_p_l->Fill(ppl.M());
	mm_phi_l->Fill(pphil.M());
	mm_kp_l->Fill(pkpl.M());
	mm_km_l->Fill(pkml.M());    
	mm_g_l->Fill(pgl.M());    
	mm_pt_cm->Fill(pptcm.M());  // checking for proton mass
	
	mm_p_cm->Fill(ppcm.M());
	mm_phi_cm->Fill(pphicm.M());
	mm_kp_cm->Fill(pkpcm.M());
	mm_km_cm->Fill(pkmcm.M());    
	mm_g_cm->Fill(pgcm.M());    
	
	mm_pt_rest->Fill(pptrest.M());  // checking for proton mass
	mm_p_rest->Fill(pprest.M());
	mm_phi_rest->Fill(pphirest.M());
	mm_kp_rest->Fill(pkprest.M());
	mm_km_rest->Fill(pkmrest.M());    
	mm_g_rest->Fill(pgrest.M());    
	
	mm_pt_hel->Fill(ppthel.M());  // checking for proton mass
	mm_p_hel->Fill(pphel.M());
	mm_phi_hel->Fill(pphihel.M());
	mm_kp_hel->Fill(pkphel.M());
	mm_km_hel->Fill(pkmhel.M());    
	mm_g_hel->Fill(pghel.M());    
	
	
	mom3_p_l->Fill(ppl.Rho());
	mom3_kp_l->Fill(pkpl.Rho());
	mom3_km_l->Fill(pkml.Rho());
	mom3_phi_l->Fill(pphil.Rho());
	
	mom3_p_cm->Fill(ppcm.Rho());
	mom3_kp_cm->Fill(pkpcm.Rho());
	mom3_km_cm->Fill(pkmcm.Rho());
	mom3_phi_cm->Fill(pphicm.Rho());
	
	mom3_p_rest->Fill(pprest.Rho());
	mom3_kp_rest->Fill(pkprest.Rho());
	mom3_km_rest->Fill(pkmrest.Rho());
	mom3_phi_rest->Fill(pphirest.Rho());
	
	mom3_p_hel->Fill(pphel.Rho());
	mom3_kp_hel->Fill(pkphel.Rho());
	mom3_km_hel->Fill(pkmhel.Rho());
	mom3_phi_hel->Fill(pphihel.Rho());
	
	
	px_pt_l->Fill(aux.Px());  // checking for proton mass
	px_p_l->Fill(ppl.Px());
	px_phi_l->Fill(pphil.Px());
	px_kp_l->Fill(pkpl.Px());
	px_km_l->Fill(pkml.Px());    
	px_g_l->Fill(pgl.Px());    
	
	px_pt_cm->Fill(pptcm.Px());  // checking for proton mass
	px_p_cm->Fill(ppcm.Px());
	px_phi_cm->Fill(pphicm.Px());
	px_kp_cm->Fill(pkpcm.Px());
	px_km_cm->Fill(pkmcm.Px());    
	px_g_cm->Fill(pgcm.Px());    
	
	
	px_pt_rest->Fill(pptrest.Px());  // checking for proton mass
	px_p_rest->Fill(pprest.Px());
	px_phi_rest->Fill(pphirest.Px());
	px_kp_rest->Fill(pkprest.Px());
	px_km_rest->Fill(pkmrest.Px());    
	px_g_rest->Fill(pgrest.Px());    
	
	px_pt_hel->Fill(ppthel.Px());  // checking for proton mass
	px_p_hel->Fill(pphel.Px());
	px_phi_hel->Fill(pphihel.Px());
	px_kp_hel->Fill(pkphel.Px());
	px_km_hel->Fill(pkmhel.Px());    
	px_g_hel->Fill(pghel.Px());    
	
	
	py_pt_l->Fill(aux.Py());  // checking for proton mass
	py_p_l->Fill(ppl.Py());
	py_phi_l->Fill(pphil.Py());
	py_kp_l->Fill(pkpl.Py());
	py_km_l->Fill(pkml.Py());    
	py_g_l->Fill(pgl.Py());    
	
	py_pt_cm->Fill(pptcm.Py());  // checking for proton mass
	py_p_cm->Fill(ppcm.Py());
	py_phi_cm->Fill(pphicm.Py());
	py_kp_cm->Fill(pkpcm.Py());
	py_km_cm->Fill(pkmcm.Py());    
	py_g_cm->Fill(pgcm.Py());    
	
	
	py_pt_rest->Fill(pptrest.Py());  // checking for proton mass
	py_p_rest->Fill(pprest.Py());
	py_phi_rest->Fill(pphirest.Py());
	py_kp_rest->Fill(pkprest.Py());
	py_km_rest->Fill(pkmrest.Py());    
	py_g_rest->Fill(pgrest.Py());    
	
	py_pt_hel->Fill(ppthel.Py());  // checking for proton mass
	py_p_hel->Fill(pphel.Py());
	py_phi_hel->Fill(pphihel.Py());
	py_kp_hel->Fill(pkphel.Py());
	py_km_hel->Fill(pkmhel.Py());    
	py_g_hel->Fill(pghel.Py());    
	
	pz_pt_l->Fill(aux.Pz());  // checking for proton mass
	pz_p_l->Fill(ppl.Pz());
	pz_phi_l->Fill(pphil.Pz());
	pz_kp_l->Fill(pkpl.Pz());
	pz_km_l->Fill(pkml.Pz());    
	pz_g_l->Fill(pgl.Pz());    
	
	pz_pt_cm->Fill(pptcm.Pz());  // checking for proton mass
	pz_p_cm->Fill(ppcm.Pz());
	pz_phi_cm->Fill(pphicm.Pz());
	pz_kp_cm->Fill(pkpcm.Pz());
	pz_km_cm->Fill(pkmcm.Pz());    
	pz_g_cm->Fill(pgcm.Pz());    
	
	
	pz_pt_rest->Fill(pptrest.Pz());  // checking for proton mass
	pz_p_rest->Fill(pprest.Pz());
	pz_phi_rest->Fill(pphirest.Pz());
	pz_kp_rest->Fill(pkprest.Pz());
	pz_km_rest->Fill(pkmrest.Pz());    
	pz_g_rest->Fill(pgrest.Pz());    
	
	
	pz_pt_hel->Fill(ppthel.Pz());  // checking for proton mass
	pz_p_hel->Fill(pphel.Pz());
	pz_phi_hel->Fill(pphihel.Pz());
	pz_kp_hel->Fill(pkphel.Pz());
	pz_km_hel->Fill(pkmhel.Pz());    
	pz_g_hel->Fill(pghel.Pz());    
	
	erg_g_l->Fill(pgl.E());            //Energy  distribution
	erg_p_l->Fill(ppl.E());            //Energy  distribution
	erg_kp_l->Fill(pkpl.E());
	erg_km_l->Fill(pkml.E());
	
	s_vs_t_l->Fill((ppl + pphil).M2(), (pptl - ppl).M2());
	s_vs_t_cm->Fill((ppcm + pphicm).M2(), (pptcm - ppcm).M2());
	s_vs_t_rest->Fill((pprest + pphirest).M2(), (pptrest - pprest).M2());
	s_vs_t_hel->Fill((pphel + pphihel).M2(), (ppthel - pphel).M2());
	
	t_vs_t_l->Fill((pgl - ppl).M2(), (pptl - pphil).M2());
	t_vs_t_cm->Fill((pgcm - ppcm).M2(), (pptcm - pphicm).M2());
	t_vs_t_rest->Fill((pgrest - pprest).M2(), (pptrest - pphirest).M2());
	t_vs_t_hel->Fill((pghel - pphel).M2(), (ppthel - pphihel).M2());
	
	kp_km_vs_t_l->Fill((pkml + pkpl).M2(), -(pgl - ppl).M2());
	//      cout << (pkml + pkpl).M2() << "::: " <<  (-pgl + ppl).M2() << endl;
	
	int m = 0;
	
	hdsdw_p_l[m]->Fill(azimuth(ppl)*180.0/TMath::Pi(), cos(polar(ppl)));
	hdsdw_kp_l[m]->Fill(azimuth(pkpl)*180.0/TMath::Pi(), cos(polar(pkpl)));
	hdsdw_km_l[m]->Fill(azimuth(pkml)*180.0/TMath::Pi(), cos(polar(pkml)));
	hdsdw_phi_l[m]->Fill(azimuth(pphil)*180.0/TMath::Pi(), cos(polar(pphil)));
	
	hdsdw_p_cm[m]->Fill(azimuth(ppcm)*180.0/TMath::Pi(), cos(polar(ppcm)));
	hdsdw_kp_cm[m]->Fill(azimuth(pkpcm)*180.0/TMath::Pi(), cos(polar(pkpcm)));
	hdsdw_km_cm[m]->Fill(azimuth(pkmcm)*180.0/TMath::Pi(), cos(polar(pkmcm)));
	hdsdw_phi_cm[m]->Fill(azimuth(pphicm)*180.0/TMath::Pi(), cos(polar(pphicm)));
	
	hdsdw_p_rest[m]->Fill(azimuth(pprest)*180.0/TMath::Pi(), cos(polar(pprest)));
	hdsdw_kp_rest[m]->Fill(azimuth(pkprest)*180.0/TMath::Pi(), cos(polar(pkprest)));
	hdsdw_km_rest[m]->Fill(azimuth(pkmrest)*180.0/TMath::Pi(), cos(polar(pkmrest)));
	hdsdw_phi_rest[m]->Fill(azimuth(pphirest)*180.0/TMath::Pi(), cos(polar(pphirest)));
	
	hdsdw_p_hel[m]->Fill(azimuth(pphel)*180.0/TMath::Pi(), cos(polar(pphel)));
	hdsdw_kp_hel[m]->Fill(azimuth(pkphel)*180.0/TMath::Pi(), cos(polar(pkphel)));
	hdsdw_km_hel[m]->Fill(azimuth(pkmhel)*180.0/TMath::Pi(), cos(polar(pkmhel)));
	hdsdw_phi_hel[m]->Fill(azimuth(pphihel)*180.0/TMath::Pi(), cos(polar(pphihel)));
	
	hdsdw_cos_p_l[m]->Fill(cos(polar(ppl)));
	hdsdw_cos_kp_l[m]->Fill(cos(polar(pkpl)));
	hdsdw_cos_km_l[m]->Fill(cos(polar(pkml)));
	hdsdw_cos_phi_l[m]->Fill(cos(polar(pphil)));
	
	hdsdw_cos_p_cm[m]->Fill(cos(polar(ppcm)));
	hdsdw_cos_kp_cm[m]->Fill(cos(polar(pkpcm)));
	hdsdw_cos_km_cm[m]->Fill(cos(polar(pkmcm)));
	hdsdw_cos_phi_cm[m]->Fill(cos(polar(pphicm)));
	
	hdsdw_cos_p_rest[m]->Fill(cos(polar(pprest)));
	hdsdw_cos_kp_rest[m]->Fill(cos(polar(pkprest)));
	hdsdw_cos_km_rest[m]->Fill(cos(polar(pkmrest)));
	hdsdw_cos_phi_rest[m]->Fill(cos(polar(pphirest)));
	
	hdsdw_cos_p_hel[m]->Fill(cos(polar(pphel)));
	hdsdw_cos_kp_hel[m]->Fill(cos(polar(pkphel)));
	hdsdw_cos_km_hel[m]->Fill(cos(polar(pkmhel)));
	hdsdw_cos_phi_hel[m]->Fill(cos(polar(pphihel)));
	
	hdsdw_azth_p_l[m]->Fill(azimuth(ppl)*180.0/TMath::Pi());
	hdsdw_azth_kp_l[m]->Fill(azimuth(pkpl)*180.0/TMath::Pi());
	hdsdw_azth_km_l[m]->Fill(azimuth(pkml)*180.0/TMath::Pi());
	hdsdw_azth_phi_l[m]->Fill(azimuth(pphil)*180.0/TMath::Pi());
	
	hdsdw_azth_p_cm[m]->Fill(azimuth(ppcm)*180.0/TMath::Pi());
	hdsdw_azth_kp_cm[m]->Fill(azimuth(pkpcm)*180.0/TMath::Pi());
	hdsdw_azth_km_cm[m]->Fill(azimuth(pkmcm)*180.0/TMath::Pi());
	hdsdw_azth_phi_cm[m]->Fill(azimuth(pphicm)*180.0/TMath::Pi());
	
	hdsdw_azth_p_rest[m]->Fill(azimuth(pprest)*180.0/TMath::Pi());
	hdsdw_azth_kp_rest[m]->Fill(azimuth(pkprest)*180.0/TMath::Pi());
	hdsdw_azth_km_rest[m]->Fill(azimuth(pkmrest)*180.0/TMath::Pi());
	hdsdw_azth_phi_rest[m]->Fill(azimuth(pphirest)*180.0/TMath::Pi());
	
	hdsdw_azth_p_hel[m]->Fill(azimuth(pphel)*180.0/TMath::Pi());
	hdsdw_azth_kp_hel[m]->Fill(azimuth(pkphel)*180.0/TMath::Pi());
	hdsdw_azth_km_hel[m]->Fill(azimuth(pkmhel)*180.0/TMath::Pi());
	hdsdw_azth_phi_hel[m]->Fill(azimuth(pphihel)*180.0/TMath::Pi());
	
	
	//g + pt  -> phi + p
	//1  + 2  -> 3 + 4;
	
	ht_tmin_g_phi_cm[m]->Fill(-t13-fabs(tmin_t13_cm));
	ht_tmin_pt_p_cm[m]->Fill(-t24-fabs(tmin_t24_cm));
	
	ht_g_phi_l[m]->Fill(t13);
	ht_pt_p_l[m]->Fill(t24);
	
	//	ht_g_phi_cm[m]->Fill(t13_cm);
	ht_g_phi_cm[m]->Fill(tval);
	ht_pt_p_cm[m]->Fill(t24_cm);
	
	hs_g_pt_l[m]->Fill(s12);
	hs_p_phi_l[m]->Fill(s34);
	
	hs_g_pt_cm[m]->Fill(s12_cm);
	hs_p_phi_cm[m]->Fill(s34_cm);
	
	
	// calculating director cosines
	
      }
    }//if(t13 ....
    
    dcx_pl = ppl.Px()/sqrt(ppl.E()*ppl.E()- ppl.M2());
    dcy_pl = ppl.Py()/sqrt(ppl.E()*ppl.E()- ppl.M2());
    dcz_pl = ppl.Pz()/sqrt(ppl.E()*ppl.E()- ppl.M2());
        
    dcx_phil = pphil.Px()/sqrt(pphil.E()*pphil.E()- pphil.M2());
    dcx_kpl = pkpl.Px()/sqrt(pkpl.E()*pkpl.E()- pkpl.M2());
    dcx_kml = pkml.Px()/sqrt(pkml.E()*pkml.E()- pkml.M2());
    
    dcy_phil = pphil.Py()/sqrt(pphil.E()*pphil.E()- pphil.M2());
    dcy_kpl = pkpl.Py()/sqrt(pkpl.E()*pkpl.E()- pkpl.M2());
    dcy_kml = pkml.Py()/sqrt(pkml.E()*pkml.E()- pkml.M2());
    
    dcz_phil = pphil.Pz()/sqrt(pphil.E()*pphil.E()- pphil.M2());
    dcz_kpl = pkpl.Pz()/sqrt(pkpl.E()*pkpl.E()- pkpl.M2());
    dcz_kml = pkml.Pz()/sqrt(pkml.E()*pkml.E()- pkml.M2());
    
    //aperture angles

    //    ang_p_l->Fill(psi_rp_pol*180.0/TMath::Pi());
    ang_p_l->Fill(psi_rp_pol*180.0/TMath::Pi());
    ang_kp_l->Fill(180/PI*pkpl.Pz()/sqrt(pkpl.E()*pkpl.E()-pkpl.M2()));
    ang_km_l->Fill(180/PI*pkml.Pz()/sqrt(pkml.E()*pkml.E()-pkml.M2()));


    hph->Fill(ph*180.0/TMath::Pi());
    double aux = psi + 2*TMath::Pi();
    if(aux > 2*TMath::Pi())
      aux = aux - 2*TMath::Pi(); 
    
    hpsi->Fill(aux*180.0/TMath::Pi());
    
    double dif = ph + psi;              // remmember psi = 2pi - psi so ph-psi = ph + 2pi-psi
    double sum = ph + 2*TMath::Pi() - psi; // ph + psi = ph + 2pi - (2pi -psi)
    
    if(sum > 2*TMath::Pi()){
      sum = sum - 2*TMath::Pi();
    }
    
    if(dif > 2*TMath::Pi()){
      dif = dif - 2*TMath::Pi();
    }
    pol_ang_minus->Fill(dif*180.0/TMath::Pi());
    pol_ang_plus->Fill(sum*180.0/TMath::Pi());
    
    cos__th->Fill(cth);

    //finding the vertex at target    
    zl = r1.Uniform(-40,0);    
    //xl = 0;
    //yl = 0;
    
    xl = gausFunc->GetRandom(-1.2,1.3);
    yl = gausFunc->GetRandom(-1.3,1.4);

    z_targ->Fill(zl);
    
    // writting data in outfile
    
    // writting information of HEAD bank
    outfile << v_ev << " ";                     // version of event format (Head bank BOS file)
    outfile << run << " ";                      // run number
    outfile << i << " ";                        // event number
    outfile << time(NULL) << " ";               // unix time
    outfile << ev_type << " ";                  // event type
    outfile << ev_weigth << " ";                // event weigth 
    outfile << ev_class << " ";                 // evet class
    outfile << trig << endl;                    // trigger bits 
    
    // writing information of MCVX bank
    outfile << xl << " ";                       // vertex x-coordinate  
    outfile << yl << " ";                       // vertex y-coordinate  
    outfile << zl << " ";                       // vertex z-coordinate  
    outfile << 0 << " ";                        // sec of fligth
    outfile << 1 << endl;                       // vertex flag
    
    // writting informaton of MCTK bank
    
    // photon
    outfile << ZERO << " ";                               // director cosine in x   
    outfile << ZERO << " ";                               // director cosine in y
    outfile << 1.0 << " ";                                // director cosine in x
    outfile << EG << " ";                                 // momentum 
    outfile << ZERO << " ";                               // mass
    outfile << ZERO << " ";                               // electric charge
    outfile << pid_g << " ";                              // PDG id
    outfile << -1 << " ";                                 // track flag
    outfile << 0 << " ";                                  // begining vertex
    outfile << 1 << " ";                                  // ending vertex
    outfile << 0 << endl;                                 // Parent track

    //kaon+
    outfile << dcx_kpl << " ";                            // director cosine in x   
    outfile << dcy_kpl << " ";                            // director cosine in y
    outfile << dcz_kpl << " ";                            // director cosine in x
    outfile << sqrt(pkpl.E()*pkpl.E()- pkpl.M2()) << " ";     // momentum 
    outfile << MK << " ";                                 // mass
    outfile << q << " ";                                  // electric charge
    outfile << pid_kp << " ";                             // PDG id
    outfile << 1 << " ";                                  // track flag
    outfile << 1 << " ";                                  // begining vertex
    outfile << 0 << " ";                                  // ending vertex
    outfile << -1 << endl;                                // Parent track
    
    // kaon-
    outfile << dcx_kml << " ";                            // director cosine in x   
    outfile << dcy_kml << " ";                            // director cosine in y
    outfile << dcz_kml << " ";                            // director cosine in x
    outfile << sqrt(pkml.E()*pkml.E()- pkml.M2()) << " ";     // momentum 
    outfile << MK << " ";                                 // mass
    outfile << -q << " ";                                 // electric charge
    outfile << pid_km << " ";                             // PDG id
    outfile << 2 << " ";                                  // track flag
    outfile << 1 << " ";                                  // begining vertex
    outfile << 0 << " ";                                  // ending vertex
    outfile << -1 << endl;                                // parent track      
    
    
    // proton
    outfile << dcx_pl << " ";                             // director cosine in x   
    outfile << dcy_pl << " ";                             // director cosine in y
    outfile << dcz_pl << " ";                             // director cosine in x
    outfile << sqrt(ppl.E()*ppl.E()- ppl.M2()) << " ";        // momentum 
    outfile << MP << " ";                                 // mass
    outfile << q << " ";                                  // electric charge
    outfile << pid_p << " ";                              // PDG id
    outfile << 3 << " ";                                  // track flag
    outfile << 1 << " ";                                  // begining vertex
    outfile << 0 << " ";                                  // ending vertex
    outfile << -1 << endl;                                // parent track      
    


    if(ppev == 1){             // printing processed events if "-p" flag
      
      if(i%1000==0)
	cout << i << " events processed out of " << NEVENT << " at: " << EG << "GeV" << endl;
    }
    
  }// Loop events
  
  f->Write();
  f->Close();
  
  cout << evt_tru << " events out of " << NEVENT << endl;
  
} //int main()

