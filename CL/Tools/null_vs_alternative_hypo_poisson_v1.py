#!/usr/bin/env python

import numpy as np
from scipy.stats import poisson
from matplotlib import pyplot as plt

# define distributions parameters
mu_values = [4, 15] # mean values of the poisson distribution
linestyles = ['-', '-']
colours = ['green', 'red']# null hypothesis: green /alternative hypothesis: red

# define figure dimensions
fig, ax = plt.subplots(figsize=(5, 3.75))

for mu, ls, cs in zip(mu_values, linestyles, colours):
    # create a poisson distribution
    dist = poisson(mu)
    x = np.arange(0, 30)
    plt.plot(x, dist.pmf(x), ls=ls, color=cs,
             label=r'$\lambda=%i$' % mu, linestyle='solid')

plt.xlim(0., 30)
plt.ylim(0, 0.218)
plt.xlabel('$N_{ev}$')
plt.ylabel('arbitrary')
# plt.title('Poisson Distribution')
plt.legend()
plt.savefig('bgd_plus_s_v1_py.png', bbox_inches='tight')
plt.show()

#plt.fill_between(x=np.arange(0,1,0.01), 
#                 y1= stats.expon.pdf(np.arange(0,1,0.01)) ,
#                 facecolor='blue',
#                 alpha=0.35)

#import ROOT
#from ROOT import gROOT
#from ROOT import TCanvas, TPad, TFormula, TF1, TPaveLabel, TGraph
#from ROOT import TH1F, TH2F, TFile, gPad, gStyle, TLine, TLatex
#from ROOT import kGreen, kRed, kOrange

#gStyle.SetOptStat(0);

# define canvas
#c1 = TCanvas( 'gauss', 'gauss', 800, 400)

# define histo
#h  = TH1F( 'h_work', ';N_{ev};arbitrary', 60, 0, 30.)
#h.SetMaximum(0.218);

# define function: null hypothesis
#fga  = TF1('fga','TMath::Poisson(x,[0])', 0, 30);
#fga.SetLineColor(kGreen);
#fga.SetParameter( 0, 4.0);

# define function: alternative hypothesis
#falt = TF1('falt','TMath::Poisson(x,[0])', 0, 30);
#falt.SetLineColor(kRed);
#falt.SetParameter( 0, 15);

#print "CL_s+b(x=7; lambda) =",  "%.3f" % falt.Integral(-50,7) 
#print "CL_b(x=7; lambda) =",  "%.3f" % fga.Integral(7,50)

#g = TGraph(1);
#g.SetFillColor(4);
#a = TGraph(1);
#a.SetFillColor(5);

#for i in range(0,101):
#    g.SetPoint(i, 7+6.*i/100., fga.Eval(7+6.*i/100.))
#    a.SetPoint(i, 7-7.*i/100., falt.Eval(7-7.*i/100.))

#g.SetPoint(101,11,0);
#g.SetPoint(102,7,0);
#a.SetPoint(101,3,0);
#a.SetPoint(102,7,0);
   
#line = TLine() 
#line.SetLineWidth(4);

#text = TLatex()
#text.SetTextSize(0.04);
#text.SetTextColor(1);

#h.Draw();

#text.SetTextSize(0.04);   
#text.SetTextColor( kGreen - 6);
#text.DrawLatex(5., 0.18, "Null-Hypothesis (background-only):  #lambda_{b} = 4");
#text.SetTextColor(1);
#text.DrawLatex(5.6,0.144, "Observation d = 7");   
#text.SetTextColor(4);
#text.SetTextSize(0.06);   
#text.DrawLatex(7.8,0.048, "#alpha");   

#g.Draw("lf,same");
#a.Draw("lf,same");
#fga.Draw("l,same");
#falt.Draw("l,same");

#text.SetTextColor(kOrange);
#text.DrawLatex(6,0.012, "#beta");
#text.SetTextColor(kRed);
#text.SetTextSize(0.04);   
#text.DrawLatex(10.8, 0.121, "Alternative hypothesis: #lambda_{s+b} = 15");
#text.DrawLatex(12, 0.11, "(signal + background)");
#line.DrawLine(7,0.14,7,0.0);
#gPad.RedrawAxis();

#c1.SaveAs("bgd_plus_s_py.pdf");
