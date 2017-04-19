#include "uti.h"

TGraphAsymmErrors* gCUJETD5TeV;
TGraph* gShanshanD5TeV;
TGraphErrors* gMagdalenaD5TeV;
TGraphErrors* gPHSDWOShadowing;
TGraphErrors* gPHSDWShadowing;
TGraph* gIvanD5TeV;
TGraphErrors* gADSCFT1D5TeV;
TGraphErrors* gADSCFT2D5TeV;

//void fillgadscft(TString datfile, TGraphErrors* gadscft);
TGraphErrors* fillgadscft(TString datfile);
void drawTheory0100()
{
  gStyle->SetHatchesLineWidth(3);

  // CUJET
  TFile* infCUJETD5TeV = new TFile("TheoryPredictions/CUJET_D0_RAA_0_100.root");
  gCUJETD5TeV = (TGraphAsymmErrors*)infCUJETD5TeV->Get("gRAADmeson5TeV");
  gCUJETD5TeV->SetLineWidth(1);
  gCUJETD5TeV->SetLineColor(0);//4
  gCUJETD5TeV->SetFillColor(kAzure-1);//4
  gCUJETD5TeV->SetFillColorAlpha(kAzure-2,0.6);
  gCUJETD5TeV->SetFillStyle(3481);//3001
  // Shanshan
  gShanshanD5TeV = new TGraph("TheoryPredictions/Shanshan-D-RAA_PbPb5020_00-80.dat");
  gShanshanD5TeV->SetLineWidth(3);
  gShanshanD5TeV->SetLineColor(kRed+1);
  // Magdalena
  gMagdalenaD5TeV = new TGraphErrors("TheoryPredictions/Magdalena-5TeV-0100-plot2.txt");
  gMagdalenaD5TeV->SetLineWidth(3);
  gMagdalenaD5TeV->SetLineColor(kRed-7);//kCyan+1
  gMagdalenaD5TeV->SetFillColor(kRed-4);//kCyan+1
  gMagdalenaD5TeV->SetFillColorAlpha(kRed-4,0.5);//kCyan+1
  gMagdalenaD5TeV->SetFillStyle(3344);//3004

  // ADSCFT 1
  gADSCFT1D5TeV = fillgadscft("TheoryPredictions/RAA_5TeV_0080_D0_DiffusionConstant_band.dat");
  gADSCFT1D5TeV->SetName("gADSCFT1D5TeV");
  gADSCFT1D5TeV->SetLineColor(0);
  gADSCFT1D5TeV->SetFillColor(kOrange+1);//kGreen-2
  gADSCFT1D5TeV->SetFillColorAlpha(kOrange+1,0.6);//kGreen-2
  gADSCFT1D5TeV->SetFillStyle(3325);
  // ADSCFT 2
  gADSCFT2D5TeV = fillgadscft("TheoryPredictions/RAA_5TeV_0080_D0_DiffusionDynamic_band.dat");
  gADSCFT2D5TeV->SetName("gADSCFT2D5TeV");
  gADSCFT2D5TeV->SetLineColor(0);//kViolet-8
  gADSCFT2D5TeV->SetFillColor(kPink-9);//kViolet-8
  gADSCFT2D5TeV->SetFillColorAlpha(kPink-9,0.6);//kViolet-8
  gADSCFT2D5TeV->SetFillStyle(3352);

  //
  gADSCFT1D5TeV->Draw("4 same");
  gMagdalenaD5TeV->Draw("f same");
  gMagdalenaD5TeV->Draw("l same");
  gCUJETD5TeV->Draw("3 same");
  gShanshanD5TeV->Draw("c same");
  gADSCFT2D5TeV->Draw("4 same");
}

void drawTheory010(Int_t isTheoryComparison)
{
  gStyle->SetHatchesLineWidth(3);

  // CUJET
  TFile* infCUJETD5TeV = new TFile("TheoryPredictions/CUJET_D0_RAA_0_10.root");
  gCUJETD5TeV = (TGraphAsymmErrors*)infCUJETD5TeV->Get("gRAADmeson5TeV");
  gCUJETD5TeV->SetLineWidth(1);
  gCUJETD5TeV->SetLineColor(0);//4
  gCUJETD5TeV->SetFillColor(kAzure-1);//4
  gCUJETD5TeV->SetFillColorAlpha(kAzure-2,0.6);
  gCUJETD5TeV->SetFillStyle(3481);//3001
  // Shanshan
  gShanshanD5TeV = new TGraph("TheoryPredictions/Shanshan-D-RAA_PbPb5020_00-10.dat");
  gShanshanD5TeV->SetLineWidth(3);
  gShanshanD5TeV->SetLineColor(kRed+1);
  // Magdalena
  gMagdalenaD5TeV = new TGraphErrors("TheoryPredictions/Magdalena-5TeV-plot2.txt");
  gMagdalenaD5TeV->SetLineWidth(3);
  gMagdalenaD5TeV->SetLineColor(kRed-7);//kCyan+1
  gMagdalenaD5TeV->SetFillColor(kRed-4);//kCyan+1
  gMagdalenaD5TeV->SetFillColorAlpha(kRed-4,0.5);//kCyan+1
  gMagdalenaD5TeV->SetFillStyle(3344);//3004
  // PHSD w/o shadowing
  gPHSDWOShadowing = new TGraphErrors("TheoryPredictions/phsd502TeVWoShadowing.txt");
  gPHSDWOShadowing->SetLineColor(kAzure-6);//kGreen+2
  gPHSDWOShadowing->SetLineWidth(3);
  gPHSDWOShadowing->SetLineStyle(2);
  // PHSD w/ shadowing
  gPHSDWShadowing = new TGraphErrors("TheoryPredictions/phsd502TeVWShadowing.txt");
  gPHSDWShadowing->SetLineColor(kAzure-6);//kGreen+2
  gPHSDWShadowing->SetLineWidth(3);
  gPHSDWShadowing->SetLineStyle(1);
  // Ivan 
  gIvanD5TeV = new TGraph("TheoryPredictions/R-PbPb_cen_cron1.5_eloss1.5.5100GeVD0.txt");
  gIvanD5TeV->SetLineColor(kViolet+1);//kViolet
  gIvanD5TeV->SetFillColor(kViolet+1);//kViolet
  gIvanD5TeV->SetFillColorAlpha(kViolet+1,0.5);
  gIvanD5TeV->SetFillStyle(3358);//3011
  gIvanD5TeV->SetLineWidth(3);

  // ADSCFT 1
  gADSCFT1D5TeV = fillgadscft("TheoryPredictions/RAA_5TeV_0010_D0_DiffusionConstant_band.dat");
  gADSCFT1D5TeV->SetName("gADSCFT1D5TeV");
  gADSCFT1D5TeV->SetLineColor(0);
  gADSCFT1D5TeV->SetFillColor(kOrange+1);//kGreen-2
  gADSCFT1D5TeV->SetFillColorAlpha(kOrange+1,0.6);//kGreen-2
  gADSCFT1D5TeV->SetFillStyle(3325);
  // ADSCFT 2
  gADSCFT2D5TeV = fillgadscft("TheoryPredictions/RAA_5TeV_0010_D0_DiffusionDynamic_band.dat");
  gADSCFT2D5TeV->SetName("gADSCFT2D5TeV");
  gADSCFT2D5TeV->SetLineColor(0);//kViolet-8
  gADSCFT2D5TeV->SetFillColor(kPink-9);//kViolet-8
  gADSCFT2D5TeV->SetFillColorAlpha(kPink-9,0.6);//kViolet-8
  gADSCFT2D5TeV->SetFillStyle(3352);

  if(isTheoryComparison==1||isTheoryComparison==2)
    {
      gMagdalenaD5TeV->Draw("f same");
      gMagdalenaD5TeV->Draw("l same");
      gIvanD5TeV->Draw("f same");
      gIvanD5TeV->Draw("l same");
      gCUJETD5TeV->Draw("3 same");
    }
  if (isTheoryComparison==1||isTheoryComparison==3)
    {
      gADSCFT1D5TeV->Draw("4 same");
      gPHSDWShadowing->Draw("c same");
      gPHSDWOShadowing->Draw("c same");
      gShanshanD5TeV->Draw("c same");
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
