#include "uti.h"
#include "TLegendEntry.h"


void YieldStudies(TString inputPP="ROOTfiles/hPtSpectrumDzeroPbPb.root",TString inputPPMC="ROOTfiles/hPtSpectrumDzeroPbPbMBMCClosure.root")
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);


  TFile* filesPPMC=new TFile(inputPPMC.Data());  
  TH1D* hClosure=(TH1D*)filesPPMC->Get("hPtCor");
  TH1D* hPtGen=(TH1D*)filesPPMC->Get("hPtGen");
  hClosure->Sumw2();
  hClosure->Divide(hPtGen);

  TH2F* hemptyClosure=new TH2F("hemptyClosure","",50,0.,100.,10.,0.7,1.3);  
  hemptyClosure->GetXaxis()->CenterTitle();
  hemptyClosure->GetYaxis()->CenterTitle();
  hemptyClosure->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyClosure->GetYaxis()->SetTitle("Corr. yield/Gen");
  hemptyClosure->GetXaxis()->SetTitleOffset(1.);
  hemptyClosure->GetYaxis()->SetTitleOffset(1.4);
  hemptyClosure->GetXaxis()->SetTitleSize(0.045);
  hemptyClosure->GetYaxis()->SetTitleSize(0.05);
  hemptyClosure->GetXaxis()->SetTitleFont(42);
  hemptyClosure->GetYaxis()->SetTitleFont(42);
  hemptyClosure->GetXaxis()->SetLabelFont(42);
  hemptyClosure->GetYaxis()->SetLabelFont(42);
  hemptyClosure->GetXaxis()->SetLabelSize(0.04);
  hemptyClosure->GetYaxis()->SetLabelSize(0.04);  
  
  TCanvas* cClosure = new TCanvas("cClosure","",500,500);
  cClosure->cd(1);
  hemptyClosure->Draw();
  hClosure->SetLineWidth(2);
  hClosure->Draw("same");
  TLine* lunity = new TLine(5,1,100,1);
  lunity->SetLineWidth(2);
  lunity->SetLineStyle(2);
  lunity->Draw("same");
  cClosure->SaveAs("cClosure.pdf");

  }


int main(int argc, char *argv[])
{
  if((argc != 3))
  {
    std::cout << "Wrong number of inputs" << std::endl;
    return 1;
  }
  
  if(argc == 3)
    YieldStudies(argv[1], argv[2]);
  return 0;
}


