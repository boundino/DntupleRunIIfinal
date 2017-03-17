using namespace std;
#include "uti.h"
#include "parameters.h"
#include "fitDdraw.h"

void combineGJTOfitD(int usePbPb, TString inputGJ, TString inputTO, TString collsyst, Float_t centmin=0., Float_t centmax=0.)
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  collisionsystem = collsyst;
  hiBinMin = centmin*2;
  hiBinMax = centmax*2;
  centMin = centmin;
  centMax = centmax;
  bool isPbPb=(bool)(usePbPb);

  TF1* fit(TH1D* h, TH1D* hMCSignal, TH1D* hMCSwapped, Double_t ptmin, Double_t ptmax, bool isPbPb, TF1* &total, Float_t centmin, Float_t centmax);

  TString infnameGJ = Form("%s.root",inputGJ.Data());
  TString infnameTO = Form("%s.root",inputTO.Data());
  TFile* fGJ = new TFile(infnameGJ.Data());
  TFile* fTO = new TFile(infnameTO.Data());
  TF1 *totalmass;
  for(int i=0;i<nBins;i++)
    {
      TH1D* hGJ = (TH1D*)fGJ->Get(Form("h-%d",i+1));
      hGJ->SetName(Form("hGJ-%d",i+1));
      TH1D* hMCSignalGJ = (TH1D*)fGJ->Get(Form("hMCSignal-%d",i+1));
      hMCSignalGJ->SetName(Form("hMCSignalGJ-%d",i+1));
      TH1D* hMCSwappedGJ = (TH1D*)fGJ->Get(Form("hMCSwapped-%d",i+1));
      hMCSwappedGJ->SetName(Form("hMCSwappedGJ-%d",i+1));
      TH1D* hTO = (TH1D*)fTO->Get(Form("h-%d",i+1));
      hTO->SetName(Form("hTO-%d",i+1));
      TH1D* hMCSignalTO = (TH1D*)fTO->Get(Form("hMCSignal-%d",i+1));
      hMCSignalTO->SetName(Form("hMCSignalTO-%d",i+1));
      TH1D* hMCSwappedTO = (TH1D*)fTO->Get(Form("hMCSwapped-%d",i+1));
      hMCSwappedTO->SetName(Form("hMCSwappedTO-%d",i+1));
      
      TH1D* h = (TH1D*)hGJ->Clone(Form("h-%d",i+1));
      h->Add(hTO);
      TH1D* hMCSignal = (TH1D*)hMCSignalGJ->Clone(Form("hMCSignal-%d",i+1));
      hMCSignal->Add(hMCSignalTO);
      TH1D* hMCSwapped = (TH1D*)hMCSwappedGJ->Clone(Form("hMCSwapped-%d",i+1));
      hMCSwapped->Add(hMCSwappedTO);

      TF1* f = fit(h,hMCSignal,hMCSwapped,ptBins[i],ptBins[i+1],isPbPb,totalmass,centmin,centmax);
    }  
}

int main(int argc, char *argv[])
{
  if(argc==7)
    {
      combineGJTOfitD(atoi(argv[1]), argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]));
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
  
}


