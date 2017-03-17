using namespace std;
#include "uti.h"
#include "parameters.h"
#include "fitDdraw.h"

void fitDdraw(int usePbPb, TString input, TString collsyst, Float_t centmin=0., Float_t centmax=0., Int_t useGJ=1.)
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
  bool isGJ=(bool)(useGJ);
  tGJ = isGJ?"GJ":"TO";

  TF1* fit(TH1D* h, TH1D* hMCSignal, TH1D* hMCSwapped, Double_t ptmin, Double_t ptmax, bool isPbPb, TF1* &total, Float_t centmin, Float_t centmax);

  TString infname = Form("%s.root",input.Data());
  TFile* f = new TFile(infname.Data());
  TF1 *totalmass;
  for(int i=0;i<nBins;i++)
    {
      TH1D* h = (TH1D*)f->Get(Form("h-%d",i+1));
      TH1D* hMCSignal = (TH1D*)f->Get(Form("hMCSignal-%d",i+1));
      TH1D* hMCSwapped = (TH1D*)f->Get(Form("hMCSwapped-%d",i+1));
      TF1* f = fit(h,hMCSignal,hMCSwapped,ptBins[i],ptBins[i+1],isPbPb,totalmass,centmin,centmax);
    }  
}

int main(int argc, char *argv[])
{
  if(argc==7)
    {
      fitDdraw(atoi(argv[1]), argv[2], argv[3], atof(argv[4]), atof(argv[5]),atoi(argv[6]));
      return 0;
    }
  else if(argc==6)
    {
      fitDdraw(atoi(argv[1]), argv[2], argv[3], atof(argv[4]), atof(argv[5]));
      return 0;
    }
  else if(argc==4)
    {
      fitDdraw(atoi(argv[1]), argv[2], argv[3]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
  
}
