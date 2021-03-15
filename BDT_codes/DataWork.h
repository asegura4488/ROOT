//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug 21 00:03:01 2013 by ROOT version 5.34/00
// from TTree treeS/signal
// found on file: ROOTSlimDataBd-BDT.root
//////////////////////////////////////////////////////////

#ifndef DataWork_h
#define DataWork_h

#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class DataWork {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        mB;
   Double_t        mJ;
   Double_t        mKs0;
   Double_t        bdt;
   Double_t        Bdl;
   Double_t        Bpt;

   // List of branches
   TBranch        *b_mB;   //!
   TBranch        *b_mJ;   //!
   TBranch        *b_mKs0;   //!
   TBranch        *b_bdt;   //!
   TBranch        *b_Bdl;   //!
   TBranch        *b_Bpt;   //!

   DataWork(TTree *tree=0);
   virtual ~DataWork();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

//#ifdef DataWork_cxx
DataWork::DataWork(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ROOTSlimDataBd-BDT.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ROOTSlimDataBd-BDT.root");
      }
      f->GetObject("treeS",tree);

   }
   Init(tree);
}

DataWork::~DataWork()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t DataWork::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t DataWork::LoadTree(Long64_t entry)
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

void DataWork::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mB", &mB, &b_mB);
   fChain->SetBranchAddress("mJ", &mJ, &b_mJ);
   fChain->SetBranchAddress("mKs0", &mKs0, &b_mKs0);
   fChain->SetBranchAddress("bdt", &bdt, &b_bdt);
   fChain->SetBranchAddress("Bdl", &Bdl, &b_Bdl);
   fChain->SetBranchAddress("Bpt", &Bpt, &b_Bpt);
   Notify();
}

Bool_t DataWork::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void DataWork::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t DataWork::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
//#endif // #ifdef DataWork_cxx
