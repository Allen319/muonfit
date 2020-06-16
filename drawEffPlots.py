import ROOT as rt
import os
import ROOT
from copy import deepcopy, copy
import numpy as np 
import matplotlib.pyplot as plt

Runs = {'2017':['RunB','RunC','RunD','RunE','RunF','DY'],'2018':['RunA','RunB','RunC','RunD','DY']}
#refs = ['Mu17', 'DoubleIsoMu17Mu8_IsoMu17leg', 'DoubleIsoMu17Mu8_IsoMu8leg', 'DoubleIsoMu17Mu8_Mu17leg','DoubleIsoMu17Mu8_Mu8leg']

ptPos=[]
pt_width=[]
etaBins= [0.0,0.6,1.2,1.8,2.4]
etaPos=[]
eta_width=[]

histos={}

def getBinning(th1, width, pos):
	NbinsX = th1.GetNbinsX()
	for aBin in range(0,NBinsX):
		pos.append(th1.GetBinCenter(aBin))
		width.append(th1.GetBinWidth(aBin))
	print width,pos

def main():
	for year in Runs:
		for aRun in Runs[year]:
			histos[year+aRun+'eta']=deepcopy(root_file.Get("efficiencies_ref_"+year+aRun+"_eta"))
			histos[year+aRun+'pt'] =deepcopy(root_file.Get("efficiencies_ref_"+year+aRun+"_pt"))
			histos[year+aRun+'pt_eta']=deepcopy(root_file.Get("efficiencies_ref_"+year+aRun+"_pt_eta"))
	fig = plt.figure()
	for year in Runs:
		for aRun in Runs[year]:
			name = year+aRun+'pt'
			bins = []
			errors = []
			for aBin in range(1,histos[name].GetNbinsX()+1):
				bins.append(histos[name].GetBinContent(aBin))
				errors.append(histos[name].GetBinError(aBin))
			plt.errorbar(
			  ptPos, bins, fmt='', ms=3, marker='o' , ls='none',
			  xerr=pt_width, yerr=errors, label=year+(aRun if not 'DY' in aRun else 'MC'))
#plt.errorbar(ptPos,bins,yerr=errors,label=name)
		plt.legend(loc='lower right')
		plt.xlim(25, 200)
		plt.ylim(0.8, 1)
		plt.title('Mu17')
		plt.xlabel('pt')
		plt.ylabel('efficiency')
		plt.savefig(year+'_Mu17_pt.png')
		plt.cla()
	for year in Runs:
		for aRun in Runs[year]:
			name = year+aRun+'eta'
			bins = []
			errors = []
			for aBin in range(1,histos[name].GetNbinsX()+1):
				bins.append(histos[name].GetBinContent(aBin))
				errors.append(histos[name].GetBinError(aBin))
			plt.errorbar(
			  etaPos, bins, fmt='', ms=4, marker='o', ls='none',
			  xerr=eta_width, yerr=errors, label=year+(aRun if not 'DY' in aRun else 'MC'))
#plt.errorbar(ptPos,bins,yerr=errors,label=name)
		plt.legend(loc='lower right')
		plt.xlim(0, 2.4)
		plt.ylim(0.8, 1)
		plt.title('Mu17')
		plt.xlabel('$|\eta|$')
		plt.ylabel('efficiency')
		plt.savefig(year+'_Mu17_eta.png')
		plt.cla()


	for year in Runs:
		for i in range(1,5):
			for aRun in Runs[year]:
				name = year+aRun+'pt_eta'
				bins = []
				errors = []
				for aBin in range(1,histos[name].GetNbinsX()+1):
					bins.append(histos[name].GetBinContent(aBin,i))
					errors.append(histos[name].GetBinError(aBin,i))
				plt.errorbar(
					ptPos, bins, fmt='', ms=4, marker='o', ls='none',
					xerr=pt_width, yerr=errors, label=year+
					(aRun if not 'DY' in aRun else 'MC'))
			plt.legend(loc='lower right')
			plt.xlim(25, 200)
			plt.ylim(0.8, 1)
			plt.title(r'Mu17 $|\eta|$ '+str(0.6*(i-1))+'-'+str(0.6*i))
			plt.xlabel('pt')
			plt.ylabel('efficiency')
			plt.savefig(year+'_Mu17_abseta'+str(0.6*(i-1))+'-'+str(0.6*i)+'.png')
			plt.cla()
if __name__ == '__main__':

	refs = ['Mu17', 'DoubleIsoMu17Mu8_IsoMu17leg', 'DoubleIsoMu17Mu8_IsoMu8leg', 'DoubleIsoMu17Mu8_Mu17leg','DoubleIsoMu17Mu8_Mu8leg']
	for ref in refs:
		
		root_file = rt.TFile("eff"+ref+".root")
		main()
