#define fitter_tree_cxx
#include "../Includes/fitter_tree.h"
#include <iostream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH3.h>

   Float_t ptBins[]= {20,25,30,40,50,60,120,200};
   //Float_t etaBins[]={0, 0.3,0.6,0.9,1.2,1.5,1.8,2.1,2.4};
   Float_t etaBins[]={0,0.9,1.2,2.1,2.4};
   //Float_t massBins[] = {60.0,61.5,63.0,64.5,66.0,67.5,69.0,70.5,72.0,73.5,75.0,76.5,78.0,79.5,81.0,82.5,84.0,85.5,87.0,88.5,90.0,91.5,93.0,94.5,96.0,97.5,99.0,100.5,102.0,103.5,105.0,106.5,108.0,109.5,111.0,112.5,114.0,115.5,117.0,118.5,120.0};
   Float_t massBins[120];
   Float_t nvtxBins[60];
  
void fitter_tree::Loop(TString fileName, TString ref)
{    
  for(int i = 0 ; i < 60 ; i++){
    nvtxBins[i]=i;
   }
  for(int i = 0 ; i < 120 ; i++){
    massBins[i]=i*0.5+60;
   }
//   In a ROOT session, you can do:
//      root> .L fitter_tree.C
//      root> fitter_tree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
    TFile *f1 = new TFile("histo3D_"+fileName+".root","RECREATE");
   Long64_t nbytes = 0, nb = 0;

   TH2F * ptPass = new TH2F("ref_pt_pass","ref_pt_pass",sizeof(ptBins)/sizeof(Float_t)-1,ptBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * ptFail = new TH2F("ref_pt_fail","ref_pt_fail",sizeof(ptBins)/sizeof(Float_t)-1,ptBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * ptAll  = new TH2F("ref_pt_all", "ref_pt_all", sizeof(ptBins)/sizeof(Float_t)-1,ptBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   
   TH2F * etaPass = new TH2F("ref_eta_pass","ref_eta_pass",sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * etaFail = new TH2F("ref_eta_fail","ref_eta_fail",sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * etaAll  = new TH2F("ref_eta_all", "ref_eta_all", sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);

   TH2F * nvtxPass = new TH2F("ref_nvtx_pass","ref_nvtx_pass",sizeof(nvtxBins)/sizeof(Float_t)-1,nvtxBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * nvtxFail = new TH2F("ref_nvtx_fail","ref_nvtx_fail",sizeof(nvtxBins)/sizeof(Float_t)-1,nvtxBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * nvtxAll  = new TH2F("ref_nvtx_all", "ref_nvtx_all", sizeof(nvtxBins)/sizeof(Float_t)-1,nvtxBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   
   TH3F * pass2d = new TH3F("ref_2D_pass", "ref_2D_pass", sizeof(ptBins)/   sizeof(Float_t)-1,ptBins,sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);   
   TH3F * fail2d = new TH3F("ref_2D_fail", "ref_2D_fail", sizeof(ptBins)/   sizeof(Float_t)-1,ptBins,sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);   
   TH3F * all2d = new TH3F("ref_2D_all", "ref_2D_all", sizeof(ptBins)/   sizeof(Float_t)-1,ptBins,sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);


   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%10000 ==0) std::cout<<"processing events"<<jentry<<std::endl;
      // if (Cut(ientry) < 0) continue;
      float wt = 1.0;
      if ((fileName.Contains("DY") || fileName.Contains("closure"))&& !fileName.Contains("PU")) wt = wt *weight;
      bool passBaseline = combRelIsoPF04<0.15&&mass>60&&mass<120&&CutBasedIdTight==1&&pt>10&&tag_pt>10;
      bool pass_tag = tag_pt > 25 && tag_abseta < 2.4 && tag_IsoMu24;
      bool pass_probe = CutBasedIdMediumPrompt;
     if(!passBaseline) continue;
      if(!pair_BestZ) continue;
      if(pass_tag){
        if(pass_probe){
          ptPass->Fill(pt,mass,wt);
          etaPass->Fill(abseta,mass,wt);
          nvtxPass->Fill(tag_nVertices,mass,wt);
          pass2d->Fill(pt,abseta,mass,wt);
        }
        else{
          ptFail->Fill(pt,mass,wt);
          etaFail->Fill(abseta,mass,wt);
          nvtxFail->Fill(tag_nVertices,mass,wt);
          fail2d->Fill(pt,abseta,mass,wt);
        }
      }
   }

   ptAll->Add(ptPass,ptFail);
   etaAll->Add(etaPass,etaFail);
   nvtxAll->Add(nvtxPass,nvtxFail);
   all2d->Add(pass2d,fail2d);
        
   f1->Write();
   f1->Close();
}
