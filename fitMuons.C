#include <math.h>
#include "../Sources/fitter_tree.C"
using namespace RooFit ;


TFile *myFile;
void do1BinFit(TString type,TString nameofHisto, RooWorkspace *theWorkSpace, float *theEfficiency, float *theEffError){


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



    TH1F *histoPass = (TH1F*) myFile->Get(nameofHisto+"_pass");
    TH1F *histoFail = (TH1F*) myFile->Get(nameofHisto+"_fail");
    TH1F *histoAll = (TH1F*) myFile->Get(nameofHisto+"_all");




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

    c0->Print(type+"_total.png");

}

void do1DFit(TString type, TString nameofHisto, int xBinLow, int xBinHigh, RooWorkspace *theWorkSpace, float *theEfficiency, float *theEffError){


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


    TH2F *histoPass2D = (TH2F*) myFile->Get(nameofHisto+"_pass");
    TH2F *histoFail2D = (TH2F*) myFile->Get(nameofHisto+"_fail");
    TH2F *histoAll2D = (TH2F*) myFile->Get(nameofHisto+"_all");
    
    TH1F *histoPass = (TH1F*)histoPass2D->ProjectionY(nameofHisto+"pass",xBinLow,xBinHigh);
    TH1F *histoFail = (TH1F*)histoFail2D->ProjectionY(nameofHisto+"fail",xBinLow,xBinHigh);
    TH1F *histoAll  = (TH1F*)histoAll2D->ProjectionY(nameofHisto+"all",xBinLow,xBinHigh);

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

    c0->Print(type+"_"+nameofHisto+"_"+Form("xBin%0.1i-%0.1i.png",xBinLow,xBinHigh));



}


void do2DFit(TString type, TString nameofHisto, int xBinLow, int xBinHigh, int yBinLow, int yBinHigh, RooWorkspace *theWorkSpace, float *theEfficiency, float *theEffError){


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


    TH3F *histoPass3D = (TH3F*) myFile->Get(nameofHisto+"_pass");
    TH3F *histoFail3D = (TH3F*) myFile->Get(nameofHisto+"_fail");
    TH3F *histoAll3D = (TH3F*) myFile->Get(nameofHisto+"_all");
    
    TH1F *histoPass = (TH1F*)histoPass3D->ProjectionZ(nameofHisto+"pass",xBinLow,xBinHigh,yBinLow,yBinHigh);
    TH1F *histoFail = (TH1F*)histoFail3D->ProjectionZ(nameofHisto+"fail",xBinLow,xBinHigh,yBinLow,yBinHigh);
    TH1F *histoAll  = (TH1F*)histoAll3D->ProjectionZ(nameofHisto+"all",xBinLow,xBinHigh,yBinLow,yBinHigh);

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

    c0->Print(type+"_"+nameofHisto+"_"+Form("xBin%0.1i-%0.1i_yBin%0.1i-%0.1i.png",xBinLow,xBinHigh,yBinLow,yBinHigh));



}

void count2D(TString type, TString nameofHisto, int xBinLow, int xBinHigh, int yBinLow, int yBinHigh, float *theEfficiency, float *theEffError){


    TH3F *histoPass3D = (TH3F*) myFile->Get(nameofHisto+"_pass");
    TH3F *histoFail3D = (TH3F*) myFile->Get(nameofHisto+"_fail");
    TH3F *histoAll3D = (TH3F*) myFile->Get(nameofHisto+"_all");
    
    TH1F *histoPass = (TH1F*)histoPass3D->ProjectionZ(nameofHisto+"pass",xBinLow,xBinHigh,yBinLow,yBinHigh);
    TH1F *histoFail = (TH1F*)histoFail3D->ProjectionZ(nameofHisto+"fail",xBinLow,xBinHigh,yBinLow,yBinHigh);
    TH1F *histoAll  = (TH1F*)histoAll3D->ProjectionZ(nameofHisto+"all",xBinLow,xBinHigh,yBinLow,yBinHigh);






    Double_t errPass, errFail, errAll;
    float  numTot = histoAll->IntegralAndError(0,-1,errAll);
    float  nbPass = histoPass->IntegralAndError(0,-1,errPass);
    float nbFail = histoFail->IntegralAndError(0,-1,errFail);

    *theEfficiency = nbPass/numTot;
    *theEffError = (1/(numTot*numTot))*sqrt(numTot*numTot*errAll*errAll+nbPass*nbPass*errPass*errPass);




    cout <<"nb pass " <<nbPass << endl;
    cout << "nbfail " << nbFail << endl;


}

void count1D(TString type, TString nameofHisto, int xBinLow, int xBinHigh, float *theEfficiency, float *theEffError){


    TH2F *histoPass2D = (TH2F*) myFile->Get(nameofHisto+"_pass");
    TH2F *histoFail2D = (TH2F*) myFile->Get(nameofHisto+"_fail");
    TH2F *histoAll2D = (TH2F*) myFile->Get(nameofHisto+"_all");
    
    TH1F *histoPass = (TH1F*)histoPass2D->ProjectionY(nameofHisto+"pass",xBinLow,xBinHigh);
    TH1F *histoFail = (TH1F*)histoFail2D->ProjectionY(nameofHisto+"fail",xBinLow,xBinHigh);
    TH1F *histoAll  = (TH1F*)histoAll2D->ProjectionY(nameofHisto+"all",xBinLow,xBinHigh);






    Double_t errPass, errFail, errAll;
    float  numTot = histoAll->IntegralAndError(0,-1,errAll);
    float  nbPass = histoPass->IntegralAndError(0,-1,errPass);
    float nbFail = histoFail->IntegralAndError(0,-1,errFail);

    *theEfficiency = nbPass/numTot;
    *theEffError = (1/(numTot*numTot))*sqrt(numTot*numTot*errAll*errAll+nbPass*nbPass*errPass*errPass);




    cout <<"nb pass " <<nbPass << endl;
    cout << "nbfail " << nbFail << endl;


}

void count1Bin(TString type, TString nameofHisto,  float *theEfficiency, float *theEffError){


    TH1F *histoPass = (TH1F*) myFile->Get(nameofHisto+"_pass");
    TH1F *histoFail = (TH1F*) myFile->Get(nameofHisto+"_fail");
    TH1F *histoAll = (TH1F*) myFile->Get(nameofHisto+"_all");


    Double_t errPass, errFail, errAll;
    float  numTot = histoAll->IntegralAndError(0,-1,errAll);
    float  nbPass = histoPass->IntegralAndError(0,-1,errPass);
    float nbFail = histoFail->IntegralAndError(0,-1,errFail);

    *theEfficiency = nbPass/numTot;
    *theEffError = (1/(numTot*numTot))*sqrt(numTot*numTot*errAll*errAll+nbPass*nbPass*errPass*errPass);




    cout <<"nb pass " <<nbPass << endl;
    cout << "nbfail " << nbFail << endl;


}


void fitMuons(TString type){


    gStyle->SetOptStat(0);
    myFile = new TFile("histo3D_"+type+".root");
    int nbPtBins = sizeof(ptBins)/sizeof(Float_t)-1;
    int nbEtaBins = sizeof(etaBins)/sizeof(Float_t)-1 ;
     for(int i = 0 ; i < 60 ; i++){
    nvtxBins[i]=i;
   }
    int nbNvtxBins = sizeof(nvtxBins)/sizeof(Int_t)-1 ;
    
    TH2F *efficiencies_eta = new TH2F(type+"_soup_eta",type+"_soup_eta",nbEtaBins, etaBins, nbEtaBins, etaBins);
    TH1F *efficiencies_nvtx = new TH1F(type+"_nvtx",type+"_nvtx",nbNvtxBins,nvtxBins);
    TH2F *efficiencies_pt_eta = new TH2F(type+"_ref_pt_eta",type+"_ref_pt_eta",nbPtBins,ptBins, nbEtaBins, etaBins);
    TH1F *efficiencies_subleading = new TH1F(type+"_subleadingpt",type+"_subleadingpt",nbPtBins,ptBins);
    TH1F *efficiencies_total = new TH1F(type+"efficiencies_total",type+"efficiencies_total",2,0,2);
    TH2F *ref_pt_eta = new TH2F(type+"ref_pt_eta",type+"ref_pt_eta",nbPtBins, ptBins, nbEtaBins, etaBins);
    TH1F *ref_pt = new TH1F(type+"_ref_pt",type+"_ref_pt",nbPtBins,ptBins);

    TH1F *ref_eta = new TH1F(type+"_ref_eta",type+"_ref_eta",nbEtaBins,etaBins);

    TH1F *ref_nvtx = new TH1F(type+"_ref_nvtx",type+"_ref_nvtx",nbNvtxBins,nvtxBins);
    RooWorkspace* voigtPlusExpo = new RooWorkspace("voigtPlusExpo");
    voigtPlusExpo->factory("invMass[90,60,120]");
    voigtPlusExpo->factory("Voigtian::signalPass(invMass, mean1p[90,80,100], width1p[2.495], sigma1p[3,1,20])");
   // voigtPlusExpo->factory("Voigtian::theSig2p(invMass, mean2p[90,80,100], width2p[2.495], sigma2p[3,1,20])");
   // voigtPlusExpo->factory("SUM::signalPass(vPropp[0.8,0,1]*theSig1p,theSig2p)");
    voigtPlusExpo->factory("Voigtian::signalFail(invMass, mean1f[90,80,100], width1f[3,1,2], sigma1f[3,0,20])");
   // voigtPlusExpo->factory("Voigtian::theSig2f(invMass, mean2f[90,80,100], width2f[3,1,2], sigma2f[3,0,20])");
   // voigtPlusExpo->factory("SUM::signalFail(vPropf[0.8,0,1]*theSig1f,theSig2f)");
    voigtPlusExpo->factory("Exponential::backgroundPass(invMass, lp[0,-10,10])");
    voigtPlusExpo->factory("Exponential::backgroundFail(invMass, lf[0,-10,10])");
    voigtPlusExpo->factory("efficiency[0.9,0,1]");
    voigtPlusExpo->factory("signalFractionInPassing[0.9]");
    

    float effVal, effErr;

    for (int i = 0 ; i < nbEtaBins ; i++){
        for (int j = 0 ; j < nbEtaBins ; j++){   
			do2DFit(type,"eta",i,i+1,j,j+1,voigtPlusExpo, &effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
            cout<<"test\n\n\n\n\n\n\n"<<endl;
            efficiencies_eta->SetBinContent(i+1,j+1,effVal);
            efficiencies_eta->SetBinError(i+1,j+1,effErr);
            //count2D(type,"eta",i,i+1,j,j+1,&effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;

        }
    }

    for (int i = 0 ; i < nbPtBins ; i++){
        for (int j = 0 ; j < nbEtaBins ; j++){   
            do2DFit(type,"ref_2D",i,i+1,j,j+1,voigtPlusExpo, &effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
            cout<<"test\n\n\n\n\n\n\n"<<endl;
            efficiencies_pt_eta->SetBinContent(i+1,j+1,effVal);
            efficiencies_pt_eta->SetBinError(i+1,j+1,effErr);

            cout << "val=" << effVal << " error=" << effErr << endl;

        }
    }

    for (int i = 0 ; i < nbNvtxBins ; i++){
            do1DFit(type,"nvtx",i,i+1,voigtPlusExpo, &effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
            cout<<"test\n\n\n\n\n\n\n"<<endl;
            efficiencies_nvtx->SetBinContent(i+1,effVal);
            efficiencies_nvtx->SetBinError(i+1,effErr);
            //count1D(type,"pt",0,-1,i,i+1,&effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
    }

    for (int i = 0 ; i < nbPtBins ; i++){
            do2DFit(type,"pt",0,-1,i,i+1,voigtPlusExpo, &effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
            cout<<"test\n\n\n\n\n\n\n"<<endl;
            efficiencies_subleading->SetBinContent(i+1,effVal);
            efficiencies_subleading->SetBinError(i+1,effErr);
            count2D(type,"pt",0,-1,i,i+1,&effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
    }

    for (int i = 0 ; i < nbPtBins ; i++){
            do1DFit(type,"ref_pt",i,i+1,voigtPlusExpo, &effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
            cout<<"test\n\n\n\n\n\n\n"<<endl;
            ref_pt->SetBinContent(i+1,effVal);
            ref_pt->SetBinError(i+1,effErr);
            //count1D(type,"pt",0,-1,i,i+1,&effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
    }

    for (int i = 0 ; i < nbEtaBins ; i++){
            do1DFit(type,"ref_eta",i,i+1,voigtPlusExpo, &effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
            cout<<"test\n\n\n\n\n\n\n"<<endl;
            ref_eta->SetBinContent(i+1,effVal);
            ref_eta->SetBinError(i+1,effErr);
            //count1D(type,"pt",0,-1,i,i+1,&effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
    }

    for (int i = 0 ; i < nbNvtxBins ; i++){
            do1DFit(type,"ref_nvtx",i,i+1,voigtPlusExpo, &effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
            cout<<"test\n\n\n\n\n\n\n"<<endl;
            ref_nvtx->SetBinContent(i+1,effVal);
            ref_nvtx->SetBinError(i+1,effErr);
            //count1D(type,"pt",0,-1,i,i+1,&effVal, &effErr);
            cout << "val=" << effVal << " error=" << effErr << endl;
    }
    do1DFit(type,"ref_eta",0,-1,voigtPlusExpo, &effVal, &effErr);
    efficiencies_total->SetBinContent(1,effVal);
    efficiencies_total->SetBinError(1,effErr);
    do2DFit(type,"eta",0,-1,0,-1,voigtPlusExpo, &effVal, &effErr);
    efficiencies_total->SetBinContent(2,effVal);
    efficiencies_total->SetBinError(2,effErr);

    TFile *myOutFile = new TFile("eff.root","update");
    efficiencies_eta->Write();
    efficiencies_pt_eta->Write();
    efficiencies_subleading->Write();
    efficiencies_nvtx->Write();
    efficiencies_total->Write();
    ref_eta->Write();
    ref_nvtx->Write();
    ref_pt->Write();
    myOutFile->Close();

}
