using namespace std;
#include "uti.h"
#include "ChargedHad/RAA_0_10.C"
#include "ChargedHad/RAA_0_100.C"
#include "BmesonRaa/canvasRAAPbPb_0_100_ThmRAA.C"
#include "NonpromptJpsi/nonPrompt_276raa_20170201.h"
#include "TLegendEntry.h"
#include "TGraphErrors.h"
#include "systematics.h"
#include "drawTheory.h"

void Compare0100_010()
{
  gStyle->SetOptTitle(0);   
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  

  TFile* file0100 = new TFile("ROOTfiles/outputRAA.root");  
  TFile* fileMB0100 = new TFile("ROOTfiles/outputRAAMB.root");  
  TFile* file010 = new TFile("ROOTfilesCent10/outputRAA.root");  
  TFile* fileMB010 = new TFile("ROOTfilesCent10/outputRAAMB.root");  
  
    
  TH1D* hNuclearModification0100 = (TH1D*)file0100->Get("hNuclearModification");
  TH1D* hNuclearModificationMB0100 = (TH1D*)fileMB0100->Get("hNuclearModification");
  TH1D* hNuclearModification010 = (TH1D*)file010->Get("hNuclearModification");
  TH1D* hNuclearModificationMB010 = (TH1D*)fileMB010->Get("hNuclearModification");
  
  hNuclearModification0100->SetLineColor(2);
  hNuclearModification0100->SetMarkerColor(2);
  hNuclearModificationMB0100->SetLineColor(2);
  hNuclearModificationMB0100->SetMarkerColor(2);
  
  TCanvas* canvasRAA = new TCanvas("canvasRAA","canvasRAA",600,600);//550,500
  canvasRAA->cd();
  canvasRAA->SetFillColor(0);
  canvasRAA->SetBorderMode(0);
  canvasRAA->SetBorderSize(2);
  canvasRAA->SetLeftMargin(0.185);//0.200
  canvasRAA->SetRightMargin(0.025);
  canvasRAA->SetTopMargin(0.080);
  canvasRAA->SetBottomMargin(0.150);
  canvasRAA->SetFrameBorderMode(0);


  TH2F* hemptyEff = new TH2F("hemptyEff","",50,2,130.,10.,0,1.75);
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("R_{AA}");
  hemptyEff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEff->GetXaxis()->SetTitleOffset(1.15);//0.9
  hemptyEff->GetYaxis()->SetTitleOffset(1.15);//1.
  hemptyEff->GetXaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetYaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);
  hemptyEff->GetXaxis()->SetLabelFont(42);
  hemptyEff->GetYaxis()->SetLabelFont(42);
  hemptyEff->GetXaxis()->SetLabelSize(0.050);//0.035
  hemptyEff->GetYaxis()->SetLabelSize(0.050);//0.035  
  hemptyEff->GetXaxis()->SetLabelOffset(0.01);
  hemptyEff->SetMaximum(2);
  hemptyEff->SetMinimum(0.);
  hemptyEff->Draw();
  
  hNuclearModification0100->Draw("same");
  hNuclearModification010->Draw("same");
  hNuclearModificationMB0100->Draw("same");
  hNuclearModificationMB010->Draw("same");

}
