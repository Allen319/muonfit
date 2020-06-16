reference=(Mu17 DoubleIsoMu17Mu8_IsoMu17leg DoubleIsoMu17Mu8_Mu17leg DoubleIsoMu17Mu8_IsoMu8leg DoubleIsoMu17Mu8_Mu8leg)
for ref in $reference
do
  hadd eff_$ref".root" *$ref".root"
done
