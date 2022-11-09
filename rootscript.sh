#!/bin/sh

ROOT_SCRIPT='\
TH1D histD ("histD", "; N", 11, -0.5, 10.5);\
TH1D histP ("histP", "; N", 11, -0.5, 10.5);\
TTree tD; TTree tP;\
tD.ReadFile("hist.txt", "N/I:counts/I");\
tP.ReadFile("histpoi.txt", "N/I:counts/F");\
tD.Draw("N>>histD", "counts", "hist");\
tP.Draw("N>>histP", "counts", "hist");\
gStyle->SetOptStat(0);\
histD.Draw("hist");\
histP.SetLineColor(kRed);\
histP.Draw("hist,same");'

root -e "$ROOT_SCRIPT"
