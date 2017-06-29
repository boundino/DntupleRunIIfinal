using namespace std;
#include "uti.h"
#include "fitDdraw.h"

void fitDstats(TString outputPP="ROOTfiles/hFitParPP", TString outputPPMB="ROOTfiles/hFitParPPMB", TString outputPbPb0100="ROOTfiles/hFitParPbPb", TString outputPbPbMB0100="ROOTfiles/hFitParPbPbMB", TString outputPbPb010="ROOTfilesCent10/hFitParPbPb", TString outputPbPbMB010="ROOTfilesCent10/hFitParPbPbMB")
{
  //const int nbins = 14;
  //Float_t ptbins[nbins+1] = {2, 3, 4, 5, 6, 8, 10, 12.5, 15, 20, 25, 30, 40, 60, 100};
  
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  TString infnamePP = Form("%s.root",outputPP.Data());
  TFile* infPP = new TFile(infnamePP.Data());
  TH1D* hPtMCPP = (TH1D*)infPP->Get("hPtMC");
  hPtMCPP->SetName("hPtMCPP");
  TH1D* hPtMCNoswapPP = (TH1D*)infPP->Get("hPtMCNoswap");
  hPtMCNoswapPP->SetName("hPtMCNoswapPP");

  TString infnamePPMB = Form("%s.root",outputPPMB.Data());
  TFile* infPPMB = new TFile(infnamePPMB.Data());
  TH1D* hPtMCPPMB = (TH1D*)infPPMB->Get("hPtMC");
  hPtMCPPMB->SetName("hPtMCPPMB");
  TH1D* hPtMCNoswapPPMB = (TH1D*)infPPMB->Get("hPtMCNoswap");
  hPtMCNoswapPPMB->SetName("hPtMCNoswapPPMB");

  TString infnamePbPb0100 = Form("%s.root",outputPbPb0100.Data());
  TFile* infPbPb0100 = new TFile(infnamePbPb0100.Data());
  TH1D* hPtMCPbPb0100 = (TH1D*)infPbPb0100->Get("hPtMC");
  hPtMCPbPb0100->SetName("hPtMCPbPb0100");
  TH1D* hPtMCNoswapPbPb0100 = (TH1D*)infPbPb0100->Get("hPtMCNoswap");
  hPtMCNoswapPbPb0100->SetName("hPtMCNoswapPbPb0100");

  TString infnamePbPbMB0100 = Form("%s.root",outputPbPbMB0100.Data());
  TFile* infPbPbMB0100 = new TFile(infnamePbPbMB0100.Data());
  TH1D* hPtMCPbPbMB0100 = (TH1D*)infPbPbMB0100->Get("hPtMC");
  hPtMCPbPbMB0100->SetName("hPtMCPbPbMB0100");
  TH1D* hPtMCNoswapPbPbMB0100 = (TH1D*)infPbPbMB0100->Get("hPtMCNoswap");
  hPtMCNoswapPbPbMB0100->SetName("hPtMCNoswapPbPbMB0100");

  TString infnamePbPb010 = Form("%s.root",outputPbPb010.Data());
  TFile* infPbPb010 = new TFile(infnamePbPb010.Data());
  TH1D* hPtMCPbPb010 = (TH1D*)infPbPb010->Get("hPtMC");
  hPtMCPbPb010->SetName("hPtMCPbPb010");
  TH1D* hPtMCNoswapPbPb010 = (TH1D*)infPbPb010->Get("hPtMCNoswap");
  hPtMCNoswapPbPb010->SetName("hPtMCNoswapPbPb010");

  TString infnamePbPbMB010 = Form("%s.root",outputPbPbMB010.Data());
  TFile* infPbPbMB010 = new TFile(infnamePbPbMB010.Data());
  TH1D* hPtMCPbPbMB010 = (TH1D*)infPbPbMB010->Get("hPtMC");
  hPtMCPbPbMB010->SetName("hPtMCPbPbMB010");
  TH1D* hPtMCNoswapPbPbMB010 = (TH1D*)infPbPbMB010->Get("hPtMCNoswap");
  hPtMCNoswapPbPbMB010->SetName("hPtMCNoswapPbPbMB010");

  TH1D* hStatsPP = (TH1D*)hPtMCPP->Clone("hStatsPP");
  //TH1D* hStatsPP->SetTitle(";D^{0} p_{T} (GeV/c);#sigma^{stat}(w/ swap) / #sigma^{stat}(w/o swap)");
  hStatsPP->SetStats(0);
  hStatsPP->SetMarkerStyle(20);
  hStatsPP->SetMarkerSize(1.8);
  hStatsPP->SetMarkerColor(kBlack);
  hStatsPP->SetLineColor(kBlack);
  TH1D* hStatsPPMB = (TH1D*)hPtMCPPMB->Clone("hStatsPPMB");
  hStatsPPMB->SetStats(0);
  hStatsPPMB->SetMarkerStyle(20);
  hStatsPPMB->SetMarkerSize(1.8);
  hStatsPPMB->SetMarkerColor(kBlack);
  hStatsPPMB->SetLineColor(kBlack);
  TH1D* hStatsPbPb0100 = (TH1D*)hPtMCPbPb0100->Clone("hStatsPbPb0100");
  hStatsPbPb0100->SetStats(0);
  hStatsPbPb0100->SetMarkerStyle(21);
  hStatsPbPb0100->SetMarkerSize(1.8);
  hStatsPbPb0100->SetMarkerColor(kRed);
  hStatsPbPb0100->SetLineColor(kRed);
  TH1D* hStatsPbPbMB0100 = (TH1D*)hPtMCPbPbMB0100->Clone("hStatsPbPbMB0100");
  hStatsPbPbMB0100->SetStats(0);
  hStatsPbPbMB0100->SetMarkerStyle(21);
  hStatsPbPbMB0100->SetMarkerSize(1.8);
  hStatsPbPbMB0100->SetMarkerColor(kRed);
  hStatsPbPbMB0100->SetLineColor(kRed);
  TH1D* hStatsPbPb010 = (TH1D*)hPtMCPbPb010->Clone("hStatsPbPb010");
  hStatsPbPb010->SetStats(0);
  hStatsPbPb010->SetMarkerStyle(22);
  hStatsPbPb010->SetMarkerSize(1.8);
  hStatsPbPb010->SetMarkerColor(kBlue);
  hStatsPbPb010->SetLineColor(kBlue);
  TH1D* hStatsPbPbMB010 = (TH1D*)hPtMCPbPbMB010->Clone("hStatsPbPbMB010");
  hStatsPbPbMB010->SetStats(0);
  hStatsPbPbMB010->SetMarkerStyle(22);
  hStatsPbPbMB010->SetMarkerSize(1.8);
  hStatsPbPbMB010->SetMarkerColor(kBlue);
  hStatsPbPbMB010->SetLineColor(kBlue);

  for(int i=0;i<(hPtMCPP->GetSize()-2);i++)
    {
      hStatsPP->SetBinContent(i+1,hPtMCPP->GetBinError(i+1)/hPtMCNoswapPP->GetBinError(i+1));
      hStatsPP->SetBinError(i+1,0);
      hStatsPbPb0100->SetBinContent(i+1,hPtMCPbPb0100->GetBinError(i+1)/hPtMCNoswapPbPb0100->GetBinError(i+1));
      hStatsPbPb0100->SetBinError(i+1,0);
      hStatsPbPb010->SetBinContent(i+1,hPtMCPbPb010->GetBinError(i+1)/hPtMCNoswapPbPb010->GetBinError(i+1));
      hStatsPbPb010->SetBinError(i+1,0);
    }
  for(int i=0;i<(hPtMCPPMB->GetSize()-2);i++)
    {
      hStatsPPMB->SetBinContent(i+1,hPtMCPPMB->GetBinError(i+1)/hPtMCNoswapPPMB->GetBinError(i+1));
      hStatsPPMB->SetBinError(i+1,0);
      hStatsPbPbMB0100->SetBinContent(i+1,hPtMCPbPbMB0100->GetBinError(i+1)/hPtMCNoswapPbPbMB0100->GetBinError(i+1));
      if(i==0) hStatsPbPbMB0100->SetBinContent(i+1,0);
      hStatsPbPbMB0100->SetBinError(i+1,0);
      hStatsPbPbMB010->SetBinContent(i+1,hPtMCPbPbMB010->GetBinError(i+1)/hPtMCNoswapPbPbMB010->GetBinError(i+1));
      if(i==0||i==1) hStatsPbPbMB010->SetBinContent(i+1,0);
      hStatsPbPbMB010->SetBinError(i+1,0);
    }

  TH2F* hempty = new TH2F("hempty",";D^{0} p_{T} (GeV/c);#sigma^{stat}(w/ swap) / #sigma^{stat}(w/o swap)", 10, 0, 100, 10, 0.5, 1.5);
  sethempty(hempty);
  TLegend* leg = new TLegend(0.50, 0.35, 0.85, 0.53);
  setleg(leg, 0.045);
  leg->AddEntry(hStatsPP, "pp");
  leg->AddEntry(hStatsPbPb0100, "PbPb cent. 0-100%");
  leg->AddEntry(hStatsPbPb010, "PbPb cent. 0-10%");

  TCanvas* cstats = new TCanvas("cstats","",800,600);
  hempty->Draw();
  hStatsPP->Draw("pe same");
  hStatsPPMB->Draw("pe same");
  hStatsPbPb0100->Draw("pe same");
  hStatsPbPbMB0100->Draw("pe same");
  hStatsPbPb010->Draw("pe same");
  hStatsPbPbMB010->Draw("pe same");
  leg->Draw();

  cstats->SaveAs("plotStats/cstats.pdf");

}

int main(int argc, char *argv[])
{
  if(argc==7)
    {
      fitDstats(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs - fitDstats" << std::endl;
      return 1;
    }
  
}
