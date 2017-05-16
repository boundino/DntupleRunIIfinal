using namespace std;
#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"
#include "systematics.h"
#include "drawTheory.h"

void CombineCrossSections(TString fileMB="ROOTfiles/CrossSectionFONLLPPMB.root", TString file="ROOTfiles/CrossSectionFONLLPP.root", Int_t isPbPb=0, Float_t centMin=0., Float_t centMax=100.)
{

  bool doComparisonLHC=false;
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TString texPbPb = "PbPb";
  if(isPbPb==0) texPbPb = "PP";

  TFile* filePPMB = new TFile(fileMB.Data());  
  TGraphAsymmErrors* gaeRatioCrossFONLLstatMB = (TGraphAsymmErrors*)filePPMB->Get("gaeRatioCrossFONLLstat");
  TGraphAsymmErrors* gaeRatioCrossFONLLsystMB = (TGraphAsymmErrors*)filePPMB->Get("gaeRatioCrossFONLLsyst");
  TGraphAsymmErrors* gaeCrossSystMB = (TGraphAsymmErrors*)filePPMB->Get("gaeCrossSyst");
  TGraphAsymmErrors* gaeBplusReferenceMB = (TGraphAsymmErrors*)filePPMB->Get("gaeSigmaDzero");
  TGraphAsymmErrors* gaeRatioCrossFONLLunityMB = (TGraphAsymmErrors*)filePPMB->Get("gaeRatioCrossFONLLunity");
  TH1D* hSigmaPPStatMB = (TH1D*)filePPMB->Get("hPtSigma");
  TH1D* hfPromptMB = (TH1D*)filePPMB->Get("hfprompt");

  TFile* filePP = new TFile(file.Data());  
  TGraphAsymmErrors* gaeRatioCrossFONLLstat = (TGraphAsymmErrors*)filePP->Get("gaeRatioCrossFONLLstat");
  TGraphAsymmErrors* gaeRatioCrossFONLLsyst = (TGraphAsymmErrors*)filePP->Get("gaeRatioCrossFONLLsyst");
  TGraphAsymmErrors* gaeCrossSyst = (TGraphAsymmErrors*)filePP->Get("gaeCrossSyst");
  TGraphAsymmErrors* gaeBplusReference = (TGraphAsymmErrors*)filePP->Get("gaeSigmaDzero");
  TGraphAsymmErrors* gaeRatioCrossFONLLunity = (TGraphAsymmErrors*)filePP->Get("gaeRatioCrossFONLLunity");
  TH1D* hSigmaPPStat = (TH1D*)filePP->Get("hPtSigma");
  TH1D* hfPrompt = (TH1D*)filePP->Get("hfprompt");

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

  hSigmaPPStatMB->SetLineWidth(2);
  hSigmaPPStatMB->SetMarkerSize(1);//4
  hSigmaPPStatMB->SetMarkerStyle(20);
  hSigmaPPStatMB->SetLineColor(1);//kGreen+4
  hSigmaPPStatMB->SetMarkerColor(1);//kGreen+4

  hSigmaPPStat->SetLineWidth(2);
  hSigmaPPStat->SetMarkerSize(1);//4
  hSigmaPPStat->SetMarkerStyle(20);
  hSigmaPPStat->SetLineColor(1);//kGreen+4
  hSigmaPPStat->SetMarkerColor(1);//kGreen+4

  gaeCrossSystMB->SetFillColor(1);
  gaeCrossSystMB->SetFillStyle(0); 
  gaeCrossSystMB->SetLineWidth(2);
  gaeCrossSystMB->SetLineColor(1);//kGreen+4

  gaeCrossSyst->SetFillColor(1);
  gaeCrossSyst->SetFillStyle(0); 
  gaeCrossSyst->SetLineWidth(2);
  gaeCrossSyst->SetLineColor(1);//kGreen+4

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

  //
  TString yaxistitle = (isPbPb==1)?"#frac{1}{<T_{AA}> N_{evt}} #frac{dN^{PbPb}}{dp_{T}}  #left[#frac{pb}{GeV/c}#right]":"#frac{d#sigma^{pp}}{dp_{T}}  #left[#frac{pb}{GeV/c}#right]";

  TH2F* hemptySigmaOnly = new TH2F("hemptySigmaOnly","",50,0.,110.,10.,0.1,1.e12);
  hemptySigmaOnly->GetXaxis()->CenterTitle();
  hemptySigmaOnly->GetYaxis()->CenterTitle();
  hemptySigmaOnly->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  hemptySigmaOnly->GetYaxis()->SetTitle(yaxistitle);
  //hemptySigmaOnly->GetYaxis()->SetTitle("d#sigma / dp_{T}( pb GeV^{-1}c)");
  //if(isPbPb==1) hemptySigmaOnly->GetYaxis()->SetTitle("1/T_{AA} * dN / dp_{T}( pb GeV^{-1}c)");
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

  //
  TH2F* hemptySigma = new TH2F("hemptySigma","",50,0.,110.,10.,0.11,1.e12);
  hemptySigma->GetXaxis()->CenterTitle();
  hemptySigma->GetYaxis()->CenterTitle();
  hemptySigma->GetYaxis()->SetTitle(yaxistitle);
  //hemptySigma->GetYaxis()->SetTitle("d#sigma / dp_{T}( pb GeV^{-1}c)");
  //if(isPbPb==1) hemptySigma->GetYaxis()->SetTitle("1/T_{AA} * dN / dp_{T}( pb GeV^{-1}c)");
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

  TH2F* hemptyRatio = new TH2F("hemptyRatio","",50,0.,110.,10.,0.,2.7);//50,0.,110.,10.,0.,4
  hemptyRatio->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("#frac{Data}{FONLL}");
  //hemptyRatio->GetYaxis()->SetTitle("Data / FONLL");
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

  //
  TH2F* hemptyRatioBor = new TH2F("hemptyRatioBor","",50,0.,110.,10.,-0.2 ,2.7);//50,0.,110.,10.,0.,4
  hemptyRatioBor->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  hemptyRatioBor->GetXaxis()->CenterTitle();
  hemptyRatioBor->GetYaxis()->CenterTitle();
  hemptyRatioBor->GetYaxis()->SetTitle("#frac{Data}{FONLL}");
  //hemptyRatioBor->GetYaxis()->SetTitle("Data / FONLL");
  hemptyRatioBor->GetXaxis()->SetTitleOffset(1.0);
  hemptyRatioBor->GetYaxis()->SetTitleOffset(0.36367);
  hemptyRatioBor->GetXaxis()->SetTitleSize(0.13);
  hemptyRatioBor->GetYaxis()->SetTitleSize(0.146);// 0.144
  hemptyRatioBor->GetXaxis()->SetTitleFont(42);
  hemptyRatioBor->GetYaxis()->SetTitleFont(42);
  hemptyRatioBor->GetXaxis()->SetLabelFont(42);
  hemptyRatioBor->GetYaxis()->SetLabelFont(42);
  hemptyRatioBor->GetYaxis()->SetLabelOffset(0.012);// 0.01
  hemptyRatioBor->GetXaxis()->SetLabelSize(0.1);
  hemptyRatioBor->GetYaxis()->SetLabelSize(0.133335);

  TH2F* hemptyRatioBorGM = new TH2F("hemptyRatioBorGM","",50,0.,110.,10.,0.,2.7);//50,0.,110.,10.,0.,4
  hemptyRatioBorGM->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  hemptyRatioBorGM->GetXaxis()->CenterTitle();
  hemptyRatioBorGM->GetYaxis()->CenterTitle();
  hemptyRatioBorGM->GetYaxis()->SetTitle("#frac{Data}{GM-VFNS}");
  //hemptyRatioBorGM->GetYaxis()->SetTitle("Data / GM-VFNS");
  hemptyRatioBorGM->GetXaxis()->SetTitleOffset(1.0);
  hemptyRatioBorGM->GetYaxis()->SetTitleOffset(0.5455);// 0.4 before y title changes -> 0.5555
  hemptyRatioBorGM->GetXaxis()->SetTitleSize(0.13);
  hemptyRatioBorGM->GetYaxis()->SetTitleSize(0.096);// 0.12 before y title changes -> 0.096
  hemptyRatioBorGM->GetXaxis()->SetTitleFont(42);
  hemptyRatioBorGM->GetYaxis()->SetTitleFont(42);
  hemptyRatioBorGM->GetXaxis()->SetLabelFont(42);
  hemptyRatioBorGM->GetYaxis()->SetLabelFont(42);
  hemptyRatioBorGM->GetYaxis()->SetLabelOffset(0.015);
  hemptyRatioBorGM->GetXaxis()->SetLabelSize(0.1);
  hemptyRatioBorGM->GetYaxis()->SetLabelSize(0.08889);// 0.1 before y title changes -> 0.08889

  //
  TString texper="%";
  TLatex* texCent = new TLatex(0.55,0.85,Form("Centrality %.0f - %.0f%s",centMin,centMax,texper.Data()));
  texCent->SetNDC();
  texCent->SetTextFont(42);
  texCent->SetTextSize(0.045);
  TLatex* texCentOnly = new TLatex(0.55,0.895,Form("Centrality %.0f - %.0f%s",centMin,centMax,texper.Data()));
  texCentOnly->SetNDC();
  texCentOnly->SetTextFont(42);
  texCentOnly->SetTextSize(0.0315);
  TLatex* texCentCal = new TLatex(0.55,0.55,Form("Centrality %.0f - %.0f%s",centMin,centMax,texper.Data()));
  texCentCal->SetNDC();
  texCentCal->SetTextFont(42);
  texCentCal->SetTextSize(0.045);

  TLatex* texY = new TLatex(0.55,0.79,"|y| < 1.0");
  texY->SetNDC();
  texY->SetTextFont(42);
  texY->SetTextSize(0.045);
  texY->SetLineWidth(2);
  TLatex* texYOnly = new TLatex(0.55,0.853,"|y| < 1.0");
  texYOnly->SetNDC();
  texYOnly->SetTextFont(42);
  texYOnly->SetTextSize(0.0315);
  texYOnly->SetLineWidth(2);
  TLatex* texYCal = new TLatex(0.55,0.853,"|y| < 1.0");
  texYCal->SetNDC();
  texYCal->SetTextFont(42);
  texYCal->SetTextSize(0.045);
  texYCal->SetLineWidth(2);

  Float_t systnormhigh,systnormlow;
  if(isPbPb==1) 
    {
      systnormhigh = normalizationUncertaintyForPbPb(centMin,centMax);
      systnormlow = normalizationUncertaintyForPbPb(centMin,centMax,false);
    }
  else
    {
      systnormhigh = normalizationUncertaintyForPP();
    }
  TLatex* texSystnorm;
  if(isPbPb==1)
    {
      texSystnorm = new TLatex(0.55,0.61,Form("Global uncert. + %.1f%s - %.1f%s",systnormhigh,texper.Data(),systnormlow,texper.Data()));
    }
  else
    {
      texSystnorm = new TLatex(0.55,0.61,Form("Global uncert. %.1f%s",systnormhigh,texper.Data()));
    }
  texSystnorm->SetNDC();
  texSystnorm->SetTextFont(42);
  texSystnorm->SetTextSize(0.045);
  texSystnorm->SetLineWidth(2);
  TLatex* texSystnormOnly;// = new TLatex(0.55,0.727,Form("Global uncert. %.1f%s",systnorm,texper.Data()));
  if(isPbPb==1)
    {
      texSystnormOnly = new TLatex(0.55,0.727,Form("Global uncert. + %.1f%s - %.1f%s",systnormhigh,texper.Data(),systnormlow,texper.Data()));
    }
  else
    {
      texSystnormOnly = new TLatex(0.55,0.727,Form("Global uncert. %.1f%s",systnormhigh,texper.Data()));
    }
  texSystnormOnly->SetNDC();
  texSystnormOnly->SetTextFont(42);
  texSystnormOnly->SetTextSize(0.0315);
  texSystnormOnly->SetLineWidth(2);

  TLegend* legendSigma = new TLegend(0.54,0.66,0.87,0.77,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);
  TLegendEntry* ent_SigmaPPMB = legendSigma->AddEntry(hSigmaPPStatMB,"data","pf");
  ent_SigmaPPMB->SetTextFont(42);
  ent_SigmaPPMB->SetLineColor(2);
  ent_SigmaPPMB->SetMarkerColor(2);
  TLegendEntry* ent_SigmaFONLL = legendSigma->AddEntry(gaeBplusReferenceMB,"FONLL pp ref.","f");
  ent_SigmaFONLL->SetTextFont(42);
  ent_SigmaFONLL->SetLineColor(5);
  ent_SigmaFONLL->SetMarkerColor(1);
  TLegend* legendSigmaOnly = new TLegend(0.54,0.8005,0.87,0.839,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigmaOnly->SetBorderSize(0);
  legendSigmaOnly->SetLineColor(0);
  legendSigmaOnly->SetFillColor(0);
  legendSigmaOnly->SetFillStyle(1001);
  legendSigmaOnly->SetTextFont(42);
  legendSigmaOnly->SetTextSize(0.0315);
  TLegendEntry* ent_SigmaOnlyPPMB = legendSigmaOnly->AddEntry(hSigmaPPStatMB,"data","pf");
  ent_SigmaOnlyPPMB->SetTextFont(42);
  ent_SigmaOnlyPPMB->SetLineColor(2);
  ent_SigmaOnlyPPMB->SetMarkerColor(2);
  //TLegendEntry* ent_SigmaOnlyFONLL = legendSigmaOnly->AddEntry(gaeBplusReferenceMB,"FONLL pp ref.","f");
  //ent_SigmaOnlyFONLL->SetTextFont(42);
  //ent_SigmaOnlyFONLL->SetLineColor(5);
  //ent_SigmaOnlyFONLL->SetMarkerColor(1);
  TLegend* legendSigmaCal = new TLegend(0.54,0.66,0.87,0.825,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigmaCal->SetBorderSize(0);
  legendSigmaCal->SetLineColor(0);
  legendSigmaCal->SetFillColor(0);
  legendSigmaCal->SetFillStyle(1001);
  legendSigmaCal->SetTextFont(42);
  legendSigmaCal->SetTextSize(0.045);
  TLegendEntry* ent_SigmaCalPPMB = legendSigmaCal->AddEntry(hSigmaPPStatMB,"data","pf");
  ent_SigmaCalPPMB->SetTextFont(42);
  ent_SigmaCalPPMB->SetLineColor(2);
  ent_SigmaCalPPMB->SetMarkerColor(2);
  TLegendEntry* ent_SigmaCalFONLL = legendSigmaCal->AddEntry(gaeBplusReferenceMB,"FONLL pp ref.","f");
  ent_SigmaCalFONLL->SetTextFont(42);
  ent_SigmaCalFONLL->SetLineColor(5);
  ent_SigmaCalFONLL->SetMarkerColor(1);
  
  TString tlumi = isPbPb?"530 #mub^{-1} (5.02 TeV PbPb)":"27.4 pb^{-1} (5.02 TeV pp)";
  TLatex* tlatex1 = new TLatex(0.95,0.96,tlumi.Data());
  tlatex1->SetNDC();
  tlatex1->SetTextAlign(32);
  tlatex1->SetTextColor(1);
  tlatex1->SetTextFont(42);
  tlatex1->SetTextSize(0.045);
  TLatex* tlatex1Only = new TLatex(0.95,0.972,tlumi.Data());
  tlatex1Only->SetNDC();
  tlatex1Only->SetTextAlign(32);
  tlatex1Only->SetTextColor(1);
  tlatex1Only->SetTextFont(42);
  tlatex1Only->SetTextSize(0.0315);

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
  //gaeBplusReferenceMB->Draw("5same");
  //gaeBplusReference->Draw("5same");
  hSigmaPPStatMB->Draw("epsame"); 
  hSigmaPPStat->Draw("epsame"); 
  gaeCrossSystMB->Draw("5same");  
  gaeCrossSyst->Draw("5same");  
  if(isPbPb==1) texCentOnly->Draw();
  texYOnly->Draw();
  texSystnormOnly->Draw();
  legendSigmaOnly->Draw("same");
  tlatex1Only->Draw();
  texcmsOnly->Draw();
  texDzeroOnly->Draw();
  //texpreOnly->Draw();

  TString tprev = doComparisonLHC?"CrossSectionComparisonExperiments":"CrossSectionComparison";
  TString tend = isPbPb?Form("%s_%.0f_%.0f",texPbPb.Data(),centMin,centMax):Form("%s",texPbPb.Data());

  cSigmaOnly->SaveAs(Form("plotCrossSection/%s_NoRatio_%s.pdf",tprev.Data(),tend.Data()));

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
  gaeCrossSystMB->Draw("5same");  
  gaeCrossSyst->Draw("5same");  
  if(isPbPb==1) texCent->Draw();
  texY->Draw();
  texSystnorm->Draw();
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

  if(doComparisonLHC)
    {
      const int nBinsATLAS=9;
      double ptBinsATLAS[nBinsATLAS+1] = {3.5,5.0,6.5,8.0,12.0,20.0,30.,40.,60.,100.};
      double ptBinscenterATLAS[nBinsATLAS];
      double zerosATLAS[nBinsATLAS];
      
      const int nBinsALICE=9;
      double ptBinsALICE[nBinsALICE+1] = {1.,2.,3.,4.,5.,6.,7.,8.,12.,16.};
      double ptBinscenterALICE[nBinsALICE];
      double zerosALICE[nBinsALICE];
      
      double valuesALICE[nBinsALICE]={1.6,1.75,1.8,1.75,1.5,1.4,1.2,1.4,1.1};
      double errorsvaluesALICEup[nBinsALICE]={0.5,0.25,0.3,0.3,0.25,0.25,0.25,0.23,0.23};
      double errorsvaluesALICElow[nBinsALICE]={1.0,0.5,0.3,0.3,0.25,0.25,0.25,0.23,0.23};
      
      double valuesATLAS[nBinsATLAS]={1./0.55,1./0.5,1./0.55,1./0.54,1./0.8,1./0.7,1./0.7,1./0.7,1./0.7};
      double errorsvaluesATLASup[nBinsATLAS];
      double errorsvaluesATLASlow[nBinsATLAS];
      
      errorsvaluesATLASup[0]=valuesATLAS[0]*0.15;
      errorsvaluesATLASlow[0]=valuesATLAS[0]*0.15;
      errorsvaluesATLASup[1]=valuesATLAS[1]*0.12;
      errorsvaluesATLASlow[1]=valuesATLAS[1]*0.12;
      errorsvaluesATLASup[2]=valuesATLAS[2]*0.10;
      errorsvaluesATLASlow[2]=valuesATLAS[2]*0.10;
      errorsvaluesATLASup[3]=valuesATLAS[3]*0.17;
      errorsvaluesATLASlow[3]=valuesATLAS[3]*0.17;
      errorsvaluesATLASup[4]=valuesATLAS[4]*0.10;
      errorsvaluesATLASlow[4]=valuesATLAS[4]*0.10;
      errorsvaluesATLASup[5]=valuesATLAS[5]*0.10;
      errorsvaluesATLASlow[5]=valuesATLAS[5]*0.10;
      errorsvaluesATLASup[6]=valuesATLAS[6]*0.12;
      errorsvaluesATLASlow[6]=valuesATLAS[6]*0.12;
      errorsvaluesATLASup[7]=valuesATLAS[7]*0.10;
      errorsvaluesATLASlow[7]=valuesATLAS[7]*0.10;
      errorsvaluesATLASup[8]=valuesATLAS[8]*0.2;
      errorsvaluesATLASlow[8]=valuesATLAS[8]*0.2;
      
      double aptlATLAS[nBinsATLAS];
      double aptlALICE[nBinsALICE];
      
      for (int i=0;i<nBinsATLAS;i++)
        {
          ptBinscenterATLAS[i]=(ptBinsATLAS[i]+ptBinsATLAS[i+1])/2.;
          ptBinscenterALICE[i]=(ptBinsALICE[i]+ptBinsALICE[i+1])/2.;
          zerosATLAS[i]=0.;
          zerosALICE[i]=0.;
          aptlATLAS[i] = (ptBinsATLAS[i+1]-ptBinsATLAS[i])/2;
          aptlALICE[i] = (ptBinsALICE[i+1]-ptBinsALICE[i])/2;
        }
      
      TGraphAsymmErrors* gaeCrossSystATLAS = new TGraphAsymmErrors(nBinsATLAS,ptBinscenterATLAS,valuesATLAS,aptlATLAS,aptlATLAS,errorsvaluesATLASlow,errorsvaluesATLASup);
      gaeCrossSystATLAS->SetName("gaeCrossSystATLAS");
      gaeCrossSystATLAS->SetLineWidth(2);
      gaeCrossSystATLAS->SetLineColor(kRed);
      gaeCrossSystATLAS->SetFillColor(kRed);
      gaeCrossSystATLAS->SetFillStyle(3002);
      gaeCrossSystATLAS->Draw("5same");
      
      TGraphAsymmErrors* gaeCrossSystALICE = new TGraphAsymmErrors(nBinsALICE,ptBinscenterALICE,valuesALICE,aptlALICE,aptlALICE,errorsvaluesALICElow,errorsvaluesALICEup);
      gaeCrossSystALICE->SetName("gaeCrossSystALICE");
      gaeCrossSystALICE->SetLineWidth(2);
      gaeCrossSystALICE->SetLineColor(kBlue);
      gaeCrossSystALICE->SetFillColor(kBlue);
      gaeCrossSystALICE->SetFillStyle(3002);
      gaeCrossSystALICE->Draw("5same");
      
      TLegend *legendOtherexp=new TLegend(0.5385906,0.6925208,0.8691275,0.9252078,"");//0.5100806,0.5868644,0.8084677,0.7605932
      legendOtherexp->SetBorderSize(0);
      legendOtherexp->SetLineColor(0);
      legendOtherexp->SetFillColor(0);
      legendOtherexp->SetFillStyle(1001);
      legendOtherexp->SetTextFont(42);
      legendOtherexp->SetTextSize(0.055);
      
      TLegendEntry *entATLAS = legendOtherexp->AddEntry(gaeCrossSystATLAS,"ATLAS 7 TeV (|y|<2)","pf");
      entATLAS->SetTextFont(42);
      entATLAS->SetLineColor(kRed);
      entATLAS->SetMarkerColor(kRed);
      entATLAS->SetTextColor(kRed);
      
      TLegendEntry *entALICE = legendOtherexp->AddEntry(gaeCrossSystALICE,"ALICE 7 TeV (|y|<0.5)","pf");
      entALICE->SetTextFont(42);
      entALICE->SetLineColor(kBlue);
      entALICE->SetMarkerColor(kBlue);
      entALICE->SetTextColor(kBlue);
      legendOtherexp->Draw();
    }

  cSigma->SaveAs(Form("plotCrossSection/%s_%s.pdf",tprev.Data(),tend.Data()));

  //

  TCanvas* cSigmaCal = new TCanvas("cSigmaCal","",750,750);
  cSigmaCal->SetFrameBorderMode(0);
  cSigmaCal->SetFrameBorderMode(0);
  cSigmaCal->Range(-1.989924,-0.2917772,25.49622,2.212202);
  cSigmaCal->SetFillColor(0);
  cSigmaCal->SetBorderMode(0);
  cSigmaCal->SetBorderSize(2);
  cSigmaCal->SetLeftMargin(0.12);//0.1451613
  cSigmaCal->SetRightMargin(0.03);//0.05443548
  cSigmaCal->SetTopMargin(0.07);//0.08474576
  cSigmaCal->SetBottomMargin(0.15);//0.1165254
  cSigmaCal->SetFrameBorderMode(0);
  cSigmaCal->SetFrameBorderMode(0);
  cSigmaCal->SetLogx();
  cSigmaCal->cd();
  TPad* pSigmaCal = new TPad("pSigmaCal","",0,0.30,1,1);
  pSigmaCal->SetFillColor(0);
  pSigmaCal->SetBorderMode(0);
  pSigmaCal->SetBorderSize(2);
  pSigmaCal->SetLeftMargin(0.12);//0.1451613
  pSigmaCal->SetRightMargin(0.03);//0.05443548
  pSigmaCal->SetTopMargin(0.07);//0.08474576
  pSigmaCal->SetBottomMargin(0);
  pSigmaCal->SetLogy();
  pSigmaCal->SetLogx();
  pSigmaCal->Draw();
  pSigmaCal->cd();

  hemptySigma->Draw();
  gaeBplusReferenceMB->Draw("5same");
  gaeBplusReference->Draw("5same");
  drawTheoryPP(false,hSigmaPPStatMB,hSigmaPPStat,gaeCrossSystMB,gaeCrossSyst);
  hSigmaPPStatMB->Draw("epsame"); 
  hSigmaPPStat->Draw("epsame"); 
  gaeCrossSystMB->Draw("5same");  
  gaeCrossSyst->Draw("5same");  
  if(isPbPb==1) texCentCal->Draw();
  texYCal->Draw();
  texSystnorm->Draw();
  TLegendEntry* ent_SigmaCalGMVFNS = legendSigmaCal->AddEntry(gGMVFNSD5TeV,"GM-VFNS","f");
  ent_SigmaCalGMVFNS->SetTextFont(42);
  ent_SigmaCalGMVFNS->SetLineColor(5);
  ent_SigmaCalGMVFNS->SetMarkerColor(1);
  legendSigmaCal->Draw("same");
  tlatex1->Draw();
  texcms->Draw();
  texDzero->Draw();
  //texpre->Draw();

  cSigmaCal->cd();
  TPad* pRatioCal = new TPad("pRatioCal","",0,0,1,0.30);
  pRatioCal->SetLeftMargin(0.12);//0.1451613
  pRatioCal->SetRightMargin(0.03);//0.05443548
  pRatioCal->SetTopMargin(0);
  pRatioCal->SetBottomMargin(0.33);//0.25
  pRatioCal->SetLogx();
  pRatioCal->Draw();
  pRatioCal->cd();

  hemptyRatio->Draw();
  gaeRatioCrossFONLLunityMB->Draw("5same");
  gaeRatioCrossFONLLstatMB->Draw("epsame");
  gaeRatioCrossFONLLsystMB->Draw("5same");
  gaeRatioCrossFONLLunity->Draw("5same");
  gaeRatioCrossFONLLstat->Draw("epsame");
  gaeRatioCrossFONLLsyst->Draw("5same");
  l->Draw("same");  

  cSigmaCal->SaveAs(Form("plotCrossSection/%s_Calculation_%s.pdf",tprev.Data(),tend.Data()));

  //
  TCanvas* cSigmaBor = new TCanvas("cSigmaBor","",750,900);
  cSigmaBor->SetFrameBorderMode(0);
  cSigmaBor->SetFrameBorderMode(0);
  cSigmaBor->Range(-1.989924,-0.2917772,25.49622,2.212202);
  cSigmaBor->SetFillColor(0);
  cSigmaBor->SetBorderMode(0);
  cSigmaBor->SetBorderSize(2);
  cSigmaBor->SetLeftMargin(0.12);//0.1451613
  cSigmaBor->SetRightMargin(0.03);//0.05443548
  cSigmaBor->SetTopMargin(0.07);//0.08474576
  cSigmaBor->SetBottomMargin(0.15);//0.1165254
  cSigmaBor->SetFrameBorderMode(0);
  cSigmaBor->SetFrameBorderMode(0);
  cSigmaBor->SetLogx();
  cSigmaBor->cd();
  TPad* pSigmaBor = new TPad("pSigmaBor","",0,0.416666666667,1,1);
  pSigmaBor->SetFillColor(0);
  pSigmaBor->SetBorderMode(0);
  pSigmaBor->SetBorderSize(2);
  pSigmaBor->SetLeftMargin(0.12);//0.1451613
  pSigmaBor->SetRightMargin(0.03);//0.05443548
  pSigmaBor->SetTopMargin(0.07);//0.08474576
  pSigmaBor->SetBottomMargin(0);
  pSigmaBor->SetLogy();
  pSigmaBor->SetLogx();
  pSigmaBor->Draw();
  pSigmaBor->cd();

  hemptySigma->Draw();
  gaeBplusReferenceMB->Draw("5same");
  gaeBplusReference->Draw("5same");
  drawTheoryPP(false,hSigmaPPStatMB,hSigmaPPStat,gaeCrossSystMB,gaeCrossSyst);
  hSigmaPPStatMB->Draw("epsame"); 
  hSigmaPPStat->Draw("epsame"); 
  gaeCrossSystMB->Draw("5same");  
  gaeCrossSyst->Draw("5same");  
  if(isPbPb==1) texCentCal->Draw();
  texYCal->Draw();
  texSystnorm->Draw();
  legendSigmaCal->Draw("same");
  tlatex1->Draw();
  texcms->Draw();
  texDzero->Draw();
  //texpre->Draw();

  cSigmaBor->cd();
  TPad* pRatioFOBor = new TPad("pRatioFOBor","",0,0.25,1,0.416666666667);
  pRatioFOBor->SetLeftMargin(0.12);//0.1451613
  pRatioFOBor->SetRightMargin(0.03);//0.05443548
  pRatioFOBor->SetTopMargin(0);
  pRatioFOBor->SetBottomMargin(0);//0.25
  pRatioFOBor->SetLogx();
  pRatioFOBor->Draw();
  pRatioFOBor->cd();

  hemptyRatioBor->Draw();
  gaeRatioCrossFONLLunityMB->Draw("5same");
  gaeRatioCrossFONLLstatMB->Draw("epsame");
  gaeRatioCrossFONLLsystMB->Draw("5same");
  gaeRatioCrossFONLLunity->Draw("5same");
  gaeRatioCrossFONLLstat->Draw("epsame");
  gaeRatioCrossFONLLsyst->Draw("5same");
  l->Draw("same");  

  cSigmaBor->cd();
  TPad* pRatioGMBor = new TPad("pRatioGMBor","",0,0,1,0.25);
  pRatioGMBor->SetLeftMargin(0.12);//0.1451613
  pRatioGMBor->SetRightMargin(0.03);//0.05443548
  pRatioGMBor->SetTopMargin(0);
  pRatioGMBor->SetBottomMargin(0.33);//0.25
  pRatioGMBor->SetLogx();
  pRatioGMBor->Draw();
  pRatioGMBor->cd();

  hemptyRatioBorGM->Draw();
  drawTheoryPP(true,hSigmaPPStatMB,hSigmaPPStat,gaeCrossSystMB,gaeCrossSyst);
  l->Draw("same");  

  cSigmaBor->SaveAs(Form("plotCrossSection/%s_Calculation_BothRatio_%s.pdf",tprev.Data(),tend.Data()));

  /*
  TCanvas* cFprompt = new TCanvas("cFprompt","",550,500);
  TH2F* hemptyPrompt = new TH2F("hemptyPrompt","",50,0.,110.,10.,0,1.3);  
  hemptyPrompt->GetXaxis()->CenterTitle();
  hemptyPrompt->GetYaxis()->CenterTitle();
  hemptyPrompt->GetYaxis()->SetTitle("f_{prompt}");
  hemptyPrompt->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyPrompt->GetXaxis()->SetTitleOffset(0.9);
  hemptyPrompt->GetYaxis()->SetTitleOffset(1.05);
  hemptyPrompt->GetXaxis()->SetTitleSize(0.045);
  hemptyPrompt->GetYaxis()->SetTitleSize(0.045);
  hemptyPrompt->GetXaxis()->SetTitleFont(42);
  hemptyPrompt->GetYaxis()->SetTitleFont(42);
  hemptyPrompt->GetXaxis()->SetLabelFont(42);
  hemptyPrompt->GetYaxis()->SetLabelFont(42);
  hemptyPrompt->GetXaxis()->SetLabelSize(0.04);
  hemptyPrompt->GetYaxis()->SetLabelSize(0.04);  
  hemptyPrompt->SetMaximum(2);
  hemptyPrompt->SetMinimum(0.);
  hemptyPrompt->Draw();
  cFprompt->cd();
  hemptyPrompt->Draw();
  hfPromptMB->SetLineWidth(2);
  hfPromptMB->SetLineColor(1);
  hfPromptMB->SetMarkerStyle(23);
  hfPromptMB->SetMarkerSize(1);
  hfPromptMB->Draw("psame");
  hfPrompt->SetLineWidth(2);
  hfPrompt->SetLineColor(1);
  hfPrompt->SetMarkerStyle(23);
  hfPrompt->SetMarkerSize(1);
  hfPrompt->Draw("psame");
  
  if(!isPbPb) cFprompt->SaveAs("plotOthers/cFpromptTotalPP.pdf");
  else cFprompt->SaveAs("plotOthers/cFpromptTotalPbPb.pdf");
  */
}


int main(int argc, char *argv[])
{
  if(argc==6)
    {
      CombineCrossSections(argv[1], argv[2], atoi(argv[3]), atof(argv[4]), atof(argv[5]));
      return 0;
    }
  else if(argc==4)
    {
      CombineCrossSections(argv[1], argv[2], atoi(argv[3]));
      return 0;
    }
  else if(argc==3)
    {
      CombineCrossSections(argv[1], argv[2]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}

