import yaml

config  ={}
config['sample'] = ['2017DYnoPUreweighting','2018DYnoPUreweighting','2017RunB','2017RunC','2017RunD','2017RunE','2017RunF','2017data','2017DY','2018RunA','2018RunB','2018RunC','2018RunD','2018DY','2018data','2017closure','2018closure']
#config['sample'] = ['2017DY']
config['observable'] = ['pt','abseta']
config['binning'] = {'pt':[25,50,50,75,100,150,200],
                     'abseta':[0.0,0.6,1.2,1.8,2.4]}
config['ref'] = ['Mu17', 'DoubleIsoMu17Mu8_IsoMu17leg', 'DoubleIsoMu17Mu8_IsoMu8leg', 'DoubleIsoMu17Mu8_Mu17leg','DoubleIsoMu17Mu8_Mu8leg']
print(yaml.dump(config))
with open(r'config.yaml', 'w') as f:
  yaml.dump(config, f)
