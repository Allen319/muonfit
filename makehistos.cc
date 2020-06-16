#include "Includes/ArgParser.h"
#include <iostream>
#include <string>
#include "TString.h"
//#include "Includes/config.h"
#include "Sources/fitter_tree.C"
using namespace std;
int main (int argc, char ** argv) {

	 TString type = "";
   TString ref = "Mu17";
   if (argc>1) {
      for (int i=0;i<argc;i++){
         TString currentArg = argv[i];
		 if (currentArg.BeginsWith("fileName")) getArg(currentArg,type);
     if(currentArg.BeginsWith("ref"))getArg(currentArg,ref); 
        }
      }
   //std::cout<<"tag_eta&eta bin =="<<tag_bin<<"\t"<<bin<<std::endl;
   //std::cout<<"root -l -b -q performTheFitsMuons1D.C\'(\""+type+"\",\""+ref+"\")\'"<<std::endl;
   
   fitter_tree ft(type);
   ft.Loop(type,ref);
	 //TString inputFile = type+".root";
     //for(int i=0; i<sizeof(ptBins)/sizeof(float)-1 ; i++){
	   //makeHistos(type,inputFile,"pt",ptBins[i],ptBins[i+1]);
	   //for(int ii=0; ii<sizeof(ptBins)/sizeof(float)-1; ii++){
	   //makeHistos2D(type,inputFile,"pt",ptBins[i],ptBins[i+1],ptBins[ii],ptBins[ii+1]);
	   //}
     //}
     //for(int j=0; j<sizeof(etaBins)/sizeof(float)-1 ; j++){
	   //makeHistos(type,inputFile,"abseta",etaBins[j],etaBins[j+1]);
	   //for(int jj=0; jj<sizeof(etaBins)/sizeof(float)-1; jj++){
	     //makeHistos2D(type,inputFile,"abseta",etaBins[j],etaBins[j+1],etaBins[jj],etaBins[jj+1]);
	   //}
	 //}
//TString cmd = "hadd -f histos_muons_"+type+".root histos_muons_"+type+"_*.root";
	// system(cmd.Data());
	 //TString cmd1 = "root -l -b -q performTheFitsMuons1D.C\'(\""+type+"\",\""+ref+"\")\'";
	 //system(cmd1.Data());
     //TString cmd2 = "root -l -b -q performTheFitsMuons.C\'(\""+type+"\",\""+ref+"\")\'";
	 //system(cmd2.Data());
   TString cmd3 = "root -l -b -q fitMuons.C\'(\""+type+"\")\'";
	 system(cmd3.Data());




   return 0;
   } 
