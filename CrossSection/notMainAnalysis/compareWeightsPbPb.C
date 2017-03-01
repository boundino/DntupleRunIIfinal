#include "uti.h"
#include "bFeedDown/bFeedDownCorrection.C"


void compareWeightsPbPb(bool isLowpt=false)
{
  
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  const int nFiles=3;

    
  TString mynamefiles[nFiles];
  TString label[nFiles];
  int colors[nFiles]={1,2,3};
  if(!isLowpt){
  mynamefiles[0] ="DetailEfficiency/PbPbnoweight.root";
  mynamefiles[1] ="DetailEfficiency/PbPbfinal.root";
  mynamefiles[2] ="DetailEfficiency/PbPbpthat.root";
  label[0]="no weight";
  label[1]="final";
  label[2]="pthat";
  }

  if(isLowpt){
  mynamefiles[0] ="DetailEfficiency/PbPbMBnoweight.root";
  mynamefiles[1] ="DetailEfficiency/PbPbMBfinal.root";
  mynamefiles[2] ="DetailEfficiency/PbPbMBpthat.root";
  label[0]="no weight";
  label[1]="final";
  label[2]="pthat";
  }

  TFile* files[nFiles];
    TLegendEntry *entry[nFiles];
  
  TH1D* hEff[nFiles];

  for (int ifile=0;ifile<nFiles;ifile++){
       files[ifile]=new TFile(mynamefiles[ifile].Data());  
       hEff[ifile]=(TH1D*)files[ifile]->Get("hEff");
}
  
  TH1D*hdefaultMB=(TH1D*)hEff[4]->Clone("hdefaultMB");
  TH1D*hdefault=(TH1D*)hEff[0]->Clone("hdefault");
     
  TCanvas* canvas = new TCanvas("canvas","",600,600);

  TH2F* hempty=new TH2F("hempty","",50,0.,100.,10,0,1.2);  
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetYaxis()->SetTitle("efficiency");
  hempty->GetXaxis()->SetTitle("p_{T}");
  hempty->GetXaxis()->SetTitleOffset(0.9);
  hempty->GetYaxis()->SetTitleOffset(1.1);
  hempty->GetXaxis()->SetTitleSize(0.05);
  hempty->GetYaxis()->SetTitleSize(0.05);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.035);
  hempty->GetYaxis()->SetLabelSize(0.035);  
  hempty->Draw();

  for (int ifile=0;ifile<nFiles;ifile++){
      hEff[ifile]->Divide(hdefault);
      hEff[ifile]  ->SetLineColor(1);
      hEff[ifile]  ->SetMarkerColor(1);
      hEff[ifile]  ->SetFillStyle(0);
      hEff[ifile]  ->Draw("psame");  
  }
      
  TLegend *legendSigma=new TLegend(0.311747,0.6945694,0.6401439,0.8740055,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);
      
  for (int ifile=0;ifile<nFiles;ifile++){
    hEff[ifile] ->SetLineColor(colors[ifile]);
    hEff[ifile] ->SetLineWidth(3);
    hEff[ifile] ->SetMarkerColor(colors[ifile]);
    hEff[ifile] ->Draw("same");  
    entry[ifile]=legendSigma->AddEntry(hEff[ifile],label[ifile].Data(),"f");
    entry[ifile]->SetTextFont(42);
    entry[ifile]->SetLineColor(colors[ifile]);
    entry[ifile]->SetMarkerColor(colors[ifile]);
  }
  legendSigma->Draw();

}
