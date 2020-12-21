#!/bin/env python

import ROOT as root
from ROOT import gROOT, TCanvas, TF1
c1 = TCanvas( 'c1', 'Graph', 200, 10, 700, 500 )

file1=root.TFile("Met_tau/W+Jets.root")
file2=root.TFile("Met_WJets/W+Jets.root")
file3=root.TFile("Emulated_WJets/W+Jets.root")

h1=file1.Get("METCut/Tau1MetMt")
h2=file2.Get("METCut/Tau1MetMt")
h3=file3.Get("METCut/Tau1MetMt")

h1.SetLineColor(1)
h2.SetLineColor(2)
h3.SetLineColor(4)
h1.SetLineWidth(2)
h2.SetLineWidth(2)
h3.SetLineWidth(2)

l=[h1,h2,h3]
first=""
for h in l:
    print (h)
    print (h.Integral())
   # h.Scale(1./h.Integral())    
    h.Draw(first)
    print (h.Integral())
    first="same"

c1.Update()
c1.Draw()

input()
