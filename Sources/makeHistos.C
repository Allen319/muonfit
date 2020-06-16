#include "../Includes/makeHistos.h"

void doTheHistos(TString type,TString obs, TString nameHisto, TString testCut, TString baseCut, float left, float right){
    std::cout << "fill the histo:" << nameHisto << std::endl;
    TString fileName = Form("histos_muons_"+type+".root");//Form("histos_muons_"+type+"_"+obs+"_probe%0.1f-%0.1f.root",left, right);
    TFile *myFile = new TFile(fileName,"UPDATE");
    TH1F *passing = new TH1F("passing","",40,60,120);
    chain->Draw("mass>>passing",baseCut+"&&"+testCut);
    myFile->cd();
    passing->Write(nameHisto+"_pass");
    TH1F *failling = new TH1F("failling","",40,60,120);
    chain->Draw("mass>>failling",baseCut+"&&(!("+testCut+"))");
    myFile->cd();
    failling->Write(nameHisto+"_fail");    
    TH1F *all = new TH1F("all","",40,60,120);
    all->Add(passing,failling);
    myFile->cd();
    all->Write(nameHisto+"_all");
    delete all;    
    delete failling;
    delete passing;
    myFile->Close();
}

void makeHistos(TString type,TString nameFile,TString obs,float left, float right){
   chain->Add(nameFile);
   TString theCut = Form(""+ obs +">%f&&"+ obs +"<%f", left, right);
   //TString theCut = Form(""+ obs +">%f&&"+ obs +"<%f&&tag_"+ obs +">%f&&tag_"+ obs +"<%f",etaBins[i], etaBins[i+1],etaBins[j],etaBins[j+1]);
   doTheHistos(type, obs, Form(type+"_"+obs+"_"+"probe%0.1f-%0.1f", left, right),theCutToTest,baseAcceptCut+"&&"+theCut, left, right);    
}
void doTheHistos2D(TString type,TString obs, TString nameHisto, TString testCut, TString baseCut, float tag_low, float tag_high, float probe_low,float probe_high){
    std::cout << "fill the histo:" << nameHisto << std::endl;
    TString fileName = Form("histos_muons_"+type+".root");//Form("histos_muons_"+type+"_"+obs+"_tag%0.1f-%0.1f_probe%0.1f-%0.1f.root",tag_low, tag_high, probe_low, probe_high);
	TFile *myFile = new TFile(fileName,"UPDATE");
    TH1F *passing = new TH1F("passing","",40,60,120);
    chain->Draw("mass>>passing",baseCut+"&&"+testCut);
    myFile->cd();
    passing->Write(nameHisto+"_pass");
    TH1F *failling = new TH1F("failling","",40,60,120);
    chain->Draw("mass>>failling",baseCut+"&&(!("+testCut+"))");
    myFile->cd();
    failling->Write(nameHisto+"_fail");    
    TH1F *all = new TH1F("all","",40,60,120);
    all->Add(passing,failling);
    myFile->cd();
    all->Write(nameHisto+"_all");
    delete all;    
    delete failling;
    delete passing;
    myFile->Close();
}

void makeHistos2D(TString type,TString nameFile,TString obs,float tag_low, float tag_high, float probe_low, float probe_high){
   chain->Add(nameFile);
   //TString theCut = Form(""+ obs +">%f&&"+ obs +"<%f", left, right);
   TString theCut = Form(""+ obs +">%f&&"+ obs +"<%f&&tag_"+ obs +">%f&&tag_"+ obs +"<%f",probe_low, probe_high ,tag_low, tag_high);
   //TString theCut = Form(""+ obs +">%f&&"+ obs +"<%f&&tag_"+ obs +">%f&&tag_"+ obs +"<%f",etaBins[i], etaBins[i+1],etaBins[j],etaBins[j+1]);
	doTheHistos2D(type, obs, Form(type+"_"+obs+"_"+"tag%0.1f-%0.1f_probe%0.1f-%0.1f",tag_low,tag_high,probe_low,probe_high),soupCutToTest,baseAcceptCutSoup+"&&"+theCut, tag_low, tag_high, probe_low,probe_high);
}
