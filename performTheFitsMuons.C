#include "../Sources/fitter_tree.C"
using namespace RooFit ;


TFile *myFile;

void doFit(TString type,TString ref, TString obs, float tag_low, float tag_high, float probe_low, float probe_high, RooWorkspace *theWorkSpace, float *theEfficiency, float *theEffError){


    theWorkSpace->factory("expr::nSignalPass('efficiency*fSigAll*numTot', efficiency, fSigAll[0.9,0,1],numTot[1,0,1e10])");
    theWorkSpace->factory("expr::nSignalFail('(1-efficiency)*fSigAll*numTot', efficiency, fSigAll,numTot)");
    theWorkSpace->factory("expr::nBkgPass('effBkg*(1-fSigAll)*numTot', effBkg[0.9,0,1],fSigAll,numTot)");
    theWorkSpace->factory("expr::nBkgFail('(1-effBkg)*(1-fSigAll)*numTot', effBkg,fSigAll,numTot)");
    theWorkSpace->factory("SUM::passing(nSignalPass*signalPass,nBkgPass*backgroundPass)");
    theWorkSpace->factory("SUM::failling(nSignalFail*signalFail,nBkgFail*backgroundFail)");
    theWorkSpace->factory("expr::nPass('nSignalPass+nBkgPass',nSignalPass,nBkgPass)");
    theWorkSpace->factory("expr::nFail('nSignalFail+nBkgFail',nSignalFail,nBkgFail)");
    theWorkSpace->factory("SUM::tot(nPass*passing, nFail*failling)");
    theWorkSpace->factory("SUM::bgExtended(nBkgPass*backgroundPass,theZero[0]*backgroundFail)");

    RooCategory TnPcat("TnP","TnP") ;
    TnPcat.defineType("passing") ;
    TnPcat.defineType("failling") ;


    RooSimultaneous simPdf("simPdf","simultaneous pdf",TnPcat) ;
    simPdf.addPdf(*theWorkSpace->pdf("passing"),"passing") ;
    simPdf.addPdf(*theWorkSpace->pdf("failling"),"failling") ;


    TString nameofHisto;
    if(!(tag_low==0 && tag_high == 0)) nameofHisto = Form(type+"_"+obs+"_"+"leading%0.1f-%0.1f_subleading%0.1f-%0.1f_",tag_low,tag_high,probe_low,probe_high);
    else nameofHisto = Form(type+"_"+obs+"_"+"leading25-inf_subleading%0.1f-%0.1f_",probe_low,probe_high); 
    TH1F *histoPass = (TH1F*) myFile->Get(nameofHisto+"pass");
    TH1F *histoFail = (TH1F*) myFile->Get(nameofHisto+"fail");
    TH1F *histoAll = (TH1F*) myFile->Get(nameofHisto+"all");




    RooDataHist *dataPass= new RooDataHist("dataPass","dataPass",*theWorkSpace->var("invMass"),histoPass);
    RooDataHist *dataFail = new RooDataHist("dataFail","dataFail",*theWorkSpace->var("invMass"),histoFail);
    RooDataHist *dataAll = new RooDataHist("dataAll","dataAll",*theWorkSpace->var("invMass"),histoAll);


    RooDataHist combData("combData","combined data",*theWorkSpace->var("invMass"),Index(TnPcat),Import("passing",*dataPass),Import("failling",*dataFail)) ;


    simPdf.fitTo(combData) ;
    simPdf.fitTo(combData) ;
    simPdf.fitTo(combData) ;

    //// cout << "failling = " << theWorkSpace->obj("nBkgPass")->getVal() << endl;

    RooPlot* xframe = theWorkSpace->var("invMass")->frame(Title("TnP model Passing"),Bins(50)) ;
    dataPass->plotOn(xframe);
    theWorkSpace->pdf("passing")->plotOn(xframe,LineColor(kGreen));
    theWorkSpace->pdf("passing")->plotOn(xframe,Components(*theWorkSpace->pdf("backgroundPass")), LineStyle(kDashed),LineColor(kGreen));

    RooPlot* xframe2 = theWorkSpace->var("invMass")->frame(Title("TnP model Failling"),Bins(50)) ;
    dataFail->plotOn(xframe2);
    theWorkSpace->pdf("failling")->plotOn(xframe2,LineColor(kRed));
    theWorkSpace->pdf("failling")->plotOn(xframe2,Components(*theWorkSpace->pdf("backgroundFail")), LineStyle(kDashed),LineColor(kRed));


    RooPlot* xframe3 = theWorkSpace->var("invMass")->frame(Title("TnP model Total"),Bins(50)) ;
    dataAll->plotOn(xframe3);
    theWorkSpace->pdf("tot")->plotOn(xframe3,LineColor(kBlue));


    int numTot = theWorkSpace->var("numTot")->getVal();
    float fSigAll = theWorkSpace->var("fSigAll")->getVal();
    float efficiency = theWorkSpace->var("efficiency")->getVal();
    float effBkg = theWorkSpace->var("effBkg")->getVal();

    *theEfficiency = theWorkSpace->var("efficiency")->getVal();
    *theEffError = theWorkSpace->var("efficiency")->getError();

    float efficiencyErr = theWorkSpace->var("efficiency")->getError();


    int nbPass = (int) (efficiency*fSigAll*numTot+effBkg*(1-fSigAll)*numTot);
    int nbFail = (int) ((1-efficiency)*fSigAll*numTot + (1-effBkg)*(1-fSigAll)*numTot);

    cout <<"nb pass " <<nbPass << endl;
    cout << "nbfail " << nbFail << endl;


    TCanvas *c0 = new TCanvas("c0","coucou",800,800);
	c0->SetFillColor(0);
    c0->Divide(2,2);

    c0->cd(1);
    xframe->Draw();


    c0->cd(2);
    xframe2->Draw();

    c0->cd(3);
    xframe3->Draw();

    c0->Print(type+"_"+ref+"_"+Form(obs+"_"+"leading%0.1f-%0.1f_subleading%0.1f-%0.1f.png",tag_low,tag_high,probe_low,probe_high));



}

void performTheFitsMuons(TString type, TString ref){

    //TString samples[] = {"2017RunB","2017RunC", "2017RunD", "2017RunE", "2017RunF", "2017DY", "data"};
    //TString samples[] = {"2017DY"};//, "data"};

    gStyle->SetOptStat(0);
    myFile = new TFile("histo3D_"+type+"_"+ref+".root");
    int nbPtBins = sizeof(ptBins)/sizeof(Float_t)-1;
    //float ptBins[] = {25, 50,75,100,150, 200};
    int nbEtaBins = sizeof(etaBins)/sizeof(Float_t)-1 ;
    //float etaBins[] = {0.0, 0.6, 1.2, 1.8, 2.4};
   // float etaBins[15] = {-2.4,-2.1,-1.6,-1.2,-0.9,-0.3,-0.2,0, 0.2,0.3,0.9,1.2,1.6,2.1,2.4};
    
    TH2F *efficiencies_eta = new TH2F("efficiencies_soupMC_"+type+"_eta","",nbEtaBins, etaBins, nbEtaBins, etaBins);
    TH2F *efficiencies_pt = new TH2F("efficiencies_soupMC_"+type+"_pt","",nbPtBins, ptBins, nbPtBins, ptBins);
    TH2F *efficiencies_pt_eta = new TH2F("efficiencies_ref_"+type+"_pt_eta","",nbPtBins, ptBins, nbEtaBins, etaBins);
    TH1F *efficiencies_subleading = new TH1F("efficiencies_subleadingpt","efficiencies_subleadingpt",nbPtBins,ptBins);
    RooWorkspace* voigtPlusExpo = new RooWorkspace("voigtPlusExpo");
    voigtPlusExpo->factory("invMass[90,70,120]");
    voigtPlusExpo->factory("Voigtian::signalPass(invMass, mean1p[90,80,100], width1p[2.495], sigma1p[3,1,20])");
   // voigtPlusExpo->factory("Voigtian::theSig2p(invMass, mean2p[90,80,100], width2p[2.495], sigma2p[3,1,20])");
   // voigtPlusExpo->factory("SUM::signalPass(vPropp[0.8,0,1]*theSig1p,theSig2p)");
    voigtPlusExpo->factory("Voigtian::signalFail(invMass, mean1f[90,80,100], width1f[3,1,2], sigma1f[3,0,20])");
   // voigtPlusExpo->factory("Voigtian::theSig2f(invMass, mean2f[90,80,100], width2f[3,1,2], sigma2f[3,0,20])");
   // voigtPlusExpo->factory("SUM::signalFail(vPropf[0.8,0,1]*theSig1f,theSig2f)");
    voigtPlusExpo->factory("Exponential::backgroundPass(invMass, lp[0,-5,5])");
    voigtPlusExpo->factory("Exponential::backgroundFail(invMass, lf[0,-5,5])");
    voigtPlusExpo->factory("efficiency[0.9,0,1]");
    voigtPlusExpo->factory("signalFractionInPassing[0.9]");
    



    float effVal, effErr;

    for (int i = 0 ; i < nbEtaBins ; i++){
        for (int j = 0 ; j < nbEtaBins ; j++){
            
			doFit(type,ref,"abseta",etaBins[i],etaBins[i+1],etaBins[j],etaBins[j+1],voigtPlusExpo, &effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
            cout<<"test\n\n\n\n\n\n\n"<<endl;
            efficiencies_eta->SetBinContent(i+1,j+1,effVal);
            efficiencies_eta->SetBinError(i+1,j+1,effErr);


        }
    }

    for (int i = 0 ; i < nbPtBins ; i++){
        for (int j = 0 ; j < nbPtBins ; j++){
            doFit(type,ref, "pt",ptBins[i],ptBins[i+1],ptBins[j],ptBins[j+1],voigtPlusExpo, &effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
            cout<<"test\n\n\n\n\n\n\n"<<endl;
            efficiencies_pt->SetBinContent(i+1,j+1,effVal);
            efficiencies_pt->SetBinError(i+1,j+1,effErr);
            cout<<"test"<<endl;
        }
    }
     for (int i = 0 ; i < nbPtBins ; i++){
            doFit(type,ref, "pt",0,0,ptBins[i],ptBins[i+1],voigtPlusExpo, &effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
            efficiencies_subleading->SetBinContent(i+1,effVal);
            efficiencies_subleading->SetBinError(i+1,effErr);
            cout<<"test"<<endl;
    }
    
    for (int i = 0 ; i < nbPtBins ; i++){
        for (int j = 0 ; j < nbEtaBins ; j++){
            doFit(type,ref, "ptWithEtaBin",ptBins[i],ptBins[i+1],etaBins[j],etaBins[j+1],voigtPlusExpo, &effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
            efficiencies_pt_eta->SetBinContent(i+1,j+1,effVal);
            efficiencies_pt_eta->SetBinError(i+1,j+1,effErr);
            cout<<"test"<<endl;
        }
    }


    TFile *myOutFile = new TFile("soupEfficencyMuons_"+type+"_"+ref+".root","recreate");
    efficiencies_eta->Write();
    efficiencies_pt->Write();
    efficiencies_pt_eta->Write();
    efficiencies_subleading->Write();
    myOutFile->Close();

}
