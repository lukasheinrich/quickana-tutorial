import ROOT
import glob
glob.glob('submitDir/hist-*root*')
f = ROOT.TFile.Open(glob.glob('submitDir/hist-*root*')[0])
muons = f.Get('nmuons')
c = ROOT.TCanvas()
muons.Draw()
c.SaveAs('submitDir/plot.png')