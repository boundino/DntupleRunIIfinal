#include "uti.h"

TGraphAsymmErrors* gCUJETD5TeV;
TGraph* gShanshanD5TeV;
TGraph* gMagdalenaD5TeV;
TGraphErrors* gPHSDWOShadowing;
TGraphErrors* gPHSDWShadowing;
TGraph* gIvan5TeV;

void drawTheory0100()
{
  // CUJET
  TFile* infCUJETD5TeV = new TFile("TheoryPredictions/CUJET_D0_RAA_0_100.root");
  gCUJETD5TeV = (TGraphAsymmErrors*)infCUJETD5TeV->Get("gRAADmeson5TeV");
  gCUJETD5TeV->SetLineWidth(1);
  gCUJETD5TeV->SetLineColor(4);
  gCUJETD5TeV->SetFillColor(4);
  gCUJETD5TeV->SetFillStyle(3001);
  // Shanshan
  gShanshanD5TeV = new TGraph("TheoryPredictions/Shanshan-D-RAA_PbPb5020_00-80.dat");
  gShanshanD5TeV->SetLineWidth(3);
  gShanshanD5TeV->SetLineColor(kRed+1);
  // Magdalena
  gMagdalenaD5TeV = new TGraph("TheoryPredictions/Magdalena-5TeV-0100-plot2.txt");
  gMagdalenaD5TeV->SetLineWidth(3);
  gMagdalenaD5TeV->SetLineColor(kCyan+1);
  gMagdalenaD5TeV->SetFillColor(kCyan+1);
  gMagdalenaD5TeV->SetFillStyle(3004);

  //
  gCUJETD5TeV->Draw("3 same");
  gShanshanD5TeV->Draw("c same");
  gMagdalenaD5TeV->Draw("f same");
  gMagdalenaD5TeV->Draw("l same");

}

void drawTheory010(Int_t isTheoryComparison)
{
  // CUJET
  TFile* infCUJETD5TeV = new TFile("TheoryPredictions/CUJET_D0_RAA_0_10.root");
  gCUJETD5TeV = (TGraphAsymmErrors*)infCUJETD5TeV->Get("gRAADmeson5TeV");
  gCUJETD5TeV->SetLineWidth(1);
  gCUJETD5TeV->SetLineColor(4);
  gCUJETD5TeV->SetFillColor(4);
  gCUJETD5TeV->SetFillStyle(3001);
  // Shanshan
  gShanshanD5TeV = new TGraph("TheoryPredictions/Shanshan-D-RAA_PbPb5020_00-10.dat");
  gShanshanD5TeV->SetLineWidth(3);
  gShanshanD5TeV->SetLineColor(kRed+1);
  // Magdalena
  gMagdalenaD5TeV = new TGraph("TheoryPredictions/Magdalena-5TeV-plot2.txt");
  gMagdalenaD5TeV->SetLineWidth(3);
  gMagdalenaD5TeV->SetLineColor(kCyan+1);
  gMagdalenaD5TeV->SetFillColor(kCyan+1);
  gMagdalenaD5TeV->SetFillStyle(3004);
  // PHSD w/o shadowing
  gPHSDWOShadowing = new TGraphErrors("TheoryPredictions/phsd502TeVWoShadowing.txt");
  gPHSDWOShadowing->SetLineColor(kGreen+2);
  gPHSDWOShadowing->SetLineWidth(3);
  gPHSDWOShadowing->SetLineStyle(2);
  // PHSD w/ shadowing
  gPHSDWShadowing = new TGraphErrors("TheoryPredictions/phsd502TeVWShadowing.txt");
  gPHSDWShadowing->SetLineColor(kGreen+2);
  gPHSDWShadowing->SetLineWidth(3);
  // Ivan 
  gIvan5TeV = new TGraph("TheoryPredictions/R-PbPb_cen_cron1.5_eloss1.5.5100GeVD0.txt");
  gIvan5TeV->SetLineColor(kViolet);
  gIvan5TeV->SetFillColor(kViolet);
  gIvan5TeV->SetFillStyle(3011);
  gIvan5TeV->SetLineWidth(3);
  if(isTheoryComparison==1||isTheoryComparison==2)
    {
      gCUJETD5TeV->Draw("3 same");
      gMagdalenaD5TeV->Draw("f same");
      gMagdalenaD5TeV->Draw("l same");
      gIvan5TeV->Draw("f same");
      gIvan5TeV->Draw("l same");
    }
  if (isTheoryComparison==1||isTheoryComparison==3)
    {
      gPHSDWShadowing->Draw("c same");
      gPHSDWOShadowing->Draw("c same");
      gShanshanD5TeV->Draw("c same");
    }

}
