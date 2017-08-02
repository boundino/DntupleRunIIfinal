#include "uti.h"
#include "systematics.h"
#include "drawTheory.h"
#include "CombineCrossSections.h"

void CombineCrossSections(TString filenameMB="ROOTfiles/CrossSectionFONLLPPMB.root", TString filename="ROOTfiles/CrossSectionFONLLPP.root", Int_t isPbPb=0, Float_t centmin=0., Float_t centmax=100.)
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TString texPbPb = isPbPb?"PbPb":"PP";
  TString legPbPb = isPbPb?"PbPb":"pp";
  TString tprev = "CrossSectionComparison";
  TString tend = isPbPb?Form("%s_%.0f_%.0f",texPbPb.Data(),centmin,centmax):Form("%s",texPbPb.Data());

  TFile* fileMB = new TFile(filenameMB.Data());  
  TGraphAsymmErrors* gaeRatioCrossFONLLstatMB = (TGraphAsymmErrors*)fileMB->Get("gaeRatioCrossFONLLstat");
  TGraphAsymmErrors* gaeRatioCrossFONLLsystMB = (TGraphAsymmErrors*)fileMB->Get("gaeRatioCrossFONLLsyst");
  TGraphAsymmErrors* gaeCrossSystMB = (TGraphAsymmErrors*)fileMB->Get("gaeCrossSyst");
  TGraphAsymmErrors* gaeDzeroReferenceMB = (TGraphAsymmErrors*)fileMB->Get("gaeSigmaDzero");
  TGraphAsymmErrors* gaeRatioCrossFONLLunityMB = (TGraphAsymmErrors*)fileMB->Get("gaeRatioCrossFONLLunity");
  TH1D* hSigmaStatMB = (TH1D*)fileMB->Get("hPtSigma");

  TFile* file = new TFile(filename.Data());  
  TGraphAsymmErrors* gaeRatioCrossFONLLstat = (TGraphAsymmErrors*)file->Get("gaeRatioCrossFONLLstat");
  TGraphAsymmErrors* gaeRatioCrossFONLLsyst = (TGraphAsymmErrors*)file->Get("gaeRatioCrossFONLLsyst");
  TGraphAsymmErrors* gaeCrossSyst = (TGraphAsymmErrors*)file->Get("gaeCrossSyst");
  TGraphAsymmErrors* gaeDzeroReference = (TGraphAsymmErrors*)file->Get("gaeSigmaDzero");
  TGraphAsymmErrors* gaeRatioCrossFONLLunity = (TGraphAsymmErrors*)file->Get("gaeRatioCrossFONLLunity");
  TH1D* hSigmaStat = (TH1D*)file->Get("hPtSigma");

  setthgrstyle(gaeDzeroReferenceMB,       -1, -1, -1,  kOrange+7, -1, 2,      kOrange+1, 0.2, 1001);
  setthgrstyle(gaeDzeroReference,         -1, -1, -1,  kOrange+7, -1, 2,      kOrange+1, 0.2, 1001);
  setthgrstyle(gaeRatioCrossFONLLunityMB, -1, -1, -1,  kOrange+7, -1, 2,      kOrange+1, 0.2, 1001);
  setthgrstyle(gaeRatioCrossFONLLunity,   -1, -1, -1,  kOrange+7, -1, 2,      kOrange+1, 0.2, 1001);
  
  setthgrstyle(hSigmaStatMB,              1,  20, 1.4, 1,         -1, 2,      -1,        -1,  -1);
  setthgrstyle(hSigmaStat,                1,  20, 1.4, 1,         -1, 2,      -1,        -1,  -1);
  setthgrstyle(gaeCrossSystMB,            -1, -1, -1,  1,         -1, 2,      1,         -1,  0);
  setthgrstyle(gaeCrossSyst,              -1, -1, -1,  1,         -1, 2,      1,         -1,  0);
  setthgrstyle(gaeRatioCrossFONLLstatMB,  1,  20, 1.4, 1,         -1, 2,      -1,        -1,  -1);
  setthgrstyle(gaeRatioCrossFONLLstat,    1,  20, 1.4, 1,         -1, 2,      -1,        -1,  -1);
  setthgrstyle(gaeRatioCrossFONLLsystMB,  -1, -1, -1,  1,         -1, 2/*3*/, 1,         -1,  0);
  setthgrstyle(gaeRatioCrossFONLLsyst,    -1, -1, -1,  1,         -1, 2/*3*/, 1,         -1,  0);
  
  
  //
  TString str_hemptySigma = (isPbPb==1)?"#frac{1}{T_{AA}} #frac{dN_{PbPb}}{dp_{T}}  #left(#frac{pb}{GeV/c}#right)":"#frac{d#sigma_{pp}}{dp_{T}}  #left(#frac{pb}{GeV/c}#right)";  
  //
  Float_t xminSigma = 0, xmaxSigma = 110., yminSigma = 0.11, ymaxSigma = 1.e13;
  TH2F* hemptySigmaOnly = new TH2F("hemptySigmaOnly", Form(";p_{T} (GeV/c);%s", str_hemptySigma.Data()), 50, xminSigma, xmaxSigma, 10, yminSigma, ymaxSigma);
  sethemptystyle(hemptySigmaOnly, 1.0, 1.7861, 0.039, 0.028, 0.03, 0.028);
  hemptySigmaOnly->GetXaxis()->SetLabelOffset(0.001);
  TH2F* hemptySigma = new TH2F("hemptySigma", Form(";;%s", str_hemptySigma.Data()), 50, xminSigma, xmaxSigma, 10, yminSigma, ymaxSigma);
  sethemptystyle(hemptySigma, -1, 1.25, -1, 0.04, -1, 0.04);
  TH2F* hemptySigmaBor = new TH2F("hemptySigmaBor", Form(";;%s", str_hemptySigma.Data()), 50, xminSigma, xmaxSigma, 10, yminSigma, ymaxSigma);
  sethemptystyle(hemptySigmaBor, -1, 1.25, -1, 0.05, -1, 0.04571);
  hemptySigmaBor->GetXaxis()->SetTickLength(0.03);

  //
  Float_t xminRatio = xminSigma, xmaxRatio = xmaxSigma, yminRatio = 0, yminRatioBor = -0.2, ymaxRatio = 2.7;  
  TH2F* hemptyRatio = new TH2F("hemptyRatio", ";p_{T} (GeV/c);#frac{Data}{FONLL}", 50, xminRatio, xmaxRatio, 10, yminRatio, ymaxRatio);
  sethemptystyle(hemptyRatio, 1.0, 0.5455, 0.13, 0.096, 0.1, 0.08889);
  hemptyRatio->GetYaxis()->SetLabelOffset(0.015);
  TH2F* hemptyRatioBor = new TH2F("hemptyRatioBor", ";p_{T} (GeV/c);#frac{Data}{FONLL}", 50, xminRatio, xmaxRatio, 10, yminRatioBor, ymaxRatio);
  sethemptystyle(hemptyRatioBor, -1, 0.36367, -1, 0.1825, -1, 0.15238);
  hemptyRatioBor->GetYaxis()->SetLabelOffset(0.012);
  hemptyRatioBor->GetXaxis()->SetTickLength(0.10);
  TH2F* hemptyRatioBorGM = new TH2F("hemptyRatioBorGM", ";p_{T} (GeV/c);#frac{Data}{GM-VFNS}", 50, xminRatio, xmaxRatio, 10, yminRatio, ymaxRatio);
  sethemptystyle(hemptyRatioBorGM, 1.0, 0.5455, 0.13, 0.12, 0.1, 0.10159);
  hemptyRatioBorGM->GetYaxis()->SetLabelOffset(0.015);
  hemptyRatioBorGM->GetXaxis()->SetTickLength(0.07);

  //
  TLatex* texCent = new TLatex(0.55,0.85,Form("Centrality %.0f - %.0f%s",centmin,centmax,texper.Data()));
  settex(texCent, 0.045);
  TLatex* texCentOnly = new TLatex(0.55,0.895,Form("Centrality %.0f - %.0f%s",centmin,centmax,texper.Data()));
  settex(texCentOnly, 0.0315);
  TLatex* texCentCal = new TLatex(0.55,0.55,Form("Centrality %.0f - %.0f%s",centmin,centmax,texper.Data()));
  settex(texCentCal, 0.045);
  TLatex* texCentBor = new TLatex(0.23,0.07,Form("Centrality %.0f - %.0f%s",centmin,centmax,texper.Data()));
  settex(texCentBor, 0.055);

  TLatex* texY = new TLatex(0.55,0.79,"|y| < 1.0");
  settex(texY, 0.045);
  TLatex* texYOnly = new TLatex(0.55,0.853,"|y| < 1.0");
  settex(texYOnly, 0.0315);
  TLatex* texYCal = new TLatex(0.55,0.853,"|y| < 1.0");
  settex(texYCal, 0.045);
  TLatex* texYBor = new TLatex(0.19,0.73427,"|y| < 1.0");
  settex(texYBor, 0.07328);

  //
  Float_t systnormhigh = isPbPb?normalizationUncertaintyForPbPb(centmin,centmax):normalizationUncertaintyForPP();
  Float_t systnormlow = isPbPb?normalizationUncertaintyForPbPb(centmin,centmax,false):0;

  TString str_texSystnorm = isPbPb?Form("Global uncert. + %.1f%s - %.1f%s",systnormhigh,texper.Data(),systnormlow,texper.Data()):Form("Global uncert. %.1f%s",systnormhigh,texper.Data());
  TLatex* texSystnorm = new TLatex(0.55, 0.61, str_texSystnorm.Data());
  settex(texSystnorm, 0.045);
  TLatex* texSystnormBor = new TLatex(0.23, 0.13, str_texSystnorm.Data());
  settex(texSystnormBor, 0.055);
  TLatex* texSystnormOnly = new TLatex(0.55, 0.727, str_texSystnorm.Data());
  settex(texSystnormOnly, 0.0315);

  TString str_legendSigma = legPbPb;
  TLegend* legendSigma = new TLegend(0.54,0.66,0.87,0.77,"");
  setleg(legendSigma, 0.045);
  legendSigma->AddEntry(hSigmaStatMB, str_legendSigma.Data(), "pf");
  legendSigma->AddEntry(gaeDzeroReferenceMB, "FONLL", "f");
  TLegend* legendSigmaOnly = new TLegend(0.54,0.8005,0.87,0.839,"");
  setleg(legendSigmaOnly, 0.0315);
  legendSigmaOnly->AddEntry(hSigmaStatMB, str_legendSigma.Data(), "pf");
  TLegend* legendSigmaCal = new TLegend(0.54,0.66,0.87,0.825,"");
  setleg(legendSigmaCal, 0.045);
  legendSigmaCal->AddEntry(hSigmaStatMB, str_legendSigma.Data(), "pf");
  legendSigmaCal->AddEntry(gaeDzeroReferenceMB, "FONLL", "f");
  TLegend* legendSigmaBor = new TLegend(0.22,0.18,0.55,0.39,"");
  setleg(legendSigmaBor, 0.055);
  legendSigmaBor->AddEntry(hSigmaStatMB, str_legendSigma.Data(), "pf");
  legendSigmaBor->AddEntry(gaeDzeroReferenceMB,"FONLL","f");

  //  
  TString str_texlumi = isPbPb?"530 #mub^{-1} (5.02 TeV PbPb)":"27.4 pb^{-1} (5.02 TeV pp)";
  TLatex* texlumi = new TLatex(0.95,0.96,str_texlumi.Data());
  settex(texlumi, 0.045, 32);
  TLatex* texlumiOnly = new TLatex(0.95,0.972,str_texlumi.Data());
  settex(texlumiOnly, 0.0315, 32);

  //
  TLatex* texcms = new TLatex(0.15,0.90,"CMS");
  settex(texcms, 0.06, 13, 62);
  TLatex* texcmsBor = new TLatex(0.19,0.87656,"CMS");
  settex(texcmsBor, 0.107, 13, 62);
  TLatex* texcmsOnly = new TLatex(0.15,0.93,"CMS");
  settex(texcmsOnly, 0.042, 13, 62);

  //
  // TString str_texDzero = "#frac{#scale[0.8]{1}}{#scale[0.8]{2}} (D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}})";
  TString str_texDzero = "#frac{D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}}{#scale[0.9]{2}}";
  TLatex* texDzero = new TLatex(0.15,0.84,str_texDzero.Data());
  settex(texDzero, 0.06, 13, 62);
  TLatex* texDzeroBor = new TLatex(0.939,0.915,str_texDzero.Data());
  settex(texDzeroBor, 0.107, 33, 62);
  TLatex* texDzeroOnly = new TLatex(0.15,0.888,str_texDzero.Data());
  settex(texDzeroOnly, 0.042, 13, 62);

  //
  TLine* l = new TLine(2.2,1,110,1);
  l->SetLineWidth(1);
  l->SetLineStyle(2);

  //
  TCanvas* cSigmaOnly = new TCanvas("cSigmaOnly", "", 750, 750);
  cSigmaOnly->SetFrameBorderMode(0);
  cSigmaOnly->Range(-1.989924,-0.2917772,25.49622,2.212202);
  cSigmaOnly->SetFillColor(0);
  cSigmaOnly->SetBorderMode(0);
  cSigmaOnly->SetBorderSize(2);
  cSigmaOnly->SetLeftMargin(0.12);
  cSigmaOnly->SetRightMargin(0.03);
  cSigmaOnly->SetTopMargin(0.049);
  cSigmaOnly->SetBottomMargin(0.099);
  cSigmaOnly->SetFrameBorderMode(0);
  cSigmaOnly->SetFrameBorderMode(0);
  cSigmaOnly->SetLogx();
  cSigmaOnly->SetLogy();
  cSigmaOnly->cd();

  hemptySigmaOnly->Draw();
  hSigmaStatMB->Draw("epsame"); 
  hSigmaStat->Draw("epsame"); 
  gaeCrossSystMB->Draw("5same");  
  gaeCrossSyst->Draw("5same");  
  if(isPbPb) texCentOnly->Draw();
  texYOnly->Draw();
  texSystnormOnly->Draw();
  legendSigmaOnly->Draw("same");
  texlumiOnly->Draw();
  texcmsOnly->Draw();
  texDzeroOnly->Draw();

  cSigmaOnly->SaveAs(Form("plotCrossSection/%s_NoRatio_%s.pdf",tprev.Data(),tend.Data()));

  //
  TCanvas* cSigma = new TCanvas("cSigma","",750,750);
  cSigma->SetFrameBorderMode(0);
  cSigma->SetFrameBorderMode(0);
  cSigma->Range(-1.989924,-0.2917772,25.49622,2.212202);
  cSigma->SetFillColor(0);
  cSigma->SetBorderMode(0);
  cSigma->SetBorderSize(2);
  cSigma->SetLeftMargin(0.12);
  cSigma->SetRightMargin(0.03);
  cSigma->SetTopMargin(0.07);
  cSigma->SetBottomMargin(0.15);
  cSigma->SetFrameBorderMode(0);
  cSigma->SetFrameBorderMode(0);
  cSigma->SetLogx();
  cSigma->cd();
  TPad* pSigma = new TPad("pSigma","",0,0.30,1,1);
  pSigma->SetFillColor(0);
  pSigma->SetBorderMode(0);
  pSigma->SetBorderSize(2);
  pSigma->SetLeftMargin(0.12);
  pSigma->SetRightMargin(0.03);
  pSigma->SetTopMargin(0.07);
  pSigma->SetBottomMargin(0);
  pSigma->SetLogy();
  pSigma->SetLogx();
  pSigma->Draw();
  pSigma->cd();

  hemptySigma->Draw();
  gaeDzeroReferenceMB->Draw("5same");
  gaeDzeroReference->Draw("5same");
  hSigmaStatMB->Draw("epsame"); 
  hSigmaStat->Draw("epsame"); 
  gaeCrossSystMB->Draw("5same");  
  gaeCrossSyst->Draw("5same");  
  if(isPbPb) texCent->Draw();
  texY->Draw();
  texSystnorm->Draw();
  legendSigma->Draw("same");
  texlumi->Draw();
  texcms->Draw();
  texDzero->Draw();

  cSigma->cd();
  TPad* pRatio = new TPad("pRatio","",0,0,1,0.30);
  pRatio->SetLeftMargin(0.12);
  pRatio->SetRightMargin(0.03);
  pRatio->SetTopMargin(0);
  pRatio->SetBottomMargin(0.33);
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

  cSigma->SaveAs(Form("plotCrossSection/%s_%s.pdf",tprev.Data(),tend.Data()));

  //
  TCanvas* cSigmaCal = new TCanvas("cSigmaCal","",750,750);
  cSigmaCal->SetFrameBorderMode(0);
  cSigmaCal->Range(-1.989924,-0.2917772,25.49622,2.212202);
  cSigmaCal->SetFillColor(0);
  cSigmaCal->SetBorderMode(0);
  cSigmaCal->SetBorderSize(2);
  cSigmaCal->SetLeftMargin(0.12);
  cSigmaCal->SetRightMargin(0.03);
  cSigmaCal->SetTopMargin(0.07);
  cSigmaCal->SetBottomMargin(0.15);
  cSigmaCal->SetFrameBorderMode(0);
  cSigmaCal->SetFrameBorderMode(0);
  cSigmaCal->SetLogx();
  cSigmaCal->cd();
  TPad* pSigmaCal = new TPad("pSigmaCal","",0,0.30,1,1);
  pSigmaCal->SetFillColor(0);
  pSigmaCal->SetBorderMode(0);
  pSigmaCal->SetBorderSize(2);
  pSigmaCal->SetLeftMargin(0.12);
  pSigmaCal->SetRightMargin(0.03);
  pSigmaCal->SetTopMargin(0.07);
  pSigmaCal->SetBottomMargin(0);
  pSigmaCal->SetLogy();
  pSigmaCal->SetLogx();
  pSigmaCal->Draw();
  pSigmaCal->cd();

  hemptySigma->Draw();
  gaeDzeroReferenceMB->Draw("5same");
  gaeDzeroReference->Draw("5same");
  drawTheoryPP(false,hSigmaStatMB,hSigmaStat,gaeCrossSystMB,gaeCrossSyst);
  hSigmaStatMB->Draw("epsame"); 
  hSigmaStat->Draw("epsame"); 
  gaeCrossSystMB->Draw("5same");  
  gaeCrossSyst->Draw("5same");  
  if(isPbPb==1) texCentCal->Draw();
  texYCal->Draw();
  texSystnorm->Draw();
  legendSigmaCal->AddEntry(gGMVFNSD5TeV,"GM-VFNS","f");
  legendSigmaCal->Draw("same");
  texlumi->Draw();
  texcms->Draw();
  texDzero->Draw();

  cSigmaCal->cd();
  TPad* pRatioCal = new TPad("pRatioCal","",0,0,1,0.30);
  pRatioCal->SetLeftMargin(0.12);
  pRatioCal->SetRightMargin(0.03);
  pRatioCal->SetTopMargin(0);
  pRatioCal->SetBottomMargin(0.33);
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
  cSigmaBor->SetLeftMargin(0.15);
  cSigmaBor->SetRightMargin(0.03);
  cSigmaBor->SetTopMargin(0.07);
  cSigmaBor->SetBottomMargin(0.15);
  cSigmaBor->SetFrameBorderMode(0);
  cSigmaBor->SetFrameBorderMode(0);
  cSigmaBor->SetLogx();
  cSigmaBor->cd();
  TPad* pSigmaBor = new TPad("pSigmaBor","",0,0.416666666667,1,1);
  pSigmaBor->SetFillColor(0);
  pSigmaBor->SetBorderMode(0);
  pSigmaBor->SetBorderSize(2);
  pSigmaBor->SetLeftMargin(0.15);
  pSigmaBor->SetRightMargin(0.03);
  pSigmaBor->SetTopMargin(0.07);
  pSigmaBor->SetBottomMargin(0);
  pSigmaBor->SetLogy();
  pSigmaBor->SetLogx();
  pSigmaBor->Draw();
  pSigmaBor->cd();

  hemptySigmaBor->Draw();
  gaeDzeroReferenceMB->Draw("5same");
  gaeDzeroReference->Draw("5same");
  drawTheoryPP(false,hSigmaStatMB,hSigmaStat,gaeCrossSystMB,gaeCrossSyst);
  hSigmaStatMB->Draw("epsame"); 
  hSigmaStat->Draw("epsame"); 
  gaeCrossSystMB->Draw("5same");  
  gaeCrossSyst->Draw("5same");  
  if(isPbPb==1) texCentBor->Draw();
  texYBor->Draw();
  texSystnormBor->Draw();
  legendSigmaBor->AddEntry(gGMVFNSD5TeV,"GM-VFNS","f");
  legendSigmaBor->Draw("same");
  texlumi->Draw();
  texcmsBor->Draw();
  texDzeroBor->Draw();

  cSigmaBor->cd();
  TPad* pRatioFOBor = new TPad("pRatioFOBor","",0,0.25,1,0.416666666667);
  pRatioFOBor->SetLeftMargin(0.15);
  pRatioFOBor->SetRightMargin(0.03);
  pRatioFOBor->SetTopMargin(0);
  pRatioFOBor->SetBottomMargin(0);
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
  pRatioGMBor->SetLeftMargin(0.15);
  pRatioGMBor->SetRightMargin(0.03);
  pRatioGMBor->SetTopMargin(0);
  pRatioGMBor->SetBottomMargin(0.33);
  pRatioGMBor->SetLogx();
  pRatioGMBor->Draw();
  pRatioGMBor->cd();

  hemptyRatioBorGM->Draw();
  drawTheoryPP(true,hSigmaStatMB,hSigmaStat,gaeCrossSystMB,gaeCrossSyst);
  l->Draw("same");  

  cSigmaBor->SaveAs(Form("plotCrossSection/%s_Calculation_BothRatio_%s.pdf",tprev.Data(),tend.Data()));
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

