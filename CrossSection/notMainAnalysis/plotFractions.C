using namespace std;
#include "uti.h"
#include "plotFractionsHeads/bFeedDownCorrectionNew.C"

const int nBins=14;
double ptBins[nBins+1] = {2.,3.,4.,5.,6.,8.,10.,12.5,15.0,20.,25.,30.,40.,60.,100};

void plotFractions(TString tPbPb="PbPb", Float_t centmax=100, Float_t centmin=0)
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  Bool_t isPbPb = (tPbPb=="PbPb")?true:false;

  TH1F* hfpromptPre = new TH1F("hfpromptPre","",nBins,ptBins);
  TH1F* hfpromptNew = new TH1F("hfpromptNew","",nBins,ptBins);

  for(int i=0;i<nBins;i++)
    {
      double prompt;
      if(centmax==100) prompt=bFeedDownCorrectionNew((ptBins[i]+ptBins[i+1])/2.,isPbPb,30);
      else if(centmax==10) prompt=bFeedDownCorrectionNew((ptBins[i]+ptBins[i+1])/2.,isPbPb,31);
      hfpromptNew->SetBinContent(i+1,prompt);
      hfpromptNew->SetBinError(i+1,0);

      prompt=bFeedDownCorrectionNew((ptBins[i]+ptBins[i+1])/2.,isPbPb,1);
      hfpromptPre->SetBinContent(i+1,prompt);
      hfpromptPre->SetBinError(i+1,0);
  }

  TH2F* hempty = new TH2F("hempty","",20,0.,102,10.,0.,1.);  
  hempty->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hempty->GetYaxis()->SetTitle("Prompt fraction");
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitleOffset(1.3);
  hempty->GetYaxis()->SetTitleOffset(1.8);
  hempty->GetXaxis()->SetTitleSize(0.045);
  hempty->GetYaxis()->SetTitleSize(0.045);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.04);
  hempty->GetYaxis()->SetLabelSize(0.04);

  hfpromptPre->SetMarkerSize(1.1);
  hfpromptPre->SetMarkerStyle(21);
  hfpromptPre->SetLineColor(kBlue);
  hfpromptPre->SetMarkerColor(kBlue);
  hfpromptNew->SetMarkerSize(1.1);
  hfpromptNew->SetMarkerStyle(20);
  hfpromptNew->SetLineColor(kRed);
  hfpromptNew->SetMarkerColor(kRed);

  TString tper = "%";
  TLatex* texCent = new TLatex(0.32,0.58, Form("Cent. %.0f-%.0f%s",centmin,centmax,tper.Data()));
  texCent->SetNDC();
  texCent->SetTextAlign(12);
  texCent->SetTextSize(0.04);
  texCent->SetTextFont(42);

  TCanvas* cInclusive = new TCanvas("cInclusive","",600,600);
  hempty->Draw();

  hfpromptPre->Draw("plsame");
  hfpromptNew->Draw("plsame");

  TLatex* texCms = new TLatex(0.16,0.95, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  texCms->Draw();

  TLatex* texCol = new TLatex(0.94,0.95, Form("%s #sqrt{s_{NN}} = 5.02 TeV",tPbPb.Data()));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);
  texCol->Draw();

  texCent->Draw();
  TLegend* legInclusive = new TLegend(0.30, 0.45, 0.80, 0.55);
  legInclusive->SetBorderSize(0);
  legInclusive->SetTextSize(0.04);
  legInclusive->SetTextFont(42);
  legInclusive->SetFillStyle(0);
  legInclusive->AddEntry(hfpromptPre, "Preliminary", "pl");
  legInclusive->AddEntry(hfpromptNew, "New", "pl");
  legInclusive->Draw();
  if(isPbPb) cInclusive->SaveAs(Form("plotsPromptfraction/cPromptFraction_%s_cent_%.0f_%.0f.pdf",tPbPb.Data(),centmin,centmax));
  else cInclusive->SaveAs(Form("plotsPromptfraction/cPromptFraction_%s.pdf",tPbPb.Data()));

}

