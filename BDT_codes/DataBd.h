//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Aug 20 16:45:53 2013 by ROOT version 5.34/00
// from TTree ntuple/Bs->J/psi Ks0 ntuple
// found on file: /home/eduard/work/CMS/Bd/datos_ks0/crab1_ks0.root
//////////////////////////////////////////////////////////

#ifndef DataBd_h
#define DataBd_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class DataBd {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          nB;
   UInt_t          nMu;
   vector<float>   *B_mass;
   vector<float>   *B_px;
   vector<float>   *B_py;
   vector<float>   *B_pz;
   vector<float>   *B_Ks0_mass;
   vector<float>   *B_Ks0_px;
   vector<float>   *B_Ks0_py;
   vector<float>   *B_Ks0_pz;
   vector<float>   *B_J_mass;
   vector<float>   *B_J_px;
   vector<float>   *B_J_py;
   vector<float>   *B_J_pz;
   vector<float>   *B_Ks0_pt1;
   vector<float>   *B_Ks0_px1;
   vector<float>   *B_Ks0_py1;
   vector<float>   *B_Ks0_pz1;
   vector<int>     *B_Ks0_charge1;
   vector<float>   *B_Ks0_pt2;
   vector<float>   *B_Ks0_px2;
   vector<float>   *B_Ks0_py2;
   vector<float>   *B_Ks0_pz2;
   vector<int>     *B_Ks0_charge2;
   vector<float>   *B_J_pt1;
   vector<float>   *B_J_px1;
   vector<float>   *B_J_py1;
   vector<float>   *B_J_pz1;
   vector<int>     *B_J_charge1;
   vector<float>   *B_J_pt2;
   vector<float>   *B_J_px2;
   vector<float>   *B_J_py2;
   vector<float>   *B_J_pz2;
   vector<int>     *B_J_charge2;
   vector<int>     *B_Ks0_parentId1;
   vector<int>     *B_Ks0_parentId2;
   vector<int>     *B_Ks0_pId1;
   vector<int>     *B_Ks0_pId2;
   vector<int>     *B_J_parentId1;
   vector<int>     *B_J_parentId2;
   vector<int>     *B_J_muId1;
   vector<int>     *B_J_muId2;
   vector<int>     *B_parentId1;
   vector<int>     *B_parentId2;
   vector<int>     *B_parentId3;
   vector<int>     *B_parentId4;
   vector<float>   *B_chi2;
   vector<float>   *B_Ks0_chi2;
   vector<float>   *B_J_chi2;
   vector<float>   *B_Prob;
   vector<float>   *B_ks0_Prob;
   vector<float>   *B_J_Prob;
   Float_t         priVtxX;
   Float_t         priVtxY;
   Float_t         priVtxZ;
   Float_t         priVtxXE;
   Float_t         priVtxYE;
   Float_t         priVtxZE;
   Float_t         priVtxCL;
   vector<float>   *pVtxX;
   vector<float>   *pVtxY;
   vector<float>   *pVtxZ;
   vector<float>   *pVtxXE;
   vector<float>   *pVtxYE;
   vector<float>   *pVtxZE;
   vector<float>   *pVtxCL;
   UInt_t          nVtx;
   Int_t           run;
   Int_t           evt;
   Int_t           nTrgL;
   Int_t           nTrgL1L;
   Char_t          triggersL[1262];   //[nTrgL]
   Char_t          triggersL1L[1985];   //[nTrgL1L]
   vector<string>  *triggersMuPL;
   vector<string>  *triggersMuML;
   vector<string>  *triggersL1L2_MuPL;
   vector<string>  *triggersL1L2_MuML;
   vector<float>   *priRfVtxX;
   vector<float>   *priRfVtxY;
   vector<float>   *priRfVtxZ;
   vector<float>   *priRfVtxXE;
   vector<float>   *priRfVtxYE;
   vector<float>   *priRfVtxZE;
   vector<float>   *priRfVtxCL;
   vector<int>     *priRfNTrkDif;
   vector<float>   *bctau;
   vector<float>   *bctau2D;
   vector<float>   *bctauBS;
   vector<float>   *bctauE;
   vector<float>   *bctau2DE;
   vector<float>   *bctauBSE;
   vector<float>   *bctau_ks0;
   vector<float>   *bctau2D_ks0;
   vector<float>   *bctauE_ks0;
   vector<float>   *bctau2DE_ks0;
   vector<float>   *bDecayVtxX;
   vector<float>   *bDecayVtxY;
   vector<float>   *bDecayVtxZ;
   vector<double>  *bDecayVtxXE;
   vector<double>  *bDecayVtxYE;
   vector<double>  *bDecayVtxZE;
   vector<float>   *bResMass;
   vector<float>   *bResVtxCL;
   vector<float>   *bResPx;
   vector<float>   *bResPy;
   vector<float>   *bResPz;
   vector<float>   *bResDecayVtxX;
   vector<float>   *bResDecayVtxY;
   vector<float>   *bResDecayVtxZ;
   vector<float>   *bResDecayVtxXE;
   vector<float>   *bResDecayVtxYE;
   vector<float>   *bResDecayVtxZE;
   vector<float>   *VDecayVtxX;
   vector<float>   *VDecayVtxY;
   vector<float>   *VDecayVtxZ;
   vector<float>   *VDecayVtxXE;
   vector<float>   *VDecayVtxYE;
   vector<float>   *VDecayVtxZE;
   vector<float>   *JDecayVtxX;
   vector<float>   *JDecayVtxY;
   vector<float>   *JDecayVtxZ;
   vector<float>   *JDecayVtxXE;
   vector<float>   *JDecayVtxYE;
   vector<float>   *JDecayVtxZE;
   vector<int>     *JmuOL;
   vector<float>   *mumD0;
   vector<float>   *mumD0E;
   vector<float>   *mumC2;
   vector<int>     *mumCat;
   vector<int>     *mumME1;
   vector<int>     *mumAngT;
   vector<int>     *mumNHits;
   vector<int>     *mumNPHits;
   vector<float>   *mupD0;
   vector<float>   *mupD0E;
   vector<float>   *mupC2;
   vector<int>     *mupCat;
   vector<int>     *mupME1;
   vector<int>     *mupAngT;
   vector<int>     *mupNHits;
   vector<int>     *mupNPHits;

   // List of branches
   TBranch        *b_nB;   //!
   TBranch        *b_nMu;   //!
   TBranch        *b_B_mass;   //!
   TBranch        *b_B_px;   //!
   TBranch        *b_B_py;   //!
   TBranch        *b_B_pz;   //!
   TBranch        *b_B_Ks0_mass;   //!
   TBranch        *b_B_Ks0_px;   //!
   TBranch        *b_B_Ks0_py;   //!
   TBranch        *b_B_Ks0_pz;   //!
   TBranch        *b_B_J_mass;   //!
   TBranch        *b_B_J_px;   //!
   TBranch        *b_B_J_py;   //!
   TBranch        *b_B_J_pz;   //!
   TBranch        *b_B_Ks0_pt1;   //!
   TBranch        *b_B_Ks0_px1;   //!
   TBranch        *b_B_Ks0_py1;   //!
   TBranch        *b_B_Ks0_pz1;   //!
   TBranch        *b_B_Ks0_charge1;   //!
   TBranch        *b_B_Ks0_pt2;   //!
   TBranch        *b_B_Ks0_px2;   //!
   TBranch        *b_B_Ks0_py2;   //!
   TBranch        *b_B_Ks0_pz2;   //!
   TBranch        *b_B_Ks0_charge2;   //!
   TBranch        *b_B_J_pt1;   //!
   TBranch        *b_B_J_px1;   //!
   TBranch        *b_B_J_py1;   //!
   TBranch        *b_B_J_pz1;   //!
   TBranch        *b_B_J_charge1;   //!
   TBranch        *b_B_J_pt2;   //!
   TBranch        *b_B_J_px2;   //!
   TBranch        *b_B_J_py2;   //!
   TBranch        *b_B_J_pz2;   //!
   TBranch        *b_B_J_charge2;   //!
   TBranch        *b_B_Ks0_parentId1;   //!
   TBranch        *b_B_Ks0_parentId2;   //!
   TBranch        *b_B_Ks0_pId1;   //!
   TBranch        *b_B_Ks0_pId2;   //!
   TBranch        *b_B_J_parentId1;   //!
   TBranch        *b_B_J_parentId2;   //!
   TBranch        *b_B_J_muId1;   //!
   TBranch        *b_B_J_muId2;   //!
   TBranch        *b_B_parentId1;   //!
   TBranch        *b_B_parentId2;   //!
   TBranch        *b_B_parentId3;   //!
   TBranch        *b_B_parentId4;   //!
   TBranch        *b_B_chi2;   //!
   TBranch        *b_B_Ks0_chi2;   //!
   TBranch        *b_B_J_chi2;   //!
   TBranch        *b_B_Prob;   //!
   TBranch        *b_B_ks0_Prob;   //!
   TBranch        *b_B_J_Prob;   //!
   TBranch        *b_priVtxX;   //!
   TBranch        *b_priVtxY;   //!
   TBranch        *b_priVtxZ;   //!
   TBranch        *b_priVtxXE;   //!
   TBranch        *b_priVtxYE;   //!
   TBranch        *b_priVtxZE;   //!
   TBranch        *b_priVtxCL;   //!
   TBranch        *b_pVtxX;   //!
   TBranch        *b_pVtxY;   //!
   TBranch        *b_pVtxZ;   //!
   TBranch        *b_pVtxXE;   //!
   TBranch        *b_pVtxYE;   //!
   TBranch        *b_pVtxZE;   //!
   TBranch        *b_pVtxCL;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_run;   //!
   TBranch        *b_evt;   //!
   TBranch        *b_nTrgL;   //!
   TBranch        *b_nTrgL1L;   //!
   TBranch        *b_triggersL;   //!
   TBranch        *b_triggersL1L;   //!
   TBranch        *b_triggersMuPL;   //!
   TBranch        *b_triggersMuML;   //!
   TBranch        *b_triggersL1L2_MuPL;   //!
   TBranch        *b_triggersL1L2_MuML;   //!
   TBranch        *b_priRfVtxX;   //!
   TBranch        *b_priRfVtxY;   //!
   TBranch        *b_priRfVtxZ;   //!
   TBranch        *b_priRfVtxXE;   //!
   TBranch        *b_priRfVtxYE;   //!
   TBranch        *b_priRfVtxZE;   //!
   TBranch        *b_priRfVtxCL;   //!
   TBranch        *b_priRfNTrkDif;   //!
   TBranch        *b_bctau;   //!
   TBranch        *b_bctau2D;   //!
   TBranch        *b_bctauBS;   //!
   TBranch        *b_bctauE;   //!
   TBranch        *b_bctau2DE;   //!
   TBranch        *b_bctauBSE;   //!
   TBranch        *b_bctau_ks0;   //!
   TBranch        *b_bctau2D_ks0;   //!
   TBranch        *b_bctauE_ks0;   //!
   TBranch        *b_bctau2DE_ks0;   //!
   TBranch        *b_bDecayVtxX;   //!
   TBranch        *b_bDecayVtxY;   //!
   TBranch        *b_bDecayVtxZ;   //!
   TBranch        *b_bDecayVtxXE;   //!
   TBranch        *b_bDecayVtxYE;   //!
   TBranch        *b_bDecayVtxZE;   //!
   TBranch        *b_bResMass;   //!
   TBranch        *b_bResVtxCL;   //!
   TBranch        *b_bResPx;   //!
   TBranch        *b_bResPy;   //!
   TBranch        *b_bResPz;   //!
   TBranch        *b_bResDecayVtxX;   //!
   TBranch        *b_bResDecayVtxY;   //!
   TBranch        *b_bResDecayVtxZ;   //!
   TBranch        *b_bResDecayVtxXE;   //!
   TBranch        *b_bResDecayVtxYE;   //!
   TBranch        *b_bResDecayVtxZE;   //!
   TBranch        *b_VDecayVtxX;   //!
   TBranch        *b_VDecayVtxY;   //!
   TBranch        *b_VDecayVtxZ;   //!
   TBranch        *b_VDecayVtxXE;   //!
   TBranch        *b_VDecayVtxYE;   //!
   TBranch        *b_VDecayVtxZE;   //!
   TBranch        *b_JDecayVtxX;   //!
   TBranch        *b_JDecayVtxY;   //!
   TBranch        *b_JDecayVtxZ;   //!
   TBranch        *b_JDecayVtxXE;   //!
   TBranch        *b_JDecayVtxYE;   //!
   TBranch        *b_JDecayVtxZE;   //!
   TBranch        *b_JmuOL;   //!
   TBranch        *b_mumD0;   //!
   TBranch        *b_mumD0E;   //!
   TBranch        *b_mumC2;   //!
   TBranch        *b_mumCat;   //!
   TBranch        *b_mumME1;   //!
   TBranch        *b_mumAngT;   //!
   TBranch        *b_mumNHits;   //!
   TBranch        *b_mumNPHits;   //!
   TBranch        *b_mupD0;   //!
   TBranch        *b_mupD0E;   //!
   TBranch        *b_mupC2;   //!
   TBranch        *b_mupCat;   //!
   TBranch        *b_mupME1;   //!
   TBranch        *b_mupAngT;   //!
   TBranch        *b_mupNHits;   //!
   TBranch        *b_mupNPHits;   //!

   DataBd(TTree *tree=0);
   virtual ~DataBd();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef DataBd_cxx
DataBd::DataBd(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/eduard/work/CMS/Bd/datos_ks0/crab1_ks0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/eduard/work/CMS/Bd/datos_ks0/crab1_ks0.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/home/eduard/work/CMS/Bd/datos_ks0/crab1_ks0.root:/mkcands");
      dir->GetObject("ntuple",tree);

   }
   Init(tree);
}

DataBd::~DataBd()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t DataBd::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t DataBd::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void DataBd::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   B_mass = 0;
   B_px = 0;
   B_py = 0;
   B_pz = 0;
   B_Ks0_mass = 0;
   B_Ks0_px = 0;
   B_Ks0_py = 0;
   B_Ks0_pz = 0;
   B_J_mass = 0;
   B_J_px = 0;
   B_J_py = 0;
   B_J_pz = 0;
   B_Ks0_pt1 = 0;
   B_Ks0_px1 = 0;
   B_Ks0_py1 = 0;
   B_Ks0_pz1 = 0;
   B_Ks0_charge1 = 0;
   B_Ks0_pt2 = 0;
   B_Ks0_px2 = 0;
   B_Ks0_py2 = 0;
   B_Ks0_pz2 = 0;
   B_Ks0_charge2 = 0;
   B_J_pt1 = 0;
   B_J_px1 = 0;
   B_J_py1 = 0;
   B_J_pz1 = 0;
   B_J_charge1 = 0;
   B_J_pt2 = 0;
   B_J_px2 = 0;
   B_J_py2 = 0;
   B_J_pz2 = 0;
   B_J_charge2 = 0;
   B_Ks0_parentId1 = 0;
   B_Ks0_parentId2 = 0;
   B_Ks0_pId1 = 0;
   B_Ks0_pId2 = 0;
   B_J_parentId1 = 0;
   B_J_parentId2 = 0;
   B_J_muId1 = 0;
   B_J_muId2 = 0;
   B_parentId1 = 0;
   B_parentId2 = 0;
   B_parentId3 = 0;
   B_parentId4 = 0;
   B_chi2 = 0;
   B_Ks0_chi2 = 0;
   B_J_chi2 = 0;
   B_Prob = 0;
   B_ks0_Prob = 0;
   B_J_Prob = 0;
   pVtxX = 0;
   pVtxY = 0;
   pVtxZ = 0;
   pVtxXE = 0;
   pVtxYE = 0;
   pVtxZE = 0;
   pVtxCL = 0;
   triggersMuPL = 0;
   triggersMuML = 0;
   triggersL1L2_MuPL = 0;
   triggersL1L2_MuML = 0;
   priRfVtxX = 0;
   priRfVtxY = 0;
   priRfVtxZ = 0;
   priRfVtxXE = 0;
   priRfVtxYE = 0;
   priRfVtxZE = 0;
   priRfVtxCL = 0;
   priRfNTrkDif = 0;
   bctau = 0;
   bctau2D = 0;
   bctauBS = 0;
   bctauE = 0;
   bctau2DE = 0;
   bctauBSE = 0;
   bctau_ks0 = 0;
   bctau2D_ks0 = 0;
   bctauE_ks0 = 0;
   bctau2DE_ks0 = 0;
   bDecayVtxX = 0;
   bDecayVtxY = 0;
   bDecayVtxZ = 0;
   bDecayVtxXE = 0;
   bDecayVtxYE = 0;
   bDecayVtxZE = 0;
   bResMass = 0;
   bResVtxCL = 0;
   bResPx = 0;
   bResPy = 0;
   bResPz = 0;
   bResDecayVtxX = 0;
   bResDecayVtxY = 0;
   bResDecayVtxZ = 0;
   bResDecayVtxXE = 0;
   bResDecayVtxYE = 0;
   bResDecayVtxZE = 0;
   VDecayVtxX = 0;
   VDecayVtxY = 0;
   VDecayVtxZ = 0;
   VDecayVtxXE = 0;
   VDecayVtxYE = 0;
   VDecayVtxZE = 0;
   JDecayVtxX = 0;
   JDecayVtxY = 0;
   JDecayVtxZ = 0;
   JDecayVtxXE = 0;
   JDecayVtxYE = 0;
   JDecayVtxZE = 0;
   JmuOL = 0;
   mumD0 = 0;
   mumD0E = 0;
   mumC2 = 0;
   mumCat = 0;
   mumME1 = 0;
   mumAngT = 0;
   mumNHits = 0;
   mumNPHits = 0;
   mupD0 = 0;
   mupD0E = 0;
   mupC2 = 0;
   mupCat = 0;
   mupME1 = 0;
   mupAngT = 0;
   mupNHits = 0;
   mupNPHits = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nB", &nB, &b_nB);
   fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
   fChain->SetBranchAddress("B_mass", &B_mass, &b_B_mass);
   fChain->SetBranchAddress("B_px", &B_px, &b_B_px);
   fChain->SetBranchAddress("B_py", &B_py, &b_B_py);
   fChain->SetBranchAddress("B_pz", &B_pz, &b_B_pz);
   fChain->SetBranchAddress("B_Ks0_mass", &B_Ks0_mass, &b_B_Ks0_mass);
   fChain->SetBranchAddress("B_Ks0_px", &B_Ks0_px, &b_B_Ks0_px);
   fChain->SetBranchAddress("B_Ks0_py", &B_Ks0_py, &b_B_Ks0_py);
   fChain->SetBranchAddress("B_Ks0_pz", &B_Ks0_pz, &b_B_Ks0_pz);
   fChain->SetBranchAddress("B_J_mass", &B_J_mass, &b_B_J_mass);
   fChain->SetBranchAddress("B_J_px", &B_J_px, &b_B_J_px);
   fChain->SetBranchAddress("B_J_py", &B_J_py, &b_B_J_py);
   fChain->SetBranchAddress("B_J_pz", &B_J_pz, &b_B_J_pz);
   fChain->SetBranchAddress("B_Ks0_pt1", &B_Ks0_pt1, &b_B_Ks0_pt1);
   fChain->SetBranchAddress("B_Ks0_px1", &B_Ks0_px1, &b_B_Ks0_px1);
   fChain->SetBranchAddress("B_Ks0_py1", &B_Ks0_py1, &b_B_Ks0_py1);
   fChain->SetBranchAddress("B_Ks0_pz1", &B_Ks0_pz1, &b_B_Ks0_pz1);
   fChain->SetBranchAddress("B_Ks0_charge1", &B_Ks0_charge1, &b_B_Ks0_charge1);
   fChain->SetBranchAddress("B_Ks0_pt2", &B_Ks0_pt2, &b_B_Ks0_pt2);
   fChain->SetBranchAddress("B_Ks0_px2", &B_Ks0_px2, &b_B_Ks0_px2);
   fChain->SetBranchAddress("B_Ks0_py2", &B_Ks0_py2, &b_B_Ks0_py2);
   fChain->SetBranchAddress("B_Ks0_pz2", &B_Ks0_pz2, &b_B_Ks0_pz2);
   fChain->SetBranchAddress("B_Ks0_charge2", &B_Ks0_charge2, &b_B_Ks0_charge2);
   fChain->SetBranchAddress("B_J_pt1", &B_J_pt1, &b_B_J_pt1);
   fChain->SetBranchAddress("B_J_px1", &B_J_px1, &b_B_J_px1);
   fChain->SetBranchAddress("B_J_py1", &B_J_py1, &b_B_J_py1);
   fChain->SetBranchAddress("B_J_pz1", &B_J_pz1, &b_B_J_pz1);
   fChain->SetBranchAddress("B_J_charge1", &B_J_charge1, &b_B_J_charge1);
   fChain->SetBranchAddress("B_J_pt2", &B_J_pt2, &b_B_J_pt2);
   fChain->SetBranchAddress("B_J_px2", &B_J_px2, &b_B_J_px2);
   fChain->SetBranchAddress("B_J_py2", &B_J_py2, &b_B_J_py2);
   fChain->SetBranchAddress("B_J_pz2", &B_J_pz2, &b_B_J_pz2);
   fChain->SetBranchAddress("B_J_charge2", &B_J_charge2, &b_B_J_charge2);
   fChain->SetBranchAddress("B_Ks0_parentId1", &B_Ks0_parentId1, &b_B_Ks0_parentId1);
   fChain->SetBranchAddress("B_Ks0_parentId2", &B_Ks0_parentId2, &b_B_Ks0_parentId2);
   fChain->SetBranchAddress("B_Ks0_pId1", &B_Ks0_pId1, &b_B_Ks0_pId1);
   fChain->SetBranchAddress("B_Ks0_pId2", &B_Ks0_pId2, &b_B_Ks0_pId2);
   fChain->SetBranchAddress("B_J_parentId1", &B_J_parentId1, &b_B_J_parentId1);
   fChain->SetBranchAddress("B_J_parentId2", &B_J_parentId2, &b_B_J_parentId2);
   fChain->SetBranchAddress("B_J_muId1", &B_J_muId1, &b_B_J_muId1);
   fChain->SetBranchAddress("B_J_muId2", &B_J_muId2, &b_B_J_muId2);
   fChain->SetBranchAddress("B_parentId1", &B_parentId1, &b_B_parentId1);
   fChain->SetBranchAddress("B_parentId2", &B_parentId2, &b_B_parentId2);
   fChain->SetBranchAddress("B_parentId3", &B_parentId3, &b_B_parentId3);
   fChain->SetBranchAddress("B_parentId4", &B_parentId4, &b_B_parentId4);
   fChain->SetBranchAddress("B_chi2", &B_chi2, &b_B_chi2);
   fChain->SetBranchAddress("B_Ks0_chi2", &B_Ks0_chi2, &b_B_Ks0_chi2);
   fChain->SetBranchAddress("B_J_chi2", &B_J_chi2, &b_B_J_chi2);
   fChain->SetBranchAddress("B_Prob", &B_Prob, &b_B_Prob);
   fChain->SetBranchAddress("B_ks0_Prob", &B_ks0_Prob, &b_B_ks0_Prob);
   fChain->SetBranchAddress("B_J_Prob", &B_J_Prob, &b_B_J_Prob);
   fChain->SetBranchAddress("priVtxX", &priVtxX, &b_priVtxX);
   fChain->SetBranchAddress("priVtxY", &priVtxY, &b_priVtxY);
   fChain->SetBranchAddress("priVtxZ", &priVtxZ, &b_priVtxZ);
   fChain->SetBranchAddress("priVtxXE", &priVtxXE, &b_priVtxXE);
   fChain->SetBranchAddress("priVtxYE", &priVtxYE, &b_priVtxYE);
   fChain->SetBranchAddress("priVtxZE", &priVtxZE, &b_priVtxZE);
   fChain->SetBranchAddress("priVtxCL", &priVtxCL, &b_priVtxCL);
   fChain->SetBranchAddress("pVtxX", &pVtxX, &b_pVtxX);
   fChain->SetBranchAddress("pVtxY", &pVtxY, &b_pVtxY);
   fChain->SetBranchAddress("pVtxZ", &pVtxZ, &b_pVtxZ);
   fChain->SetBranchAddress("pVtxXE", &pVtxXE, &b_pVtxXE);
   fChain->SetBranchAddress("pVtxYE", &pVtxYE, &b_pVtxYE);
   fChain->SetBranchAddress("pVtxZE", &pVtxZE, &b_pVtxZE);
   fChain->SetBranchAddress("pVtxCL", &pVtxCL, &b_pVtxCL);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("evt", &evt, &b_evt);
   fChain->SetBranchAddress("nTrgL", &nTrgL, &b_nTrgL);
   fChain->SetBranchAddress("nTrgL1L", &nTrgL1L, &b_nTrgL1L);
   fChain->SetBranchAddress("triggersL", triggersL, &b_triggersL);
   fChain->SetBranchAddress("triggersL1L", triggersL1L, &b_triggersL1L);
   fChain->SetBranchAddress("triggersMuPL", &triggersMuPL, &b_triggersMuPL);
   fChain->SetBranchAddress("triggersMuML", &triggersMuML, &b_triggersMuML);
   fChain->SetBranchAddress("triggersL1L2_MuPL", &triggersL1L2_MuPL, &b_triggersL1L2_MuPL);
   fChain->SetBranchAddress("triggersL1L2_MuML", &triggersL1L2_MuML, &b_triggersL1L2_MuML);
   fChain->SetBranchAddress("priRfVtxX", &priRfVtxX, &b_priRfVtxX);
   fChain->SetBranchAddress("priRfVtxY", &priRfVtxY, &b_priRfVtxY);
   fChain->SetBranchAddress("priRfVtxZ", &priRfVtxZ, &b_priRfVtxZ);
   fChain->SetBranchAddress("priRfVtxXE", &priRfVtxXE, &b_priRfVtxXE);
   fChain->SetBranchAddress("priRfVtxYE", &priRfVtxYE, &b_priRfVtxYE);
   fChain->SetBranchAddress("priRfVtxZE", &priRfVtxZE, &b_priRfVtxZE);
   fChain->SetBranchAddress("priRfVtxCL", &priRfVtxCL, &b_priRfVtxCL);
   fChain->SetBranchAddress("priRfNTrkDif", &priRfNTrkDif, &b_priRfNTrkDif);
   fChain->SetBranchAddress("bctau", &bctau, &b_bctau);
   fChain->SetBranchAddress("bctau2D", &bctau2D, &b_bctau2D);
   fChain->SetBranchAddress("bctauBS", &bctauBS, &b_bctauBS);
   fChain->SetBranchAddress("bctauE", &bctauE, &b_bctauE);
   fChain->SetBranchAddress("bctau2DE", &bctau2DE, &b_bctau2DE);
   fChain->SetBranchAddress("bctauBSE", &bctauBSE, &b_bctauBSE);
   fChain->SetBranchAddress("bctau_ks0", &bctau_ks0, &b_bctau_ks0);
   fChain->SetBranchAddress("bctau2D_ks0", &bctau2D_ks0, &b_bctau2D_ks0);
   fChain->SetBranchAddress("bctauE_ks0", &bctauE_ks0, &b_bctauE_ks0);
   fChain->SetBranchAddress("bctau2DE_ks0", &bctau2DE_ks0, &b_bctau2DE_ks0);
   fChain->SetBranchAddress("bDecayVtxX", &bDecayVtxX, &b_bDecayVtxX);
   fChain->SetBranchAddress("bDecayVtxY", &bDecayVtxY, &b_bDecayVtxY);
   fChain->SetBranchAddress("bDecayVtxZ", &bDecayVtxZ, &b_bDecayVtxZ);
   fChain->SetBranchAddress("bDecayVtxXE", &bDecayVtxXE, &b_bDecayVtxXE);
   fChain->SetBranchAddress("bDecayVtxYE", &bDecayVtxYE, &b_bDecayVtxYE);
   fChain->SetBranchAddress("bDecayVtxZE", &bDecayVtxZE, &b_bDecayVtxZE);
   fChain->SetBranchAddress("bResMass", &bResMass, &b_bResMass);
   fChain->SetBranchAddress("bResVtxCL", &bResVtxCL, &b_bResVtxCL);
   fChain->SetBranchAddress("bResPx", &bResPx, &b_bResPx);
   fChain->SetBranchAddress("bResPy", &bResPy, &b_bResPy);
   fChain->SetBranchAddress("bResPz", &bResPz, &b_bResPz);
   fChain->SetBranchAddress("bResDecayVtxX", &bResDecayVtxX, &b_bResDecayVtxX);
   fChain->SetBranchAddress("bResDecayVtxY", &bResDecayVtxY, &b_bResDecayVtxY);
   fChain->SetBranchAddress("bResDecayVtxZ", &bResDecayVtxZ, &b_bResDecayVtxZ);
   fChain->SetBranchAddress("bResDecayVtxXE", &bResDecayVtxXE, &b_bResDecayVtxXE);
   fChain->SetBranchAddress("bResDecayVtxYE", &bResDecayVtxYE, &b_bResDecayVtxYE);
   fChain->SetBranchAddress("bResDecayVtxZE", &bResDecayVtxZE, &b_bResDecayVtxZE);
   fChain->SetBranchAddress("VDecayVtxX", &VDecayVtxX, &b_VDecayVtxX);
   fChain->SetBranchAddress("VDecayVtxY", &VDecayVtxY, &b_VDecayVtxY);
   fChain->SetBranchAddress("VDecayVtxZ", &VDecayVtxZ, &b_VDecayVtxZ);
   fChain->SetBranchAddress("VDecayVtxXE", &VDecayVtxXE, &b_VDecayVtxXE);
   fChain->SetBranchAddress("VDecayVtxYE", &VDecayVtxYE, &b_VDecayVtxYE);
   fChain->SetBranchAddress("VDecayVtxZE", &VDecayVtxZE, &b_VDecayVtxZE);
   fChain->SetBranchAddress("JDecayVtxX", &JDecayVtxX, &b_JDecayVtxX);
   fChain->SetBranchAddress("JDecayVtxY", &JDecayVtxY, &b_JDecayVtxY);
   fChain->SetBranchAddress("JDecayVtxZ", &JDecayVtxZ, &b_JDecayVtxZ);
   fChain->SetBranchAddress("JDecayVtxXE", &JDecayVtxXE, &b_JDecayVtxXE);
   fChain->SetBranchAddress("JDecayVtxYE", &JDecayVtxYE, &b_JDecayVtxYE);
   fChain->SetBranchAddress("JDecayVtxZE", &JDecayVtxZE, &b_JDecayVtxZE);
   fChain->SetBranchAddress("JmuOL", &JmuOL, &b_JmuOL);
   fChain->SetBranchAddress("mumD0", &mumD0, &b_mumD0);
   fChain->SetBranchAddress("mumD0E", &mumD0E, &b_mumD0E);
   fChain->SetBranchAddress("mumC2", &mumC2, &b_mumC2);
   fChain->SetBranchAddress("mumCat", &mumCat, &b_mumCat);
   fChain->SetBranchAddress("mumME1", &mumME1, &b_mumME1);
   fChain->SetBranchAddress("mumAngT", &mumAngT, &b_mumAngT);
   fChain->SetBranchAddress("mumNHits", &mumNHits, &b_mumNHits);
   fChain->SetBranchAddress("mumNPHits", &mumNPHits, &b_mumNPHits);
   fChain->SetBranchAddress("mupD0", &mupD0, &b_mupD0);
   fChain->SetBranchAddress("mupD0E", &mupD0E, &b_mupD0E);
   fChain->SetBranchAddress("mupC2", &mupC2, &b_mupC2);
   fChain->SetBranchAddress("mupCat", &mupCat, &b_mupCat);
   fChain->SetBranchAddress("mupME1", &mupME1, &b_mupME1);
   fChain->SetBranchAddress("mupAngT", &mupAngT, &b_mupAngT);
   fChain->SetBranchAddress("mupNHits", &mupNHits, &b_mupNHits);
   fChain->SetBranchAddress("mupNPHits", &mupNPHits, &b_mupNPHits);
   Notify();
}

Bool_t DataBd::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void DataBd::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t DataBd::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef DataBd_cxx
