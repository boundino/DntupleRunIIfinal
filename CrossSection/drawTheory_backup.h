#include "uti.h"

TGraphAsymmErrors* gCUJETD5TeV;
TGraph* gShanshanD5TeV;
TGraph* gMagdalenaD5TeV;
TGraphErrors* gPHSDWOShadowing;
TGraphErrors* gPHSDWShadowing;
TGraph* gIvanD5TeV;
TGraphErrors* gADSCFT1D5TeV;
TGraphErrors* gADSCFT2D5TeV;

//void fillgadscft(TString datfile, TGraphErrors* gadscft);
TGraphErrors* fillgadscft(TString datfile);
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
  //gMagdalenaD5TeV->SetLineColor(kCyan+2);
  //gMagdalenaD5TeV->SetFillColor(kCyan+2);
  gMagdalenaD5TeV->SetLineColor(kCyan+1);
  gMagdalenaD5TeV->SetFillColor(kCyan+1);
  gMagdalenaD5TeV->SetFillStyle(3004);

  gStyle->SetHatchesLineWidth(3);

  // ADSCFT 1
  gADSCFT1D5TeV = fillgadscft("TheoryPredictions/RAA_5TeV_0080_D0_DiffusionConstant_band.dat");
  gADSCFT1D5TeV->SetName("gADSCFT1D5TeV");
  gADSCFT1D5TeV->SetLineColor(kGreen-2);
  gADSCFT1D5TeV->SetFillColor(kGreen-2);
  gADSCFT1D5TeV->SetFillColorAlpha(kGreen-2,0.5);
  gADSCFT1D5TeV->SetFillStyle(3325);
  // ADSCFT 2
  gADSCFT2D5TeV = fillgadscft("TheoryPredictions/RAA_5TeV_0080_D0_DiffusionDynamic_band.dat");
  gADSCFT2D5TeV->SetName("gADSCFT2D5TeV");
  gADSCFT2D5TeV->SetLineColor(kViolet-8);
  gADSCFT2D5TeV->SetFillColor(kViolet-8);
  gADSCFT2D5TeV->SetFillColorAlpha(kViolet-8,0.5);
  gADSCFT2D5TeV->SetFillStyle(3352);

  //
  gCUJETD5TeV->Draw("3 same");
  gShanshanD5TeV->Draw("c same");
  gMagdalenaD5TeV->Draw("f same");
  gMagdalenaD5TeV->Draw("l same");
  gADSCFT1D5TeV->Draw("4 same");
  gADSCFT2D5TeV->Draw("4 same");
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
  gIvanD5TeV = new TGraph("TheoryPredictions/R-PbPb_cen_cron1.5_eloss1.5.5100GeVD0.txt");
  gIvanD5TeV->SetLineColor(kViolet);
  gIvanD5TeV->SetFillColor(kViolet);
  gIvanD5TeV->SetFillStyle(3011);
  gIvanD5TeV->SetLineWidth(3);

  gStyle->SetHatchesLineWidth(3);

  // ADSCFT 1
  gADSCFT1D5TeV = fillgadscft("TheoryPredictions/RAA_5TeV_0010_D0_DiffusionConstant_band.dat");
  gADSCFT1D5TeV->SetName("gADSCFT1D5TeV");
  gADSCFT1D5TeV->SetLineColor(kGreen-2);
  gADSCFT1D5TeV->SetFillColor(kGreen-2);
  gADSCFT1D5TeV->SetFillColorAlpha(kGreen-2,0.5);
  gADSCFT1D5TeV->SetFillStyle(3325);
  // ADSCFT 2
  gADSCFT2D5TeV = fillgadscft("TheoryPredictions/RAA_5TeV_0010_D0_DiffusionDynamic_band.dat");
  gADSCFT2D5TeV->SetName("gADSCFT2D5TeV");
  gADSCFT2D5TeV->SetLineColor(kViolet-8);
  gADSCFT2D5TeV->SetFillColor(kViolet-8);
  gADSCFT2D5TeV->SetFillColorAlpha(kViolet-8,0.5);
  gADSCFT2D5TeV->SetFillStyle(3352);

  if(isTheoryComparison==1||isTheoryComparison==2)
    {
      gCUJETD5TeV->Draw("3 same");
      gMagdalenaD5TeV->Draw("f same");
      gMagdalenaD5TeV->Draw("l same");
      gIvanD5TeV->Draw("f same");
      gIvanD5TeV->Draw("l same");
    }
  if (isTheoryComparison==1||isTheoryComparison==3)
    {
      gPHSDWShadowing->Draw("c same");
      gPHSDWOShadowing->Draw("c same");
      gShanshanD5TeV->Draw("c same");
      gADSCFT1D5TeV->Draw("4 same");
      gADSCFT2D5TeV->Draw("4 same");
    }

}

TGraphErrors* fillgadscft(TString datfile)
{
  const int n = 1000;
  Float_t bCx[n],bCy[n],bCye[n],bDummy[n];
  Int_t nbin=0;
  ifstream getadscft(datfile);
  if(!getadscft.is_open()) cout<<"Opening the file fails: ADS/CFT DiffusionConstant"<<endl;
  nbin=0;
  while(!getadscft.eof())
    {
      getadscft>>bCx[nbin]>>bCy[nbin]>>bDummy[nbin]>>bCye[nbin];
      nbin++;
    }
  bCx[nbin] = bCx[nbin-1];
  bCy[nbin] = bCy[nbin-1];
  bCye[nbin] = bCye[nbin-1];
  nbin++;
  Float_t* aADSCFTD5TeVx = new Float_t[nbin];
  Float_t* aADSCFTD5TeVxe = new Float_t[nbin];
  Float_t* aADSCFTD5TeVy = new Float_t[nbin];
  Float_t* aADSCFTD5TeVye = new Float_t[nbin];
  for(int i=0;i<nbin;i++)
    {
      aADSCFTD5TeVx[i] = bCx[i];
      aADSCFTD5TeVxe[i] = 0;
      aADSCFTD5TeVy[i] = bCy[i];
      aADSCFTD5TeVye[i] = bCye[i];
    }
  getadscft.close();
  getadscft.clear();

  TGraphErrors* gadscft = new TGraphErrors(nbin, aADSCFTD5TeVx, aADSCFTD5TeVy, aADSCFTD5TeVxe, aADSCFTD5TeVye);
  return gadscft;
}
