#define fitter_tree_cxx
#include "../Includes/fitter_tree.h"
#include <iostream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH3.h>

   Float_t ptBins[]= {10,15,17,20,25,30,40,50,75,100,150,200};
   //Float_t etaBins[]={0, 0.3,0.6,0.9,1.2,1.5,1.8,2.1,2.4};
   Float_t etaBins[]={0,0.6,1.2,1.8,2.4};
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

   TH3F * ptPass = new TH3F("pt_pass","pt_pass",sizeof(ptBins)/sizeof(Float_t)-1,ptBins,sizeof(ptBins)/sizeof(Float_t)-1,ptBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH3F * ptFail = new TH3F("pt_fail","pt_fail",sizeof(ptBins)/sizeof(Float_t)-1,ptBins,sizeof(ptBins)/sizeof(Float_t)-1,ptBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH3F * ptAll  = new TH3F("pt_all", "pt_all", sizeof(ptBins)/sizeof(Float_t)-1,ptBins,sizeof(ptBins)/sizeof(Float_t)-1,ptBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH3F * etaPass = new TH3F("eta_pass","eta_pass",sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH3F * etaFail = new TH3F("eta_fail","eta_fail",sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH3F * etaAll  = new TH3F("eta_all", "eta_all", sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * nvtxPass = new TH2F("nvtx_pass","nvtx_pass",sizeof(nvtxBins)/sizeof(Float_t)-1,nvtxBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * nvtxFail = new TH2F("nvtx_fail","nvtx_fail",sizeof(nvtxBins)/sizeof(Float_t)-1,nvtxBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * nvtxAll  = new TH2F("nvtx_all", "nvtx_all", sizeof(nvtxBins)/sizeof(Float_t)-1,nvtxBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);

   TH2F * ptDistribution_pass = new TH2F("pt_distribution","pt_distribution",100,0,200,100,0,200);
   TH2F * etaDistribution_pass =new TH2F("eta_distribution","eta_distribution",12,0,2.4,12,0,2.4);
   TH2F * ptDistribution_fail = new TH2F("pt_distribution","pt_distribution",100,0,200,100,0,200);
   TH2F * etaDistribution_fail =new TH2F("eta_distribution","eta_distribution",12,0,2.4,12,0,2.4);
   TH2F * ptDistribution_all = new TH2F("pt_distribution","pt_distribution",100,0,200,100,0,200);
   TH2F * etaDistribution_all =new TH2F("eta_distribution","eta_distribution",12,0,2.4,12,0,2.4);
   
   TH2F * refptPass = new TH2F("ref_pt_pass","ref_pt_pass",sizeof(ptBins)/sizeof(Float_t)-1,ptBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * refptFail = new TH2F("ref_pt_fail","ref_pt_fail",sizeof(ptBins)/sizeof(Float_t)-1,ptBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * refptAll  = new TH2F("ref_pt_all", "ref_pt_all", sizeof(ptBins)/sizeof(Float_t)-1,ptBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   
   TH2F * refetaPass = new TH2F("ref_eta_pass","ref_eta_pass",sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * refetaFail = new TH2F("ref_eta_fail","ref_eta_fail",sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * refetaAll  = new TH2F("ref_eta_all", "ref_eta_all", sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);

   TH2F * refnvtxPass = new TH2F("ref_nvtx_pass","ref_nvtx_pass",sizeof(nvtxBins)/sizeof(Float_t)-1,nvtxBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * refnvtxFail = new TH2F("ref_nvtx_fail","ref_nvtx_fail",sizeof(nvtxBins)/sizeof(Float_t)-1,nvtxBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   TH2F * refnvtxAll  = new TH2F("ref_nvtx_all", "ref_nvtx_all", sizeof(nvtxBins)/sizeof(Float_t)-1,nvtxBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);
   
   TH3F * ref2Dpass = new TH3F("ref_2D_pass", "ref_2D_pass", sizeof(ptBins)/   sizeof(Float_t)-1,ptBins,sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);   
   TH3F * ref2Dfail = new TH3F("ref_2D_fail", "ref_2D_fail", sizeof(ptBins)/   sizeof(Float_t)-1,ptBins,sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);   
   TH3F * ref2Dall = new TH3F("ref_2D_all", "ref_2D_all", sizeof(ptBins)/   sizeof(Float_t)-1,ptBins,sizeof(etaBins)/sizeof(Float_t)-1,etaBins,sizeof(massBins)/sizeof(Float_t)-1,massBins);   
   TH1F * numberofpairs = new TH1F("numOfPairs","numOfPairs",5,0,5);


   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%10000 ==0) std::cout<<"processing events"<<jentry<<std::endl;
      // if (Cut(ientry) < 0) continue;
      float wt = 1.0;
      if ((fileName.Contains("DY") || fileName.Contains("closure"))&& !fileName.Contains("PU")) wt = wt *weight;
      std::cout<<wt<<std::endl;
      bool passBaseline = combRelIsoPF04<0.15&&mass>60&&mass<120&&CutBasedIdTight==1&&pt>10&&tag_pt>10;
      bool passSoupTrigger;
      bool pass_tag, pass_probe, pass_either;
      if (ref.Contains("_IsoMu17leg")){
        pass_tag = tag_DoubleIsoMu17Mu8_IsoMu17leg;
        pass_probe = DoubleIsoMu17Mu8_IsoMu17leg;
      }
      else if (ref.Contains("_IsoMu8leg")){
        pass_tag = tag_DoubleIsoMu17Mu8_IsoMu8leg;
        pass_probe = DoubleIsoMu17Mu8_IsoMu8leg;
      }
      else if (ref.Contains("_Mu17leg")){
        pass_tag = tag_DoubleIsoMu17Mu8_Mu17leg;
        pass_probe = DoubleIsoMu17Mu8_Mu17leg;
      }
      else if (ref.Contains("_Mu8leg")){
        pass_tag = tag_DoubleIsoMu17Mu8_Mu8leg;
        pass_probe = DoubleIsoMu17Mu8_Mu8leg;
      }
      else if (!ref.Contains("_")){
        pass_tag = tag_Mu17;
        pass_probe = Mu17;
      }
      else{;}
      pass_either= pass_tag || pass_probe;
      if (fileName.Contains("2017"))passSoupTrigger = DoubleIsoMu17Mu8dZ_Mass8 || IsoMu27 || tag_IsoMu27 ||tag_DoubleIsoMu17Mu8dZ_Mass8;
      if (fileName.Contains("2018"))passSoupTrigger = DoubleIsoMu17Mu8dZ_Mass3p8 || IsoMu24 || tag_IsoMu24 ||tag_DoubleIsoMu17Mu8dZ_Mass3p8;
      //std::cout<<fileName.Contains("2018")<<passSoupTrigger<<DoubleIsoMu17Mu8dZ_Mass8<<IsoMu24<<tag_IsoMu24<<tag_DoubleIsoMu17Mu8dZ_Mass8<<std::endl;
      if(!passBaseline) continue;
      numberofpairs->Fill(pair_probeMultiplicity);
      //std::cout<<pair_probeMultiplicity<<"\t"<<pair_BestZ<<"\t"<<(pair_probeMultiplicity>1 && !pair_BestZ)<<std::endl;
      if(!pair_BestZ) continue;
      if(pass_tag&& tag_pt>25){
        if(pass_probe){
          refptPass->Fill(pt,mass,wt);
          refetaPass->Fill(abseta,mass,wt);
          refnvtxPass->Fill(tag_nVertices,mass,wt);
          ref2Dpass->Fill(pt,abseta,mass,wt);
        }
        else{
          refptFail->Fill(pt,mass,wt);
          refetaFail->Fill(abseta,mass,wt);
          refnvtxFail->Fill(tag_nVertices,mass,wt);
          ref2Dfail->Fill(pt,abseta,mass,wt);
        }
      }
      if(!pass_either && !fileName.Contains("closure")) continue;
      //if(pt<25) continue;
      
      //if(!pair_BestZOnePair) continue;
      if(passSoupTrigger)
      { //std::cout<<"passSoup"<<std::endl;
        nvtxPass->Fill(tag_nVertices,mass,wt);
        if(tag_pt>pt)
        {
          ptPass->Fill(tag_pt,pt,mass,wt);
          if (pt > 25)etaPass->Fill(tag_abseta,abseta,mass,wt);
          ptDistribution_pass->Fill(tag_pt,pt,wt);
          if (pt > 25)etaDistribution_pass->Fill(tag_abseta,abseta,wt);


        }
        else{
          ptPass->Fill(pt,tag_pt,mass,wt);
          if (tag_pt > 25)etaPass->Fill(abseta,tag_abseta,mass,wt);
          ptDistribution_pass->Fill(pt,tag_pt,wt);
          if (tag_pt > 25)etaDistribution_pass->Fill(abseta,tag_abseta,wt);
        }
      }
      else{
        nvtxFail->Fill(tag_nVertices,mass,wt);
       if(tag_pt>pt)
        {
          ptFail->Fill(tag_pt,pt,mass,wt);
          if (pt > 25)etaFail->Fill(tag_abseta,abseta,mass,wt);
          ptDistribution_fail->Fill(tag_pt,pt,wt);
          if (pt > 25)etaDistribution_fail->Fill(tag_abseta,abseta,wt);
        }
        else{
          ptFail->Fill(pt,tag_pt,mass,wt);
          if (tag_pt > 25)etaFail->Fill(abseta,tag_abseta,mass,wt);
          ptDistribution_fail->Fill(pt,tag_pt,wt);
          if (tag_pt > 25)etaDistribution_fail->Fill(abseta,tag_abseta,wt);
        
        }
      }
   }

   ptAll->Add(ptPass,ptFail);
   etaAll->Add(etaPass,etaFail);
   nvtxAll->Add(nvtxPass,nvtxFail);
   refptAll->Add(refptPass,refptFail);
   refetaAll->Add(refetaPass,refetaFail);
   refnvtxAll->Add(refnvtxPass,refnvtxFail);
   ref2Dall->Add(ref2Dpass,ref2Dfail);
   ptDistribution_all->Add(ptDistribution_pass,ptDistribution_fail);
   etaDistribution_all->Add(etaDistribution_pass,etaDistribution_fail);
   /*
   for (int i = 0; i < sizeof(ptBins)/sizeof(Float_t)-1; i++){
        ptAll->ProjectionZ(Form("pt_leading25-inf_subleading%0.1f-%0.1f_all",ptBins[i],ptBins[i+1]),2,-1,i,i+1)->Write();
        ptPass->ProjectionZ(Form("pt_leading25-inf_subleading%0.1f-%0.1f_pass",ptBins[i],ptBins[i+1]),2,-1,i,i+1)->Write();
        ptFail->ProjectionZ(Form("pt_leading25-inf_subleading%0.1f-%0.1f_fail",ptBins[i],ptBins[i+1]),2,-1,i,i+1)->Write();
      
      for(int j = 0 ; j < sizeof(ptBins)/sizeof(Float_t)-1; j++){
        ptAll->ProjectionZ(Form("pt_leading%0.1f-%0.1f_subleading%0.1f-%0.1f_all",ptBins[i],ptBins[i+1],ptBins[j],ptBins[j+1]),i,i+1,j,j+1)->Write();
        ptPass->ProjectionZ(Form("pt_leading%0.1f-%0.1f_subleading%0.1f-%0.1f_pass",ptBins[i],ptBins[i+1],ptBins[j],ptBins[j+1]),i,i+1,j,j+1)->Write();
        ptFail->ProjectionZ(Form("pt_leading%0.1f-%0.1f_subleading%0.1f-%0.1f_fail",ptBins[i],ptBins[i+1],ptBins[j],ptBins[j+1]),i,i+1,j,j+1)->Write();
      }
   }
   
   for (int i = 0; i < sizeof(etaBins)/sizeof(Float_t)-1; i++){
     for (int j = 0 ; j < sizeof(ptBins)/sizeof(Float_t)-1; j++){
     ref2Dall->ProjectionZ(Form("ptWithEtaBin_leading%0.1f-%0.1f_subleading%0.1f-%0.1f_all",ptBins[j],ptBins[j+1],etaBins[i],etaBins[i+1]),i,i+1,j,j+1)->Write();
    ref2Dpass->ProjectionZ(Form("ptWithEtaBin_leading%0.1f-%0.1f_subleading%0.1f-%0.1f_pass",ptBins[j],ptBins[j+1],etaBins[i],etaBins[i+1]),i,i+1,j,j+1)->Write();
    ref2Dfail->ProjectionZ(Form("ptWithEtaBin_leading%0.1f-%0.1f_subleading%0.1f-%0.1f_fail",ptBins[j],ptBins[j+1],etaBins[i],etaBins[i+1]),i,i+1,j,j+1)->Write(); 
   }
}
  for (int i = 0; i < sizeof(etaBins)/sizeof(Float_t)-1; i++){ 
     for(int j = 0 ; j < sizeof(etaBins)/sizeof(Float_t)-1; j++){

        etaAll->ProjectionZ(Form("abseta_leading%0.1f-%0.1f_subleading%0.1f-%0.1f_all",etaBins[i],etaBins[i+1],etaBins[j],etaBins[j+1]),i,i+1,j,j+1)->Write();
        etaPass->ProjectionZ(Form("abseta_leading%0.1f-%0.1f_subleading%0.1f-%0.1f_pass",etaBins[i],etaBins[i+1],etaBins[j],etaBins[j+1]),i,i+1,j,j+1)->Write();
        etaFail->ProjectionZ(Form("abseta_leading%0.1f-%0.1f_subleading%0.1f-%0.1f_fail",etaBins[i],etaBins[i+1],etaBins[j],etaBins[j+1]),i,i+1,j,j+1)->Write();
      }
   }
   for (int i = 0; i < sizeof(ptBins)/sizeof(Float_t)-1; i++){
        refptAll->ProjectionY(Form("pt_probe%0.1f-%0.1f_all",ptBins[i],ptBins[i+1]),i,i+1)->Write();
        refptPass->ProjectionY(Form("pt_probe%0.1f-%0.1f_pass",ptBins[i],ptBins[i+1]),i,i+1)->Write();
        refptFail->ProjectionY(Form("pt_probe%0.1f-%0.1f_fail",ptBins[i],ptBins[i+1]),i,i+1)->Write();
        refetaAll->ProjectionY(Form("abseta_probe%0.1f-%0.1f_all",etaBins[i],etaBins[i+1]),i,i+1)->Write();
        refetaPass->ProjectionY(Form("abseta_probe%0.1f-%0.1f_pass",etaBins[i],etaBins[i+1]),i,i+1)->Write();
        refetaFail->ProjectionY(Form("abseta_probe%0.1f-%0.1f_fail",etaBins[i],etaBins[i+1]),i,i+1)->Write();
   }
    refptAll->ProjectionY("ref_all",0,-1)->Write();
    refptPass->ProjectionY("ref_pass",0,-1)->Write();
    refptFail->ProjectionY("ref_fail",0,-1)->Write();
    etaAll->ProjectionZ("soup_all",0,-1,0,-1)->Write();
        etaPass->ProjectionZ("soup_pass",0,-1,0,-1)->Write();
        etaFail->ProjectionZ("soup_fail",0,-1,0,-1)->Write();
  */
        
   f1->Write();
   f1->Close();
}
