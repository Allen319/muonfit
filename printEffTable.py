import ROOT as rt
from prettytable import PrettyTable

Runs = {'2017':['RunB','RunC','RunD','RunE','RunF','data','DY','closure'],'2018':['RunA','RunB','RunC','RunD','data','DY','closure']}


f1 = rt.TFile("eff_Mu17.root")

table = PrettyTable(['Run','Mu17','Soup|Mu17','Combined'])
for year in Runs:
	for Run in Runs[year]:
		h=f1.Get("efficiencies_total_"+year+Run)
		refEff=h.GetBinContent(2)
		refErr=h.GetBinError(2)
		soupEff=h.GetBinContent(1)
		soupErr=h.GetBinError(1)
		ref2DEff=1-(1-refEff)*(1-refEff)
		ref2DErr=abs(2-2*refEff)*refErr
		combEff=ref2DEff*soupEff*100
		combErr=pow(pow(soupEff,2)*pow(ref2DErr,2)+(pow(soupErr,2)*pow(ref2DEff,2)),0.5)*100
		refEff=refEff*100
		refErr=refErr*100
		soupEff=soupEff*100
		soupErr=soupErr*100
		if 'closure' in Run:

		
			table.add_row([year+Run,'---','---','%.4f'%soupEff +'+-'+'%.4f'%soupErr ])
		elif 'data' in Run:
			table.add_row([year+Run,'---','---','%.4f'%soupEff +'+-'+'%.4f'%soupErr ])
		else:
			table.add_row([year+Run,'%.4f'%refEff +'+-'+'%.4f'%refErr ,'%.4f'%soupEff +'+-'+'%.4f'%soupErr ,'%.4f'%combEff +'+-'+'%.4f'%combErr ])
table.align[1] = 'l'
table.border = True
table.junction_char='+'
table.horizontal_char = '-'
table.vertical_char = '|'
print(table)

