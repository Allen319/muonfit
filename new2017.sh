#!/bin/bash
#DIR="/eos/cms/store/group/phys_muon/TagAndProbe/ULRereco/2017/102X/Run2017B"
#DIR="/eos/cms/store/group/phys_muon/TagAndProbe/Run2018/102X"
DIR="/eos/cms/store/group/phys_muon/TagAndProbe/Run2017/94X"
#Run=("TnPTreeZ_17Sep2018_SingleMuon_Run2018Av2_GoldenJSON.root" "TnPTreeZ_17Sep2018_SingleMuon_Run2018Bv1_GoldenJSON.root" "TnPTreeZ_17Sep2018_SingleMuon_Run2018Cv1_GoldenJSON.root" "TnPTreeZ_SingleMuon_Run2018Dv2_GoldenJSON.root")
Run=("MC/TnPTree_94X_DYJetsToLL_M50_Madgraph.root" "RunB/TnPTree_17Nov2017_SingleMuon_Run2017Bv1_Full_GoldenJSON.root" "RunC/TnPTree_17Nov2017_SingleMuon_Run2017Cv1_Full_GoldenJSON.root" "RunD/TnPTree_17Nov2017_SingleMuon_Run2017Dv1_Full_GoldenJSON.root" "RunE/TnPTree_17Nov2017_SingleMuon_Run2017Ev1_Full_GoldenJSON.root" "RunF/TnPTree_17Nov2017_SingleMuon_Run2017Fv1_Full_GoldenJSON.root")

#cd $DIR
#for k in $(ls $DIR)
for k in ${Run[@]}
do
  ./skimTree $DIR"/"$k ${k%%/*}".root" --remove "*" --keep "Mu17_IsoTrkVVL tag_Mu17 event lumi run  pair_probeMultiplicity pt eta abseta pair_BestZ mass Mu17 DoubleMu17Mu8_Mu17 Mu20 IsoMu24 IsoMu27 TkIsoTight CutBasedIdTight CutBasedIdMedium CutBasedIdLoose PFIsoLoose DoubleIsoMu17Mu8dZ_Mass3p8 DoubleIsoMu17Mu8dZ_Mass8 DoubleIsoMu17Mu8_IsoMu17leg DoubleIsoMu17Mu8_Mu17leg DoubleIsoMu17Mu8_IsoMu8leg DoubleIsoMu17Mu8_Mu8leg tag_DoubleIsoMu17Mu8_IsoMu17leg tag_DoubleIsoMu17Mu8_Mu17leg tag_DoubleIsoMu17Mu8_IsoMu8leg tag_DoubleIsoMu17Mu8_Mu8leg tag_Mu17 truePU tag_Mu20 tag_IsoMu24 tag_IsoMu27 tag_TkIsoTight tag_CutBasedIdTight tag_CutBasedIdMedium tag_CutBasedIdLoose tag_PFIsoLoose tag_DoubleIsoMu17Mu8dZ_Mass3p8 DoubleIsoMu17Mu8dZ_Mass8 tag_DoubleIsoMu17Mu8dZ_Mass8 tag_pt tag_eta tag_abseta pair_pt combRelIsoPF04 tag_combRelIsoPF04" --cut "combRelIsoPF04<0.2&&mass>60&&mass<120&&CutBasedIdLoose==1&&pt>10&&tag_pt>10" 
  root -l -b -q addBestZOnePairRandomTagPt_RunEvent.C\'\(\"${k%%/*}".root"\"\)\' 
done
