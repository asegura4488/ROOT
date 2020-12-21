import ROOT 

f1 = ROOT.TF1("f1", 'sin(x)/x', -20.,20)
f1.Draw()


input()
