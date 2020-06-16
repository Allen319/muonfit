import ROOT as rt

def getEventEfficiency(th2):
	newEffHisto = th2.Clone()
	newEffHisto.SetDefaultSumw2()
	NbinsX = th2.GetNbinsX()
	NbinsY = th2.GetNbinsY()
	for x in range(NbinsX):
		for y in range(NbinsY):
			th2.SetBinContent(x+1,y+1,1-(1-th2.GetBinContent(x+1,y+1))*(1-th2.GetBinContent(x+1,y+1)))
			th2.SetBinError(x+1,y+1,(2-th2.GetBinContent(x+1,y+1))*th2.GetBinError(x+1,y+1))
	return th2

def getSoupEfficiency(refTh2,soupTh2,name):
	newEffHisto = refTh2.Clone()
	newEffHisto.SetDefaultSumw2()
	newEffHisto.SetName(name)
	NbinsX = refTh2.GetNbinsX()
	NbinsY = refTh2.GetNbinsY()
	for x in range(NbinsX):
		for y in range(NbinsY):
			refBin = refTh2.GetBinContent(x+1,y+1)
			soupBin = soupTh2.GetBinContent(x+1,y+1)
			refErr = refTh2.GetBinError(x+1,y+1)
			soupErr = soupTh2.GetBinError(x+1,y+1)
			newEffHisto.SetBinContent(x+1,y+1, refBin*soupBin)
			newEffHisto.SetBinError(x+1,y+1,rt.TMath.Sqrt(refBin*refBin*soupErr*soupErr+soupBin*soupBin*refErr*refErr))
	return newEffHisto

def getEfficiency(th2,name):
	newHisto = th2.Clone()
	newHisto.SetDefaultSumw2()
	newHisto.SetName(name)
	return newHisto
def getDiff(th2a,th2b,name):
	newHisto = th2a.Clone()
	newHisto.SetDefaultSumw2()
	newHisto.Add(th2b,-1)
	newHisto.SetName(name)
	return newHisto

def main():
	for year in ['2017','2018']:	
		f1 = rt.TFile.Open("eff_"+ref+".root")
		observables = ["pt","eta"]
		samples = ["data","DY"]
		types = ["ref","soup"]
		f2 = rt.TFile.Open("final.root","RECREATE")
		c2 = rt.TCanvas("c1","c1",2000,1200)
		rt.gStyle.SetPaintTextFormat("1.5f");
		h_tmp_pt = rt.TH2F()
		h_tmp_eta = rt.TH2F()
		for anObs in observables:
			for aSample in samples:
				print "efficiencies_ref_"+year+aSample+"_"+anObs
				eventRefEff  = getEfficiency(f1.Get("efficiencies_2Dref_"+year+aSample+"_"+anObs),"efficiencies_2Dref_"+year+aSample+"_"+anObs)
				eventSoupEff = getSoupEfficiency(eventRefEff, f1.Get("efficiencies_soupMC_"+year+aSample+"_"+anObs), "eff_"+year+aSample+"_"+anObs+"_final")
				eventSoupEff.Write()
				if "data" in year+aSample:
					eventSoupEff.SetTitle("combined trigger efficiency")
					eventSoupEff.Draw("COLZ TEXTE")
					c2.Print(year+"_"+ref+"efficiencies_data_"+anObs+".png")
					if "pt" in anObs:
						h_tmp_pt = eventSoupEff.Clone()
						h_tmp_pt.SetTitle("combined trigger SF")
						print h_tmp_pt
					else:
						h_tmp_eta = eventSoupEff.Clone()
						h_tmp_eta.SetTitle("combined trigger SF")
						print h_tmp_eta

		f4 = rt.TFile.Open("Closure.root","RECREATE")
		c1 = rt.TCanvas("c1","c1",2000,1200)
		rt.gStyle.SetPaintTextFormat("1.5f");
		for anObs in observables:
			eventRef = getEfficiency(f1.Get("efficiencies_2Dref_"+year+"DY_"+anObs),"efficiencies_2Dref_"+year+"DY_"+anObs)
			eventSoup = getSoupEfficiency(eventRef, f1.Get("efficiencies_soupMC_"+year+"DY_"+anObs), "eff_soupWithRef_"+anObs+"_final")
			eventSoupTrue = getEfficiency(f1.Get("efficiencies_soupMC_"+year+"closure_"+anObs),"efficiencies_soupMC_"+year+"closure_"+anObs)
			diff = getDiff(eventSoup,eventSoupTrue,"diff_"+anObs+"_final")
			if not 'pt' in anObs:
				eventRef.GetXaxis().SetTitle("|#eta| leading #mu")
				eventRef.GetYaxis().SetTitle("|#eta| subleading #mu")
				eventRef.SetTitle("reference trigger efficiency")
				eventSoup.GetXaxis().SetTitle("|#eta| leading #mu")
				eventSoup.GetYaxis().SetTitle("|#eta| subleading #mu")
				eventSoup.SetTitle("combined trigger efficiency")
				eventSoupTrue.GetXaxis().SetTitle("|#eta| leading #mu")
				eventSoupTrue.GetYaxis().SetTitle("|#eta| subleading #mu")
				eventSoupTrue.SetTitle("MC truth efficiency")
				diff.GetXaxis().SetTitle("|#eta| leading #mu")
				diff.GetYaxis().SetTitle("|#eta| subleading #mu")
				diff.SetTitle("MC closure difference")
				h_tmp_eta.GetXaxis().SetTitle("|#eta| leading #mu")
				h_tmp_eta.GetYaxis().SetTitle("|#eta| subleading #mu")
				h_eta = h_tmp_eta.Clone()
				h_eta.Add(eventSoup,-1)
				h_tmp_eta.Divide(eventSoup)

			else:
				eventRef.GetXaxis().SetTitle("pt leading #mu")
				eventRef.GetYaxis().SetTitle("pt subleading #mu")
				eventSoup.GetXaxis().SetTitle("pt leading #mu")
				eventSoup.GetYaxis().SetTitle("pt subleading #mu")
				eventSoupTrue.GetXaxis().SetTitle("pt leading #mu")
				eventSoupTrue.GetYaxis().SetTitle("pt subleading #mu")
				diff.GetXaxis().SetTitle("pt leading #mu")
				diff.GetYaxis().SetTitle("pt subleading #mu")
				h_tmp_pt.GetXaxis().SetTitle("pt leading #mu")
				h_tmp_pt.GetYaxis().SetTitle("pt subleading #mu")
				h_pt = h_tmp_pt.Clone()
				h_tmp_pt.Divide(eventSoup)
				h_pt.Add(eventSoup,-1)
			eventRef.Write()
			eventSoup.Write()
			eventSoup.Draw("COLZ TEXTE")
			c1.Print(year+"_"+ref+"eff_MCcombined_"+anObs+"_final.png")
			eventSoupTrue.Write()
			eventSoupTrue.Draw("COLZ TEXTE")
			c1.Print(year+"_"+ref+"eff_MCTrue_"+anObs+"_final.png")
			diff.Write()
			diff.Draw("COLZ TEXTE")
			c1.Print(year+"_"+ref+"closure_diff_"+anObs+"_final.png")
		h_tmp_eta.Draw("COLZ TEXTE")
		c1.Print(year+"_"+ref+"sf_eta.png")


		f1.Close()
		f2.Close()
		f4.Close()
if __name__ == '__main__':

	refs = ['Mu17', 'DoubleIsoMu17Mu8_IsoMu17leg', 'DoubleIsoMu17Mu8_IsoMu8leg', 'DoubleIsoMu17Mu8_Mu17leg','DoubleIsoMu17Mu8_Mu8leg']
	for ref in refs:
		main()
