#include "uti.h"
#include "TLegendEntry.h"
#include "parameters.h"

void compareOldAndNewCrossSection(){

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TFile *f1=new TFile("ROOTfiles/CrossSectionFONLLPP.root");
  TFile *f2=new TFile("ROOTfilesOld/CrossSectionFONLLPP.root");

  TH1D *h1=(TH1D*)f1->Get("hPtSigma");
  TH1D *h2=(TH1D*)f2->Get("hPtSigma");
  
  TH2F* hempty=new TH2F("hempty","",50,15,100.,10,1,1e6);  
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetYaxis()->SetTitle("Corrected cross section");
  hempty->GetXaxis()->SetTitle("p_{T}");
  hempty->GetXaxis()->SetTitleOffset(0.9);
  hempty->GetYaxis()->SetTitleOffset(1.0);
  hempty->GetXaxis()->SetTitleSize(0.05);
  hempty->GetYaxis()->SetTitleSize(0.05);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.035);
  hempty->GetYaxis()->SetLabelSize(0.035);  
  h1->Draw();

  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,0,100.,10,0.0,3.);  
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("Ratio new/old cross section");
  hemptyRatio->GetXaxis()->SetTitle("p_{T}");
  hemptyRatio->GetXaxis()->SetTitleOffset(0.9);
  hemptyRatio->GetYaxis()->SetTitleOffset(1.0);
  hemptyRatio->GetXaxis()->SetTitleSize(0.05);
  hemptyRatio->GetYaxis()->SetTitleSize(0.05);
  hemptyRatio->GetXaxis()->SetTitleFont(42);
  hemptyRatio->GetYaxis()->SetTitleFont(42);
  hemptyRatio->GetXaxis()->SetLabelFont(42);
  hemptyRatio->GetYaxis()->SetLabelFont(42);
  hemptyRatio->GetXaxis()->SetLabelSize(0.035);
  hemptyRatio->GetYaxis()->SetLabelSize(0.035);  

  TH1D *hRatio=(TH1D*)h1->Clone("hRatio");
  hRatio->Divide(h2);
  

  TLine *line=new TLine(0,0.92,100,0.92);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  TLine *line2=new TLine(0,1.08,100,1.08);
  line2->SetLineStyle(2);
  line2->SetLineWidth(2);

  
  TCanvas*c=new TCanvas("c","c",1000,500);
  c->Divide(2,1);
  c->cd(1);
  gPad->SetLogx();
  gPad->SetLogy();
  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h1->SetMarkerColor(1);
  h2->SetMarkerColor(2);
  hempty->Draw();
  h1->Draw("same");
  h2->Draw("same");
  TLegend *legend=new TLegend(0.2100806,0.7068644,0.5084677,0.8605932,"");
  legend->SetBorderSize(0);
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->SetTextFont(42);
  legend->SetTextSize(0.045);
  TLegendEntry *ent_pthat1=legend->AddEntry(h1,"Cross section new (no tracking selection)","pf");
  ent_pthat1->SetTextFont(42);
  ent_pthat1->SetLineColor(1);
  ent_pthat1->SetMarkerColor(1);
  TLegendEntry *ent_pthat2=legend->AddEntry(h2,"Cross section old","pf");
  ent_pthat2->SetTextFont(42);
  ent_pthat2->SetLineColor(2);
  ent_pthat2->SetMarkerColor(2);
  legend->Draw();
  c->cd(2);
  hemptyRatio->Draw();
  hRatio->Draw("same");
  line->Draw();
  line2->Draw();
 c->SaveAs("comparisonNewOldCrosssection.pdf");

}