#include "uti.h"

void compareNewOldresultsEff(int option=0)
{
  
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

 // const int nHistos=4;
  const int nFiles=4;
  int colors[4]={1,1,2,2};
  TString namehisto;
  TString namegraph;
  TString title;
  double min=0;
  double max=0;
  bool isislogy=false;
  
  
  TString myfiles[nFiles];
  TString label;
  
  if(option==0){
  myfiles[0] ="ROOTfiles/MCstudiesPP.root";
  myfiles[1] ="ROOTfiles/MCstudiesPPMB.root";
  myfiles[2] ="ROOTfilesGreenLight/MCstudiesPP.root";
  myfiles[3] ="ROOTfilesGreenLight/MCstudiesPPMB.root";
  namehisto="hEff";
  min=0.001;
  max=1.4;
  label="PP";
  title="efficiency";
  }
  
  if(option==1){
  myfiles[0] ="ROOTfiles/MCstudiesPbPb.root";
  myfiles[1] ="ROOTfiles/MCstudiesPbPbMB.root";
  myfiles[2] ="ROOTfilesGreenLight/MCstudiesPbPb.root";
  myfiles[3] ="ROOTfilesGreenLight/MCstudiesPbPbMB.root";
  namehisto="hEff";
  min=0.001;
  max=1.4;
  label="PbPb";
  title="efficiency";
  }
  
  if(option==2){
  myfiles[0] ="ROOTfiles/MCstudiesNPPP.root";
  myfiles[1] ="ROOTfiles/MCstudiesNPPPMB.root";
  myfiles[2] ="ROOTfilesGreenLight/MCstudiesNPPP.root";
  myfiles[3] ="ROOTfilesGreenLight/MCstudiesNPPPMB.root";
  namehisto="hEff";
  min=0.001;
  max=1.4;
  label="NPPP";
  title="efficiency";
  }
  
  if(option==3){
  myfiles[0] ="ROOTfiles/MCstudiesNPPbPb.root";
  myfiles[1] ="ROOTfiles/MCstudiesNPPbPbMB.root";
  myfiles[2] ="ROOTfilesGreenLight/MCstudiesNPPbPb.root";
  myfiles[3] ="ROOTfilesGreenLight/MCstudiesNPPbPbMB.root";
  namehisto="hEff";
  min=0.001;
  max=1.4;
  label="NPPbPb";
  title="efficiency";
  }
  
  double minxhisto=0.;
  double maxxhisto=100.;
  
  TH1D* histogram[nFiles];
  TGraphAsymmErrors* graph[nFiles];
  TH2D* hempty;
  TFile* files[nFiles];
  TLegendEntry *entry[2];

  

  for (int ifile=0;ifile<nFiles;ifile++){
    files[ifile]=new TFile(myfiles[ifile].Data());  
    histogram[ifile] = (TH1D*)files[ifile]->Get(namehisto.Data());
    graph[ifile] = (TGraphAsymmErrors*)files[ifile]->Get(namegraph.Data());
  }
  TCanvas* canvas = new TCanvas("canvas","",1200,600);
  canvas->Divide(2,1);
  canvas->cd(1);
  gPad->SetLogx();
  gPad->SetLogy();
  if(isislogy) gPad->SetLogy();
  hempty=new TH2D("hempty","",100,0,100,50,min,max);
      hempty->SetLineWidth(3);
      hempty->GetYaxis()->CenterTitle();
      hempty->GetYaxis()->SetTitle(title.Data());
      hempty->GetXaxis()->SetRangeUser(-10,100);//1.
      hempty->GetXaxis()->SetTitle("p_{T} (GeV/c)");
      hempty->GetXaxis()->SetTitleOffset(0.95);//0.9
      hempty->GetYaxis()->SetTitleOffset(1.25);//1.
      hempty->GetXaxis()->SetTitleSize(0.060);//0.045
      hempty->GetYaxis()->SetTitleSize(0.060);//0.045
      hempty->GetXaxis()->SetTitleFont(42);
      hempty->GetYaxis()->SetTitleFont(42);
      hempty->GetXaxis()->SetLabelFont(42);
      hempty->GetYaxis()->SetLabelFont(42);  
      hempty->GetXaxis()->SetLabelSize(0.050);//0.035
      hempty->GetYaxis()->SetLabelSize(0.050);//0.035  

  TLegend *legendSigma=new TLegend(0.3104027,0.8058042,0.6392617,0.8634965,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);

  hempty  ->Draw();
    for (int ifile=0;ifile<nFiles;ifile++){
      histogram[ifile]  ->SetLineColor(colors[ifile]);
      histogram[ifile]   ->SetMarkerColor(colors[ifile]);
      histogram[ifile] ->Draw("psame");  

  }
    entry[0]=legendSigma->AddEntry(histogram[0],"Official MC","pf");
    entry[0]->SetTextFont(42);
    entry[0]->SetLineColor(1);
    entry[0]->SetTextColor(1);
    entry[0]->SetMarkerColor(1);
    entry[1]=legendSigma->AddEntry(histogram[2],"Private MC","pf");
    entry[1]->SetTextFont(42);
    entry[1]->SetLineColor(2);
    entry[1]->SetTextColor(2);
    entry[1]->SetMarkerColor(2);
    legendSigma->Draw();
    
  canvas->cd(2);
  gPad->SetLogx();
  gPad->SetLogy();
  
  TH1D*hCrossNewOverOldMB=(TH1D*)histogram[1]->Clone("hCrossNewOverOldMB");
  TH1D*hCrossNewOverOld=(TH1D*)histogram[0]->Clone("hCrossNewOverOld");
  hCrossNewOverOldMB->Divide(histogram[3]);
  hCrossNewOverOld->Divide(histogram[2]);
  
  hemptyRatio=new TH2D("hemptyRatio","",100,0,100,50,0.5,1.5);
      hemptyRatio->SetLineWidth(3);
      hemptyRatio->GetYaxis()->CenterTitle();
      hemptyRatio->GetYaxis()->SetTitle(title.Data());
      hemptyRatio->GetXaxis()->SetRangeUser(-10,100);//1.
      hemptyRatio->GetXaxis()->SetTitle("p_{T} (GeV/c)");
      hemptyRatio->GetYaxis()->SetTitle("New/Old");
      hemptyRatio->GetXaxis()->SetTitleOffset(0.95);//0.9
      hemptyRatio->GetYaxis()->SetTitleOffset(1.25);//1.
      hemptyRatio->GetXaxis()->SetTitleSize(0.060);//0.045
      hemptyRatio->GetYaxis()->SetTitleSize(0.060);//0.045
      hemptyRatio->GetXaxis()->SetTitleFont(42);
      hemptyRatio->GetYaxis()->SetTitleFont(42);
      hemptyRatio->GetXaxis()->SetLabelFont(42);
      hemptyRatio->GetYaxis()->SetLabelFont(42);  
      hemptyRatio->GetXaxis()->SetLabelSize(0.050);//0.035
      hemptyRatio->GetYaxis()->SetLabelSize(0.050);//0.035
      hemptyRatio->Draw();
      hCrossNewOverOldMB->Draw("same");
      hCrossNewOverOld->Draw("same");
    canvas->SaveAs(Form("plotEff/compareNewOld%s.pdf",label.Data()));
        
}
