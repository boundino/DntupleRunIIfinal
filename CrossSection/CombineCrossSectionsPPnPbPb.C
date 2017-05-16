using namespace std;
#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"
#include "systematics.h"

void CombineCrossSectionsPPnPbPb(TString filePPMB, TString filePP, TString filePbPb0100MB, TString filePbPb0100, TString filePbPb010MB, TString filePbPb010)
{
  void scaleNsetCrossSection(TH1D* hSigmaStat, TGraphAsymmErrors* gaeCrossSyst, Double_t fscale, Int_t pcolor, Int_t pstyle);

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TFile* infilePPMB = new TFile(filePPMB.Data());  
  TGraphAsymmErrors* gaeRatioCrossFONLLstatMB = (TGraphAsymmErrors*)infilePPMB->Get("gaeRatioCrossFONLLstat");
  TGraphAsymmErrors* gaeRatioCrossFONLLsystMB = (TGraphAsymmErrors*)infilePPMB->Get("gaeRatioCrossFONLLsyst");
  TGraphAsymmErrors* gaeBplusReferenceMB = (TGraphAsymmErrors*)infilePPMB->Get("gaeSigmaDzero");
  TGraphAsymmErrors* gaeRatioCrossFONLLunityMB = (TGraphAsymmErrors*)infilePPMB->Get("gaeRatioCrossFONLLunity");

  TGraphAsymmErrors* gaeCrossPPSystMB = (TGraphAsymmErrors*)infilePPMB->Get("gaeCrossSyst");
  gaeCrossPPSystMB->SetName("gaeCrossPPSystMB");
  TH1D* hSigmaPPStatMB = (TH1D*)infilePPMB->Get("hPtSigma");
  hSigmaPPStatMB->SetName("hSigmaPPStatMB");
  TFile* infilePbPb0100MB = new TFile(filePbPb0100MB.Data());  
  TGraphAsymmErrors* gaeCrossPbPb0100SystMB = (TGraphAsymmErrors*)infilePbPb0100MB->Get("gaeCrossSyst");
  gaeCrossPbPb0100SystMB->SetName("gaeCrossPbPb0100SystMB");
  TH1D* hSigmaPbPb0100StatMB = (TH1D*)infilePbPb0100MB->Get("hPtSigma");
  hSigmaPbPb0100StatMB->SetName("hSigmaPbPb0100StatMB");
  TFile* infilePbPb010MB = new TFile(filePbPb010MB.Data());  
  TGraphAsymmErrors* gaeCrossPbPb010SystMB = (TGraphAsymmErrors*)infilePbPb010MB->Get("gaeCrossSyst");
  gaeCrossPbPb010SystMB->SetName("gaeCrossPbPb010SystMB");
  TH1D* hSigmaPbPb010StatMB = (TH1D*)infilePbPb010MB->Get("hPtSigma");
  hSigmaPbPb010StatMB->SetName("hSigmaPbPb010StatMB");

  TFile* infilePP = new TFile(filePP.Data());  
  TGraphAsymmErrors* gaeRatioCrossFONLLstat = (TGraphAsymmErrors*)infilePP->Get("gaeRatioCrossFONLLstat");
  TGraphAsymmErrors* gaeRatioCrossFONLLsyst = (TGraphAsymmErrors*)infilePP->Get("gaeRatioCrossFONLLsyst");
  TGraphAsymmErrors* gaeBplusReference = (TGraphAsymmErrors*)infilePP->Get("gaeSigmaDzero");
  TGraphAsymmErrors* gaeRatioCrossFONLLunity = (TGraphAsymmErrors*)infilePP->Get("gaeRatioCrossFONLLunity");

  TGraphAsymmErrors* gaeCrossPPSyst = (TGraphAsymmErrors*)infilePP->Get("gaeCrossSyst");
  gaeCrossPPSyst->SetName("gaeCrossPPSyst");
  TH1D* hSigmaPPStat = (TH1D*)infilePP->Get("hPtSigma");
  hSigmaPPStat->SetName("hSigmaPPStat");
  TFile* infilePbPb0100 = new TFile(filePbPb0100.Data());  
  TGraphAsymmErrors* gaeCrossPbPb0100Syst = (TGraphAsymmErrors*)infilePbPb0100->Get("gaeCrossSyst");
  gaeCrossPbPb0100Syst->SetName("gaeCrossPbPb0100Syst");
  TH1D* hSigmaPbPb0100Stat = (TH1D*)infilePbPb0100->Get("hPtSigma");
  hSigmaPbPb0100Stat->SetName("hSigmaPbPb0100Stat");
  TFile* infilePbPb010 = new TFile(filePbPb010.Data());  
  TGraphAsymmErrors* gaeCrossPbPb010Syst = (TGraphAsymmErrors*)infilePbPb010->Get("gaeCrossSyst");
  gaeCrossPbPb010Syst->SetName("gaeCrossPbPb010Syst");
  TH1D* hSigmaPbPb010Stat = (TH1D*)infilePbPb010->Get("hPtSigma");
  hSigmaPbPb010Stat->SetName("hSigmaPbPb010Stat");

  // FONLL
  gaeBplusReferenceMB->SetFillColor(kOrange+1);
  gaeBplusReferenceMB->SetFillColorAlpha(kOrange+1,0.2);
  gaeBplusReferenceMB->SetFillStyle(1001);
  gaeBplusReferenceMB->SetLineWidth(2);
  gaeBplusReferenceMB->SetLineColor(kOrange+7);
  gaeBplusReference->SetFillColor(kOrange+1);
  gaeBplusReference->SetFillColorAlpha(kOrange+1,0.2);
  gaeBplusReference->SetFillStyle(1001);
  gaeBplusReference->SetLineWidth(2);
  gaeBplusReference->SetLineColor(kOrange+7);

  /* // yellow
  gaeBplusReferenceMB->SetFillColor(5);//2
  gaeBplusReferenceMB->SetFillStyle(1001);//3001 
  gaeBplusReferenceMB->SetLineWidth(1);//3
  gaeBplusReferenceMB->SetLineColor(4);//2
  gaeBplusReference->SetFillColor(5);//2
  gaeBplusReference->SetFillStyle(1001);//3001 
  gaeBplusReference->SetLineWidth(1);//3
  gaeBplusReference->SetLineColor(4);//2
  */

  gaeRatioCrossFONLLunityMB->SetFillColor(kOrange+1); //kBlue-7
  gaeRatioCrossFONLLunityMB->SetFillColorAlpha(kOrange+1,0.2);
  gaeRatioCrossFONLLunityMB->SetFillStyle(1001);
  gaeRatioCrossFONLLunityMB->SetLineWidth(2);
  gaeRatioCrossFONLLunityMB->SetLineColor(kOrange+7); //kBlue+2
  gaeRatioCrossFONLLunity->SetFillColor(kOrange+1);
  gaeRatioCrossFONLLunity->SetFillColorAlpha(kOrange+1,0.2);
  gaeRatioCrossFONLLunity->SetFillStyle(1001);
  gaeRatioCrossFONLLunity->SetLineWidth(2);
  gaeRatioCrossFONLLunity->SetLineColor(kOrange+7);

  /* // yellow
  gaeRatioCrossFONLLunityMB->SetFillColor(5);
  gaeRatioCrossFONLLunityMB->SetFillStyle(1001);
  gaeRatioCrossFONLLunityMB->SetLineWidth(1);
  gaeRatioCrossFONLLunityMB->SetLineColor(4);
  gaeRatioCrossFONLLunity->SetFillColor(5);
  gaeRatioCrossFONLLunity->SetFillStyle(1001);
  gaeRatioCrossFONLLunity->SetLineWidth(1);
  gaeRatioCrossFONLLunity->SetLineColor(4);
  */
  
  gaeRatioCrossFONLLstatMB->SetMarkerSize(1);
  gaeRatioCrossFONLLstatMB->SetLineWidth(2);
  gaeRatioCrossFONLLstatMB->SetLineColor(1);//kGreen+4 
  gaeRatioCrossFONLLstatMB->SetMarkerColor(1);//kGreen+4
  gaeRatioCrossFONLLstat->SetMarkerSize(1);
  gaeRatioCrossFONLLstat->SetLineWidth(2);
  gaeRatioCrossFONLLstat->SetLineColor(1);//kGreen+4
  gaeRatioCrossFONLLstat->SetMarkerColor(1);//kGreen+4
  
  gaeRatioCrossFONLLsystMB->SetLineWidth(3);
  gaeRatioCrossFONLLsystMB->SetLineColor(1);//kGreen+4
  gaeRatioCrossFONLLsyst->SetLineWidth(3);
  gaeRatioCrossFONLLsyst->SetLineColor(1);//kGreen+4

  // data
  cout<<"pp"<<endl;
  scaleNsetCrossSection(hSigmaPPStat, gaeCrossPPSyst, 1, 1, 20);
  scaleNsetCrossSection(hSigmaPPStatMB, gaeCrossPPSystMB, 1, 1, 20);
  cout<<"PbPb 0-100"<<endl;
  scaleNsetCrossSection(hSigmaPbPb0100Stat, gaeCrossPbPb0100Syst, 1/3., kRed+2, 21);
  scaleNsetCrossSection(hSigmaPbPb0100StatMB, gaeCrossPbPb0100SystMB, 1/3., kRed+2, 21);
  cout<<"PbPb 0-10"<<endl;
  scaleNsetCrossSection(hSigmaPbPb010Stat, gaeCrossPbPb010Syst, 1/10., kAzure+3, 22);
  scaleNsetCrossSection(hSigmaPbPb010StatMB, gaeCrossPbPb010SystMB, 1/10., kAzure+3, 22);

  //

  TH2F* hemptySigmaOnly = new TH2F("hemptySigmaOnly","",50,0.,110.,10.,0.1,1.e11); //1.1, 1.e10
  hemptySigmaOnly->GetXaxis()->CenterTitle();
  hemptySigmaOnly->GetYaxis()->CenterTitle();
  hemptySigmaOnly->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  hemptySigmaOnly->GetYaxis()->SetTitle("#frac{1}{<T_{AA}> N_{evt}} #frac{dN^{PbPb}}{dp_{T}}  #left[#frac{pb}{GeV/c}#right]");
  //hemptySigmaOnly->GetYaxis()->SetTitle("1/T_{AA} * dN / dp_{T}( pb GeV^{-1}c)");
  hemptySigmaOnly->GetXaxis()->SetTitleOffset(1.0);
  hemptySigmaOnly->GetYaxis()->SetTitleOffset(1.7861);// 1.286 before y title changes
  hemptySigmaOnly->GetXaxis()->SetTitleSize(0.039);
  hemptySigmaOnly->GetYaxis()->SetTitleSize(0.028);// 0.0385 before y title changes
  hemptySigmaOnly->GetXaxis()->SetTitleFont(42);
  hemptySigmaOnly->GetYaxis()->SetTitleFont(42);
  hemptySigmaOnly->GetXaxis()->SetLabelFont(42);
  hemptySigmaOnly->GetYaxis()->SetLabelFont(42);
  hemptySigmaOnly->GetXaxis()->SetLabelSize(0.03);
  hemptySigmaOnly->GetYaxis()->SetLabelSize(0.028);// 0.0315 before y title changes  
  hemptySigmaOnly->GetXaxis()->SetLabelOffset(0.001);
  hemptySigmaOnly->SetMaximum(2);
  hemptySigmaOnly->SetMinimum(0.);

  TH2F* hemptySigmaOnly2 = new TH2F("hemptySigmaOnly2","",50,0.,110.,10.,0.1,1.e11); //1.1, 1.e10
  hemptySigmaOnly2->GetXaxis()->CenterTitle();
  hemptySigmaOnly2->GetYaxis()->CenterTitle();
  hemptySigmaOnly2->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  hemptySigmaOnly2->GetYaxis()->SetTitle("#frac{d#sigma^{pp}}{dp_{T}}  or  #frac{1}{<T_{AA}> N_{evt}} #frac{dN^{PbPb}}{dp_{T}}  #left[#frac{pb}{GeV/c}#right]");
  //hemptySigmaOnly2->GetYaxis()->SetTitle("d#sigma / dp_{T}( pb GeV^{-1}c)");
  hemptySigmaOnly2->GetXaxis()->SetTitleOffset(1.0);
  hemptySigmaOnly2->GetYaxis()->SetTitleOffset(1.7861);// 1.286 before y title changes
  hemptySigmaOnly2->GetXaxis()->SetTitleSize(0.039);
  hemptySigmaOnly2->GetYaxis()->SetTitleSize(0.028);// 0.0385 before y title changes
  hemptySigmaOnly2->GetXaxis()->SetTitleFont(42);
  hemptySigmaOnly2->GetYaxis()->SetTitleFont(42);
  hemptySigmaOnly2->GetXaxis()->SetLabelFont(42);
  hemptySigmaOnly2->GetYaxis()->SetLabelFont(42);
  hemptySigmaOnly2->GetXaxis()->SetLabelSize(0.03);
  hemptySigmaOnly2->GetYaxis()->SetLabelSize(0.028);// 0.0315 before y title changes  
  hemptySigmaOnly2->GetXaxis()->SetLabelOffset(0.001);
  hemptySigmaOnly2->SetMaximum(2);
  hemptySigmaOnly2->SetMinimum(0.);

  TH2F* hemptySigma = new TH2F("hemptySigma","",50,0.,110.,10.,0.11,1.e11); //1.1, 1.e10
  hemptySigma->GetXaxis()->CenterTitle();
  hemptySigma->GetYaxis()->CenterTitle();
  hemptySigma->GetYaxis()->SetTitle("#frac{d#sigma^{pp}}{dp_{T}}  or  #frac{1}{<T_{AA}> N_{evt}} #frac{dN^{PbPb}}{dp_{T}}  #left[#frac{pb}{GeV/c}#right]");
  //hemptySigma->GetYaxis()->SetTitle("d#sigma / dp_{T}( pb GeV^{-1}c)");
  hemptySigma->GetXaxis()->SetTitleOffset(0.7);
  hemptySigma->GetYaxis()->SetTitleOffset(1.25);// 0.9 before y title changes
  hemptySigma->GetXaxis()->SetTitleSize(0.05);
  hemptySigma->GetYaxis()->SetTitleSize(0.040);// 0.055 before y title changes
  hemptySigma->GetXaxis()->SetTitleFont(42);
  hemptySigma->GetYaxis()->SetTitleFont(42);
  hemptySigma->GetXaxis()->SetLabelFont(42);
  hemptySigma->GetYaxis()->SetLabelFont(42);
  hemptySigma->GetXaxis()->SetLabelSize(0.04);
  hemptySigma->GetYaxis()->SetLabelSize(0.040);// 0.045 before y title changes
  hemptySigma->SetMaximum(2);
  hemptySigma->SetMinimum(0.);

  TH2F* hemptyRatio = new TH2F("hemptyRatio","",50,0.,110.,10.,0.,2.7);
  hemptyRatio->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("pp / FONLL");
  hemptyRatio->GetXaxis()->SetTitleOffset(1.0);
  hemptyRatio->GetYaxis()->SetTitleOffset(0.5455);// 0.4 before y title changes -> 0.5555
  hemptyRatio->GetXaxis()->SetTitleSize(0.13);
  hemptyRatio->GetYaxis()->SetTitleSize(0.096);// 0.12 before y title changes -> 0.096
  hemptyRatio->GetXaxis()->SetTitleFont(42);
  hemptyRatio->GetYaxis()->SetTitleFont(42);
  hemptyRatio->GetXaxis()->SetLabelFont(42);
  hemptyRatio->GetYaxis()->SetLabelFont(42);
  hemptyRatio->GetYaxis()->SetLabelOffset(0.015);
  hemptyRatio->GetXaxis()->SetLabelSize(0.1);
  hemptyRatio->GetYaxis()->SetLabelSize(0.08889);// 0.1 before y title changes -> 0.08889

  TString texper="%";

  //
  TLatex* texY = new TLatex(0.55,0.85,"|y| < 1.0, Global uncert.");
  texY->SetNDC();
  texY->SetTextFont(42);
  texY->SetTextSize(0.045);
  texY->SetLineWidth(2);
  TLatex* texYOnly = new TLatex(0.55,0.853,"|y| < 1.0, Global uncert.");
  texYOnly->SetNDC();
  texYOnly->SetTextFont(42);
  texYOnly->SetTextSize(0.0315);
  texYOnly->SetLineWidth(2);
  TLatex* texYOnly2 = new TLatex(0.55,0.895,"|y| < 1.0, Global uncert.");
  texYOnly2->SetNDC();
  texYOnly2->SetTextFont(42);
  texYOnly2->SetTextSize(0.0315);
  texYOnly2->SetLineWidth(2);

  //
  Float_t systnormPP = normalizationUncertaintyForPP();
  Float_t systnormPbPbhigh0100 = normalizationUncertaintyForPbPb(0,100);
  Float_t systnormPbPblow0100 = normalizationUncertaintyForPbPb(0,100,false);
  Float_t systnormPbPbhigh010 = normalizationUncertaintyForPbPb(0,10);
  Float_t systnormPbPblow010 = normalizationUncertaintyForPbPb(0,10,false);
  TLatex* texSystnormPP = new TLatex(0.23,0.55,Form("pp, %.1f%s",systnormPP,texper.Data()));
  texSystnormPP->SetNDC();
  texSystnormPP->SetTextFont(42);
  texSystnormPP->SetTextSize(0.045);
  texSystnormPP->SetLineWidth(2);
  TLatex* texSystnormPbPb0100 = new TLatex(0.23,0.495,Form("0-100%s (/3), + %.1f%s - %.1f%s",texper.Data(),systnormPbPbhigh0100,texper.Data(),systnormPbPblow0100,texper.Data()));
  texSystnormPbPb0100->SetNDC();
  texSystnormPbPb0100->SetTextFont(42);
  texSystnormPbPb0100->SetTextSize(0.045);
  texSystnormPbPb0100->SetLineWidth(2);
  TLatex* texSystnormPbPb010 = new TLatex(0.23,0.44,Form("0-10%s (/10), + %.1f%s - %.1f%s",texper.Data(),systnormPbPbhigh010,texper.Data(),systnormPbPblow010,texper.Data()));
  texSystnormPbPb010->SetNDC();
  texSystnormPbPb010->SetTextFont(42);
  texSystnormPbPb010->SetTextSize(0.045);
  texSystnormPbPb010->SetLineWidth(2);

  //
  TLegend* legendSigma = new TLegend(0.54,0.61,0.87,0.83,"");
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);
  TLegendEntry* ent_SigmaPPMB = legendSigma->AddEntry(hSigmaPPStatMB,Form("pp, %.1f%s",systnormPP,texper.Data()),"pf");
  ent_SigmaPPMB->SetTextFont(42);
  ent_SigmaPPMB->SetLineColor(2);
  ent_SigmaPPMB->SetMarkerColor(2);
  TLegendEntry* ent_SigmaPbPb0100MB = legendSigma->AddEntry(hSigmaPbPb0100StatMB,Form("0-100%s (/3), + %.1f%s - %.1f%s",texper.Data(),systnormPbPbhigh0100,texper.Data(),systnormPbPblow0100,texper.Data()),"pf");
  ent_SigmaPbPb0100MB->SetTextFont(42);
  ent_SigmaPbPb0100MB->SetLineColor(2);
  ent_SigmaPbPb0100MB->SetMarkerColor(2);
  TLegendEntry* ent_SigmaPbPb010MB = legendSigma->AddEntry(hSigmaPbPb010StatMB,Form("0-10%s (/10), + %.1f%s - %.1f%s",texper.Data(),systnormPbPbhigh010,texper.Data(),systnormPbPblow010,texper.Data()),"pf");
  ent_SigmaPbPb010MB->SetTextFont(42);
  ent_SigmaPbPb010MB->SetLineColor(2);
  ent_SigmaPbPb010MB->SetMarkerColor(2);
  TLegendEntry* ent_SigmaFONLL = legendSigma->AddEntry(gaeBplusReferenceMB,"FONLL pp ref.","f");
  ent_SigmaFONLL->SetTextFont(42);
  ent_SigmaFONLL->SetLineColor(5);
  ent_SigmaFONLL->SetMarkerColor(1);

  TLegend* legendSigmaOnly = new TLegend(0.54,0.762,0.87,0.839,"");
  legendSigmaOnly->SetBorderSize(0);
  legendSigmaOnly->SetLineColor(0);
  legendSigmaOnly->SetFillColor(0);
  legendSigmaOnly->SetFillStyle(1001);
  legendSigmaOnly->SetTextFont(42);
  legendSigmaOnly->SetTextSize(0.0315);
  TLegendEntry* ent_SigmaOnlyPbPb0100MB = legendSigmaOnly->AddEntry(hSigmaPbPb0100StatMB,Form("0-100%s (/3), + %.1f%s - %.1f%s",texper.Data(),systnormPbPbhigh0100,texper.Data(),systnormPbPblow0100,texper.Data()),"pf");
  ent_SigmaOnlyPbPb0100MB->SetTextFont(42);
  ent_SigmaOnlyPbPb0100MB->SetLineColor(2);
  ent_SigmaOnlyPbPb0100MB->SetMarkerColor(2);
  TLegendEntry* ent_SigmaOnlyPbPb010MB = legendSigmaOnly->AddEntry(hSigmaPbPb010StatMB,Form("0-10%s (/10), + %.1f%s - %.1f%s",texper.Data(),systnormPbPbhigh010,texper.Data(),systnormPbPblow010,texper.Data()),"pf");
  ent_SigmaOnlyPbPb010MB->SetTextFont(42);
  ent_SigmaOnlyPbPb010MB->SetLineColor(2);
  ent_SigmaOnlyPbPb010MB->SetMarkerColor(2);

  TLegend* legendSigmaOnly2 = new TLegend(0.54,0.7655,0.87,0.881,"");// 727 -> 7655
  legendSigmaOnly2->SetBorderSize(0);
  legendSigmaOnly2->SetLineColor(0);
  legendSigmaOnly2->SetFillColor(0);
  legendSigmaOnly2->SetFillStyle(1001);
  legendSigmaOnly2->SetTextFont(42);
  legendSigmaOnly2->SetTextSize(0.0315);
  TLegendEntry* ent_SigmaOnly2PPMB = legendSigmaOnly2->AddEntry(hSigmaPPStatMB,Form("pp, %.1f%s",systnormPP,texper.Data()),"pf");
  ent_SigmaOnly2PPMB->SetTextFont(42);
  ent_SigmaOnly2PPMB->SetLineColor(2);
  ent_SigmaOnly2PPMB->SetMarkerColor(2);
  TLegendEntry* ent_SigmaOnly2PbPb0100MB = legendSigmaOnly2->AddEntry(hSigmaPbPb0100StatMB,Form("0-100%s (/3), + %.1f%s - %.1f%s",texper.Data(),systnormPbPbhigh0100,texper.Data(),systnormPbPblow0100,texper.Data()),"pf");
  ent_SigmaOnly2PbPb0100MB->SetTextFont(42);
  ent_SigmaOnly2PbPb0100MB->SetLineColor(2);
  ent_SigmaOnly2PbPb0100MB->SetMarkerColor(2);
  TLegendEntry* ent_SigmaOnly2PbPb010MB = legendSigmaOnly2->AddEntry(hSigmaPbPb010StatMB,Form("0-10%s (/10), + %.1f%s - %.1f%s",texper.Data(),systnormPbPbhigh010,texper.Data(),systnormPbPblow010,texper.Data()),"pf");
  ent_SigmaOnly2PbPb010MB->SetTextFont(42);
  ent_SigmaOnly2PbPb010MB->SetLineColor(2);
  ent_SigmaOnly2PbPb010MB->SetMarkerColor(2);
  //TLegendEntry* ent_SigmaOnly2FONLL = legendSigmaOnly2->AddEntry(gaeBplusReferenceMB,"FONLL pp ref.","f");
  //ent_SigmaOnly2FONLL->SetTextFont(42);
  //ent_SigmaOnly2FONLL->SetLineColor(5);
  //ent_SigmaOnly2FONLL->SetMarkerColor(1);

  //
  TString tlumi = "27.4 pb^{-1} (5.02 TeV pp) + 530 #mub^{-1} (5.02 TeV PbPb)";
  TString tlumiPbPb = "530 #mub^{-1} (5.02 TeV PbPb)";
  TLatex* tlatex1 = new TLatex(0.95,0.96,tlumi.Data());
  tlatex1->SetNDC();
  tlatex1->SetTextAlign(32);
  tlatex1->SetTextColor(1);
  tlatex1->SetTextFont(42);
  tlatex1->SetTextSize(0.045);
  TLatex* tlatex1Only = new TLatex(0.95,0.972,tlumiPbPb.Data());
  tlatex1Only->SetNDC();
  tlatex1Only->SetTextAlign(32);
  tlatex1Only->SetTextColor(1);
  tlatex1Only->SetTextFont(42);
  tlatex1Only->SetTextSize(0.0315);
  TLatex* tlatex1Only2 = new TLatex(0.95,0.972,tlumi.Data());
  tlatex1Only2->SetNDC();
  tlatex1Only2->SetTextAlign(32);
  tlatex1Only2->SetTextColor(1);
  tlatex1Only2->SetTextFont(42);
  tlatex1Only2->SetTextSize(0.0315);

  TLatex* texcms = new TLatex(0.15,0.90,"CMS");
  texcms->SetNDC();
  texcms->SetTextAlign(13);
  texcms->SetTextFont(62);//61
  texcms->SetTextSize(0.06);
  texcms->SetLineWidth(2);
  TLatex* texcmsOnly = new TLatex(0.15,0.93,"CMS");
  texcmsOnly->SetNDC();
  texcmsOnly->SetTextAlign(13);
  texcmsOnly->SetTextFont(62);//61
  texcmsOnly->SetTextSize(0.042);
  texcmsOnly->SetLineWidth(2);
  TLatex* texcmsOnly2 = new TLatex(0.15,0.93,"CMS");
  texcmsOnly2->SetNDC();
  texcmsOnly2->SetTextAlign(13);
  texcmsOnly2->SetTextFont(62);//61
  texcmsOnly2->SetTextSize(0.042);
  texcmsOnly2->SetLineWidth(2);

  TLatex* texDzero = new TLatex(0.15,0.84,"D^{0} + #bar{D^{#lower[0.2]{0}}}");
  texDzero->SetNDC();
  texDzero->SetTextAlign(13);
  texDzero->SetTextFont(62);//61
  texDzero->SetTextSize(0.06);
  texDzero->SetLineWidth(2);
  TLatex* texDzeroOnly = new TLatex(0.15,0.888,"D^{0} + #bar{D^{#lower[0.2]{0}}}");
  texDzeroOnly->SetNDC();
  texDzeroOnly->SetTextAlign(13);
  texDzeroOnly->SetTextFont(62);//61
  texDzeroOnly->SetTextSize(0.042);
  texDzeroOnly->SetLineWidth(2);
  TLatex* texDzeroOnly2 = new TLatex(0.15,0.888,"D^{0} + #bar{D^{#lower[0.2]{0}}}");
  texDzeroOnly2->SetNDC();
  texDzeroOnly2->SetTextAlign(13);
  texDzeroOnly2->SetTextFont(62);//61
  texDzeroOnly2->SetTextSize(0.042);
  texDzeroOnly2->SetLineWidth(2);

  /*
  TLatex* texpre = new TLatex(0.15,0.84,"Preliminary");
  texpre->SetNDC();
  texpre->SetTextAlign(13);
  texpre->SetTextFont(52);
  texpre->SetTextSize(0.04);
  texpre->SetLineWidth(2);
  TLatex* texpreOnly = new TLatex(0.15,0.888,"Preliminary");
  texpreOnly->SetNDC();
  texpreOnly->SetTextAlign(13);
  texpreOnly->SetTextFont(52);
  texpreOnly->SetTextSize(0.028);
  texpreOnly->SetLineWidth(2);
  TLatex* texpreOnly2 = new TLatex(0.15,0.888,"Preliminary");
  texpreOnly2->SetNDC();
  texpreOnly2->SetTextAlign(13);
  texpreOnly2->SetTextFont(52);
  texpreOnly2->SetTextSize(0.028);
  texpreOnly2->SetLineWidth(2);
  */

  TLine* l = new TLine(2.2,1,110,1);//10,1,105,1
  l->SetLineWidth(1);
  l->SetLineStyle(2);

  TCanvas* cSigmaOnly = new TCanvas("cSigmaOnly","",750,750);
  cSigmaOnly->SetFrameBorderMode(0);
  cSigmaOnly->SetFrameBorderMode(0);
  cSigmaOnly->Range(-1.989924,-0.2917772,25.49622,2.212202);
  cSigmaOnly->SetFillColor(0);
  cSigmaOnly->SetBorderMode(0);
  cSigmaOnly->SetBorderSize(2);
  cSigmaOnly->SetLeftMargin(0.12);//0.1451613
  cSigmaOnly->SetRightMargin(0.03);//0.05443548
  cSigmaOnly->SetTopMargin(0.049);//0.08474576
  cSigmaOnly->SetBottomMargin(0.099);//0.1165254
  cSigmaOnly->SetFrameBorderMode(0);
  cSigmaOnly->SetFrameBorderMode(0);
  cSigmaOnly->SetLogx();
  cSigmaOnly->SetLogy();
  cSigmaOnly->cd();

  hemptySigmaOnly->Draw();
  hSigmaPbPb0100StatMB->Draw("epsame"); 
  hSigmaPbPb0100Stat->Draw("epsame"); 
  gaeCrossPbPb0100SystMB->Draw("5same");  
  gaeCrossPbPb0100Syst->Draw("5same");  
  hSigmaPbPb010StatMB->Draw("epsame"); 
  hSigmaPbPb010Stat->Draw("epsame"); 
  gaeCrossPbPb010SystMB->Draw("5same");  
  gaeCrossPbPb010Syst->Draw("5same");  
  texYOnly->Draw();
  legendSigmaOnly->Draw("same");
  tlatex1Only->Draw();
  texcmsOnly->Draw();
  texDzeroOnly->Draw();
  //texpreOnly->Draw();

  cSigmaOnly->SaveAs("plotCrossSection/CrossSection_ComparisonPbPb.pdf");

  TCanvas* cSigmaOnly2 = new TCanvas("cSigmaOnly2","",750,750);
  cSigmaOnly2->SetFrameBorderMode(0);
  cSigmaOnly2->SetFrameBorderMode(0);
  cSigmaOnly2->Range(-1.989924,-0.2917772,25.49622,2.212202);
  cSigmaOnly2->SetFillColor(0);
  cSigmaOnly2->SetBorderMode(0);
  cSigmaOnly2->SetBorderSize(2);
  cSigmaOnly2->SetLeftMargin(0.12);//0.1451613
  cSigmaOnly2->SetRightMargin(0.03);//0.05443548
  cSigmaOnly2->SetTopMargin(0.049);//0.08474576
  cSigmaOnly2->SetBottomMargin(0.099);//0.1165254
  cSigmaOnly2->SetFrameBorderMode(0);
  cSigmaOnly2->SetFrameBorderMode(0);
  cSigmaOnly2->SetLogx();
  cSigmaOnly2->SetLogy();
  cSigmaOnly2->cd();

  hemptySigmaOnly2->Draw();
  /*
  gaeBplusReferenceMB->Draw("5same");
  gaeBplusReference->Draw("5same");
  */
  hSigmaPPStatMB->Draw("epsame"); 
  hSigmaPPStat->Draw("epsame"); 
  gaeCrossPPSystMB->Draw("5same");  
  gaeCrossPPSyst->Draw("5same");  
  hSigmaPbPb0100StatMB->Draw("epsame"); 
  hSigmaPbPb0100Stat->Draw("epsame"); 
  gaeCrossPbPb0100SystMB->Draw("5same");  
  gaeCrossPbPb0100Syst->Draw("5same");  
  hSigmaPbPb010StatMB->Draw("epsame"); 
  hSigmaPbPb010Stat->Draw("epsame"); 
  gaeCrossPbPb010SystMB->Draw("5same");  
  gaeCrossPbPb010Syst->Draw("5same");  

  texYOnly2->Draw();
  legendSigmaOnly2->Draw("same");
  tlatex1Only2->Draw();
  texcmsOnly2->Draw();
  texDzeroOnly2->Draw();
  //texpreOnly2->Draw();
  cSigmaOnly2->SaveAs("plotCrossSection/CrossSection_ComparisonPPnPbPb_noRatio.pdf");

  TCanvas* cSigma = new TCanvas("cSigma","",750,750);
  cSigma->SetFrameBorderMode(0);
  cSigma->SetFrameBorderMode(0);
  cSigma->Range(-1.989924,-0.2917772,25.49622,2.212202);
  cSigma->SetFillColor(0);
  cSigma->SetBorderMode(0);
  cSigma->SetBorderSize(2);
  cSigma->SetLeftMargin(0.12);//0.1451613
  cSigma->SetRightMargin(0.03);//0.05443548
  cSigma->SetTopMargin(0.07);//0.08474576
  cSigma->SetBottomMargin(0.15);//0.1165254
  cSigma->SetFrameBorderMode(0);
  cSigma->SetFrameBorderMode(0);
  cSigma->SetLogx();
  cSigma->cd();
  TPad* pSigma = new TPad("pSigma","",0,0.30,1,1);
  pSigma->SetFillColor(0);
  pSigma->SetBorderMode(0);
  pSigma->SetBorderSize(2);
  pSigma->SetLeftMargin(0.12);//0.1451613
  pSigma->SetRightMargin(0.03);//0.05443548
  pSigma->SetTopMargin(0.07);//0.08474576
  pSigma->SetBottomMargin(0);
  pSigma->SetLogy();
  pSigma->SetLogx();
  pSigma->Draw();
  pSigma->cd();

  hemptySigma->Draw();
  gaeBplusReferenceMB->Draw("5same");
  gaeBplusReference->Draw("5same");
  hSigmaPPStatMB->Draw("epsame"); 
  hSigmaPPStat->Draw("epsame"); 
  gaeCrossPPSystMB->Draw("5same");  
  gaeCrossPPSyst->Draw("5same");  
  hSigmaPbPb0100StatMB->Draw("epsame"); 
  hSigmaPbPb0100Stat->Draw("epsame"); 
  gaeCrossPbPb0100SystMB->Draw("5same");  
  gaeCrossPbPb0100Syst->Draw("5same");  
  hSigmaPbPb010StatMB->Draw("epsame"); 
  hSigmaPbPb010Stat->Draw("epsame"); 
  gaeCrossPbPb010SystMB->Draw("5same");  
  gaeCrossPbPb010Syst->Draw("5same");  

  texY->Draw();
  //texSystnormPP->Draw();
  //texSystnormPbPb0100->Draw();
  //texSystnormPbPb010->Draw();
  legendSigma->Draw("same");
  tlatex1->Draw();
  texcms->Draw();
  texDzero->Draw();
  //texpre->Draw();

  cSigma->cd();
  TPad* pRatio = new TPad("pRatio","",0,0,1,0.30);
  pRatio->SetLeftMargin(0.12);//0.1451613
  pRatio->SetRightMargin(0.03);//0.05443548
  pRatio->SetTopMargin(0);
  pRatio->SetBottomMargin(0.33);//0.25
  pRatio->SetLogx();
  pRatio->Draw();
  pRatio->cd();

  hemptyRatio->Draw();
  gaeRatioCrossFONLLunityMB->Draw("5same");
  gaeRatioCrossFONLLstatMB->Draw("epsame");
  gaeRatioCrossFONLLsystMB->Draw("5same");
  gaeRatioCrossFONLLunity->Draw("5same");
  gaeRatioCrossFONLLstat->Draw("epsame");
  gaeRatioCrossFONLLsyst->Draw("5same");
  l->Draw("same");

  cSigma->SaveAs("plotCrossSection/CrossSection_ComparisonPPnPbPb.pdf");
}

void scaleNsetCrossSection(TH1D* hSigmaStat, TGraphAsymmErrors* gaeCrossSyst, Double_t fscale, Int_t pcolor, Int_t pstyle)
{
  Int_t ngrbins = gaeCrossSyst->GetN();
  for(int i=0;i<ngrbins;i++)
    {
      cout<<left<<"  "<<setw(5)<<i;
      Double_t x,y;
      gaeCrossSyst->GetPoint(i,x,y);
      cout<<left<<setw(8)<<x<<setw(15)<<y<<setw(15)<<hSigmaStat->GetBinContent(i+1);
      gaeCrossSyst->SetPoint(i,x,y*fscale);
      Double_t exl = gaeCrossSyst->GetErrorXlow(i);
      Double_t exh = gaeCrossSyst->GetErrorXhigh(i);
      Double_t eyl = gaeCrossSyst->GetErrorYlow(i);
      Double_t eyh = gaeCrossSyst->GetErrorYhigh(i);
      cout<<left<<setw(15)<<eyl<<setw(15)<<eyh<<endl;
      gaeCrossSyst->SetPointError(i,exl,exh,eyl*fscale,eyh*fscale);
    }
  hSigmaStat->Scale(fscale);
  cout<<endl;
  
  hSigmaStat->SetLineWidth(2);
  hSigmaStat->SetMarkerSize(1);
  hSigmaStat->SetMarkerStyle(pstyle);
  hSigmaStat->SetLineColor(pcolor);
  hSigmaStat->SetMarkerColor(pcolor);
  
  gaeCrossSyst->SetMarkerSize(1);
  gaeCrossSyst->SetMarkerStyle(pstyle);
  gaeCrossSyst->SetFillColor(1);
  gaeCrossSyst->SetFillStyle(0);
  gaeCrossSyst->SetLineWidth(2);
  gaeCrossSyst->SetLineColor(pcolor);
}

int main(int argc, char *argv[])
{
  if(argc==7)
    {
      CombineCrossSectionsPPnPbPb(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}

