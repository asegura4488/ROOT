#include "hist_dec.h"
#include "variables.h"
void booking(){
  
  //Declaracion de directorios
  Kaon = new TDirectoryFile("Kaon","Kaon");  
  Lambda = new TDirectoryFile("Lambda","Lambda");  	 
  Invariantes = new TDirectoryFile("Invariantes","Invariantes");
  Comparasiones = new TDirectoryFile("Comparasiones","Comparasiones");
  
  

  Kaon->cd();
  //Laboratorio
  masak = new TH1F("masak","Masa del K^{+}", 50, (MK-0.001), (MK+0.001)); 
  masak->GetXaxis()->SetTitle("Masa del K^{+}");
  masak->GetYaxis()->SetTitle("Frecuencia");
  masak->GetXaxis()->CenterTitle();
  masak->GetYaxis()->CenterTitle();
  masak->SetLineColor(4);
  dkteta = new TH1F("dkteta","Distribuci#acute{o}n del #acute{a}ngulo #theta del K^{+}",200, 0, 180);
  dkteta->GetXaxis()->SetTitle("#acute{A}ngulo #theta");
  dkteta->GetYaxis()->SetTitle("Frecuencia");
  dkteta->GetXaxis()->CenterTitle();
  dkteta->GetYaxis()->CenterTitle();
  dkteta->SetLineColor(4);
  dkcos = new TH1F("Dkcos","Distribuci#acute{o}n del cos(#theta) del K^{+}",1000, -1, 1);
  dkcos->GetXaxis()->SetTitle("cos(#theta)");
  dkcos->GetYaxis()->SetTitle("Frecuencia");
  dkcos->GetXaxis()->CenterTitle();
  dkcos->GetYaxis()->CenterTitle();
  dkcos->SetLineColor(4);

  dkphi = new TH1F("Dkphi","Distribuci#acute{o}n del #acute{a}ngulo #phi del K^{+}",1000,-180,180);
  dkphi->GetXaxis()->SetTitle("#acute{A}ngulo #Phi");
  dkphi->GetYaxis()->SetTitle("Frecuencia");
  dkphi->GetXaxis()->CenterTitle();
  dkphi->GetYaxis()->CenterTitle();
  dkphi->SetLineColor(4);
  PxC = new TH1F("Pxc","Momentum en x del K^{+}",500,-5,5);	
  PxC->GetXaxis()->SetTitle("Momentum en x");
  PxC->GetYaxis()->SetTitle("Frecuencia");
  PxC->GetXaxis()->CenterTitle();
  PxC->GetYaxis()->CenterTitle();
  PxC->SetLineColor(4);
  PyC = new TH1F("Pyc","Momentum en y del K^{+}",500,-5,5);	
  PyC->GetXaxis()->SetTitle("Momentum en y");
  PyC->GetYaxis()->SetTitle("Frecuencia");
  PyC->GetXaxis()->CenterTitle();
  PyC->GetYaxis()->CenterTitle();
  PyC->SetLineColor(4);
  PzC = new TH1F("Pzc","Momentum en z del K^{+}",500,-5,5);	
  PzC->GetXaxis()->SetTitle("Momentum en z");
  PzC->GetYaxis()->SetTitle("Frecuencia");
  PzC->GetXaxis()->CenterTitle();
  PzC->GetYaxis()->CenterTitle();
  PzC->SetLineColor(4);
  EC = new TH1F("EC","Energ#acute{i}a del K^{+}",500,-5,5);	
  EC->GetXaxis()->SetTitle("Energ#acute{i}a");
  EC->GetYaxis()->SetTitle("Frecuencia");
  EC->GetXaxis()->CenterTitle();
  EC->GetYaxis()->CenterTitle();
  EC->SetLineColor(4);
  //Centro de Masas
  dktetacm = new TH1F("dktetacm","Distribuci#acute{o}n del #acute{a}ngulo #theta del K^{+} en el CM",200, 0, 180);
  dktetacm->GetXaxis()->SetTitle(" #acute{A}ngulo #theta");
  dktetacm->GetYaxis()->SetTitle("Frecuencia");
  dktetacm->GetXaxis()->CenterTitle();
  dktetacm->GetYaxis()->CenterTitle();
  dktetacm->SetLineColor(4);
  dkcoscm = new TH1F("Dkcoscm","Distribuci#acute{o}n del cos(#theta) del K^{+} en el CM",1000, -1, 1);
  dkcoscm->GetXaxis()->SetTitle("cos(#theta)");
  dkcoscm->GetYaxis()->SetTitle("Frecuencia");
  dkcoscm->GetXaxis()->CenterTitle();
  dkcoscm->GetYaxis()->CenterTitle();
  dkcoscm->SetLineColor(4);
  dkphicm = new TH1F("Dkphicm","Distribuci#acute{o}n del #acute{a}ngulo #phi del K^{+} en el CM",1000, -180, 180);
  dkphicm->GetXaxis()->SetTitle("#acute{A}ngulo #Phi");
  dkphicm->GetYaxis()->SetTitle("Frecuencia");
  dkphicm->GetXaxis()->CenterTitle();
  dkphicm->GetYaxis()->CenterTitle();
  dkphicm->SetLineColor(4);
  PxcmC = new TH1F("PxcmC","Momentum en x del K^{+} en el CM",500,-5,5);	
  PxcmC->GetXaxis()->SetTitle("Momentum en x CM");
  PxcmC->GetYaxis()->SetTitle("Frecuencia");
  PxcmC->GetXaxis()->CenterTitle();
  PxcmC->GetYaxis()->CenterTitle();
  PxcmC->SetLineColor(4);
  PycmC = new TH1F("PycmC","Momentum en y del K^{+} en el CM",500,-5,5);	
  PycmC->GetXaxis()->SetTitle("Momentum en y CM");
  PycmC->GetYaxis()->SetTitle("Frecuencia");
  PycmC->GetXaxis()->CenterTitle();
  PycmC->GetYaxis()->CenterTitle();
  PycmC->SetLineColor(4);
  PzcmC = new TH1F("PzcmC","Momentum en z del K^{+} en el CM",500,-5,5);	
  PzcmC->GetXaxis()->SetTitle("Momentum en z CM");
  PzcmC->GetYaxis()->SetTitle("Frecuencia");
  PzcmC->GetXaxis()->CenterTitle();
  PzcmC->GetYaxis()->CenterTitle();
  PzcmC->SetLineColor(4);
  
  PtcmC = new TH1F("PtcmC","Momentum total del K^{+} en el CM",500,-5,5);	
  PtcmC->GetXaxis()->SetTitle("Momentum total CM");
  PtcmC->GetYaxis()->SetTitle("Frecuencia");
  PtcmC->GetXaxis()->CenterTitle();
  PtcmC->GetYaxis()->CenterTitle();
  PtcmC->SetLineColor(4);
   
  EcmC = new TH1F("EcmC","Energ#acute{i}a del K^{+} en el CM",500,-5,5);	
  EcmC->GetXaxis()->SetTitle("Energ#acute{i}a");
  EcmC->GetYaxis()->SetTitle("Frecuencia");
  EcmC->GetXaxis()->CenterTitle();
  EcmC->GetYaxis()->CenterTitle();
  EcmC->SetLineColor(4);

  Lambda->cd();
  //Laboratorio	
  masald = new TH1F("masald","Masa del #Lambda_{0}",150,(ML-0.1),(ML+0.1)); 
  masald->GetXaxis()->SetTitle("Masa del #Lambda_{0}");
  masald->GetYaxis()->SetTitle("Frecuencia");
  masald->GetXaxis()->CenterTitle();
  masald->GetYaxis()->CenterTitle();
  masald->SetLineColor(4);

  dldteta = new TH1F("dldteta","Distribuci#acute{o}n del #acute{a}ngulo #theta del #Lambda_{0}",200, 0, 180);
  dldteta->GetXaxis()->SetTitle("#acute{A}ngulo #theta");
  dldteta->GetYaxis()->SetTitle("Frecuencia");
  dldteta->GetXaxis()->CenterTitle();
  dldteta->GetYaxis()->CenterTitle();
  dldteta->SetLineColor(4);

  dldcos = new TH1F("Dldcos","Distribuci#acute{o}n del cos(#theta) del #Lambda_{0}",1000, -1, 1);
  dldcos->GetXaxis()->SetTitle("cos(#theta)");
  dldcos->GetYaxis()->SetTitle("Frecuencia");
  dldcos->GetXaxis()->CenterTitle();
  dldcos->GetYaxis()->CenterTitle();
  dldcos->SetLineColor(4);

  dldphi = new TH1F("Dldphi","Distribuci#acute{o}n del #acute{a}ngulo #phi del #Lambda_{0}",1000,-180,180);
  dldphi->GetXaxis()->SetTitle("#acute{A}ngulo #Phi");
  dldphi->GetYaxis()->SetTitle("Frecuencia");
  dldphi->GetXaxis()->CenterTitle();
  dldphi->GetYaxis()->CenterTitle();
  dldphi->SetLineColor(4);
  PxD = new TH1F("PxD","Momentum en x del #Lambda_{0}",500,-5,5);	
  PxD->GetXaxis()->SetTitle("Momentum en x");
  PxD->GetYaxis()->SetTitle("Frecuencia");
  PxD->GetXaxis()->CenterTitle();
  PxD->GetYaxis()->CenterTitle();
  PxD->SetLineColor(4);
  PyD = new TH1F("PyD","Momentum en y del #Lambda_{0}",500,-5,5);	
  PyD->GetXaxis()->SetTitle("Momentum en y");
  PyD->GetYaxis()->SetTitle("Frecuencia");
  PyD->GetXaxis()->CenterTitle();
  PyD->GetYaxis()->CenterTitle();
  PyD->SetLineColor(4); 
  PzD = new TH1F("PzD","Momentum en z del #Lambda_{0}",500,-5,5);	
  PzD->GetXaxis()->SetTitle("Momentum en z");
  PzD->GetYaxis()->SetTitle("Frecuencia");
  PzD->GetXaxis()->CenterTitle();
  PzD->GetYaxis()->CenterTitle();
  PzD->SetLineColor(4);
  ED = new TH1F("ED","Energ#acute{i}a del #Lambda_{0}",500,-5,5);	
  ED->GetXaxis()->SetTitle("Energ#acute{i}a");
  ED->GetYaxis()->SetTitle("Frecuencia");
  ED->GetXaxis()->CenterTitle();
  ED->GetYaxis()->CenterTitle();
  ED->SetLineColor(4);
  //Centro de masas

  dldtetacm = new TH1F("dldtetacm","Distribuci#acute{o}n del #acute{a}ngulo #theta del #Lambda_{0} en el CM",200, 0, 180);
  dldtetacm->GetXaxis()->SetTitle("#acute{A}ngulo #theta");
  dldtetacm->GetYaxis()->SetTitle("Frecuencia");
  dldtetacm->GetXaxis()->CenterTitle();
  dldtetacm->GetYaxis()->CenterTitle();
  dldtetacm->SetLineColor(4);

  dldcoscm = new TH1F("Dldcoscm","Distribuci#acute{o}n del cos(#theta) del #Lambda_{0} en el CM",1000, -1, 1);
  dldcoscm->GetXaxis()->SetTitle("cos(#theta)");
  dldcoscm->GetYaxis()->SetTitle("Frecuencia");
  dldcoscm->GetXaxis()->CenterTitle();
  dldcoscm->GetYaxis()->CenterTitle();
  dldcoscm->SetLineColor(4);
  dldphicm = new TH1F("Dldphicm","Distribuci#acute{o}n del #acute{a}ngulo #phi del #Lambda_{0} en el CM",1000, -180, 180);
  dldphicm->GetXaxis()->SetTitle("#acute{A}ngulo #Phi");
  dldphicm->GetYaxis()->SetTitle("Frecuencia");
  dldphicm->GetXaxis()->CenterTitle();
  dldphicm->GetYaxis()->CenterTitle();
  dldphicm->SetLineColor(4);
  PxcmD = new TH1F("PxcmD","Momentum en x del #Lambda_{0} en el CM",500,-5,5);	
  PxcmD->GetXaxis()->SetTitle("Momentum en x");
  PxcmD->GetYaxis()->SetTitle("Frecuencia");
  PxcmD->GetXaxis()->CenterTitle();
  PxcmD->GetYaxis()->CenterTitle();
  PxcmD->SetLineColor(4);
  PycmD = new TH1F("PycmD","Momentum en y del #Lambda_{0} en el CM",500,-5,5);	
  PycmD->GetXaxis()->SetTitle("Momentum en y");
  PycmD->GetYaxis()->SetTitle("Frecuencia");
  PycmD->GetXaxis()->CenterTitle();
  PycmD->GetYaxis()->CenterTitle();
  PycmD->SetLineColor(4);
  PzcmD = new TH1F("PzcmD","Momentum en z del #Lambda_{0} en el CM",500,-5,5);	
  PzcmD->GetXaxis()->SetTitle("Momentum en z");
  PzcmD->GetYaxis()->SetTitle("Frecuencia");
  PzcmD->GetXaxis()->CenterTitle();
  PzcmD->GetYaxis()->CenterTitle();
  PzcmD->SetLineColor(4);
  
  PtcmD = new TH1F("PtcmD","Momentum total del #Lambda_{0} en el CM",500,-5,5);	
  PtcmD->GetXaxis()->SetTitle("Momentum total");
  PtcmD->GetYaxis()->SetTitle("Frecuencia");
  PtcmD->GetXaxis()->CenterTitle();
  PtcmD->GetYaxis()->CenterTitle();
  PtcmD->SetLineColor(4);

  EcmD = new TH1F("EcmD","Energ#acute{i}a del #Lambda_{0} en el CM",500,-5,5);	
  EcmD->GetXaxis()->SetTitle("Energ#acute{i}a");
  EcmD->GetYaxis()->SetTitle("Frecuencia");
  EcmD->GetXaxis()->CenterTitle();
  EcmD->GetYaxis()->CenterTitle();
  EcmD->SetLineColor(4);



  Invariantes->cd();


  SLabi = new TH1F("SLabi","Canal s Lab, estado inicial",1000, 0,5);
  SLabi->GetXaxis()->SetTitle("s^{2}");
  SLabi->GetYaxis()->SetTitle("Frecuencia");
  SLabi->GetYaxis()->CenterTitle();
  SLabi->SetLineColor(1);

  SLabf = new TH1F("SLabf","Canal s Lab, estado final",1000, 0,5);
  SLabf->GetXaxis()->SetTitle("s^{2}");
  SLabf->GetYaxis()->SetTitle("Frecuencia");
  SLabf->GetYaxis()->CenterTitle();
  SLabf->SetLineColor(1);

 
  SCmi = new TH1F("SCmi","Canal s Cm, estado inicial",1000, 0,5);
  SCmi->GetXaxis()->SetTitle("s^{2}");
  SCmi->GetYaxis()->SetTitle("Frecuencia");
  SCmi->GetYaxis()->CenterTitle();
  SCmi->SetLineColor(1);

  SCmf = new TH1F("SCmf","Canal s Cm, estado final",1000, 0,5);
  SCmf->GetXaxis()->SetTitle("s^{2}");
  SCmf->GetYaxis()->SetTitle("Frecuencia");
  SCmf->GetYaxis()->CenterTitle();
  SCmf ->SetLineColor(1);


  canalt1 = new TH1F("canalt1","Canal t, Momentum transferido",1000, -3,0);
  canalt1->GetXaxis()->SetTitle("t^{2}");
  canalt1->GetYaxis()->SetTitle("Frecuencia");
  canalt1->GetXaxis()->CenterTitle();
  canalt1->GetYaxis()->CenterTitle();
  canalt1->SetLineColor(1);

  canalt2 = new TH1F("canalt2","Canal t, Momentum transferido",1000, -3,0);
  canalt2->GetXaxis()->SetTitle("t^{2}");
  canalt2->GetYaxis()->SetTitle("Frecuencia");
  canalt2->GetXaxis()->CenterTitle();
  canalt2->GetYaxis()->CenterTitle();
  canalt2->SetLineColor(1);

  canalu1 = new TH1F("canalu1","Canal u, Momentum transferido",1000, -3,0);
  canalu1->GetXaxis()->SetTitle("u^{2}");
  canalu1->GetYaxis()->SetTitle("Frecuencia");
  canalu1->GetXaxis()->CenterTitle();
  canalu1->GetYaxis()->CenterTitle();
  canalu1->SetLineColor(1);

  canalu2 = new TH1F("canalu2","Canal u, Momentum transferido",1000, -3,0);
  canalu2->GetXaxis()->SetTitle("u^{2}");
  canalu2->GetYaxis()->SetTitle("Frecuencia");
  canalu2->GetXaxis()->CenterTitle();
  canalu2->GetYaxis()->CenterTitle();
  canalu2->SetLineColor(1);

  canalt1cm = new TH1F("canalt1cm","Canal t, centro de masas",1000, -3,0);
  canalt1cm->GetXaxis()->SetTitle("t^{2}");
  canalt1cm->GetYaxis()->SetTitle("Frecuencia");
  canalt1cm->GetXaxis()->CenterTitle();
  canalt1cm->GetYaxis()->CenterTitle();
  canalt1cm->SetLineColor(1);

  canalt2cm = new TH1F("canalt2cm","Momentum transferido canal t2cm",1000, -3,0);
  canalt2cm->GetXaxis()->SetTitle("t^{2}");
  canalt2cm->GetYaxis()->SetTitle("Frecuencia");
  canalt2cm->GetXaxis()->CenterTitle();
  canalt2cm->GetYaxis()->CenterTitle();
  canalt2cm->SetLineColor(1);

  canalu1cm = new TH1F("canalu1cm","Canal u, centro de masas",1000, -3,0);
  canalu1cm->GetXaxis()->SetTitle("u^{2}");
  canalu1cm->GetYaxis()->SetTitle("Frecuencia");
  canalu1cm->GetXaxis()->CenterTitle();
  canalu1cm->GetYaxis()->CenterTitle();
  canalu1cm->SetLineColor(1);

  canalu2cm = new TH1F("canalu2cm","Canal u, centro de masas",1000, -3,0);
  canalu2cm->GetXaxis()->SetTitle("u^{2}");
  canalu2cm->GetYaxis()->SetTitle("Frecuencia");
  canalu2cm->GetXaxis()->CenterTitle();
  canalu2cm->GetYaxis()->CenterTitle();
  canalu2cm->SetLineColor(1);

  Comparasiones->cd();
  betald = new TH2F("betald","Beta en funci#acute{o}n del momentum del #Lambda_{0}", 500,0,3, 500,0,2);
  betald->GetXaxis()->SetTitle("Momentum");
  betald->GetYaxis()->SetTitle("Beta");
  betald->GetXaxis()->CenterTitle();
  betald->GetYaxis()->CenterTitle();
  betak = new TH2F("betak","Beta en funci#acute{o}n del momentum del K^{+}", 500,0,3, 500,0,2);
  betak->GetXaxis()->SetTitle("Momentum");
  betak->GetYaxis()->SetTitle("Beta");
  betak->GetXaxis()->CenterTitle();
  betak->GetYaxis()->CenterTitle();
  enminld = new TH2F("enminld","Energ#acute{i}a m#acute{i}nima #Lambda_{0}", 500,0, 2.5, 500,0,2);
  enminld->GetXaxis()->SetTitle("Energ#acute{i}a");
  enminld->GetYaxis()->SetTitle("Momentum del #Lambda_{0}");
  enminld->GetXaxis()->CenterTitle();
  enminld->GetYaxis()->CenterTitle();
  enminkp = new TH2F("enminkp","Energ#acute{i}a m#acute{i}nima del K^{+}", 500,0, 2.5, 500,0,2);
  enminkp->GetXaxis()->SetTitle("Energ#acute{i}a");
  enminkp->GetYaxis()->SetTitle("Momentum del K^{+}");
  enminkp->GetXaxis()->CenterTitle();
  enminkp->GetYaxis()->CenterTitle();
  Energiagcm = new TH1F("Energiagcm","Energ#acute{i}a del beam en el centro de masas", 500,0, 2);
  Energiagcm->GetXaxis()->SetTitle("Energ#acute{i}a del beam, centro de masas");
  Energiagcm->GetYaxis()->SetTitle("Frecuencia");
  Energiagcm->GetXaxis()->CenterTitle();
  Energiagcm->GetYaxis()->CenterTitle();
  Energiagcm->SetLineColor(4);
  Energiapcm = new TH1F("Energiapcm","Energ#acute{i}a del target en el centro de masas", 500,0,2);
  Energiapcm->GetXaxis()->SetTitle("Energ#acute{i}a del target, centro de masas");
  Energiapcm->GetYaxis()->SetTitle("Frecuencia");
  Energiapcm->GetXaxis()->CenterTitle();
  Energiapcm->GetYaxis()->CenterTitle();
  Energiapcm->SetLineColor(4);

}
