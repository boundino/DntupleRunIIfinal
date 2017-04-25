using namespace std;
#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"

void combineGJTO(TString inputGJ, TString inputTO, TString outputplot, double lumiGJ, double lumiTO)
{
  TFile* fGJ = new TFile(inputGJ.Data());
  TFile* fTO = new TFile(inputTO.Data());
  TH1F* hPtSigmaGJ = (TH1F*)fGJ->Get("hPtSigma");
  hPtSigmaGJ->SetName("hPtSigmaGJ");
  hPtSigmaGJ->Scale(lumiGJ);
  TH1F* hPtSigmaTO = (TH1F*)fTO->Get("hPtSigma");
  hPtSigmaTO->SetName("hPtSigmaTO");
  hPtSigmaTO->Scale(lumiTO);
  TH1F* hPtSigma = (TH1F*)hPtSigmaGJ->Clone("hPtSigma");
  hPtSigma->Add(hPtSigmaTO);
  hPtSigma->Scale(1./(lumiGJ+lumiTO));
  
  TGraphAsymmErrors* gaeRatioCrossFONLLstat = (TGraphAsymmErrors*)fGJ->Get("gaeRatioCrossFONLLstat");
  TGraphAsymmErrors* gaeRatioCrossFONLLsyst = (TGraphAsymmErrors*)fGJ->Get("gaeRatioCrossFONLLsyst");
  TGraphAsymmErrors* gaeBplusReference = (TGraphAsymmErrors*)fGJ->Get("gaeSigmaDzero");
  TH1D* hfPrompt = (TH1D*)fGJ->Get("hfprompt");

  TGraphAsymmErrors* gaeCrossSystGJ = (TGraphAsymmErrors*)fGJ->Get("gaeCrossSyst");
  gaeCrossSystGJ->SetName("gaeCrossSystGJ");
  TGraphAsymmErrors* gaeRatioCrossFONLLunityGJ = (TGraphAsymmErrors*)fGJ->Get("gaeRatioCrossFONLLunity");
  gaeRatioCrossFONLLunityGJ->SetName("gaeRatioCrossFONLLunityGJ");
  TGraphAsymmErrors* gaeCrossSystTO = (TGraphAsymmErrors*)fTO->Get("gaeCrossSyst");
  gaeCrossSystTO->SetName("gaeCrossSystTO");
  TGraphAsymmErrors* gaeRatioCrossFONLLunityTO = (TGraphAsymmErrors*)fTO->Get("gaeRatioCrossFONLLunity");
  gaeRatioCrossFONLLunityTO->SetName("gaeRatioCrossFONLLunityTO");

  TGraphAsymmErrors* gaeCrossSyst = (TGraphAsymmErrors*)gaeCrossSystGJ->Clone("gaeCrossSyst");
  TGraphAsymmErrors* gaeRatioCrossFONLLunity = (TGraphAsymmErrors*)gaeRatioCrossFONLLunityGJ->Clone("gaeRatioCrossFONLLunity");
  Int_t ngrbins = gaeCrossSyst->GetN();
  for(int i=0;i<ngrbins;i++)
    {
      Double_t xGJ,yGJ,xTO,yTO;
      gaeCrossSystGJ->GetPoint(i,xGJ,yGJ);
      gaeCrossSystTO->GetPoint(i,xTO,yTO);
      Double_t x = xGJ;
      Double_t y = (yGJ*lumiGJ+yTO*lumiTO)/(lumiGJ+lumiTO);
      gaeCrossSyst->SetPoint(i,x,y);
      Double_t exl = gaeCrossSystGJ->GetErrorXlow(i);
      Double_t exh = gaeCrossSystGJ->GetErrorXhigh(i);
      Double_t eyl = (gaeCrossSystGJ->GetErrorYlow(i)*lumiGJ+gaeCrossSystTO->GetErrorYlow(i)*lumiTO)/(lumiGJ+lumiTO);
      Double_t eyh = (gaeCrossSystGJ->GetErrorYhigh(i)*lumiGJ+gaeCrossSystTO->GetErrorYhigh(i)*lumiTO)/(lumiGJ+lumiTO);
      gaeCrossSyst->SetPointError(i,exl,exh,eyl,eyh);

      Double_t xfGJ,yfGJ,xfTO,yfTO;
      gaeRatioCrossFONLLunityGJ->GetPoint(i,xfGJ,yfGJ);
      gaeRatioCrossFONLLunityTO->GetPoint(i,xfTO,yfTO);
      Double_t xf = xfGJ;
      Double_t yf = (yfGJ*lumiGJ+yfTO*lumiTO)/(lumiGJ+lumiTO);
      gaeRatioCrossFONLLunity->SetPoint(i,xf,yf);
      Double_t exfl = gaeRatioCrossFONLLunityGJ->GetErrorXlow(i);
      Double_t exfh = gaeRatioCrossFONLLunityGJ->GetErrorXhigh(i);
      Double_t eyfl = (gaeRatioCrossFONLLunityGJ->GetErrorYlow(i)*lumiGJ+gaeRatioCrossFONLLunityTO->GetErrorYlow(i)*lumiTO)/(lumiGJ+lumiTO);
      Double_t eyfh = (gaeRatioCrossFONLLunityGJ->GetErrorYhigh(i)*lumiGJ+gaeRatioCrossFONLLunityTO->GetErrorYhigh(i)*lumiTO)/(lumiGJ+lumiTO);
      gaeRatioCrossFONLLunity->SetPointError(i,exfl,exfh,eyfl,eyfh);
    }

  TFile* outputfile = new TFile(outputplot.Data(),"recreate");
  outputfile->cd();
  hPtSigma->Write();
  gaeRatioCrossFONLLstat->Write();
  gaeRatioCrossFONLLsyst->Write();
  gaeBplusReference->Write();
  gaeCrossSyst->Write();
  gaeRatioCrossFONLLunity->Write();
  hfPrompt->Write();
  outputfile->Close();
}


int main(int argc, char *argv[])
{
  if(argc==6)
    {
      combineGJTO(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]));
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
  
}


