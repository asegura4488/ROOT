#include "hist_dec.h"
void booking(){
  
  //some dirs
  dir_tdist = new TDirectoryFile("tdist","tdist");   // |t| and -t -|timin| distributions
  dir_mm = new TDirectoryFile("mm","mm");            //missing mass plots
  dir_mom = new TDirectoryFile("mom","mom");
  dir_bvsp = new TDirectoryFile("bvsp","bvsp");       
  dir_dsdw = new TDirectoryFile("dsdw","dsdw");      // angular distributions
  dir_vertex = new TDirectoryFile("vertex","vertex");   // vertex position
  dir_dalitz = new TDirectoryFile("dalitz","dalitz");   
  dir_timing = new TDirectoryFile("timing","timing");  // vertex time differences
  dir_stat = new TDirectoryFile("stat","stat");  // flags from EVNT bank i.e DCstat


  
  
  //t and s  distributions
  
  for(int i=0; i<NUMH; i++){
    dir_tdist->cd();
    char s_g_pt_l[50];
    sprintf(s_g_pt_l,"s_g_pt_l_%d",i);
    hs_g_pt_l[i] = new TH1F(s_g_pt_l,s_g_pt_l,200, 2.0, 6.0);
    
    char s_g_pt_cm[50];
    sprintf(s_g_pt_cm,"s_g_pt_cm_%d",i);
    hs_g_pt_cm[i] = new TH1F(s_g_pt_cm,s_g_pt_cm,200, 2.0, 6.0);
    
    char s_g_pt_hel[50];
    sprintf(s_g_pt_hel,"s_g_pt_hel_%d",i);
    hs_g_pt_hel[i] = new TH1F(s_g_pt_hel,s_g_pt_hel,200, 2.0, 6.0);
    
    
    char s_p_phi_l[50];
    sprintf(s_p_phi_l,"s_p_phi_l_%d",i);
    hs_p_phi_l[i] = new TH1F(s_p_phi_l,s_p_phi_l,200, 2.0, 6.0);
    
    char s_p_phi_cm[50];
    sprintf(s_p_phi_cm,"s_p_phi_cm_%d",i);
    hs_p_phi_cm[i] = new TH1F(s_p_phi_cm,s_p_phi_cm,200, 2.0, 6.0);
    
    char s_p_phi_hel[50];
    sprintf(s_p_phi_hel,"s_p_phi_hel_%d",i);
    hs_p_phi_hel[i] = new TH1F(s_p_phi_hel,s_p_phi_hel,200, 2.0, 6.0);
    
    
    
    
    char t_tmin_pt_p_cm[50];
    sprintf(t_tmin_pt_p_cm,"t_tmin_pt_p_cm_%d",i);
    ht_tmin_pt_p_cm[i] = new TH1F(t_tmin_pt_p_cm,t_tmin_pt_p_cm,200, -4.0, 4.0);

    char t_tmin_pt_p_rest[50];
    sprintf(t_tmin_pt_p_rest,"t_tmin_pt_p_rest_%d",i);
    ht_tmin_pt_p_rest[i] = new TH1F(t_tmin_pt_p_rest,t_tmin_pt_p_rest,200, -4.0, 4.0);
    
    char t_tmin_pt_p_hel[50];
    sprintf(t_tmin_pt_p_hel,"t_tmin_pt_p_hel_%d",i);
    ht_tmin_pt_p_hel[i] = new TH1F(t_tmin_pt_p_hel,t_tmin_pt_p_hel,200, -4.0, 4.0);
    
    char t_tmin_g_phi_cm[50];
    sprintf(t_tmin_g_phi_cm,"t_tmin_g_phi_cm_%d",i);
    ht_tmin_g_phi_cm[i] = new TH1F(t_tmin_g_phi_cm,t_tmin_g_phi_cm,200, -4.0, 4.0);

    char t_tmin_g_phi_rest[50];
    sprintf(t_tmin_g_phi_rest,"t_tmin_g_phi_rest_%d",i);
    ht_tmin_g_phi_rest[i] = new TH1F(t_tmin_g_phi_rest,t_tmin_g_phi_rest,200, -4.0, 4.0);
    
    char t_tmin_g_phi_hel[50];
    sprintf(t_tmin_g_phi_hel,"t_tmin_g_phi_hel_%d",i);
    ht_tmin_g_phi_hel[i] = new TH1F(t_tmin_g_phi_hel,t_tmin_g_phi_hel,200, -4.0, 4.0);

    char t_g_phi_l[50];
    sprintf(t_g_phi_l,"t_g_phi_l_%d",i);
    ht_g_phi_l[i] = new TH1F(t_g_phi_l,t_g_phi_l,200, -4.0, 4.0);

    char t_g_phi_cm[50];
    sprintf(t_g_phi_cm,"t_g_phi_cm_%d",i);
    ht_g_phi_cm[i] = new TH1F(t_g_phi_cm,t_g_phi_cm,200, -4.0, 4.0);

    char t_g_phi_rest[50];
    sprintf(t_g_phi_rest,"t_g_phi_rest_%d",i);
    ht_g_phi_rest[i] = new TH1F(t_g_phi_rest,t_g_phi_rest,200, -4.0, 4.0);

    char t_g_phi_hel[50];
    sprintf(t_g_phi_hel,"t_g_phi_hel_%d",i);
    ht_g_phi_hel[i] = new TH1F(t_g_phi_hel,t_g_phi_hel,200, -4.0, 4.0);

    char t_pt_p_l[50];
    sprintf(t_pt_p_l,"t_pt_p_l_%d",i);
    ht_pt_p_l[i] = new TH1F(t_pt_p_l,t_pt_p_l,200, -4.0, 4.0);

    char t_pt_p_cm[50];
    sprintf(t_pt_p_cm,"t_pt_p_cm_%d",i);
    ht_pt_p_cm[i] = new TH1F(t_pt_p_cm,t_pt_p_cm,200, -4.0, 4.0);

    char t_pt_p_rest[50];
    sprintf(t_pt_p_rest,"t_pt_p_rest_%d",i);
    ht_pt_p_rest[i] = new TH1F(t_pt_p_rest,t_pt_p_rest,200, -4.0, 4.0);

    char t_pt_p_hel[50];
    sprintf(t_pt_p_hel,"t_pt_p_hel_%d",i);
    ht_pt_p_hel[i] = new TH1F(t_pt_p_hel,t_pt_p_hel,200, -4.0, 4.0);

   }


  //missing mass histograms and angular distributions  
  dir_mm->cd();
  
  mm_pt_l = new TH1F("mm_pt_l","loca loca",500, 0, 2);
  mm_p_l = new TH1F("mm_p_l","mm_p_l(GeV)",500, 0, 2);    
  mm_phi_l = new TH1F("mm_phi_l","mm_phi_l(GeV)",500, 0, 2);
  mm_kp_l = new TH1F("mm_kp_l","mm_kp_l(GeV)",500, 0, 2);
  mm_km_l = new TH1F("mm_km_l","mm_km_l(GeV)",500, 0, 2);
  mm_g_l = new TH1F("mm_g_l","mm_g_l(GeV)",500, 0, 2);
  
  mm_pt_cm = new TH1F("mm_pt_cm","mm_pt_cm(GeV)",500, 0, 2);
  mm_p_cm = new TH1F("mm_p_cm","mm_p_cm(GeV)",500, 0, 2);    
  mm_phi_cm = new TH1F("mm_phi_cm","mm_phi_cm(GeV)",500, 0, 2);
  mm_kp_cm = new TH1F("mm_kp_cm","mm_kp_cm(GeV)",500, 0, 2);
  mm_km_cm = new TH1F("mm_km_cm","mm_km_cm(GeV)",500, 0, 2);
  mm_g_cm = new TH1F("mm_g_cm","mm_g_cm(GeV)",500, 0, 2);

  mm_pt_rest = new TH1F("mm_pt_rest","mm_pt_rest(GeV)",500, 0, 2);
  mm_p_rest = new TH1F("mm_p_rest","mm_p_rest(GeV)",500, 0, 2);    
  mm_phi_rest = new TH1F("mm_phi_rest","mm_phi_rest(GeV)",500, 0, 2);
  mm_kp_rest = new TH1F("mm_kp_rest","mm_kp_rest(GeV)",500, 0, 2);
  mm_km_rest = new TH1F("mm_km_rest","mm_km_rest(GeV)",500, 0, 2);
  mm_g_rest = new TH1F("mm_g_rest","mm_g_rest(GeV)",500, 0, 2);

  mm_pt_hel = new TH1F("mm_pt_hel","mm_pt_hel(GeV)",500, 0, 2);
  mm_p_hel = new TH1F("mm_p_hel","mm_p_hel(GeV)",500, 0, 2);    
  mm_phi_hel = new TH1F("mm_phi_hel","mm_phi_hel(GeV)",500, 0, 2);
  mm_kp_hel = new TH1F("mm_kp_hel","mm_kp_hel(GeV)",500, 0, 2);
  mm_km_hel = new TH1F("mm_km_hel","mm_km_hel(GeV)",500, 0, 2);
  mm_g_hel = new TH1F("mm_g_hel","mm_g_hel(GeV)",500, 0, 2);

  dir_mom->cd();

  //LAB
  px_pt_l = new TH1F("px_pt_l","px_pt_l(GeV)",500, -4, 4);
  px_p_l = new TH1F("px_p_l","px_p_l(GeV)",500, -4, 4);    
  px_phi_l = new TH1F("px_phi_l","px_phi_l(GeV)",500, -4, 4);
  px_kp_l = new TH1F("px_kp_l","px_kp_l(GeV)",500, -4, 4);
  px_km_l = new TH1F("px_km_l","px_km_l(GeV)",500, -4, 4);
  px_g_l = new TH1F("px_g_l","px_g_l(GeV)",500, -4, 4);

  py_pt_l = new TH1F("py_pt_l","py_pt_l(GeV)",500, -4, 4);
  py_p_l = new TH1F("py_p_l","py_p_l(GeV)",500, -4, 4);    
  py_phi_l = new TH1F("py_phi_l","py_phi_l(GeV)",500, -4, 4);
  py_kp_l = new TH1F("py_kp_l","py_kp_l(GeV)",500, -4, 4);
  py_km_l = new TH1F("py_km_l","py_km_l(GeV)",500, -4, 4);
  py_g_l = new TH1F("py_g_l","py_g_l(GeV)",500, -4, 4);

  pz_pt_l = new TH1F("pz_pt_l","pz_pt_l(GeV)",500, -4, 4);
  pz_p_l = new TH1F("pz_p_l","pz_p_l(GeV)",500, -4, 4);    
  pz_phi_l = new TH1F("pz_phi_l","pz_phi_l(GeV)",500, -4, 4);
  pz_kp_l = new TH1F("pz_kp_l","pz_kp_l(GeV)",500, -4, 4);
  pz_km_l = new TH1F("pz_km_l","pz_km_l(GeV)",500, -4, 4);
  pz_g_l = new TH1F("pz_g_l","pz_g_l(GeV)",500, -4, 4);

  //CM
  px_pt_cm = new TH1F("px_pt_cm","px_pt_cm(GeV)",500, -4, 4);
  px_p_cm = new TH1F("px_p_cm","px_p_cm(GeV)",500, -4, 4);    
  px_phi_cm = new TH1F("px_phi_cm","px_phi_cm(GeV)",500, -4, 4);
  px_kp_cm = new TH1F("px_kp_cm","px_kp_cm(GeV)",500, -4, 4);
  px_km_cm = new TH1F("px_km_cm","px_km_cm(GeV)",500, -4, 4);
  px_g_cm = new TH1F("px_g_cm","px_g_cm(GeV)",500, -4, 4);

  py_pt_cm = new TH1F("py_pt_cm","py_pt_cm(GeV)",500, -4, 4);
  py_p_cm = new TH1F("py_p_cm","py_p_cm(GeV)",500, -4, 4);    
  py_phi_cm = new TH1F("py_phi_cm","py_phi_cm(GeV)",500, -4, 4);
  py_kp_cm = new TH1F("py_kp_cm","py_kp_cm(GeV)",500, -4, 4);
  py_km_cm = new TH1F("py_km_cm","py_km_cm(GeV)",500, -4, 4);
  py_g_cm = new TH1F("py_g_cm","py_g_cm(GeV)",500, -4, 4);

  pz_pt_cm = new TH1F("pz_pt_cm","pz_pt_cm(GeV)",500, -4, 4);
  pz_p_cm = new TH1F("pz_p_cm","pz_p_cm(GeV)",500, -4, 4);    
  pz_phi_cm = new TH1F("pz_phi_cm","pz_phi_cm(GeV)",500, -4, 4);
  pz_kp_cm = new TH1F("pz_kp_cm","pz_kp_cm(GeV)",500, -4, 4);
  pz_km_cm = new TH1F("pz_km_cm","pz_km_cm(GeV)",500, -4, 4);
  pz_g_cm = new TH1F("pz_g_cm","pz_g_cm(GeV)",500, -4, 4);

  //REST
  px_pt_rest = new TH1F("px_pt_rest","px_pt_rest(GeV)",500, -4, 4);
  px_p_rest = new TH1F("px_p_rest","px_p_rest(GeV)",500, -4, 4);    
  px_phi_rest = new TH1F("px_phi_rest","px_phi_rest(GeV)",500, -4, 4);
  px_kp_rest = new TH1F("px_kp_rest","px_kp_rest(GeV)",500, -4, 4);
  px_km_rest = new TH1F("px_km_rest","px_km_rest(GeV)",500, -4, 4);
  px_g_rest = new TH1F("px_g_rest","px_g_rest(GeV)",500, -4, 4);

  py_pt_rest = new TH1F("py_pt_rest","py_pt_rest(GeV)",500, -4, 4);
  py_p_rest = new TH1F("py_p_rest","py_p_rest(GeV)",500, -4, 4);    
  py_phi_rest = new TH1F("py_phi_rest","py_phi_rest(GeV)",500, -4, 4);
  py_kp_rest = new TH1F("py_kp_rest","py_kp_rest(GeV)",500, -4, 4);
  py_km_rest = new TH1F("py_km_rest","py_km_rest(GeV)",500, -4, 4);
  py_g_rest = new TH1F("py_g_rest","py_g_rest(GeV)",500, -4, 4);

  pz_pt_rest = new TH1F("pz_pt_rest","pz_pt_rest(GeV)",500, -4, 4);
  pz_p_rest = new TH1F("pz_p_rest","pz_p_rest(GeV)",500, -4, 4);    
  pz_phi_rest = new TH1F("pz_phi_rest","pz_phi_rest(GeV)",500, -4, 4);
  pz_kp_rest = new TH1F("pz_kp_rest","pz_kp_rest(GeV)",500, -4, 4);
  pz_km_rest = new TH1F("pz_km_rest","pz_km_rest(GeV)",500, -4, 4);
  pz_g_rest = new TH1F("pz_g_rest","pz_g_rest(GeV)",500, -4, 4);

  
  //HEL
  px_pt_hel = new TH1F("px_pt_hel","px_pt_hel(GeV)",500, -4, 4);
  px_p_hel = new TH1F("px_p_hel","px_p_hel(GeV)",500, -4, 4);    
  px_phi_hel = new TH1F("px_phi_hel","px_phi_hel(GeV)",500, -4, 4);
  px_kp_hel = new TH1F("px_kp_hel","px_kp_hel(GeV)",500, -4, 4);
  px_km_hel = new TH1F("px_km_hel","px_km_hel(GeV)",500, -4, 4);
  px_g_hel = new TH1F("px_g_hel","px_g_hel(GeV)",500, -4, 4);

  py_pt_hel = new TH1F("py_pt_hel","py_pt_hel(GeV)",500, -4, 4);
  py_p_hel = new TH1F("py_p_hel","py_p_hel(GeV)",500, -4, 4);    
  py_phi_hel = new TH1F("py_phi_hel","py_phi_hel(GeV)",500, -4, 4);
  py_kp_hel = new TH1F("py_kp_hel","py_kp_hel(GeV)",500, -4, 4);
  py_km_hel = new TH1F("py_km_hel","py_km_hel(GeV)",500, -4, 4);
  py_g_hel = new TH1F("py_g_hel","py_g_hel(GeV)",500, -4, 4);

  pz_pt_hel = new TH1F("pz_pt_hel","pz_pt_hel(GeV)",500, -4, 4);
  pz_p_hel = new TH1F("pz_p_hel","pz_p_hel(GeV)",500, -4, 4);    
  pz_phi_hel = new TH1F("pz_phi_hel","pz_phi_hel(GeV)",500, -4, 4);
  pz_kp_hel = new TH1F("pz_kp_hel","pz_kp_hel(GeV)",500, -4, 4);
  pz_km_hel = new TH1F("pz_km_hel","pz_km_hel(GeV)",500, -4, 4);
  pz_g_hel = new TH1F("pz_g_hel","pz_g_hel(GeV)",500, -4, 4);

  mom3_p_l = new TH1F("mom3_p_l","mom3_p_l",100, 0, 4);
  mom3_kp_l = new TH1F("mom3_kp_l","mom3_kp_l",100, 0, 4);
  mom3_km_l = new TH1F("mom3_km_l","mom3_km_l",100, 0, 4);
  mom3_phi_l = new TH1F("mom3_phi_l","mom3_phi_l",100, 0, 4);

  mom3_p_cm = new TH1F("mom3_p_cm","mom3_p_cm",100, 0, 4);
  mom3_kp_cm = new TH1F("mom3_kp_cm","mom3_kp_cm",100, 0, 4);
  mom3_km_cm = new TH1F("mom3_km_cm","mom3_km_cm",100, 0, 4);
  mom3_phi_cm = new TH1F("mom3_phi_cm","mom3_phi_cm",100, 0, 4);

  mom3_p_rest = new TH1F("mom3_p_rest","mom3_p_rest",100, 0, 4);
  mom3_kp_rest = new TH1F("mom3_kp_rest","mom3_kp_rest",100, 0, 4);
  mom3_km_rest = new TH1F("mom3_km_rest","mom3_km_rest",100, 0, 4);
  mom3_phi_rest = new TH1F("mom3_phi_rest","mom3_phi_rest",100, 0, 4);


  mom3_p_hel = new TH1F("mom3_p_hel","mom3_p_hel",100, 0, 4);
  mom3_kp_hel = new TH1F("mom3_kp_hel","mom3_kp_hel",100, 0, 4);
  mom3_km_hel = new TH1F("mom3_km_hel","mom3_km_hel",100, 0, 4);
  mom3_phi_hel = new TH1F("mom3_phi_hel","mom3_phi_hel",100, 0, 4);


  dir_stat->cd();

  //some checking
  hph = new TH1F("hph","hph",36,0,360);
  hpsi = new TH1F("hpsi","hpsi",36,0,360);
  cos__th = new TH1F("cos__th","cos__th",20,-1,1);
  pol_ang_plus = new TH1F("pol_ang_plus","pol_ang_plus",36,0,360);
  pol_ang_minus = new TH1F("pol_ang_minus","pol_ang_minus",36,0,360);


  erg_g_l = new TH1F("erg_g_l","erg_g_l",500, 0, 4);
  erg_p_l = new TH1F("erg_p_l","erg_p_l",500, 0, 4);
  erg_kp_l = new TH1F("erg_kp_l","erg_kp_l",500, 0, 4);
  erg_km_l = new TH1F("erg_km_l","erg_km_l",500, 0, 4);
  
  //kp_p_vs_km_p_l  kp p mass squares vs km p mas squared
  kp_p_vs_km_p_l = new TH2F("kp_p_vs_km_p_l", "kp_p_vs_km_p_l",100, 0, 3, 100, 0, 3);
  kp_p_vs_km_p_l->GetXaxis()->SetTitle("Mkp_p^2 (GeV)^2");
  kp_p_vs_km_p_l->GetYaxis()->SetTitle("Mkm_p^2 (GeV)^2");
  
  kp_p_vs_km_p_cm = new TH2F("kp_p_vs_km_p_cm", "kp_p_vs_km_p_cm",100, 0, 3, 100, 0, 3);
  kp_p_vs_km_p_cm->GetXaxis()->SetTitle("Mkp_p^2 (GeV)^2");
  kp_p_vs_km_p_cm->GetYaxis()->SetTitle("Mkm_p^2 (GeV)^2");
  
  kp_p_vs_km_p_rest = new TH2F("kp_p_vs_km_p_rest", "kp_p_vs_km_p_rest",100, 0, 3, 100, 0, 3);
  kp_p_vs_km_p_rest->GetXaxis()->SetTitle("Mkp_p^2 (GeV)^2");
  kp_p_vs_km_p_rest->GetYaxis()->SetTitle("Mkm_p^2 (GeV)^2");
  
  //kp_km_vs_kp_p_l
  kp_km_vs_kp_p_l = new TH2F("kp_km_vs_kp_p_l", "kp_km_vs_kp_p_l",100, 0, 3, 100, 0, 3);
  kp_km_vs_kp_p_l->GetXaxis()->SetTitle("Mkp_km^2 (GeV)^2");
  kp_km_vs_kp_p_l->GetYaxis()->SetTitle("Mkp_p^2 (GeV)^2");
  
  kp_km_vs_kp_p_cm = new TH2F("kp_km_vs_kp_p_cm", "kp_km_vs_kp_p_cm",100, 0, 3, 100, 0, 3);
  kp_km_vs_kp_p_cm->GetXaxis()->SetTitle("Mkp_km^2 (GeV)^2");
  kp_km_vs_kp_p_cm->GetYaxis()->SetTitle("Mkp_p^2 (GeV)^2");
  
  kp_km_vs_kp_p_rest = new TH2F("kp_km_vs_kp_p_rest", "kp_km_vs_kp_p_rest",100, 0, 3, 100, 0, 3);
  kp_km_vs_kp_p_rest->GetXaxis()->SetTitle("Mkp_km^2 (GeV)^2");
  kp_km_vs_kp_p_rest->GetYaxis()->SetTitle("Mkp_p^2 (GeV)^2");
  
  
  // kinetic energy distributions
  
  Tkp_Tkm_l = new TH2F("Tkp_Tkm_l"," Tkp_Tkm_l",100, 0, 1, 100, 0, 1);
  Tkp_Tkm_cm = new TH2F("Tkp_Tkm_cm"," Tkp_Tkm_cm",100, 0, 1, 100, 0, 1);
  Tkp_Tkm_rest = new TH2F("Tkp_Tkm_rest"," Tkp_Tkm_rest",100, 0, 1, 100, 0, 1);
  
  Tp_Tkp_l = new TH2F("Tp_Tkp_l"," Tp_Tkp_l",100, 0, 1, 100, 0, 1);
  Tp_Tkp_cm = new TH2F("Tp_Tkp_cm"," Tp_Tkp_cm",100, 0, 1, 100, 0, 1);
  Tp_Tkp_rest = new TH2F("Tp_Tkp_rest"," Tp_Tkp_rest",100, 0, 1, 100, 0, 1);
  
  
  Tp_Tkm_l = new TH2F("Tp_Tkm_l"," Tp_Tkm_l",100, 0, 1, 100, 0, 1);
  Tp_Tkm_cm = new TH2F("Tp_Tkm_cm"," Tp_Tkm_cm",100, 0, 1, 100, 0, 1);
  Tp_Tkm_rest = new TH2F("Tp_Tkm_rest"," Tp_Tkm_rest",100, 0, 1, 100, 0, 1);
  
  s_vs_t_l = new TH2F("s_vs_t_l","s_vs_t_l",1000, -5, 5, 1000, -3, 3);
  s_vs_t_cm = new TH2F("s_vs_t_cm","s_vs_t_cm",1000, -5, 5, 1000, -3, 3);
  s_vs_t_rest = new TH2F("s_vs_t_rest","s_vs_t_rest",1000, -5, 5, 1000, -3, 3);
  s_vs_t_hel = new TH2F("s_vs_t_hel","s_vs_t_hel",1000, -5, 5, 1000, -3, 3);
  
  t_vs_t_l = new TH2F("t_vs_t_l","t_vs_t_l",1000, -5, 5, 1000, -3, 3);
  t_vs_t_cm = new TH2F("t_vs_t_cm","t_vs_t_cm",1000, -5, 5, 1000, -3, 3);
  t_vs_t_rest = new TH2F("t_vs_t_rest","t_vs_t_rest",1000, -5, 5, 1000, -3, 3);
  t_vs_t_hel = new TH2F("t_vs_t_hel","t_vs_t_hel",1000, -5, 5, 1000, -3, 3);
  
  ang_p_l = new TH1F("ang_p_l","ang_p_l",180, 0, 180);
  ang_kp_l = new TH1F("ang_kp_l","ang_kp_l",180, 0, 180);
  ang_km_l = new TH1F("ang_km_l","ang_km_l",180, 0, 180);
  
  aux_th2f = new TH2F("aux_th2f","aux_th2f",1000, -5, 5, 1000, -3, 3);
  
  kp_km_vs_t_l = new TH2F("kp_km_vs_t_l","kp_km_vs_t_l",100, 0, 2, 100, 0, 2);
  kp_km_vs_t_l->GetXaxis()->SetTitle("Mkk^2");
  kp_km_vs_t_l->GetYaxis()->SetTitle("-t (GeV)^2");

  // z-vertex 
  z_targ = new TH1F("z_targ","z_targ(z-vertex(cm))",40,-40,0.0);
  
  // theta and phi distributions.
  pol_cm = new TH1F("pol_cm","pol_cm",72,0,360);
  pol_rest = new TH1F("pol_rest","pol_rest",72,0,360);
  
  azi_cm = new TH1F("azi_cm","azi_cm",72,0,360);
  azi_rest = new TH1F("azi_rest","azi_rest",72,0,360);
  
  const int bphi = 36;
  const int bcos = 100;

  
  for(int i = 0; i < NUMH; i++){

    /**************************/
    //angular distributions LAB
    /**************************/
    dir_dsdw->cd();
    
    char dsdw_p_l[50];
    sprintf(dsdw_p_l,"dsdw_p_l_%d",i);
    hdsdw_p_l[i]= new TH2F(dsdw_p_l,dsdw_p_l,bphi,0,360,bcos,-1,1);
    
    char dsdw_kp_l[50];
    sprintf(dsdw_kp_l,"dsdw_kp_l_%d",i);
    hdsdw_kp_l[i]= new TH2F(dsdw_kp_l,dsdw_kp_l,bphi,0,360,bcos,-1,1);
    
    char dsdw_km_l[50];
    sprintf(dsdw_km_l,"dsdw_km_l_%d",i);
    hdsdw_km_l[i]= new TH2F(dsdw_km_l,dsdw_km_l,bphi,0,360,bcos,-1,1);

    char dsdw_phi_l[50];
    sprintf(dsdw_phi_l,"dsdw_phi_l_%d",i);
    hdsdw_phi_l[i]= new TH2F(dsdw_phi_l,dsdw_phi_l,bphi,0,360,bcos,-1,1);
    
    char dsdw_cos_p_l[50];
    sprintf(dsdw_cos_p_l,"dsdw_cos_p_l_%d",i);
    hdsdw_cos_p_l[i]= new TH1F(dsdw_cos_p_l,dsdw_cos_p_l,bcos,-1,1);

    char dsdw_cos_kp_l[50];
    sprintf(dsdw_cos_kp_l,"dsdw_cos_kp_l_%d",i);
    hdsdw_cos_kp_l[i]= new TH1F(dsdw_cos_kp_l,dsdw_cos_kp_l,bcos,-1,1);
    
    char dsdw_cos_km_l[50];
    sprintf(dsdw_cos_km_l,"dsdw_cos_km_l_%d",i);
    hdsdw_cos_km_l[i]= new TH1F(dsdw_cos_km_l,dsdw_cos_km_l,bcos,-1,1);

    char dsdw_cos_phi_l[50];
    sprintf(dsdw_cos_phi_l,"dsdw_cos_phi_l_%d",i);
    hdsdw_cos_phi_l[i]= new TH1F(dsdw_cos_phi_l,dsdw_cos_phi_l,bcos,-1,1);
    
    char dsdw_azth_p_l[50];
    sprintf(dsdw_azth_p_l,"dsdw_azth_p_l_%d",i);
    hdsdw_azth_p_l[i]= new TH1F(dsdw_azth_p_l,dsdw_azth_p_l,bphi,0,360);

    char dsdw_azth_kp_l[50];
    sprintf(dsdw_azth_kp_l,"dsdw_azth_kp_l_%d",i);
    hdsdw_azth_kp_l[i]= new TH1F(dsdw_azth_kp_l,dsdw_azth_kp_l,bphi,0,360);
    
    char dsdw_azth_km_l[50];
    sprintf(dsdw_azth_km_l,"dsdw_azth_km_l_%d",i);
    hdsdw_azth_km_l[i]= new TH1F(dsdw_azth_km_l,dsdw_azth_km_l,bphi,0,360);

    char dsdw_azth_phi_l[50];
    sprintf(dsdw_azth_phi_l,"dsdw_azth_phi_l_%d",i);
    hdsdw_azth_phi_l[i]= new TH1F(dsdw_azth_phi_l,dsdw_azth_phi_l,bphi,0,360);
    
    
    /**************************/
    //angular distributions CM 
    /**************************/
    char dsdw_p_cm[50];
    sprintf(dsdw_p_cm,"dsdw_p_cm_%d",i);
    hdsdw_p_cm[i]= new TH2F(dsdw_p_cm,dsdw_p_cm,bphi,0,360,bcos,-1,1);
    
    char dsdw_kp_cm[50];
    sprintf(dsdw_kp_cm,"dsdw_kp_cm_%d",i);
    hdsdw_kp_cm[i]= new TH2F(dsdw_kp_cm,dsdw_kp_cm,bphi,0,360,bcos,-1,1);
    
    char dsdw_km_cm[50];
    sprintf(dsdw_km_cm,"dsdw_km_cm_%d",i);
    hdsdw_km_cm[i]= new TH2F(dsdw_km_cm,dsdw_km_cm,bphi,0,360,bcos,-1,1);

    char dsdw_phi_cm[50];
    sprintf(dsdw_phi_cm,"dsdw_phi_cm_%d",i);
    hdsdw_phi_cm[i]= new TH2F(dsdw_phi_cm,dsdw_phi_cm,bphi,0,360,bcos,-1,1);
    
    char dsdw_cos_p_cm[50];
    sprintf(dsdw_cos_p_cm,"dsdw_cos_p_cm_%d",i);
    hdsdw_cos_p_cm[i]= new TH1F(dsdw_cos_p_cm,dsdw_cos_p_cm,bcos,-1,1);

    char dsdw_cos_kp_cm[50];
    sprintf(dsdw_cos_kp_cm,"dsdw_cos_kp_cm_%d",i);
    hdsdw_cos_kp_cm[i]= new TH1F(dsdw_cos_kp_cm,dsdw_cos_kp_cm,bcos,-1,1);
    
    char dsdw_cos_km_cm[50];
    sprintf(dsdw_cos_km_cm,"dsdw_cos_km_cm_%d",i);
    hdsdw_cos_km_cm[i]= new TH1F(dsdw_cos_km_cm,dsdw_cos_km_cm,bcos,-1,1);

    char dsdw_cos_phi_cm[50];
    sprintf(dsdw_cos_phi_cm,"dsdw_cos_phi_cm_%d",i);
    hdsdw_cos_phi_cm[i]= new TH1F(dsdw_cos_phi_cm,dsdw_cos_phi_cm,bcos,-1,1);
    
    char dsdw_azth_p_cm[50];
    sprintf(dsdw_azth_p_cm,"dsdw_azth_p_cm_%d",i);
    hdsdw_azth_p_cm[i]= new TH1F(dsdw_azth_p_cm,dsdw_azth_p_cm,bphi,0,360);

    char dsdw_azth_kp_cm[50];
    sprintf(dsdw_azth_kp_cm,"dsdw_azth_kp_cm_%d",i);
    hdsdw_azth_kp_cm[i]= new TH1F(dsdw_azth_kp_cm,dsdw_azth_kp_cm,bphi,0,360);
    
    char dsdw_azth_km_cm[50];
    sprintf(dsdw_azth_km_cm,"dsdw_azth_km_cm_%d",i);
    hdsdw_azth_km_cm[i]= new TH1F(dsdw_azth_km_cm,dsdw_azth_km_cm,bphi,0,360);

    char dsdw_azth_phi_cm[50];
    sprintf(dsdw_azth_phi_cm,"dsdw_azth_phi_cm_%d",i);
    hdsdw_azth_phi_cm[i]= new TH1F(dsdw_azth_phi_cm,dsdw_azth_phi_cm,bphi,0,360);


    /**************************/
    //angular distributions REST
    /**************************/
    char dsdw_p_rest[50];
    sprintf(dsdw_p_rest,"dsdw_p_rest_%d",i);
    hdsdw_p_rest[i]= new TH2F(dsdw_p_rest,dsdw_p_rest,bphi,0,360,bcos,-1,1);
    
    char dsdw_kp_rest[50];
    sprintf(dsdw_kp_rest,"dsdw_kp_rest_%d",i);
    hdsdw_kp_rest[i]= new TH2F(dsdw_kp_rest,dsdw_kp_rest,bphi,0,360,bcos,-1,1);
    
    char dsdw_km_rest[50];
    sprintf(dsdw_km_rest,"dsdw_km_rest_%d",i);
    hdsdw_km_rest[i]= new TH2F(dsdw_km_rest,dsdw_km_rest,bphi,0,360,bcos,-1,1);

    char dsdw_phi_rest[50];
    sprintf(dsdw_phi_rest,"dsdw_phi_rest_%d",i);
    hdsdw_phi_rest[i]= new TH2F(dsdw_phi_rest,dsdw_phi_rest,bphi,0,360,bcos,-1,1);
    
    char dsdw_cos_p_rest[50];
    sprintf(dsdw_cos_p_rest,"dsdw_cos_p_rest_%d",i);
    hdsdw_cos_p_rest[i]= new TH1F(dsdw_cos_p_rest,dsdw_cos_p_rest,bcos,-1,1);

    char dsdw_cos_kp_rest[50];
    sprintf(dsdw_cos_kp_rest,"dsdw_cos_kp_rest_%d",i);
    hdsdw_cos_kp_rest[i]= new TH1F(dsdw_cos_kp_rest,dsdw_cos_kp_rest,bcos,-1,1);
    
    char dsdw_cos_km_rest[50];
    sprintf(dsdw_cos_km_rest,"dsdw_cos_km_rest_%d",i);
    hdsdw_cos_km_rest[i]= new TH1F(dsdw_cos_km_rest,dsdw_cos_km_rest,bcos,-1,1);

    char dsdw_cos_phi_rest[50];
    sprintf(dsdw_cos_phi_rest,"dsdw_cos_phi_rest_%d",i);
    hdsdw_cos_phi_rest[i]= new TH1F(dsdw_cos_phi_rest,dsdw_cos_phi_rest,bcos,-1,1);
    
    char dsdw_azth_p_rest[50];
    sprintf(dsdw_azth_p_rest,"dsdw_azth_p_rest_%d",i);
    hdsdw_azth_p_rest[i]= new TH1F(dsdw_azth_p_rest,dsdw_azth_p_rest,bphi,0,360);

    char dsdw_azth_kp_rest[50];
    sprintf(dsdw_azth_kp_rest,"dsdw_azth_kp_rest_%d",i);
    hdsdw_azth_kp_rest[i]= new TH1F(dsdw_azth_kp_rest,dsdw_azth_kp_rest,bphi,0,360);
    
    char dsdw_azth_km_rest[50];
    sprintf(dsdw_azth_km_rest,"dsdw_azth_km_rest_%d",i);
    hdsdw_azth_km_rest[i]= new TH1F(dsdw_azth_km_rest,dsdw_azth_km_rest,bphi,0,360);

    char dsdw_azth_phi_rest[50];
    sprintf(dsdw_azth_phi_rest,"dsdw_azth_phi_rest_%d",i);
    hdsdw_azth_phi_rest[i]= new TH1F(dsdw_azth_phi_rest,dsdw_azth_phi_rest,bphi,0,360);
        

    /**************************/
    //angular distributions HEL
    /**************************/
    char dsdw_p_hel[50];
    sprintf(dsdw_p_hel,"dsdw_p_hel_%d",i);
    hdsdw_p_hel[i]= new TH2F(dsdw_p_hel,dsdw_p_hel,bphi,0,360,bcos,-1,1);
    
    char dsdw_kp_hel[50];
    sprintf(dsdw_kp_hel,"dsdw_kp_hel_%d",i);
    hdsdw_kp_hel[i]= new TH2F(dsdw_kp_hel,dsdw_kp_hel,bphi,0,360,bcos,-1,1);
    
    char dsdw_km_hel[50];
    sprintf(dsdw_km_hel,"dsdw_km_hel_%d",i);
    hdsdw_km_hel[i]= new TH2F(dsdw_km_hel,dsdw_km_hel,bphi,0,360,bcos,-1,1);

    char dsdw_phi_hel[50];
    sprintf(dsdw_phi_hel,"dsdw_phi_hel_%d",i);
    hdsdw_phi_hel[i]= new TH2F(dsdw_phi_hel,dsdw_phi_hel,bphi,0,360,bcos,-1,1);
    
    char dsdw_cos_p_hel[50];
    sprintf(dsdw_cos_p_hel,"dsdw_cos_p_hel_%d",i);
    hdsdw_cos_p_hel[i]= new TH1F(dsdw_cos_p_hel,dsdw_cos_p_hel,bcos,-1,1);

    char dsdw_cos_kp_hel[50];
    sprintf(dsdw_cos_kp_hel,"dsdw_cos_kp_hel_%d",i);
    hdsdw_cos_kp_hel[i]= new TH1F(dsdw_cos_kp_hel,dsdw_cos_kp_hel,bcos,-1,1);
    
    char dsdw_cos_km_hel[50];
    sprintf(dsdw_cos_km_hel,"dsdw_cos_km_hel_%d",i);
    hdsdw_cos_km_hel[i]= new TH1F(dsdw_cos_km_hel,dsdw_cos_km_hel,bcos,-1,1);

    char dsdw_cos_phi_hel[50];
    sprintf(dsdw_cos_phi_hel,"dsdw_cos_phi_hel_%d",i);
    hdsdw_cos_phi_hel[i]= new TH1F(dsdw_cos_phi_hel,dsdw_cos_phi_hel,bcos,-1,1);
    
    char dsdw_azth_p_hel[50];
    sprintf(dsdw_azth_p_hel,"dsdw_azth_p_hel_%d",i);
    hdsdw_azth_p_hel[i]= new TH1F(dsdw_azth_p_hel,dsdw_azth_p_hel,bphi,0,360);

    char dsdw_azth_kp_hel[50];
    sprintf(dsdw_azth_kp_hel,"dsdw_azth_kp_hel_%d",i);
    hdsdw_azth_kp_hel[i]= new TH1F(dsdw_azth_kp_hel,dsdw_azth_kp_hel,bphi,0,360);
    
    char dsdw_azth_km_hel[50];
    sprintf(dsdw_azth_km_hel,"dsdw_azth_km_hel_%d",i);
    hdsdw_azth_km_hel[i]= new TH1F(dsdw_azth_km_hel,dsdw_azth_km_hel,bphi,0,360);

    char dsdw_azth_phi_hel[50];
    sprintf(dsdw_azth_phi_hel,"dsdw_azth_phi_hel_%d",i);
    hdsdw_azth_phi_hel[i]= new TH1F(dsdw_azth_phi_hel,dsdw_azth_phi_hel,bphi,0,360);

  }  

}
