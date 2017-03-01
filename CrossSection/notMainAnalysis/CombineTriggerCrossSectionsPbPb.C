#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"
#include "../Systematics/systematics.C"


void CombineTriggerCrossSectionsPbPb(bool isTriggerCorrected=true,bool isLumiNorm=true)
{
double lumi=15.5097;
double lumiMB=0.831646;

  TString cut="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)";
  TString selection="1";
  double TAA=392.4/(70.*1e9);

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  const int nFiles = 4;
  TString myfiles[nFiles] = {"ROOTfiles/CrossSectionFONLLPbPbMB_extended.root", 
                                            "ROOTfiles/CrossSectionFONLLPbPb_20.root",
                                            "ROOTfiles/CrossSectionFONLLPbPb_40.root",
                                            "ROOTfiles/CrossSectionFONLLPbPb_60.root"};
  TString label[nFiles] = {"MB", "HLTD20", "HLTD40", "HLTD60"};

  int colors[nFiles] = {1,2,3,4};

  TH1D* hYieldCorrected[nFiles];
  TH1D* hTriggerEfficiency[nFiles];
  TH1D* hYieldCorrectedFONLLnorm[nFiles];
  TH1D* hDcandidatesCorrectedFONLLnorm[nFiles];
  
  TFile* files[nFiles];
  TLegendEntry *entry[nFiles];
  
  
  TString histoYield;
  TString histoYieldNorm;
  TString histoCandNorm;
  
  if(isTriggerCorrected){
    histoYield="hYieldTriggerCorrected";
    histoYieldNorm="hYieldTriggerCorrectedFONLLnorm";
    histoCandNorm="hDcandidatesTriggerCorrectedFONLLnorm";
  }
  else{
    histoYield="hYieldNoTriggerCorrected";
    histoYieldNorm="hYieldNoTriggerCorrectedFONLLnorm";
    histoCandNorm="hDcandidatesNoTriggerCorrectedFONLLnorm";
  }
  
  for (int ifile=0;ifile<nFiles;ifile++){
    files[ifile]=new TFile(myfiles[ifile].Data());  
    hYieldCorrected[ifile] = (TH1D*)files[ifile]->Get(histoYield.Data());
    hYieldCorrectedFONLLnorm[ifile] = (TH1D*)files[ifile]->Get(histoYieldNorm.Data());
    hDcandidatesCorrectedFONLLnorm[ifile] = (TH1D*)files[ifile]->Get(histoCandNorm.Data());
    if(ifile>0) hTriggerEfficiency[ifile] = (TH1D*)files[ifile]->Get("hTriggerEfficiencyPtBins");
    if(isLumiNorm&&ifile==0) {
      hYieldCorrected[ifile]->Scale(1/lumiMB);
      hYieldCorrectedFONLLnorm[ifile]->Scale(1/lumiMB);
      hDcandidatesCorrectedFONLLnorm[ifile]->Scale(1/lumiMB);
    }
    if(isLumiNorm&&ifile>0) {
      hYieldCorrected[ifile]->Scale(1/lumi);
      hYieldCorrectedFONLLnorm[ifile]->Scale(1/lumi);
      hDcandidatesCorrectedFONLLnorm[ifile]->Scale(1/lumi);
    }
  }
    
  TCanvas* cSigmaAll = new TCanvas("cSigmaAll","",1000,500);
  cSigmaAll->cd(1);
  gPad->SetLogy();
  gPad->SetLogx();
  TH2F* hemptySigma=new TH2F("hemptySigma","",50,0.,110.,10.,1e-5,1.e12);  
  hemptySigma->GetXaxis()->CenterTitle();
  hemptySigma->GetYaxis()->CenterTitle();
  hemptySigma->GetYaxis()->SetTitle("1/T_{AA} * dN / dp_{T}( pb GeV^{-1}c)");
  hemptySigma->GetXaxis()->SetTitleOffset(1.);
  hemptySigma->GetYaxis()->SetTitleOffset(1.4);//1.3
  hemptySigma->GetXaxis()->SetTitleSize(0.045);
  hemptySigma->GetYaxis()->SetTitleSize(0.045);
  hemptySigma->GetXaxis()->SetTitleFont(42);
  hemptySigma->GetYaxis()->SetTitleFont(42);
  hemptySigma->GetXaxis()->SetLabelFont(42);
  hemptySigma->GetYaxis()->SetLabelFont(42);
  hemptySigma->GetXaxis()->SetLabelSize(0.04);
  hemptySigma->GetYaxis()->SetLabelSize(0.04);  
  hemptySigma->Draw();
  
  TLegend *legendSigma=new TLegend(0.311747,0.6945694,0.6401439,0.8740055,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);

      
  for (int ifile=0;ifile<nFiles;ifile++){
    hYieldCorrected[ifile] ->SetLineColor(colors[ifile]);
    hYieldCorrected[ifile] ->SetLineWidth(3);
    hYieldCorrected[ifile] ->SetMarkerColor(colors[ifile]);
    hYieldCorrected[ifile] ->Draw("same");  
    entry[ifile]=legendSigma->AddEntry(hYieldCorrected[ifile],label[ifile].Data(),"f");
    entry[ifile]->SetTextFont(42);
    entry[ifile]->SetLineColor(colors[ifile]);
    entry[ifile]->SetMarkerColor(colors[ifile]);
  }
  legendSigma->Draw("same");
  

  TCanvas* cSigma = new TCanvas("cSigma","",1000,500);
  cSigma->Divide(2,1);
  cSigma->cd(1);
  gPad->SetLogx();
  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,3,100.,10.,0.0,0.1);
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("Corrected yields/FONLL");
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

  for (int ifile=0;ifile<nFiles;ifile++){
    hYieldCorrectedFONLLnorm[ifile] ->SetLineColor(colors[ifile]);
    hYieldCorrectedFONLLnorm[ifile] ->SetLineWidth(3);
    if(ifile==0)hYieldCorrectedFONLLnorm[ifile] ->SetLineWidth(6);
    hYieldCorrectedFONLLnorm[ifile] ->SetMarkerColor(colors[ifile]);
    hYieldCorrectedFONLLnorm[ifile] ->Draw("psame");  
  }
    legendSigma->Draw("same");
    
  cSigma->cd(2);
  gPad->SetLogx();
  TH2F* hemptyRatioCounting=new TH2F("hemptyRatioCounting","",50,3,100.,10.,0.0,0.1);
  hemptyRatioCounting->GetXaxis()->CenterTitle();
  hemptyRatioCounting->GetYaxis()->CenterTitle();
  hemptyRatioCounting->GetYaxis()->SetTitle("D counting/FONLL");
  hemptyRatioCounting->GetXaxis()->SetTitleOffset(1.);
  hemptyRatioCounting->GetYaxis()->SetTitleOffset(1.4);//1.3
  hemptyRatioCounting->GetXaxis()->SetTitleSize(0.045);
  hemptyRatioCounting->GetYaxis()->SetTitleSize(0.045);
  hemptyRatioCounting->GetXaxis()->SetTitleFont(42);
  hemptyRatioCounting->GetYaxis()->SetTitleFont(42);
  hemptyRatioCounting->GetXaxis()->SetLabelFont(42);
  hemptyRatioCounting->GetYaxis()->SetLabelFont(42);
  hemptyRatioCounting->GetXaxis()->SetLabelSize(0.04);
  hemptyRatioCounting->GetYaxis()->SetLabelSize(0.04);  
  hemptyRatioCounting->Draw();

  for (int ifile=0;ifile<nFiles;ifile++){
    hDcandidatesCorrectedFONLLnorm[ifile] ->SetLineColor(colors[ifile]);
    hDcandidatesCorrectedFONLLnorm[ifile] ->SetLineWidth(3);
    if(ifile==0)hDcandidatesCorrectedFONLLnorm[ifile] ->SetLineWidth(6);
    hDcandidatesCorrectedFONLLnorm[ifile] ->SetMarkerColor(colors[ifile]);
    hDcandidatesCorrectedFONLLnorm[ifile] ->Draw("psame");  
  }
    legendSigma->Draw("same");

  TCanvas* cTriggerEff = new TCanvas("cTriggerEff","",500,500);
  cTriggerEff->cd();
  TH2F* hemptyEff=new TH2F("hemptyEff","",50,10,100.,10.,0.,1.9);
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("Triggere efficiency");
  hemptyEff->GetXaxis()->SetTitleOffset(1.);
  hemptyEff->GetYaxis()->SetTitleOffset(1.4);//1.3
  hemptyEff->GetXaxis()->SetTitleSize(0.045);
  hemptyEff->GetYaxis()->SetTitleSize(0.045);
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);
  hemptyEff->GetXaxis()->SetLabelFont(42);
  hemptyEff->GetYaxis()->SetLabelFont(42);
  hemptyEff->GetXaxis()->SetLabelSize(0.04);
  hemptyEff->GetYaxis()->SetLabelSize(0.04);   
  hemptyEff->Draw();
  
  for (int ifile=1;ifile<nFiles;ifile++){
    hTriggerEfficiency[ifile] ->SetLineColor(colors[ifile]);
    hTriggerEfficiency[ifile] ->SetLineWidth(3);
    hTriggerEfficiency[ifile] ->SetMarkerColor(colors[ifile]);
    hTriggerEfficiency[ifile] ->SetMarkerStyle(23);
    hTriggerEfficiency[ifile] ->SetMarkerSize(1);
    hTriggerEfficiency[ifile] ->Draw("psame");  
  }
  
 legendSigma->Draw("same");

  TH1D* ratioHLTMB_20=(TH1D*)hDcandidatesCorrectedFONLLnorm[0]->Clone("ratioHLTMB_20");
  ratioHLTMB_20->Divide(hDcandidatesCorrectedFONLLnorm[1]);
 
  TH1D* ratioHLT40_60=(TH1D*)hDcandidatesCorrectedFONLLnorm[2]->Clone("ratioHLT40_60");
  ratioHLT40_60->Divide(hDcandidatesCorrectedFONLLnorm[3]);

  TH1D* ratioHLT20_40=(TH1D*)hDcandidatesCorrectedFONLLnorm[1]->Clone("ratioHLT20_40");
  ratioHLT20_40->Divide(hDcandidatesCorrectedFONLLnorm[2]);
  
  TH1D* ratioHLT20_60=(TH1D*)hDcandidatesCorrectedFONLLnorm[1]->Clone("ratioHLT20_60");
  ratioHLT20_60->Divide(hDcandidatesCorrectedFONLLnorm[3]);

  const int binstotal=7;
  double ptBinsTotal[binstotal+1] = {20.,25,30.,40.,50.,60.,80,100};
  double ptBinsTotalCenter[binstotal] = {22.5,27.5,35.,45.,55.,70.,90};
  
    for (int i=3;i<binstotal;i++){
    ratioHLTMB_20->SetBinContent(i+1,0.);
    ratioHLTMB_20->SetBinError(i+1,0.);
  }

  TCanvas*canvasPrescale=new TCanvas("canvasPrescale","canvasPrescale",1000,1000);
  canvasPrescale->Divide(2,2);
  TH2F* hemptyPrescale=new TH2F("hemptyPrescale","",50,0,100,10.,0,2.); 
  hemptyPrescale->GetXaxis()->CenterTitle();
  hemptyPrescale->GetYaxis()->CenterTitle();
  hemptyPrescale->GetYaxis()->SetTitle("Ratio of HLT corrected yields");
  hemptyPrescale->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyPrescale->GetXaxis()->SetTitleOffset(0.95);//0.9
  hemptyPrescale->GetYaxis()->SetTitleOffset(1.24);//1.
  hemptyPrescale->GetXaxis()->SetTitleSize(0.060);//0.045
  hemptyPrescale->GetYaxis()->SetTitleSize(0.060);//0.045
  hemptyPrescale->GetXaxis()->SetTitleFont(42);
  hemptyPrescale->GetYaxis()->SetTitleFont(42);
  hemptyPrescale->GetXaxis()->SetLabelFont(42);
  hemptyPrescale->GetYaxis()->SetLabelFont(42);
  hemptyPrescale->GetXaxis()->SetLabelSize(0.040);//0.035
  hemptyPrescale->GetYaxis()->SetLabelSize(0.040);//0.035  
  hemptyPrescale->GetXaxis()->SetLabelOffset(0.01);
  canvasPrescale->cd(1);
 // gPad->SetLogy();
  hemptyPrescale->Draw();
  ratioHLTMB_20->SetLineColor(1);
  ratioHLTMB_20->Draw("same");
  TF1 *pol0_MB= new TF1("pol0_MB","pol0_MB",40,60);
  ratioHLTMB_20->Fit("pol0_MB","","",20,40);
  TLatex *  tex_MB = new TLatex(1.82,1.836,Form("Ratio(HLTMB/HLT20)= %f #pm %f",pol0_MB->GetParameter(0),pol0_MB->GetParError(0)));
  tex_MB->SetTextSize(0.04);
  tex_MB->Draw();
  canvasPrescale->cd(2);
 // gPad->SetLogy();
  hemptyPrescale->Draw();
  ratioHLT20_40->SetLineColor(1);
  ratioHLT20_40->Draw("same");
  TF1 *pol0_0= new TF1("pol0_0","pol0_0",40,60);
  ratioHLT20_40->Fit("pol0_0","","",40,60);
  TLatex *  tex_0 = new TLatex(1.82,1.836,Form("Ratio(HLT20/HLT40)= %f #pm %f",pol0_0->GetParameter(0),pol0_0->GetParError(0)));
  tex_0->SetTextSize(0.04);
  tex_0->Draw();
  canvasPrescale->cd(3);
  hemptyPrescale->Draw();
  ratioHLT40_60->SetLineColor(1);
  ratioHLT40_60->Draw("same");
  TF1 *pol0_1= new TF1("pol0_1","pol0_1",60,100);
  ratioHLT40_60->Fit("pol0_1","","",60,100);
  TLatex *  tex_1 = new TLatex(1.82,1.836,Form("Ratio(HLT40/HLT60)= %f #pm %f",pol0_1->GetParameter(0),pol0_1->GetParError(0)));
  tex_1->SetTextSize(0.04);
  tex_1->Draw();
  canvasPrescale->cd(4);
  hemptyPrescale->Draw();
  ratioHLT20_60->SetLineColor(1);
  ratioHLT20_60->Draw("same");
  TF1 *pol0_2= new TF1("pol0_2","pol0_2",60,100);
  ratioHLT20_60->Fit("pol0_2","","",60,100);
  TLatex *  tex_2 = new TLatex(1.82,1.836,Form("Ratio(HLT20/HLT60)= %f #pm %f",pol0_2->GetParameter(0),pol0_2->GetParError(0)));
  tex_2->SetTextSize(0.04);
  tex_2->Draw();


 /*
  TString inputfilePbPbMB="/data/jisun/PbPb2015/HF2and_skim_MB1to7_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root";
  TFile* filePbPbMBraw = new TFile(inputfilePbPbMB.Data());  
  TTree* HltTreePbPbMB= (TTree*) filePbPbMBraw->Get("ntHlt");
  TTree* HltHiPbPbMB= (TTree*) filePbPbMBraw->Get("ntHi");
  HltTreePbPbMB->AddFriend(HltHiPbPbMB);
  
  TH1D*hcountsMBPbPb=new TH1D("hcountsMBPbPb","hcountsMBPbPb",2,-200,200);
  HltTreePbPbMB->Draw("1>>hcountsMBPbPb",Form("%s&&%s",cut.Data(),selection.Data()));
  double ncountsMBPbPb=hcountsMBPbPb->GetEntries();
  */
  double ncountsMBPbPb=1.48357e+08;
  double lumiPbPbMB=ncountsMBPbPb*TAA;
  cout<<"ncountsMBPbPb="<<ncountsMBPbPb<<endl;
  cout<<"luminosity MB="<<lumiPbPbMB<<endl;


  const int nbinsstudy=3;
  double binsstudy[nbinsstudy+1]={15.,20.,25.,30.};
  double binmedium[nbinsstudy]={17.5,22.5,27.5};
  
  TH1D* hValuesMB = new TH1D("hValuesMB","",nbinsstudy,binsstudy);
  TH1D* hValuesD20 = new TH1D("hValuesD20","",nbinsstudy,binsstudy);
  TH1D* hDcandValuesMB = new TH1D("hDcandValuesMB","",nbinsstudy,binsstudy);
  TH1D* hDcandValuesD20 = new TH1D("hDcandValuesD20","",nbinsstudy,binsstudy);

  for (int i=0;i<nbinsstudy;i++){
  
    double valueMB=hYieldCorrected[0]->GetBinContent(hYieldCorrected[0]->FindBin(binmedium[i]));
    double errvalueMB=hYieldCorrected[0]->GetBinError(hYieldCorrected[0]->FindBin(binmedium[i]));
    double valueD20=hYieldCorrected[1]->GetBinContent(hYieldCorrected[1]->FindBin(binmedium[i]));
    double errvalueD20=hYieldCorrected[1]->GetBinError(hYieldCorrected[1]->FindBin(binmedium[i]));
    
    double DcandvalueMB=hDcandidatesCorrectedFONLLnorm[0]->GetBinContent(hDcandidatesCorrectedFONLLnorm[0]->FindBin(binmedium[i]));
    double DcanderrvalueMB=hDcandidatesCorrectedFONLLnorm[0]->GetBinError(hDcandidatesCorrectedFONLLnorm[0]->FindBin(binmedium[i]));
    double DcandvalueD20=hDcandidatesCorrectedFONLLnorm[1]->GetBinContent(hDcandidatesCorrectedFONLLnorm[1]->FindBin(binmedium[i]));
    double DcanderrvalueD20=hDcandidatesCorrectedFONLLnorm[1]->GetBinError(hDcandidatesCorrectedFONLLnorm[1]->FindBin(binmedium[i]));

    hValuesMB->SetBinContent(i+1,valueMB);
    hValuesMB->SetBinError(i+1,errvalueMB);
    hValuesD20->SetBinContent(i+1,valueD20);
    hValuesD20->SetBinError(i+1,errvalueD20);
    
    hDcandValuesMB->SetBinContent(i+1,DcandvalueMB);
    hDcandValuesMB->SetBinError(i+1,DcanderrvalueMB);
    hDcandValuesD20->SetBinContent(i+1,DcandvalueD20);
    hDcandValuesD20->SetBinError(i+1,DcanderrvalueD20);

  }

  hValuesD20->Sumw2();
  hValuesMB->Sumw2();
  hDcandValuesD20->Sumw2();
  hDcandValuesMB->Sumw2();
  
  TH1D* hRatioTriggeredOverMB = (TH1D*)hValuesD20->Clone("hRatioTriggeredOverMB");
  hRatioTriggeredOverMB->Divide(hValuesMB);
  hRatioTriggeredOverMB->Scale(lumiPbPbMB);  
  
  TH1D* hRatioTriggeredOverMBDcand = (TH1D*)hDcandValuesD20->Clone("hRatioTriggeredOverMBDcand");
  hRatioTriggeredOverMBDcand->Divide(hDcandValuesMB);
  hRatioTriggeredOverMBDcand->Scale(lumiPbPbMB);  

  for (int i=1;i<3;i++) cout<<"luminosity="<<hRatioTriggeredOverMB->GetBinContent(i)<<"with error="<<hRatioTriggeredOverMB->GetBinError(i)<<endl;
  for (int i=1;i<3;i++) cout<<"luminosity Dcand="<<hRatioTriggeredOverMBDcand->GetBinContent(i)<<"with error="<<hRatioTriggeredOverMBDcand->GetBinError(i)<<endl;

  TCanvas*canvas=new TCanvas("canvas","canvas",1000,500);
  canvas->Divide(2,1);
  canvas->cd(1);
  TH2F* hemptyLumi=new TH2F("hemptyLumi","",50,15,35,10.,0,30); 
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
  TF1 *pol0_yield = hRatioTriggeredOverMB->GetFunction("pol0");
  TLatex *  tex_yield = new TLatex(20.82,25.836,Form("Lumi= %f #pm %f",pol0_yield->GetParameter(0),pol0_yield->GetParError(0)));
  tex_yield->SetTextSize(0.04);
  tex_yield->Draw();
  canvas->cd(2);
  hemptyLumi->Draw();
  hRatioTriggeredOverMBDcand->Draw("same");
  hRatioTriggeredOverMBDcand->Fit("pol0","","",20,30);
  TF1 *pol0_cand = hRatioTriggeredOverMBDcand->GetFunction("pol0");
  TLatex *  tex_cand = new TLatex(20.82,25.836,Form("Lumi= %f #pm %f",pol0_cand->GetParameter(0),pol0_cand->GetParError(0)));
  tex_cand->SetTextSize(0.04);
  tex_cand->Draw();
  
  TH1D* hYieldRatios[nFiles];
  TH1D* hDcandidatesRatios[nFiles];
  
  for (int ifile=0;ifile<nFiles;ifile++){
    hYieldRatios[ifile] = (TH1D*)hYieldCorrectedFONLLnorm[ifile]->Clone(Form("hYieldRatios_%d",ifile));
    hDcandidatesRatios[ifile] = (TH1D*)hDcandidatesCorrectedFONLLnorm[ifile]->Clone(Form("hDcandidatesRatios_%d",ifile));
  }
  

  
  int assignment[binstotal]={1,1,1,2,2,3,3};
  TH1D* hDcandidates=new TH1D("hDcandidates","hDcandidates",binstotal,ptBinsTotal);
  TH1D* hYieldTrigger=new TH1D("hYieldTrigger","hYieldTrigger",binstotal,ptBinsTotal);
  
  for (int i=0;i<binstotal;i++){
    hDcandidates->SetBinContent(i+1,hDcandidatesCorrectedFONLLnorm[assignment[i]]->GetBinContent(hDcandidatesCorrectedFONLLnorm[assignment[i]]->FindBin(ptBinsTotalCenter[i])));
    hYieldTrigger->SetBinContent(i+1,hYieldCorrectedFONLLnorm[assignment[i]]->GetBinContent(hYieldCorrectedFONLLnorm[assignment[i]]->FindBin(ptBinsTotalCenter[i])));
    hDcandidates->SetBinError(i+1,hDcandidatesCorrectedFONLLnorm[assignment[i]]->GetBinError(hDcandidatesCorrectedFONLLnorm[assignment[i]]->FindBin(ptBinsTotalCenter[i])));
    hYieldTrigger->SetBinError(i+1,hYieldCorrectedFONLLnorm[assignment[i]]->GetBinError(hYieldCorrectedFONLLnorm[assignment[i]]->FindBin(ptBinsTotalCenter[i])));
  }

  for (int ifile=0;ifile<nFiles;ifile++){
     hYieldRatios[ifile]->Divide(hYieldTrigger);
     hDcandidatesRatios[ifile]->Divide(hDcandidates);
  }
  
    for (int i=3;i<binstotal;i++){
    hYieldRatios[0]->SetBinContent(i+1,0.);
    hYieldRatios[0]->SetBinError(i+1,0.);
    hDcandidatesRatios[0]->SetBinContent(i+1,0.);
    hDcandidatesRatios[0]->SetBinError(i+1,0.);
  }


  TLine *line20 = new TLine(20,0,20,2);
  TLine *line40 = new TLine(40,0,40,2);
  TLine *line60 = new TLine(60,0,60,2);
  line20->SetLineWidth(3);
  line40->SetLineWidth(3);
  line60->SetLineWidth(3);
  
  line20->SetLineStyle(2);
  line40->SetLineStyle(2);
  line60->SetLineStyle(2);

  legendSigma->Draw();

  TCanvas* cSigmaRatioTrigger = new TCanvas("cSigmaRatioTrigger","",1000,500);
  cSigmaRatioTrigger->Divide(2,1);
  cSigmaRatioTrigger->cd(1);
  TH2F* hemptyRatioTrigger=new TH2F("hemptyRatioTrigger","",50,20,100.,10.,0.,3);
  hemptyRatioTrigger->GetXaxis()->CenterTitle();
  hemptyRatioTrigger->GetYaxis()->CenterTitle();
  hemptyRatioTrigger->GetYaxis()->SetTitle("Corrected D yields/Central values");
  hemptyRatioTrigger->GetXaxis()->SetTitleOffset(1.);
  hemptyRatioTrigger->GetYaxis()->SetTitleOffset(1.4);//1.3
  hemptyRatioTrigger->GetXaxis()->SetTitleSize(0.045);
  hemptyRatioTrigger->GetYaxis()->SetTitleSize(0.045);
  hemptyRatioTrigger->GetXaxis()->SetTitleFont(42);
  hemptyRatioTrigger->GetYaxis()->SetTitleFont(42);
  hemptyRatioTrigger->GetXaxis()->SetLabelFont(42);
  hemptyRatioTrigger->GetYaxis()->SetLabelFont(42);
  hemptyRatioTrigger->GetXaxis()->SetLabelSize(0.04);
  hemptyRatioTrigger->GetYaxis()->SetLabelSize(0.04);  
  hemptyRatioTrigger->Draw();

  for (int ifile=0;ifile<nFiles;ifile++){
    hYieldRatios[ifile] ->SetLineColor(colors[ifile]);
    hYieldRatios[ifile] ->SetLineWidth(3);
    if(ifile==0)hYieldRatios[ifile] ->SetLineWidth(6);
    hYieldRatios[ifile] ->SetMarkerColor(colors[ifile]);
    hYieldRatios[ifile] ->Draw("psame");  
  }
  
  line20->Draw();
  line40->Draw();
  line60->Draw();
  
  
  legendSigma->Draw("same");

  cSigmaRatioTrigger->cd(2);
  TH2F* hemptyRatioCountingTrigger=new TH2F("hemptyRatioCountingTrigger","",50,20,100.,10.,0.,3);
  hemptyRatioCountingTrigger->GetXaxis()->CenterTitle();
  hemptyRatioCountingTrigger->GetYaxis()->CenterTitle();
  hemptyRatioCountingTrigger->GetYaxis()->SetTitle("Corrected D counting/Central values");
  hemptyRatioCountingTrigger->GetXaxis()->SetTitleOffset(1.);
  hemptyRatioCountingTrigger->GetYaxis()->SetTitleOffset(1.4);//1.3
  hemptyRatioCountingTrigger->GetXaxis()->SetTitleSize(0.045);
  hemptyRatioCountingTrigger->GetYaxis()->SetTitleSize(0.045);
  hemptyRatioCountingTrigger->GetXaxis()->SetTitleFont(42);
  hemptyRatioCountingTrigger->GetYaxis()->SetTitleFont(42);
  hemptyRatioCountingTrigger->GetXaxis()->SetLabelFont(42);
  hemptyRatioCountingTrigger->GetYaxis()->SetLabelFont(42);
  hemptyRatioCountingTrigger->GetXaxis()->SetLabelSize(0.04);
  hemptyRatioCountingTrigger->GetYaxis()->SetLabelSize(0.04);  
  hemptyRatioCountingTrigger->Draw();

  for (int ifile=0;ifile<nFiles;ifile++){
    hDcandidatesRatios[ifile] ->SetLineColor(colors[ifile]);
    hDcandidatesRatios[ifile] ->SetLineWidth(3);
    if(ifile==0)hDcandidatesRatios[ifile] ->SetLineWidth(6);
    hDcandidatesRatios[ifile] ->SetMarkerColor(colors[ifile]);
    hDcandidatesRatios[ifile] ->Draw("psame");  
  }
  
  legendSigma->Draw("same");
  line20->Draw();
  line40->Draw();
  line60->Draw();

 TCanvas* cMBfocus = new TCanvas("cMBfocus","",1000,500);
  cMBfocus->Divide(2,1);
  cMBfocus->cd(1);
  TH2F* hemptyMBfocus=new TH2F("hemptyMBfocus","",50,20,40.,10.,0.5,1.5);
  hemptyMBfocus->GetXaxis()->CenterTitle();
  hemptyMBfocus->GetYaxis()->CenterTitle();
  hemptyMBfocus->GetYaxis()->SetTitle("Corrected D counting/Central values");
  hemptyMBfocus->GetXaxis()->SetTitleOffset(1.);
  hemptyMBfocus->GetYaxis()->SetTitleOffset(1.4);//1.3
  hemptyMBfocus->GetXaxis()->SetTitleSize(0.045);
  hemptyMBfocus->GetYaxis()->SetTitleSize(0.045);
  hemptyMBfocus->GetXaxis()->SetTitleFont(42);
  hemptyMBfocus->GetYaxis()->SetTitleFont(42);
  hemptyMBfocus->GetXaxis()->SetLabelFont(42);
  hemptyMBfocus->GetYaxis()->SetLabelFont(42);
  hemptyMBfocus->GetXaxis()->SetLabelSize(0.04);
  hemptyMBfocus->GetYaxis()->SetLabelSize(0.04);  
  hemptyMBfocus->Draw();
  
  TH1D*hMBfocus=(TH1D*)hDcandidatesRatios[0]->Clone("hMBfocus");
  hMBfocus->Divide(hYieldRatios[0]);
  
  hDcandidatesRatios[0] ->SetLineColor(1);
  hDcandidatesRatios[0] ->SetLineWidth(3);
  hDcandidatesRatios[0] ->SetLineWidth(6);
  hDcandidatesRatios[0] ->SetMarkerColor(2);
  hDcandidatesRatios[0] ->Draw("psame");  

  hYieldRatios[0] ->SetLineColor(2);
  hYieldRatios[0] ->SetLineWidth(3);
  hYieldRatios[0] ->SetLineWidth(6);
  hYieldRatios[0] ->SetMarkerColor(2);
  hYieldRatios[0] ->Draw("psame");  


  TLegend *legendSigmaMBfocus=new TLegend(0.311747,0.6945694,0.6401439,0.8740055,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigmaMBfocus->SetBorderSize(0);
  legendSigmaMBfocus->SetLineColor(0);
  legendSigmaMBfocus->SetFillColor(0);
  legendSigmaMBfocus->SetFillStyle(1001);
  legendSigmaMBfocus->SetTextFont(42);
  legendSigmaMBfocus->SetTextSize(0.045);
  
  TLegendEntry *myentry;
  myentry=legendSigmaMBfocus->AddEntry(hDcandidatesRatios[0] ,"Ratio MB/D20 with bin counting","f");
  myentry->SetTextFont(42);
  myentry->SetLineColor(1);
  myentry->SetMarkerColor(1);
  myentry=legendSigmaMBfocus->AddEntry(hYieldRatios[0] ,"Ratio MB/D20 with fit extraction","f");
  myentry->SetTextFont(42);
  myentry->SetLineColor(1);
  myentry->SetMarkerColor(1);
  legendSigmaMBfocus->Draw();
  
  TLine *lunity = new TLine(20,1,40,1);
  lunity->SetLineWidth(3);
  lunity->SetLineStyle(2);
  lunity->Draw();

  cMBfocus->cd(2);
  TH2F* hemptyMBfocus2=new TH2F("hemptyMBfocus2","",50,20,40.,10.,0.5,1.5);
  hemptyMBfocus2->GetXaxis()->CenterTitle();
  hemptyMBfocus2->GetYaxis()->CenterTitle();
  hemptyMBfocus2->GetYaxis()->SetTitle("Ratio counting/Fit");
  hemptyMBfocus2->GetXaxis()->SetTitleOffset(1.);
  hemptyMBfocus2->GetYaxis()->SetTitleOffset(1.4);//1.3
  hemptyMBfocus2->GetXaxis()->SetTitleSize(0.045);
  hemptyMBfocus2->GetYaxis()->SetTitleSize(0.045);
  hemptyMBfocus2->GetXaxis()->SetTitleFont(42);
  hemptyMBfocus2->GetYaxis()->SetTitleFont(42);
  hemptyMBfocus2->GetXaxis()->SetLabelFont(42);
  hemptyMBfocus2->GetYaxis()->SetLabelFont(42);
  hemptyMBfocus2->GetXaxis()->SetLabelSize(0.04);
  hemptyMBfocus2->GetYaxis()->SetLabelSize(0.04);  
  hemptyMBfocus2->Draw();
  lunity->Draw();

  hMBfocus->Draw("same");

  if(isTriggerCorrected){
  canvasPrescale->SaveAs("TriggerTests/canvasPrescaleDataDrivenPbPb.pdf");
  cMBfocus->SaveAs("TriggerTests/cMBfocus.pdf");
  cSigmaRatioTrigger->SaveAs("TriggerTests/TriggerCrossSectionRatioPbPb.pdf");
  }
  else{
  canvasPrescale->SaveAs("TriggerTests/canvasPrescaleDataDrivenPbPb_TriggerUncorrected.pdf");
  cMBfocus->SaveAs("TriggerTests/cMBfocus_TriggerUncorrected.pdf");
  cSigmaRatioTrigger->SaveAs("TriggerTests/TriggerCrossSectionRatioPbPb_TriggerUncorrected.pdf");
  }
}
