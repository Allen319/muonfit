//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jan 27 14:58:34 2020 by ROOT version 6.06/01
// from TTree fitter_tree/fitter_tree
// found on file: 2017RunB.root
//////////////////////////////////////////////////////////

#ifndef fitter_tree_h
#define fitter_tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class fitter_tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         abseta;
   Float_t         combRelIsoPF04;
   Float_t         eta;
   Float_t         pt;
   Int_t           CutBasedIdLoose;
   Int_t           CutBasedIdMedium;
   Int_t           CutBasedIdTight;
   Int_t           DoubleIsoMu17Mu8dZ_Mass3p8;
   Int_t           DoubleIsoMu17Mu8dZ_Mass8;
   Int_t           DoubleIsoMu17Mu8dZ_Mu17leg;
   Int_t           DoubleIsoMu17Mu8_IsoMu17leg;
   Int_t           tag_DoubleIsoMu17Mu8_IsoMu17leg;
   Int_t           DoubleIsoMu17Mu8_IsoMu8leg;
   Int_t           tag_DoubleIsoMu17Mu8_IsoMu8leg;
   Int_t           DoubleIsoMu17Mu8_Mu17leg;
   Int_t           tag_DoubleIsoMu17Mu8_Mu17leg;
   Int_t           DoubleIsoMu17Mu8_Mu8leg;
   Int_t           tag_DoubleIsoMu17Mu8_Mu8leg;    
   Int_t           IsoMu24;
   Int_t           IsoMu27;
   Int_t           Mu17;
   Int_t           Mu17_IsoTrkVVL;
   Int_t           Mu20;
   Int_t           PFIsoLoose;
   Int_t           TkIsoTight;
   Float_t         mass;
   Float_t         tag_abseta;
   Float_t         tag_combRelIsoPF04;
   Float_t         tag_eta;
   Float_t         tag_pt;
   Int_t           tag_DoubleIsoMu17Mu8dZ_Mass3p8;
   Int_t           tag_DoubleIsoMu17Mu8dZ_Mass8;
   Int_t           tag_DoubleIsoMu17Mu8dZ_Mu17leg;
   Int_t           tag_IsoMu24;
   Int_t           tag_IsoMu27;
   Int_t           tag_Mu17;
   Int_t           tag_Mu17_IsoTrkVVL;
   Int_t           tag_Mu20;
   Float_t         pair_pt;
   Float_t         pair_probeMultiplicity;
   Int_t           pair_BestZ;
   Int_t           mcTrue;
   Int_t           pair_BestZOnePair;
   Float_t           tag_nVertices;
   Float_t         weight;
   // List of branches
   TBranch        *b_abseta;   //!
   TBranch        *b_combRelIsoPF04;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_CutBasedIdLoose;   //!
   TBranch        *b_CutBasedIdMedium;   //!
   TBranch        *b_CutBasedIdTight;   //!
   TBranch        *b_DoubleIsoMu17Mu8dZ_Mass3p8;   //!
   TBranch        *b_DoubleIsoMu17Mu8dZ_Mass8;   //!
   TBranch        *b_DoubleIsoMu17Mu8dZ_Mu17leg;   //!
   TBranch        *b_IsoMu24;   //!
   TBranch        *b_IsoMu27;   //!
   TBranch        *b_Mu17;   //!
   TBranch        *b_Mu17_IsoTrkVVL;   //!
   TBranch        *b_Mu20;   //!
   TBranch        *b_PFIsoLoose;   //!
   TBranch        *b_TkIsoTight;   //!
   TBranch        *b_mass;   //!
   TBranch        *b_tag_abseta;   //!
   TBranch        *b_tag_combRelIsoPF04;   //!
   TBranch        *b_tag_eta;   //!
   TBranch        *b_tag_pt;   //!
   TBranch        *b_tag_DoubleIsoMu17Mu8dZ_Mass3p8;   //!
   TBranch        *b_tag_DoubleIsoMu17Mu8dZ_Mass8;   //!
   TBranch        *b_tag_DoubleIsoMu17Mu8dZ_Mu17leg;   //!
   TBranch        *b_tag_IsoMu24;   //!
   TBranch        *b_tag_IsoMu27;   //!
   TBranch        *b_tag_Mu17;   //!
   TBranch        *b_tag_Mu17_IsoTrkVVL;   //!
   TBranch        *b_tag_Mu20;   //!
   TBranch        *b_pair_pt;   //!
   TBranch        *b_pair_probeMultiplicity;   //!
   TBranch        *b_pair_BestZ;   //!
   TBranch        *b_mcTrue;
   TBranch        *b_pair_BestZOnePair;
   TBranch        *b_DoubleIsoMu17Mu8_IsoMu17leg;
   TBranch        *b_tag_DoubleIsoMu17Mu8_IsoMu17leg;
   TBranch        *b_DoubleIsoMu17Mu8_IsoMu8leg;
   TBranch        *b_tag_DoubleIsoMu17Mu8_IsoMu8leg;
   TBranch        *b_DoubleIsoMu17Mu8_Mu17leg;
   TBranch        *b_tag_DoubleIsoMu17Mu8_Mu17leg;
   TBranch        *b_DoubleIsoMu17Mu8_Mu8leg;
   TBranch        *b_tag_DoubleIsoMu17Mu8_Mu8leg;    
   TBranch        *b_tag_nVertices;
   TBranch        *b_weight; 
   
   
   fitter_tree(TString fileName,TTree *tree=0);
   virtual ~fitter_tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString fileName, TString ref);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef fitter_tree_cxx
fitter_tree::fitter_tree(TString fileName, TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  if(tree == 0)   {
      fileName = "../"+fileName;
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(fileName+".root");
      if (!f || !f->IsOpen()) {
         f = new TFile(fileName+".root");
      }
      TDirectory * dir = (TDirectory*)f->Get(fileName+".root:/tpTree");
      dir->GetObject("fitter_tree",tree);
  }
  Init(tree);
}

fitter_tree::~fitter_tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t fitter_tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t fitter_tree::LoadTree(Long64_t entry)
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

void fitter_tree::Init(TTree *tree)
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

   fChain->SetBranchAddress("abseta", &abseta, &b_abseta);
   fChain->SetBranchAddress("combRelIsoPF04", &combRelIsoPF04, &b_combRelIsoPF04);
   fChain->SetBranchAddress("eta", &eta, &b_eta);
   fChain->SetBranchAddress("pt", &pt, &b_pt);
   fChain->SetBranchAddress("CutBasedIdLoose", &CutBasedIdLoose, &b_CutBasedIdLoose);
   fChain->SetBranchAddress("CutBasedIdMedium", &CutBasedIdMedium, &b_CutBasedIdMedium);
   fChain->SetBranchAddress("CutBasedIdTight", &CutBasedIdTight, &b_CutBasedIdTight);
   fChain->SetBranchAddress("DoubleIsoMu17Mu8dZ_Mass3p8", &DoubleIsoMu17Mu8dZ_Mass3p8, &b_DoubleIsoMu17Mu8dZ_Mass3p8);
   fChain->SetBranchAddress("DoubleIsoMu17Mu8dZ_Mass8", &DoubleIsoMu17Mu8dZ_Mass8, &b_DoubleIsoMu17Mu8dZ_Mass8);
   fChain->SetBranchAddress("DoubleIsoMu17Mu8dZ_Mu17leg", &DoubleIsoMu17Mu8dZ_Mu17leg, &b_DoubleIsoMu17Mu8dZ_Mu17leg);
   fChain->SetBranchAddress("IsoMu24", &IsoMu24, &b_IsoMu24);
   fChain->SetBranchAddress("IsoMu27", &IsoMu27, &b_IsoMu27);
   fChain->SetBranchAddress("Mu17", &Mu17, &b_Mu17);
   fChain->SetBranchAddress("Mu17_IsoTrkVVL", &Mu17_IsoTrkVVL, &b_Mu17_IsoTrkVVL);
   fChain->SetBranchAddress("Mu20", &Mu20, &b_Mu20);
   fChain->SetBranchAddress("PFIsoLoose", &PFIsoLoose, &b_PFIsoLoose);
   fChain->SetBranchAddress("TkIsoTight", &TkIsoTight, &b_TkIsoTight);
   fChain->SetBranchAddress("mass", &mass, &b_mass);
   fChain->SetBranchAddress("tag_abseta", &tag_abseta, &b_tag_abseta);
   fChain->SetBranchAddress("tag_combRelIsoPF04", &tag_combRelIsoPF04, &b_tag_combRelIsoPF04);
   fChain->SetBranchAddress("tag_eta", &tag_eta, &b_tag_eta);
   fChain->SetBranchAddress("tag_pt", &tag_pt, &b_tag_pt);
   fChain->SetBranchAddress("tag_DoubleIsoMu17Mu8dZ_Mass3p8", &tag_DoubleIsoMu17Mu8dZ_Mass3p8, &b_tag_DoubleIsoMu17Mu8dZ_Mass3p8);
   fChain->SetBranchAddress("tag_DoubleIsoMu17Mu8dZ_Mass8", &tag_DoubleIsoMu17Mu8dZ_Mass8, &b_tag_DoubleIsoMu17Mu8dZ_Mass8);
   fChain->SetBranchAddress("tag_DoubleIsoMu17Mu8dZ_Mu17leg", &tag_DoubleIsoMu17Mu8dZ_Mu17leg, &b_tag_DoubleIsoMu17Mu8dZ_Mu17leg);
   fChain->SetBranchAddress("tag_IsoMu24", &tag_IsoMu24, &b_tag_IsoMu24);
   fChain->SetBranchAddress("tag_IsoMu27", &tag_IsoMu27, &b_tag_IsoMu27);
   fChain->SetBranchAddress("tag_Mu17", &tag_Mu17, &b_tag_Mu17);
   fChain->SetBranchAddress("tag_Mu17_IsoTrkVVL", &tag_Mu17_IsoTrkVVL, &b_tag_Mu17_IsoTrkVVL);
   fChain->SetBranchAddress("tag_Mu20", &tag_Mu20, &b_tag_Mu20);
   fChain->SetBranchAddress("pair_pt", &pair_pt, &b_pair_pt);
   fChain->SetBranchAddress("pair_probeMultiplicity", &pair_probeMultiplicity, &b_pair_probeMultiplicity);
   fChain->SetBranchAddress("pair_BestZ", &pair_BestZ, &b_pair_BestZ);
   fChain->SetBranchAddress("mcTrue", &mcTrue, &b_mcTrue);
   fChain->SetBranchAddress("pair_BestZOnePair", &pair_BestZOnePair, &b_pair_BestZOnePair);
   fChain->SetBranchAddress("DoubleIsoMu17Mu8_IsoMu17leg", &DoubleIsoMu17Mu8_IsoMu17leg, &b_DoubleIsoMu17Mu8_IsoMu17leg);
   fChain->SetBranchAddress("tag_DoubleIsoMu17Mu8_IsoMu17leg", &tag_DoubleIsoMu17Mu8_IsoMu17leg, &b_tag_DoubleIsoMu17Mu8_IsoMu17leg);
   fChain->SetBranchAddress("DoubleIsoMu17Mu8_IsoMu8leg", &DoubleIsoMu17Mu8_IsoMu8leg, &b_DoubleIsoMu17Mu8_IsoMu8leg);
   fChain->SetBranchAddress("tag_DoubleIsoMu17Mu8_IsoMu8leg", &tag_DoubleIsoMu17Mu8_IsoMu8leg, &b_tag_DoubleIsoMu17Mu8_IsoMu8leg);
   fChain->SetBranchAddress("DoubleIsoMu17Mu8_Mu17leg", &DoubleIsoMu17Mu8_Mu17leg, &b_DoubleIsoMu17Mu8_Mu17leg);
   fChain->SetBranchAddress("tag_DoubleIsoMu17Mu8_Mu17leg", &tag_DoubleIsoMu17Mu8_Mu17leg, &b_tag_DoubleIsoMu17Mu8_Mu17leg);
   fChain->SetBranchAddress("DoubleIsoMu17Mu8_Mu8leg", &DoubleIsoMu17Mu8_Mu8leg, &b_DoubleIsoMu17Mu8_Mu8leg);
   fChain->SetBranchAddress("tag_DoubleIsoMu17Mu8_Mu8leg",&tag_DoubleIsoMu17Mu8_Mu8leg, &b_tag_DoubleIsoMu17Mu8_Mu8leg);
   fChain->SetBranchAddress("tag_nVertices",&tag_nVertices, &b_tag_nVertices);
   fChain->SetBranchAddress("weight", &weight, &b_weight); 
   
   
   
   
   
   
   
   
   
   Notify();
}

Bool_t fitter_tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void fitter_tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t fitter_tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef fitter_tree_cxx
