#include "uti.h"

void compareNewOldresults(int option=0)
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
  TString filename;
  
  if(option==0){
  myfiles[0] ="ROOTfiles/outputRAA.root";
  myfiles[1] ="ROOTfiles/outputRAAMB.root";
  myfiles[2] ="../../DntupleRunIIGreenLight/CrossSection/ROOTfiles/outputRAA.root";
  myfiles[3] ="../../DntupleRunIIGreenLight/CrossSection/ROOTfiles/outputRAAMB.root";
  namehisto="hNuclearModification";
  namegraph="gNuclearModification";
  min=0;
  max=1.4;
  title="R_{AA}(0-100)";
  filename="canvasRAAnewold0100.pdf";
  }
 if(option==1){
  myfiles[0] ="ROOTfilesCent10/outputRAA.root";
  myfiles[1] ="ROOTfilesCent10/outputRAAMB.root";
  myfiles[2] ="../../DntupleRunIIGreenLight/CrossSection/ROOTfilesCent10/outputRAA.root";
  myfiles[3] ="../../DntupleRunIIGreenLight/CrossSection/ROOTfilesCent10/outputRAAMB.root";
  namehisto="hNuclearModification";
  namegraph="gNuclearModification";
  min=0;
  max=1.4;
  title="R_{AA}(0-10)";
  filename="canvasRAAnewold010.pdf";

  }
 if(option==2){
  myfiles[0] ="/afs/cern.ch/user/g/ginnocen/DataHFAnalysis/CMSSW_7_5_5_patch4/src/master/CrossSection/ROOTfiles/CrossSectionFONLLPP.root";
  myfiles[1] ="/afs/cern.ch/user/g/ginnocen/DataHFAnalysis/CMSSW_7_5_5_patch4/src/master/CrossSection/ROOTfiles/CrossSectionFONLLPPMB.root";
  myfiles[2] ="/afs/cern.ch/user/g/ginnocen/public/ImportantFilesHIN16002/DntupleRunII_preapproval/CrossSection/ROOTfilesCent10/CrossSectionFONLLPP.root";
  myfiles[3] ="/afs/cern.ch/user/g/ginnocen/public/ImportantFilesHIN16002/DntupleRunII_preapproval/CrossSection/ROOTfilesCent10/CrossSectionFONLLPPMB.root";
  namehisto="hPtSigma";
  namegraph="gaeCrossSyst";
  min=10;
  max=1.e12;
  isislogy=true;
  title="d#sigma/d_{p_{T}}";
  }
  
  if(option==3){
  myfiles[0] ="ROOTfilesCent10/outputRAA.root";
  myfiles[1] ="ROOTfilesCent10/outputRAAMB.root";
  myfiles[2] ="ROOTfiles/outputRAA.root";
  myfiles[3] ="ROOTfiles/outputRAAMB.root";
  namehisto="hNuclearModification";
  namegraph="gNuclearModification";
  min=0;
  max=1.4;
  title="R_{AA}(0-100)";
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
  TCanvas* canvas = new TCanvas("canvas","",600,600);
  gPad->SetLogx();
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
      graph[ifile]  ->SetLineColor(colors[ifile]);
      graph[ifile]   ->SetMarkerColor(colors[ifile]);
      graph[ifile] ->Draw("5same");  

  }
    entry[0]=legendSigma->AddEntry(histogram[0],"New","pf");
    entry[0]->SetTextFont(42);
    entry[0]->SetLineColor(1);
    entry[0]->SetTextColor(1);
    entry[0]->SetMarkerColor(1);
    entry[1]=legendSigma->AddEntry(histogram[2],"Frozen","pf");
    entry[1]->SetTextFont(42);
    entry[1]->SetLineColor(2);
    entry[1]->SetTextColor(2);
    entry[1]->SetMarkerColor(2);
    legendSigma->Draw();
    
  canvas->SaveAs(filename.Data());

  TCanvas* canvasRatio = new TCanvas("canvasRatio","",600,600);
  
  TH1D*hCrossNewOverOldMB=(TH1D*)histogram[1]->Clone("hCrossNewOverOldMB");
  TH1D*hCrossNewOverOld=(TH1D*)histogram[0]->Clone("hCrossNewOverOld");
  hCrossNewOverOldMB->Divide(histogram[3]);
  hCrossNewOverOld->Divide(histogram[2]);
  
  gPad->SetLogx();
  hemptyRatio=new TH2D("hemptyRatio","",100,0,100,50,0,2);
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
        
}
