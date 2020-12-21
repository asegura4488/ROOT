#include "ROOT.h"

//dirs

TDirectoryFile *dir_tdist;
TDirectoryFile *dir_mm;
TDirectoryFile *dir_mom;
TDirectoryFile *dir_bvsp; 
TDirectoryFile *dir_dsdw;
TDirectoryFile *dir_vertex;
TDirectoryFile *dir_dalitz;
TDirectoryFile *dir_timing;
TDirectoryFile *dir_stat;


///////////////
//1D HISTOGRAMS
///////////////

//defining mising mass histograms
TH1F* mm_pt_l;
TH1F* mm_phi_l;
TH1F* mm_rho_l;
TH1F* mm_p_l;
TH1F* mm_kp_l;
TH1F* mm_km_l;
TH1F* mm_pp_l;
TH1F* mm_pm_l;

TH1F* mm_pt_cm;
TH1F* mm_phi_cm;
TH1F* mm_rho_cm;
TH1F* mm_p_cm;
TH1F* mm_kp_cm;
TH1F* mm_km_cm;
TH1F* mm_pp_cm;
TH1F* mm_pm_cm;

TH1F* mm_pt_rest;
TH1F* mm_phi_rest;
TH1F* mm_rho_rest;
TH1F* mm_p_rest;
TH1F* mm_kp_rest;
TH1F* mm_km_rest;
TH1F* mm_pp_rest;
TH1F* mm_pm_rest;

TH1F* mm_pt_hel;
TH1F* mm_phi_hel;
TH1F* mm_rho_hel;
TH1F* mm_p_hel;
TH1F* mm_kp_hel;
TH1F* mm_km_hel;
TH1F* mm_pp_hel;
TH1F* mm_pm_hel;


TH1F* mm_g_l;
TH1F* mm_g_cm;
TH1F* mm_g_rest;
TH1F* mm_g_hel;


//3-momentum distribution

TH1F* mom3_p_l;
TH1F* mom3_kp_l;
TH1F* mom3_km_l;
TH1F* mom3_g_l;
TH1F* mom3_pt_l;
TH1F* mom3_phi_l;

TH1F* mom3_p_cm;
TH1F* mom3_kp_cm;
TH1F* mom3_km_cm;
TH1F* mom3_g_cm;
TH1F* mom3_pt_cm;
TH1F* mom3_phi_cm;

TH1F* mom3_p_rest;
TH1F* mom3_kp_rest;
TH1F* mom3_km_rest;
TH1F* mom3_g_rest;
TH1F* mom3_pt_rest;
TH1F* mom3_phi_rest;


TH1F* mom3_p_hel;
TH1F* mom3_kp_hel;
TH1F* mom3_km_hel;
TH1F* mom3_g_hel;
TH1F* mom3_pt_hel;
TH1F* mom3_phi_hel;


// px, py, pz

TH1F* px_p_l;
TH1F* pz_p_l;
TH1F* py_p_l;

TH1F* px_kp_l;
TH1F* pz_kp_l;
TH1F* py_kp_l;

TH1F* px_km_l;
TH1F* pz_km_l;
TH1F* py_km_l;

TH1F* px_phi_l;
TH1F* pz_phi_l;
TH1F* py_phi_l;

TH1F* px_g_l;
TH1F* pz_g_l;
TH1F* py_g_l;

TH1F* px_pt_l;
TH1F* pz_pt_l;
TH1F* py_pt_l;



TH1F* px_p_cm;
TH1F* pz_p_cm;
TH1F* py_p_cm;

TH1F* px_kp_cm;
TH1F* pz_kp_cm;
TH1F* py_kp_cm;

TH1F* px_km_cm;
TH1F* pz_km_cm;
TH1F* py_km_cm;

TH1F* px_phi_cm;
TH1F* pz_phi_cm;
TH1F* py_phi_cm;

TH1F* px_g_cm;
TH1F* pz_g_cm;
TH1F* py_g_cm;

TH1F* px_pt_cm;
TH1F* pz_pt_cm;
TH1F* py_pt_cm;



TH1F* px_p_rest;
TH1F* pz_p_rest;
TH1F* py_p_rest;

TH1F* px_kp_rest;
TH1F* pz_kp_rest;
TH1F* py_kp_rest;

TH1F* px_km_rest;
TH1F* pz_km_rest;
TH1F* py_km_rest;

TH1F* px_phi_rest;
TH1F* pz_phi_rest;
TH1F* py_phi_rest;

TH1F* px_g_rest;
TH1F* pz_g_rest;
TH1F* py_g_rest;

TH1F* px_pt_rest;
TH1F* pz_pt_rest;
TH1F* py_pt_rest;



TH1F* px_p_hel;
TH1F* pz_p_hel;
TH1F* py_p_hel;

TH1F* px_kp_hel;
TH1F* pz_kp_hel;
TH1F* py_kp_hel;

TH1F* px_km_hel;
TH1F* pz_km_hel;
TH1F* py_km_hel;

TH1F* px_phi_hel;
TH1F* pz_phi_hel;
TH1F* py_phi_hel;

TH1F* px_g_hel;
TH1F* pz_g_hel;
TH1F* py_g_hel;

TH1F* px_pt_hel;
TH1F* pz_pt_hel;
TH1F* py_pt_hel;




// Energy distribution
TH1F* erg_g_l;
TH1F* erg_p_l;
TH1F* erg_kp_l;
TH1F* erg_km_l;


// target vertex z-coodinate distribution
TH1F* z_targ;

// azimuthal and polar angles 
TH1F* pol_cm;
TH1F* pol_rest;
TH1F* azi_cm;
TH1F* azi_rest;

//aperture angle

TH1F* ang_p_l;
TH1F* ang_kp_l;
TH1F* ang_km_l;

////////////////
// 2D HISTOGRAMS
////////////////


//dalitz plots and chew-Low plots

TH2F* kp_km_vs_t_l;                   // kaon +/- dalitz plot  
TH2F* kp_km_vs_t_cm;
TH2F* kp_km_vs_t_rest;

TH2F* p_kp_vs_t_l;                   // proton kaon+  dalitz plot
TH2F* p_kp_vs_t_cm;
TH2F* p_kp_vs_t_rest;

TH2F* p_km_vs_t_l;                   // proton kaon- dalitz plot
TH2F* p_km_vs_t_cm;
TH2F* p_km_vs_t_rest;




TH2F* aux_th2f;

TH2F* kp_p_vs_km_p_l;                 //mass squared plots
TH2F* kp_p_vs_km_p_cm;
TH2F* kp_p_vs_km_p_rest;

TH2F* kp_km_vs_kp_p_l;                 //mass squared plots
TH2F* kp_km_vs_kp_p_cm;
TH2F* kp_km_vs_kp_p_rest;

TH2F* kp_km_vs_km_p_l;                 //mass squared plots
TH2F* kp_km_vs_km_p_cm;
TH2F* kp_km_vs_km_p_rest;



TH2F* Tkp_Tkm_l;
TH2F* Tkp_Tkm_cm;
TH2F* Tkp_Tkm_rest;
TH2F* Tp_Tkp_l;
TH2F* Tp_Tkp_cm;
TH2F* Tp_Tkp_rest;
TH2F* Tp_Tkm_l;
TH2F* Tp_Tkm_cm;
TH2F* Tp_Tkm_rest;

//mandelstam variable

TH2F *s_vs_t_l;
TH2F *s_vs_t_cm;
TH2F *s_vs_t_rest;
TH2F *s_vs_t_hel;

TH2F *t_vs_t_l;
TH2F *t_vs_t_cm;
TH2F *t_vs_t_rest;
TH2F *t_vs_t_hel;


const int NUMH = 2;

class  TH1F *hdsdw_azth_p_l[NUMH]; //Angular distribution in azimuth angle (azth = phi-angle) 
class  TH1F *hdsdw_azth_kp_l[NUMH];
class  TH1F *hdsdw_azth_km_l[NUMH];
class  TH1F *hdsdw_azth_phi_l[NUMH];

class  TH1F *hdsdw_azth_p_cm[NUMH];
class  TH1F *hdsdw_azth_kp_cm[NUMH];
class  TH1F *hdsdw_azth_km_cm[NUMH];
class  TH1F *hdsdw_azth_phi_cm[NUMH];

class  TH1F *hdsdw_azth_p_rest[NUMH];
class  TH1F *hdsdw_azth_kp_rest[NUMH];
class  TH1F *hdsdw_azth_km_rest[NUMH];
class  TH1F *hdsdw_azth_phi_rest[NUMH];

class  TH1F *hdsdw_azth_p_hel[NUMH];
class  TH1F *hdsdw_azth_kp_hel[NUMH];
class  TH1F *hdsdw_azth_km_hel[NUMH];
class  TH1F *hdsdw_azth_phi_hel[NUMH];

class  TH1F *hdsdw_cos_p_l[NUMH];         // Angular distribution in cos(theta)
class  TH1F *hdsdw_cos_kp_l[NUMH];
class  TH1F *hdsdw_cos_km_l[NUMH];
class  TH1F *hdsdw_cos_phi_l[NUMH];

class  TH1F *hdsdw_cos_p_cm[NUMH];
class  TH1F *hdsdw_cos_kp_cm[NUMH];
class  TH1F *hdsdw_cos_km_cm[NUMH];
class  TH1F *hdsdw_cos_phi_cm[NUMH];

class  TH1F *hdsdw_cos_p_rest[NUMH];
class  TH1F *hdsdw_cos_kp_rest[NUMH];
class  TH1F *hdsdw_cos_km_rest[NUMH];
class  TH1F *hdsdw_cos_phi_rest[NUMH];

class  TH1F *hdsdw_cos_p_hel[NUMH];
class  TH1F *hdsdw_cos_kp_hel[NUMH];
class  TH1F *hdsdw_cos_km_hel[NUMH];
class  TH1F *hdsdw_cos_phi_hel[NUMH];


class  TH2F *hdsdw_p_l[NUMH];
class  TH2F *hdsdw_kp_l[NUMH];
class  TH2F *hdsdw_km_l[NUMH];
class  TH2F *hdsdw_phi_l[NUMH];

class  TH2F *hdsdw_p_cm[NUMH];
class  TH2F *hdsdw_kp_cm[NUMH];
class  TH2F *hdsdw_km_cm[NUMH];
class  TH2F *hdsdw_phi_cm[NUMH];

class  TH2F *hdsdw_p_rest[NUMH];
class  TH2F *hdsdw_kp_rest[NUMH];
class  TH2F *hdsdw_km_rest[NUMH];
class  TH2F *hdsdw_phi_rest[NUMH];

class  TH2F *hdsdw_p_hel[NUMH];
class  TH2F *hdsdw_kp_hel[NUMH];
class  TH2F *hdsdw_km_hel[NUMH];
class  TH2F *hdsdw_phi_hel[NUMH];

// |t|^2 invariant 

class  TH1F *ht_pt_p_l[NUMH];        // t mandelstam variable (target - proton)^2
class  TH1F *ht_pt_p_cm[NUMH];       
class  TH1F *ht_pt_p_rest[NUMH];     
class  TH1F *ht_pt_p_hel[NUMH];      
class  TH1F *ht_g_phi_l[NUMH];       
class  TH1F *ht_g_phi_cm[NUMH];      
class  TH1F *ht_g_phi_rest[NUMH];
class  TH1F *ht_g_phi_hel[NUMH];  

//t and s distributions
class  TH1F *hs_g_pt_l[NUMH];        // s mandestam variable (gamma + target)^2
class  TH1F *hs_g_pt_cm[NUMH];      
class  TH1F *hs_g_pt_rest[NUMH];    
class  TH1F *hs_g_pt_hel[NUMH];     
class  TH1F *hs_p_phi_l[NUMH];      
class  TH1F *hs_p_phi_cm[NUMH];     
class  TH1F *hs_p_phi_rest[NUMH];   
class  TH1F *hs_p_phi_hel[NUMH];    

class  TH1F *ht_tmin_pt_p_cm[NUMH];        // -t-|tmin| by using target and outgoing proton in cm
class  TH1F *ht_tmin_pt_p_rest[NUMH];      
class  TH1F *ht_tmin_pt_p_hel[NUMH];      
class  TH1F *ht_tmin_g_phi_cm[NUMH];       
class  TH1F *ht_tmin_g_phi_rest[NUMH];     
class  TH1F *ht_tmin_g_phi_hel[NUMH]; 


//some checking

class  TH1F *hph;
class  TH1F *hpsi;
class  TH1F *cos__th;
  
class  TH1F *pol_ang_plus;
class  TH1F *pol_ang_minus;





