#include <iostream>
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "TH1F.h"

TChain *chain = new TChain("tpTree/fitter_tree");
//TFile *myFile = new TFile("histos_muons_data.root","RECREATE");
TString baseAcceptCut = "combRelIsoPF04<0.15&&mass>60&&mass<120&&CutBasedIdTight==1&&pt>25&&tag_pt>25&&tag_Mu17==1";
TString theCutToTest = "Mu17==1";
//TString theCutToTest = "IsoMu27==1||DoubleIsoMu17Mu8dZ_Mass8==1";
TString shortNameCut = "isTight";

TString baseAcceptCutSoup = "combRelIsoPF04<0.15&&mass>60&&mass<120&&CutBasedIdTight==1&&pt>25&&tag_pt>25&&(Mu17==1||tag_Mu17==1)";
TString soupCutToTest = "IsoMu27==1||DoubleIsoMu17Mu8dZ_Mass8==1";
//float etaBins[15] = {-2.4,-2.1,-1.6,-1.2,-0.9,-0.3,-0.2,0, 0.2,0.3,0.9,1.2,1.6,2.1,2.4};
