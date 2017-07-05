using namespace std;
#include "uti.h"

void drawtoyMCpickevt(TString output, TString collsyst, Float_t ptmin, Float_t ptmax, Float_t centmin=0., Float_t centmax=0.)
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  Bool_t isPbPb = (collsyst=="PP" || collsyst=="PPMB")?false:true;
  TString tcol = isPbPb?"PbPb":"pp";

  TFile* inf = new TFile(Form("%s.root",output.Data()));
  TH1D* hSmear = (TH1D*)inf->Get("hSmear");
  setth1d(hSmear);
  hSmear->SetMaximum(hSmear->GetMaximum()*3);
  hSmear->GetXaxis()->SetNdivisions(-50205);
  hSmear->SetMarkerStyle(20);
  hSmear->SetMarkerSize(1.3);
  hSmear->SetMarkerColor(kBlack);
  hSmear->SetLineColor(kBlack);
  hSmear->SetStats(0);
  
  TCanvas* csmear = new TCanvas("csmear","",600,600);
  csmear->SetLogy();
  hSmear->Draw("pe");
  hSmear->Fit("gaus","q");
  TLatex* texGaussMean = new TLatex(0.92,0.86,Form("#mu: %.3f",hSmear->GetFunction("gaus")->GetParameter(1)));
  settex(texGaussMean,0.045,32);
  texGaussMean->Draw();      
  TLatex* texGaussSigma = new TLatex(0.92,0.80,Form("#sigma: %.3f",hSmear->GetFunction("gaus")->GetParameter(2)));
  settex(texGaussSigma,0.045,32);
  texGaussSigma->Draw();
  TLatex* texpt = new TLatex(0.21,0.855,Form("%.1f < D^{0} p_{T} < %.1f GeV",ptmin,ptmax));
  settex(texpt,0.045,12);
  texpt->Draw();
  TLatex* texy = new TLatex(0.22,0.795,"|y| < 1");
  settex(texy,0.045,12);
  texy->Draw();
  drawCMS(tcol);
  TString csmearname = isPbPb?Form("plotToyMCpickevt/csmear_%s_pt_%.0f_%.0f_cent_%.0f_%.0f",collsyst.Data(),ptmin,ptmax,centmin,centmax):Form("plotToyMCpickevt/csmear_%s_pt_%.0f_%.0f",collsyst.Data(),ptmin,ptmax);
  csmear->SaveAs(Form("%s.pdf",csmearname.Data()));

}

int main(int argc, char *argv[])
{
  if(argc==7)
    {
      drawtoyMCpickevt(argv[1], argv[2], atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]));
      return 0;
    }
  else if(argc==5)
    {
      drawtoyMCpickevt(argv[1], argv[2], atof(argv[3]), atof(argv[4]));
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs - drawtoyMCpickevt" << std::endl;
      return 1;
    }  
}
