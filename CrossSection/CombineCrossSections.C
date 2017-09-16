#include "uti.h"
#include "systematics.h"
#include "drawTheory.h"
#include "PaperDraw.h"

void CombineCrossSections(TString filenameMB="ROOTfiles/CrossSectionFONLLPPMB.root", TString filename="ROOTfiles/CrossSectionFONLLPP.root", Int_t isPbPb=0, Float_t centmin=0., Float_t centmax=100., Bool_t verbose=true)
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
  Float_t xminSigma = 0, xmaxSigma = 100., yminSigma = 0.11, ymaxSigma = 1.e13;
  TH2F* hemptySigmaBor = new TH2F("hemptySigmaBor", Form(";;%s", str_hemptySigma.Data()), 50, xminSigma, xmaxSigma, 10, yminSigma, ymaxSigma);
  sethemptystyle(hemptySigmaBor, -1, ytitleoffsetpSigma, -1, ytitlesizepSigma, -1, ylabelsizepSigma);
  hemptySigmaBor->GetXaxis()->SetTickLength(0.03);
  Float_t xminRatio = xminSigma, xmaxRatio = xmaxSigma, yminRatio = 0, yminRatioBor = -0.3, ymaxRatio = 2.7, ymaxRatioBor = 2.7;  
  TH2F* hemptyRatioBor = new TH2F("hemptyRatioBor", ";p_{T} (GeV/c);#frac{Data}{FONLL}", 50, xminRatio, xmaxRatio, 10, yminRatioBor, ymaxRatioBor);
  sethemptystyle(hemptyRatioBor, -1, ytitleoffsetpFOBor, -1, ytitlesizepFOBor, -1, ylabelsizepFOBor);
  hemptyRatioBor->GetYaxis()->SetLabelOffset(0.012);
  hemptyRatioBor->GetXaxis()->SetTickLength(0.10);
  hemptyRatioBor->GetYaxis()->SetTickLength(0.026);
  TH2F* hemptyRatioBorGM = new TH2F("hemptyRatioBorGM", ";p_{T} (GeV/c);#frac{Data}{GM-VFNS}", 50, xminRatio, xmaxRatio, 10, yminRatio, ymaxRatio);
  sethemptystyle(hemptyRatioBorGM, xtitleoffsetpGMBor, ytitleoffsetpGMBor, xtitlesizepGMBor, ytitlesizepGMBor, xlabelsizepGMBor, ylabelsizepGMBor);
  hemptyRatioBorGM->GetXaxis()->SetLabelOffset(-0.03);
  hemptyRatioBorGM->GetYaxis()->SetLabelOffset(0.015);
  hemptyRatioBorGM->GetXaxis()->SetTickLength(0.07);

  //  
  TString str_texLumi = isPbPb?"530 #mub^{-1} (5.02 TeV PbPb)":"27.4 pb^{-1} (5.02 TeV pp)";
  TLatex* texLumi = new TLatex(LumixposBor, LumiyposBor, str_texLumi.Data());
  settex(texLumi, LumisizeBor, 32);
  //
  TLatex* texCMSBor = new TLatex(CMSxposBor, CMSyposBor, str_texCMS.Data());
  settex(texCMSBor, CMSsizeBor, 13, 62);
  //
  TLatex* texYBor = new TLatex(YxposBor, YyposBor, str_texY.Data());
  settex(texYBor, YsizeBor, 12);
  //
  TLatex* texDzeroBor = new TLatex(DZEROxposBor, DZEROyposBor, str_texDzero.Data());
  settex(texDzeroBor, DZEROsizeBor, 33, 62);

  //
  TString str_legendSigma = legPbPb;
  TLegend* legendSigmaBor = new TLegend(0.25, 0.18, 0.58, 0.39,"");
  setleg(legendSigmaBor, 0.055);
  legendSigmaBor->AddEntry(hSigmaStatMB, str_legendSigma.Data(), "pf");
  legendSigmaBor->AddEntry(gaeDzeroReferenceMB,"FONLL","f");

  Float_t systnormhigh = isPbPb?normalizationUncertaintyForPbPb(centmin,centmax):normalizationUncertaintyForPP();
  Float_t systnormlow = isPbPb?normalizationUncertaintyForPbPb(centmin,centmax,false):0;
  TString str_texSystnorm = isPbPb?Form("Global uncert. + %.1f%s - %.1f%s",systnormhigh,texper.Data(),systnormlow,texper.Data()):Form("Global uncert. %.1f%s",systnormhigh,texper.Data());
  TLatex* texSystnormBor = new TLatex(0.26, 0.13, str_texSystnorm.Data());
  settex(texSystnormBor, 0.055);

  TLatex* texCentBor = new TLatex(0.26,0.07,Form("Centrality %.0f - %.0f%s",centmin,centmax,texper.Data()));
  settex(texCentBor, 0.055);

  //
  TLine* l = new TLine(xminRatio, 1, xmaxRatio, 1);
  l->SetLineWidth(1);
  l->SetLineStyle(2);

  //
  TCanvas* cSigmaBor = new TCanvas("cSigmaBor","",750,900);
  cSigmaBor->SetFrameBorderMode(0);
  cSigmaBor->SetFillColor(0);
  cSigmaBor->SetBorderMode(0);
  cSigmaBor->SetBorderSize(2);
  cSigmaBor->cd();
  TPad* pSigmaBor = new TPad("pSigmaBor", "", 0, ypadh, 1, 1);
  pSigmaBor->SetFillColor(0);
  pSigmaBor->SetBorderMode(0);
  pSigmaBor->SetBorderSize(2);
  pSigmaBor->SetLeftMargin(leftmarginp);
  pSigmaBor->SetRightMargin(rightmarginp);
  pSigmaBor->SetTopMargin(topmarginpSigma);
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
  texLumi->Draw();
  texCMSBor->Draw();
  texDzeroBor->Draw();

  cSigmaBor->cd();
  TPad* pRatioFOBor = new TPad("pRatioFOBor", "", 0, ypadl, 1, ypadh);
  pRatioFOBor->SetLeftMargin(leftmarginp);
  pRatioFOBor->SetRightMargin(rightmarginp);
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
  TPad* pRatioGMBor = new TPad("pRatioGMBor", "", 0, 0, 1, ypadl);
  pRatioGMBor->SetLeftMargin(leftmarginp);
  pRatioGMBor->SetRightMargin(rightmarginp);
  pRatioGMBor->SetTopMargin(0);
  pRatioGMBor->SetBottomMargin(bottommarginpGMBor);
  pRatioGMBor->SetLogx();
  pRatioGMBor->Draw();
  pRatioGMBor->cd();

  hemptyRatioBorGM->Draw();
  drawTheoryPP(true,hSigmaStatMB,hSigmaStat,gaeCrossSystMB,gaeCrossSyst);
  l->Draw("same");  

  cSigmaBor->SaveAs(Form("plotCrossSection/%s_Calculation_BothRatio_%s.pdf",tprev.Data(),tend.Data()));

  if(verbose)
  {
    for(int i=0;i<(hSigmaStatMB->GetSize()-2);i++)
      {
        std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hSigmaStatMB->GetBinCenter(i+1)-hSigmaStatMB->GetBinWidth(i+1)/2.;
        std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hSigmaStatMB->GetBinCenter(i+1)+hSigmaStatMB->GetBinWidth(i+1)/2.;
        std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hSigmaStatMB->GetBinCenter(i+1);
        std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<hSigmaStatMB->GetBinContent(i+1);
        std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<hSigmaStatMB->GetBinError(i+1);
        // std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<gaeCrossSystMB->GetErrorYhigh(i);
        std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<gaeCrossSystMB->GetErrorYlow(i)<<std::endl;
      }
    for(int i=0;i<(hSigmaStat->GetSize()-2);i++)
      {
        std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hSigmaStat->GetBinCenter(i+1)-hSigmaStat->GetBinWidth(i+1)/2.;
        std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hSigmaStat->GetBinCenter(i+1)+hSigmaStat->GetBinWidth(i+1)/2.;
        std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<hSigmaStat->GetBinCenter(i+1);
        std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<hSigmaStat->GetBinContent(i+1);
        std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<hSigmaStat->GetBinError(i+1);
        // std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<gaeCrossSyst->GetErrorYhigh(i);
        std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<gaeCrossSyst->GetErrorYlow(i)<<std::endl;
      }
  }



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

