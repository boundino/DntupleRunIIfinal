using namespace std;
#include "uti.h"

void fitDclosure(TString input, TString collsyst, Float_t centmin=0., Float_t centmax=0.)
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  //collisionsystem = collsyst;
  //Bool_t isPbPb = (collsyst[0]=='P' || collsyst[1]=='P')?false:true;

  TString infname = Form("%s.root",input.Data());
  TFile* inf = new TFile(infname.Data());

  TH1D* hPtMCclosure = (TH1D*)inf->Get("hPtMCclosure");
  hPtMCclosure->SetTitle(";D p_{T} (GeV/c);Fit yield / truth");
  setth1d(hPtMCclosure);
  hPtMCclosure->SetMinimum(0.5,1.5);
  TH1D* hPtMCclosure_3gaus = (TH1D*)inf->Get("hPtMCclosure_3gaus");
  hPtMCclosure_3gaus->SetTitle(";D p_{T} (GeV/c);Fit yield / truth");
  setth1d(hPtMCclosure_3gaus);
  hPtMCclosure->SetMinimum(0.5,1.5);
  TH1D* hPt_rela3gaus = (TH1D*)inf->Get("hPt_rela3gaus");
  hPt_rela3gaus->SetTitle(";D p_{T} (GeV/c);triple-gaus / double-gaus");
  setth1d(hPt_rela3gaus);
  hPt_rela3gaus->SetMinimum(0.5,1.5);

  /*
  TH1D* hPtMC_rela3gaus = (TH1D*)inf->Get("hPtMC_rela3gaus");
  TH1D* hPtMCSignal_rela3gaus = (TH1D*)inf->Get("hPtMCSignal_rela3gaus");
  */
  
  TCanvas* cclosure = new TCanvas("cclosure","",600,600);
  hPtMCclosure->Draw("pe");
  drawCMS(collsyst);
  cclosure->SaveAs(Form("plotClosure/cclosure_%s.pdf",collsyst.Data()));

  TCanvas* cclosure_3gaus = new TCanvas("cclosure_3gaus","",600,600);
  hPtMCclosure_3gaus->Draw("pe");
  drawCMS(collsyst);
  cclosure_3gaus->SaveAs(Form("plotClosure/cclosure_3gaus_%s.pdf",collsyst.Data()));

  TCanvas* crela3gaus = new TCanvas("crela3gaus","",600,600);
  hPt_rela3gaus->Draw("pe");
  drawCMS(collsyst);
  crela3gaus->SaveAs(Form("plotClosure/crela3gaus_%s.pdf",collsyst.Data()));

}

int main(int argc, char *argv[])
{
  if(argc==5)
    {
      fitDclosure(argv[1], argv[2], atof(argv[3]), atof(argv[4]));
      return 0;
    }
  else if(argc==3)
    {
      fitDclosure(argv[1], argv[2]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs - fitDclosure" << std::endl;
      return 1;
    }
  
}
