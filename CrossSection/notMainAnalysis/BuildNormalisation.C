#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"


void BuildNormalisationPP(double pt=17.5,double lumiPP=25.8 )
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TString fileMBinput="ROOTfiles/CrossSectionFONLLPPMBNorm.root"; 
  TString fileinput="ROOTfiles/CrossSectionFONLLPPNorm.root";
  
  TFile* fileMB = new TFile(fileMBinput.Data());  
  TH1D* hSigmaStatMB = (TH1D*)fileMB->Get("hPtSigma");

  TFile* file = new TFile(fileinput.Data());  
  TH1D* hTriggerEfficiencyPtBins = (TH1D*)file->Get("hTriggerEfficiencyPtBins");
  TH1D* hSigmaStat = (TH1D*)file->Get("hPtSigma");
    
  hSigmaStat->Sumw2();
  hSigmaStatMB->Sumw2();
  
  TH1D* hRatioMBOverTriggered = (TH1D*)hSigmaStatMB->Clone("hRatioMBOverTriggered");
  hRatioMBOverTriggered->Divide(hSigmaStat);

  hRatioMBOverTriggered->Scale(lumiPP);  
  for (int i=1;i<4;i++) cout<<"luminosity="<<hRatioMBOverTriggered->GetBinContent(i)<<"with error="<<hRatioMBOverTriggered->GetBinError(i)<<endl;

  TCanvas*canvas=new TCanvas("canvas","canvas",1000,500);
  canvas->Divide(2,1);
  canvas->cd(1);
  TH2F* hemptyLumi=new TH2F("hemptyLumi","",50,5,30,10.,0,0.05); 
  hemptyLumi->GetXaxis()->CenterTitle();
  hemptyLumi->GetYaxis()->CenterTitle();
  hemptyLumi->GetYaxis()->SetTitle("Luminosity (pb)");
  hemptyLumi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyLumi->GetXaxis()->SetTitleOffset(0.95);//0.9
  hemptyLumi->GetYaxis()->SetTitleOffset(1.24);//1.
  hemptyLumi->GetXaxis()->SetTitleSize(0.060);//0.045
  hemptyLumi->GetYaxis()->SetTitleSize(0.060);//0.045
  hemptyLumi->GetXaxis()->SetTitleFont(42);
  hemptyLumi->GetYaxis()->SetTitleFont(42);
  hemptyLumi->GetXaxis()->SetLabelFont(42);
  hemptyLumi->GetYaxis()->SetLabelFont(42);
  hemptyLumi->GetXaxis()->SetLabelSize(0.040);//0.035
  hemptyLumi->GetYaxis()->SetLabelSize(0.040);//0.035  
  hemptyLumi->GetXaxis()->SetLabelOffset(0.01);
  hemptyLumi->Draw();
  hRatioMBOverTriggered->Draw("same");
  hRatioMBOverTriggered->Fit("pol0","","",10,25);
  canvas->cd(2);
  TH2F* hemptyEff=new TH2F("hemptyEff","",50,5,30,10.,0,1.5); 
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("Trigger efficiency");
  hemptyEff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEff->GetXaxis()->SetTitleOffset(0.95);//0.9
  hemptyEff->GetYaxis()->SetTitleOffset(1.30);//1.
  hemptyEff->GetXaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetYaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);
  hemptyEff->GetXaxis()->SetLabelFont(42);
  hemptyEff->GetYaxis()->SetLabelFont(42);
  hemptyEff->GetXaxis()->SetLabelSize(0.050);//0.035
  hemptyEff->GetYaxis()->SetLabelSize(0.050);//0.035  
  hemptyEff->GetXaxis()->SetLabelOffset(0.01);
  hemptyEff->Draw();
  hTriggerEfficiencyPtBins->Draw("same");


  }
  
  void BuildNormalisationPbPb(TString range="0100")
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  
  
  TString cut="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)";
  double TAA=1.;  
  TString selection;

  if(range=="0100"){
    cout<<"WUI"<<endl;
    selection="1";
    TAA=392.4/(70.*1e9);
  }  
  
  if(range=="010"){
    selection="hiBin<20";
    TAA=(23.2/1e9);
  }  

  TString inputfilePbPbMB="/data/jisun/PbPb2015/HF2and_skim_MB1to7_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root";
  TFile* filePbPbMBraw = new TFile(inputfilePbPbMB.Data());  
  TTree* HltTreePbPbMB= (TTree*) filePbPbMBraw->Get("ntHlt");
  TTree* HltHiPbPbMB= (TTree*) filePbPbMBraw->Get("ntHi");
  HltTreePbPbMB->AddFriend(HltHiPbPbMB);

  TH1D*hcountsMBPbPb=new TH1D("hcountsMBPbPb","hcountsMBPbPb",2,-200,200);
  HltTreePbPbMB->Draw("1>>hcountsMBPbPb",Form("%s&&%s",cut.Data(),selection.Data()));
  double ncountsMBPbPb=hcountsMBPbPb->GetEntries();

  double lumiPbPbMB=ncountsMBPbPb*TAA;
  cout<<"ncountsMBPbPb="<<ncountsMBPbPb<<endl;
  cout<<"luminosity MB="<<lumiPbPbMB<<endl;

  TString fileMBinput="ROOTfiles/CrossSectionFONLLPbPbMBNorm.root"; 
  TString fileinput="ROOTfiles/CrossSectionFONLLPbPbNorm.root";
  
  TFile* fileMB = new TFile(fileMBinput.Data());  
  TH1D* hSigmaStatMB = (TH1D*)fileMB->Get("hPtSigma");

  TFile* file = new TFile(fileinput.Data());  
  TH1D* hTriggerEfficiencyPtBins = (TH1D*)file->Get("hTriggerEfficiencyPtBins");
  TH1D* hSigmaStat = (TH1D*)file->Get("hPtSigma");
    
  hSigmaStat->Sumw2();
  hSigmaStatMB->Sumw2();
  
  TH1D* hRatioTriggeredOverMB = (TH1D*)hSigmaStat->Clone("hRatioTriggeredOverMB");
  hRatioTriggeredOverMB->Divide(hSigmaStatMB);

  hRatioTriggeredOverMB->Scale(lumiPbPbMB);  
  for (int i=1;i<3;i++) cout<<"luminosity="<<hRatioTriggeredOverMB->GetBinContent(i)<<"with error="<<hRatioTriggeredOverMB->GetBinError(i)<<endl;

  TCanvas*canvas=new TCanvas("canvas","canvas",1000,500);
  canvas->Divide(2,1);
  canvas->cd(1);
  TH2F* hemptyLumi=new TH2F("hemptyLumi","",50,15,35,10.,10,20); 
  hemptyLumi->GetXaxis()->CenterTitle();
  hemptyLumi->GetYaxis()->CenterTitle();
  hemptyLumi->GetYaxis()->SetTitle("Luminosity (pb)");
  hemptyLumi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyLumi->GetXaxis()->SetTitleOffset(0.95);//0.9
  hemptyLumi->GetYaxis()->SetTitleOffset(1.24);//1.
  hemptyLumi->GetXaxis()->SetTitleSize(0.060);//0.045
  hemptyLumi->GetYaxis()->SetTitleSize(0.060);//0.045
  hemptyLumi->GetXaxis()->SetTitleFont(42);
  hemptyLumi->GetYaxis()->SetTitleFont(42);
  hemptyLumi->GetXaxis()->SetLabelFont(42);
  hemptyLumi->GetYaxis()->SetLabelFont(42);
  hemptyLumi->GetXaxis()->SetLabelSize(0.040);//0.035
  hemptyLumi->GetYaxis()->SetLabelSize(0.040);//0.035  
  hemptyLumi->GetXaxis()->SetLabelOffset(0.01);
  hemptyLumi->Draw();
  hRatioTriggeredOverMB->Draw("same");
  hRatioTriggeredOverMB->Fit("pol0","","",20,30);
  canvas->cd(2);
  TH2F* hemptyEff=new TH2F("hemptyEff","",50,15,35,10.,0,1.5); 
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("Trigger efficiency");
  hemptyEff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEff->GetXaxis()->SetTitleOffset(0.95);//0.9
  hemptyEff->GetYaxis()->SetTitleOffset(1.30);//1.
  hemptyEff->GetXaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetYaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);
  hemptyEff->GetXaxis()->SetLabelFont(42);
  hemptyEff->GetYaxis()->SetLabelFont(42);
  hemptyEff->GetXaxis()->SetLabelSize(0.050);//0.035
  hemptyEff->GetYaxis()->SetLabelSize(0.050);//0.035  
  hemptyEff->GetXaxis()->SetLabelOffset(0.01);
  hemptyEff->Draw();
  hTriggerEfficiencyPtBins->Draw("same");

  }
  