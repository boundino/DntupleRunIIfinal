#include "uti.h"

void StudyTrackingPP()
{
  
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
//PPstdtrack PPnochi2 PPnohit PPlooseptresolution

/*
  const int nFiles = 8;
  TString myfiles[nFiles] = { "ROOTfiles/hPtSpectrumDzero_PPstdtrack.root", 
                                            "ROOTfiles/hPtSpectrumDzero_PPnochi2.root",
                                            "ROOTfiles/hPtSpectrumDzero_PPnohit.root",
                                            "ROOTfiles/hPtSpectrumDzero_PPlooseptresolution.root", 
                                            "ROOTfiles/hPtSpectrumDzero_PPMBstdtrack.root",
                                            "ROOTfiles/hPtSpectrumDzero_PPMBwithchi2.root",
                                            "ROOTfiles/hPtSpectrumDzero_PPMBwithhit.root", 
                                            "ROOTfiles/hPtSpectrumDzero_PPMBtightptresolution.root"};
                                            
  TString label[nFiles] = {"std track sel", "no track chi2 cut", "no track hit","loose selection", "MB std track", "MB with chi2","MB with nhit","MB tight resolution"};

  int colors[nFiles] = {1,2,3,4,5,6,7,8};
  */
  const int nFiles = 4;
  TString myfiles[nFiles] = { "ROOTfiles/hPtSpectrumDzero_PPstdtrack.root", 
                                            "ROOTfiles/hPtSpectrumDzero_PPnochi2.root",
                                            "ROOTfiles/hPtSpectrumDzero_PPnohit.root",
                                            "ROOTfiles/hPtSpectrumDzero_PPlooseptresolution.root"};
                                            
  TString label[nFiles] = {"std track sel", "no track chi2 cut", "no track hit","loose selection"};

  int colors[nFiles] = {1,2,3};
  int colors2[nFiles] = {4,6,7};


  TH1D* hPtSigma[nFiles];
  TFile* files[nFiles];
  TLegendEntry *entry[nFiles];
    
  for (int ifile=0;ifile<nFiles;ifile++){
    files[ifile]=new TFile(myfiles[ifile].Data());  
    hPtSigma[ifile] = (TH1D*)files[ifile]->Get("hPtSigma");
    hPtSigma[ifile]->Sumw2();
  }
  
  TH1D*hRefhigh=(TH1D*)hPtSigma[0]->Clone("hRefhigh");
  //TH1D*hReflow=(TH1D*)hPtSigma[4]->Clone("hReflow");
  for (int ifile=0;ifile<nFiles;ifile++){
    hPtSigma[ifile]->Divide(hRefhigh);
   // if(ifile>=4) hPtSigma[ifile]->Divide(hReflow);
   // else hPtSigma[ifile]->Divide(hRefhigh);
  }

  TCanvas* cRatio = new TCanvas("cRatio","",500,500);
  cRatio->cd(1);
  gPad->SetLogx();
  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,0,100.,10.,0.5,2.0);
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("Modified track selection/std track selection");
  hemptyRatio->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hemptyRatio->GetXaxis()->SetTitleOffset(1.);
  hemptyRatio->GetYaxis()->SetTitleOffset(1.4);//1.3
  hemptyRatio->GetXaxis()->SetTitleSize(0.045);
  hemptyRatio->GetYaxis()->SetTitleSize(0.045);
  hemptyRatio->GetXaxis()->SetTitleFont(42);
  hemptyRatio->GetYaxis()->SetTitleFont(42);
  hemptyRatio->GetXaxis()->SetLabelFont(42);
  hemptyRatio->GetYaxis()->SetLabelFont(42);
  hemptyRatio->GetXaxis()->SetLabelSize(0.04);
  hemptyRatio->GetYaxis()->SetLabelSize(0.04);  
  hemptyRatio->Draw();
  
  TLegend *legendSigma=new TLegend(0.3111702,0.5744337,0.6396277,0.8754045,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);
      
  for (int ifile=0;ifile<nFiles;ifile++){
    hPtSigma[ifile] ->SetLineColor(colors[ifile]);
    hPtSigma[ifile] ->SetLineWidth(3);
    hPtSigma[ifile] ->SetMarkerColor(colors[ifile]);
    hPtSigma[ifile] ->Draw("same");  
    entry[ifile]=legendSigma->AddEntry(hPtSigma[ifile],label[ifile].Data(),"f");
    entry[ifile]->SetTextFont(42);
    entry[ifile]->SetLineColor(colors[ifile]);
    entry[ifile]->SetMarkerColor(colors[ifile]);
  }
  legendSigma->Draw("same");
  
}


void StudyTrackingPbPb()
{
  
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  const int nFiles = 4;
  TString myfiles[nFiles] = {"ROOTfiles/hPtSpectrumDzero_PbPbstdtrack.root", 
                                            "ROOTfiles/hPtSpectrumDzero_PbPbnochi2.root",
                                            "ROOTfiles/hPtSpectrumDzero_PbPbnohit.root",
                                            "ROOTfiles/hPtSpectrumDzero_PbPblooseptresolution.root"};
                                            
  TString label[nFiles] = {"std track", "no chi2", "no track hits","loose pt resolution cut"};

  int colors[nFiles] = {1,2,3,4};

  TH1D* hPtSigma[nFiles];
  TFile* files[nFiles];
  TLegendEntry *entry[nFiles];
    
  for (int ifile=0;ifile<nFiles;ifile++){
    files[ifile]=new TFile(myfiles[ifile].Data());  
    hPtSigma[ifile] = (TH1D*)files[ifile]->Get("hPtSigma");
    hPtSigma[ifile]->Sumw2();
  }
  
  for (int ifile=1;ifile<nFiles;ifile++){
    hPtSigma[ifile]->Divide(hPtSigma[0]);
  }

  TCanvas* cRatio = new TCanvas("cRatio","",500,500);
  cRatio->cd(1);
  gPad->SetLogx();
  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,20,100.,10.,0.,2.0);
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("Modified track selection/std track selection");
  hemptyRatio->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hemptyRatio->GetXaxis()->SetTitleOffset(1.);
  hemptyRatio->GetYaxis()->SetTitleOffset(1.4);//1.3
  hemptyRatio->GetXaxis()->SetTitleSize(0.045);
  hemptyRatio->GetYaxis()->SetTitleSize(0.045);
  hemptyRatio->GetXaxis()->SetTitleFont(42);
  hemptyRatio->GetYaxis()->SetTitleFont(42);
  hemptyRatio->GetXaxis()->SetLabelFont(42);
  hemptyRatio->GetYaxis()->SetLabelFont(42);
  hemptyRatio->GetXaxis()->SetLabelSize(0.04);
  hemptyRatio->GetYaxis()->SetLabelSize(0.04);  
  hemptyRatio->Draw();
  
  TLegend *legendSigma=new TLegend(0.311747,0.6945694,0.6401439,0.8740055,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);
      
  for (int ifile=1;ifile<nFiles;ifile++){
    hPtSigma[ifile] ->SetLineColor(colors2[ifile]);
    hPtSigma[ifile] ->SetLineWidth(3);
    hPtSigma[ifile] ->SetMarkerColor(colors2[ifile]);
    hPtSigma[ifile] ->Draw("same");  
    entry[ifile]=legendSigma->AddEntry(hPtSigma[ifile],label[ifile].Data(),"f");
    entry[ifile]->SetTextFont(42);
    entry[ifile]->SetLineColor(colors2[ifile]);
    entry[ifile]->SetMarkerColor(colors2[ifile]);
  }
  legendSigma->Draw("same");
  
}


