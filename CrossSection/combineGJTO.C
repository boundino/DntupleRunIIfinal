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
  TGraphAsymmErrors* gaeCrossSyst = (TGraphAsymmErrors*)fGJ->Get("gaeCrossSyst");
  TGraphAsymmErrors* gaeBplusReference = (TGraphAsymmErrors*)fGJ->Get("gaeSigmaDzero");
  TGraphAsymmErrors* gaeRatioCrossFONLLunity = (TGraphAsymmErrors*)fGJ->Get("gaeRatioCrossFONLLunity");
  TH1D* hfPrompt = (TH1D*)fGJ->Get("hfprompt");


  TFile* outputfile = new TFile(outputplot.Data(),"recreate");
  outputfile->cd();
  hPtSigma->Write();
  gaeRatioCrossFONLLstat->Write();
  gaeRatioCrossFONLLsyst->Write();
  gaeCrossSyst->Write();
  gaeBplusReference->Write();
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


