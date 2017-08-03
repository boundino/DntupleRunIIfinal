#include "uti.h"
#include "systematics.h"
#include "drawTheory.h"
#include "CombineCrossSections.h"

void CombineCrossSectionsPPnPbPb(TString filePPMB, TString filePP, TString filePbPb0100MB, TString filePbPb0100, TString filePbPb010MB, TString filePbPb010)
{
  void scaleNsetCrossSection(TH1D* hSigmaStat, TGraphAsymmErrors* gaeCrossSyst, Double_t fscale, Int_t pcolor, Int_t pstyle, Bool_t verbose=false);

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TFile* infilePPMB = new TFile(filePPMB.Data());  
  TGraphAsymmErrors* gaeRatioCrossFONLLstatMB = (TGraphAsymmErrors*)infilePPMB->Get("gaeRatioCrossFONLLstat");
  TGraphAsymmErrors* gaeRatioCrossFONLLsystMB = (TGraphAsymmErrors*)infilePPMB->Get("gaeRatioCrossFONLLsyst");
  TGraphAsymmErrors* gaeDzeroReferenceMB = (TGraphAsymmErrors*)infilePPMB->Get("gaeSigmaDzero");
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
  TGraphAsymmErrors* gaeDzeroReference = (TGraphAsymmErrors*)infilePP->Get("gaeSigmaDzero");
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
  setthgrstyle(gaeDzeroReferenceMB,       -1, -1, -1,  kOrange+7, -1, 2,      kOrange+1, 0.2, 1001);
  setthgrstyle(gaeDzeroReference,         -1, -1, -1,  kOrange+7, -1, 2,      kOrange+1, 0.2, 1001);
  setthgrstyle(gaeRatioCrossFONLLunityMB, -1, -1, -1,  kOrange+7, -1, 2,      kOrange+1, 0.2, 1001);
  setthgrstyle(gaeRatioCrossFONLLunity,   -1, -1, -1,  kOrange+7, -1, 2,      kOrange+1, 0.2, 1001);

  setthgrstyle(gaeRatioCrossFONLLstatMB,  1,  20, 1.4, 1,         -1, 2,      -1,        -1,  -1);
  setthgrstyle(gaeRatioCrossFONLLstat,    1,  20, 1.4, 1,         -1, 2,      -1,        -1,  -1);
  setthgrstyle(gaeRatioCrossFONLLsystMB,  -1, -1, -1,  1,         -1, 2/*3*/, 1,         -1,  0);
  setthgrstyle(gaeRatioCrossFONLLsyst,    -1, -1, -1,  1,         -1, 2/*3*/, 1,         -1,  0);
  // data
 scaleNsetCrossSection(hSigmaPPStat,         gaeCrossPPSyst,         1,      1,        20);
 scaleNsetCrossSection(hSigmaPPStatMB,       gaeCrossPPSystMB,       1,      1,        20);
 scaleNsetCrossSection(hSigmaPbPb0100Stat,   gaeCrossPbPb0100Syst,   1/10.,  kRed+2,   21);
 scaleNsetCrossSection(hSigmaPbPb0100StatMB, gaeCrossPbPb0100SystMB, 1/10.,  kRed+2,   21);
 scaleNsetCrossSection(hSigmaPbPb010Stat,    gaeCrossPbPb010Syst,    1/100., kAzure+3, 33);
 scaleNsetCrossSection(hSigmaPbPb010StatMB,  gaeCrossPbPb010SystMB,  1/100., kAzure+3, 33);

  //
  TString str_hemptySigmaOnlyLong = "#frac{d#sigma_{pp}}{dp_{T}}  or  #frac{1}{T_{AA}} #frac{dN_{PbPb}}{dp_{T}}  #left(#frac{pb}{GeV/c}#right)";
  TH2F* hemptySigmaOnlyLong = new TH2F("hemptySigmaOnlyLong", Form(";p_{T} (GeV/c);%s",str_hemptySigmaOnlyLong.Data()), 50, 0., 100., 10., 1.e-5, 1.e12);
  sethemptystyle(hemptySigmaOnlyLong, xtitleoffsetpLong, ytitleoffsetpLong, xtitlesizepLong, ytitlesizepLong, xlabelsizepLong, ylabelsizepLong);
  hemptySigmaOnlyLong->GetXaxis()->SetLabelOffset(-0.015);

  //
  TString str_texLumi = "27.4 pb^{-1} (5.02 TeV pp) + 530 #mub^{-1} (5.02 TeV PbPb)";
  TLatex* texLumiOnlyLong = new TLatex(LumixposLong, LumiyposLong, str_texLumi.Data());
  settex(texLumiOnlyLong, LumisizeLong, 32);
  //
  TLatex* texCMSOnlyLong = new TLatex(CMSxposLong, CMSyposLong, str_texCMS.Data());
  settex(texCMSOnlyLong, CMSsizeLong, 13, 62);
  //
  TLatex* texYOnlyLong = new TLatex(YxposLong, YyposLong, str_texY.Data());
  settex(texYOnlyLong, YsizeLong, 12);
  //
  TLatex* texDzeroOnlyLong = new TLatex(DZEROxposLong, DZEROyposLong, str_texDzero.Data());
  settex(texDzeroOnlyLong, DZEROsizeLong, 33, 62);

  //
  Float_t systnormPP = normalizationUncertaintyForPP();
  Float_t systnormPbPbhigh0100 = normalizationUncertaintyForPbPb(0,100);
  Float_t systnormPbPblow0100 = normalizationUncertaintyForPbPb(0,100,false);
  Float_t systnormPbPbhigh010 = normalizationUncertaintyForPbPb(0,10);
  Float_t systnormPbPblow010 = normalizationUncertaintyForPbPb(0,10,false);

  TLegend* legendSigmaOnlyLong = new TLegend(0.215, 0.11, 0.56, 0.23, "");
  setleg(legendSigmaOnlyLong, 0.037);
  legendSigmaOnlyLong->AddEntry(hSigmaPPStatMB, "pp", "pf");
  legendSigmaOnlyLong->AddEntry(hSigmaPbPb0100StatMB, "PbPb Cent. 0-100 (/10)", "pf");
  legendSigmaOnlyLong->AddEntry(hSigmaPbPb010StatMB, "PbPb Cent. 0-10 (/100)", "pf");
  //
  Float_t xpostexGuOnlyLong = 0.73, ypostexGuOnlyLong = 0.20, dypostexGuOnlyLong = 0.0401;
  TLatex* texGuOnlyLong = new TLatex(xpostexGuOnlyLong, ypostexGuOnlyLong+dypostexGuOnlyLong, "Global uncert.");
  settex(texGuOnlyLong, 0.037);
  TLatex* texGuOnlyLongPP = new TLatex(xpostexGuOnlyLong, ypostexGuOnlyLong, Form("%.1f%s", systnormPP, texper.Data()));
  settex(texGuOnlyLongPP, 0.037);
  TLatex* texGuOnlyLongPbPb0100 = new TLatex(xpostexGuOnlyLong, ypostexGuOnlyLong = (ypostexGuOnlyLong-dypostexGuOnlyLong), Form("+ %.1f%s, - %.1f%s", texper.Data(), systnormPbPbhigh0100, texper.Data(), systnormPbPblow0100,texper.Data()));
  settex(texGuOnlyLongPbPb0100, 0.037);
  TLatex* texGuOnlyLongPbPb010 = new TLatex(xpostexGuOnlyLong, ypostexGuOnlyLong = (ypostexGuOnlyLong-dypostexGuOnlyLong), Form("+ %.1f%s, - %.1f%s", texper.Data(), systnormPbPbhigh010, texper.Data(), systnormPbPblow010,texper.Data()));
  settex(texGuOnlyLongPbPb010, 0.037);

  //
  TCanvas* cSigmaOnlyLong = new TCanvas("cSigmaOnlyLong","",750,900);
  cSigmaOnlyLong->SetFrameBorderMode(0);
  cSigmaOnlyLong->SetFillColor(0);
  cSigmaOnlyLong->SetBorderMode(0);
  cSigmaOnlyLong->SetBorderSize(2);

  cSigmaOnlyLong->SetLeftMargin(leftmarginp);
  cSigmaOnlyLong->SetRightMargin(rightmarginp);
  cSigmaOnlyLong->SetTopMargin(topmarginpLong);
  cSigmaOnlyLong->SetBottomMargin(bottommarginpLong);
  cSigmaOnlyLong->SetLogx();
  cSigmaOnlyLong->SetLogy();
  cSigmaOnlyLong->cd();

  hemptySigmaOnlyLong->Draw();
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

  texYOnlyLong->Draw();
  texGuOnlyLong->Draw();
  texGuOnlyLongPP->Draw();
  texGuOnlyLongPbPb0100->Draw();
  texGuOnlyLongPbPb010->Draw();
  legendSigmaOnlyLong->Draw("same");
  texLumiOnlyLong->Draw();
  texCMSOnlyLong->Draw();
  texDzeroOnlyLong->Draw();

  cSigmaOnlyLong->SaveAs("plotCrossSection/CrossSection_ComparisonPPnPbPb_noRatio_Long.pdf");


  /*
  gaeDzeroReferenceMB->Draw("5same");
  gaeDzeroReference->Draw("5same");
  */

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

