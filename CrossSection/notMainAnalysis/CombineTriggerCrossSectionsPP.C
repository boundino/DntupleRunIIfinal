#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"
#include "../Systematics/systematics.C"

double lumiPP=25.8;
double lumiPPMB=0.0361128;

void CombineTriggerCrossSectionsPP(bool isTriggerCorrected=true,bool isLumiNorm=true)
{
  
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  const int nFiles = 5;
  TString myfiles[nFiles] = {"ROOTfiles/CrossSectionFONLLPPMB_extended.root", 
                                            "ROOTfiles/CrossSectionFONLLPP_8.root",
                                            "ROOTfiles/CrossSectionFONLLPP_15.root",
                                            "ROOTfiles/CrossSectionFONLLPP_30.root",
                                            "ROOTfiles/CrossSectionFONLLPP_50.root"};
  TString label[nFiles] = {"MB", "HLTD8", "HLTD15", "HLTD30","HLTD50"};

  int colors[nFiles] = {1,2,3,4,6};

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
      hYieldCorrected[ifile]->Scale(1/lumiPPMB);
      hYieldCorrectedFONLLnorm[ifile]->Scale(1/lumiPPMB);
      hDcandidatesCorrectedFONLLnorm[ifile]->Scale(1/lumiPPMB);
    }
    if(isLumiNorm&&ifile>0) {
      hYieldCorrected[ifile]->Scale(1/lumiPP);
      hYieldCorrectedFONLLnorm[ifile]->Scale(1/lumiPP);
      hDcandidatesCorrectedFONLLnorm[ifile]->Scale(1/lumiPP);
    }
  }
    
  TCanvas* cSigmaAll = new TCanvas("cSigmaAll","",1000,500);
  cSigmaAll->cd(1);
  gPad->SetLogy();
  gPad->SetLogx();
  TH2F* hemptySigma=new TH2F("hemptySigma","",50,0.,110.,10.,1e-3,1.e12);  
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
  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,3,100.,10.,0.,0.2);
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
  TH2F* hemptyRatioCounting=new TH2F("hemptyRatioCounting","",50,3,100.,10.,0.,0.2);
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

  TH1D* ratioHLT30_50=(TH1D*)hYieldCorrectedFONLLnorm[3]->Clone("ratioHLT30_50");
  ratioHLT30_50->Divide(hYieldCorrectedFONLLnorm[4]);

  TH1D* ratioHLT15_30=(TH1D*)hYieldCorrectedFONLLnorm[2]->Clone("ratioHLT15_30");
  ratioHLT15_30->Divide(hYieldCorrectedFONLLnorm[3]);

  TH1D* ratioHLT8_15=(TH1D*)hYieldCorrectedFONLLnorm[1]->Clone("ratioHLT8_15");
  ratioHLT8_15->Divide(hYieldCorrectedFONLLnorm[2]);
  
  TH1D* ratioHLTMB_8=(TH1D*)hYieldCorrectedFONLLnorm[0]->Clone("ratioHLTMB_8");
  ratioHLTMB_8->Divide(hYieldCorrectedFONLLnorm[1]);

  TH1D* ratioHLT15_50=(TH1D*)hYieldCorrectedFONLLnorm[2]->Clone("ratioHLT15_50");
  ratioHLT15_50->Divide(hYieldCorrectedFONLLnorm[4]);
  
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
  ratioHLTMB_8->SetLineColor(1);
  ratioHLTMB_8->Draw("same");
  TF1 *pol0_MB= new TF1("pol0_MB","pol0_MB",20,30);
  ratioHLTMB_8->Fit("pol0_MB","","",20,30);
  TLatex *  tex_MB = new TLatex(1.82,1.836,Form("Ratio(HLTMB/HLT8)= %f #pm %f",pol0_MB->GetParameter(0),pol0_MB->GetParError(0)));
  tex_MB->SetTextSize(0.04);
  tex_MB->Draw();
  canvasPrescale->cd(2);
 // gPad->SetLogy();
  hemptyPrescale->Draw();
  ratioHLT8_15->SetLineColor(1);
  ratioHLT8_15->Draw("same");
  TF1 *pol0_0= new TF1("pol0_0","pol0_0",20,30);
  ratioHLT8_15->Fit("pol0_0","","",20,30);
  TLatex *  tex_0 = new TLatex(1.82,1.836,Form("Ratio(HLT8/HLT15)= %f #pm %f",pol0_0->GetParameter(0),pol0_0->GetParError(0)));
  tex_0->SetTextSize(0.04);
  tex_0->Draw();
  canvasPrescale->cd(3);
  hemptyPrescale->Draw();
  ratioHLT15_30->SetLineColor(1);
  ratioHLT15_30->Draw("same");
  TF1 *pol0_1= new TF1("pol0_1","pol0_1",30,50);
  ratioHLT15_30->Fit("pol0_1","","",30,50);
  TLatex *  tex_1 = new TLatex(1.82,1.836,Form("Ratio(HLT15/HLT30)= %f #pm %f",pol0_1->GetParameter(0),pol0_1->GetParError(0)));
  tex_1->SetTextSize(0.04);
  tex_1->Draw();
  canvasPrescale->cd(4);
  hemptyPrescale->Draw();
  ratioHLT30_50->SetLineColor(1);
  ratioHLT30_50->Draw("same");
  TF1 *pol0_2;
  pol0_2= new TF1("pol0_2","pol0_2",20,30);
  ratioHLT30_50->Fit("pol0_2","","",50,80);
  TLatex *  tex_2 = new TLatex(1.82,1.836,Form("Ratio(HLT30/HLT50)= %f #pm %f",pol0_2->GetParameter(0),pol0_2->GetParError(0)));
  tex_2->SetTextSize(0.04);
  tex_2->Draw();
  /*
  canvasPrescale->cd(5);
  hemptyPrescale->Draw();
  ratioHLT15_50->SetLineColor(1);
  ratioHLT15_50->Draw("same");
  TF1 *pol0_3;
  pol0_3= new TF1("pol0_3","pol0_3",20,30);
  ratioHLT15_50->Fit("pol0_3","","",50,80);
  TLatex *  tex_3 = new TLatex(1.82,1.836,Form("Ratio(HLT15/HLT50)= %f #pm %f",pol0_3->GetParameter(0),pol0_3->GetParError(0)));
  tex_3->SetTextSize(0.04);
  tex_3->Draw();
  */

  const int nbinsstudy=3;
  double binsstudy[nbinsstudy+1]={10.,15.,20.,25.};
  double binmedium[nbinsstudy]={12.5,17.5,22.5};
    
  TH1D* hValuesMB = new TH1D("hValuesMB","",nbinsstudy,binsstudy);
  TH1D* hValuesD8 = new TH1D("hValuesD8","",nbinsstudy,binsstudy);
  TH1D* hDcandValuesMB = new TH1D("hDcandValuesMB","",nbinsstudy,binsstudy);
  TH1D* hDcandValuesD8 = new TH1D("hDcandValuesD8","",nbinsstudy,binsstudy);


  for (int i=0;i<nbinsstudy;i++){

    double valueMB=hYieldCorrected[0]->GetBinContent(hYieldCorrected[0]->FindBin(binmedium[i]));
    double errvalueMB=hYieldCorrected[0]->GetBinError(hYieldCorrected[0]->FindBin(binmedium[i]));
    double valueD8=hYieldCorrected[1]->GetBinContent(hYieldCorrected[1]->FindBin(binmedium[i]));
    double errvalueD8=hYieldCorrected[1]->GetBinError(hYieldCorrected[1]->FindBin(binmedium[i]));
    
    double DcandvalueMB=hDcandidatesCorrectedFONLLnorm[0]->GetBinContent(hDcandidatesCorrectedFONLLnorm[0]->FindBin(binmedium[i]));
    double DcanderrvalueMB=hDcandidatesCorrectedFONLLnorm[0]->GetBinError(hDcandidatesCorrectedFONLLnorm[0]->FindBin(binmedium[i]));
    double DcandvalueD8=hDcandidatesCorrectedFONLLnorm[1]->GetBinContent(hDcandidatesCorrectedFONLLnorm[1]->FindBin(binmedium[i]));
    double DcanderrvalueD8=hDcandidatesCorrectedFONLLnorm[1]->GetBinError(hDcandidatesCorrectedFONLLnorm[1]->FindBin(binmedium[i]));

    hValuesMB->SetBinContent(i+1,valueMB);
    hValuesMB->SetBinError(i+1,errvalueMB);
    hValuesD8->SetBinContent(i+1,valueD8);
    hValuesD8->SetBinError(i+1,errvalueD8);
    
    hDcandValuesMB->SetBinContent(i+1,DcandvalueMB);
    hDcandValuesMB->SetBinError(i+1,DcanderrvalueMB);
    hDcandValuesD8->SetBinContent(i+1,DcandvalueD8);
    hDcandValuesD8->SetBinError(i+1,DcanderrvalueD8);
    
  }
  
  hValuesD8->Sumw2();
  hValuesMB->Sumw2();
  
  TH1D* hRatioMBOverTriggered = (TH1D*)hValuesMB->Clone("hRatioMBOverTriggered");
  hRatioMBOverTriggered->Divide(hValuesD8);
  hRatioMBOverTriggered->Scale(25.8);  
  
  TH1D* hRatioMBOverTriggeredDcand = (TH1D*)hDcandValuesMB->Clone("hRatioMBOverTriggeredDcand");
  hRatioMBOverTriggeredDcand->Divide(hDcandValuesD8);
  hRatioMBOverTriggeredDcand->Scale(25.8);  

  
  for (int i=1;i<nbinsstudy+1;i++) cout<<"luminosity="<<hRatioMBOverTriggered->GetBinContent(i)<<"with error="<<hRatioMBOverTriggered->GetBinError(i)<<endl;
  for (int i=1;i<nbinsstudy+1;i++) cout<<"luminosity D cand="<<hRatioMBOverTriggeredDcand->GetBinContent(i)<<"with error="<<hRatioMBOverTriggeredDcand->GetBinError(i)<<endl;

  TCanvas*canvasLumi=new TCanvas("canvasLumi","canvasLumi",1000,500);
  canvasLumi->Divide(2,1);
  canvasLumi->cd(1);
  TH2F* hemptyLumi=new TH2F("hemptyLumi","",50,5,30,10.,0,0.10); 
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
  TF1 *pol0_yield = hRatioMBOverTriggered->GetFunction("pol0");
  TLatex *  tex_yield = new TLatex(10.82,0.07,Form("Lumi= %f #pm %f",pol0_yield->GetParameter(0),pol0_yield->GetParError(0)));
  tex_yield->SetTextSize(0.04);
  tex_yield->Draw();
  canvasLumi->cd(2);
  hemptyLumi->Draw();
  hRatioMBOverTriggeredDcand->Draw("same");
  hRatioMBOverTriggeredDcand->Fit("pol0","","",10,25);
  TF1 *pol0_cand = hRatioMBOverTriggeredDcand->GetFunction("pol0");
  TLatex *  tex_cand = new TLatex(10.82,0.07,Form("Lumi= %f #pm %f",pol0_cand->GetParameter(0),pol0_cand->GetParError(0)));
  tex_cand->SetTextSize(0.04);
  tex_cand->Draw();
  
  TH1D* hYieldRatios[nFiles];
  TH1D* hDcandidatesRatios[nFiles];
  
  for (int ifile=0;ifile<nFiles;ifile++){
    hYieldRatios[ifile] = (TH1D*)hYieldCorrectedFONLLnorm[ifile]->Clone(Form("hYieldRatios_%d",ifile));
    hDcandidatesRatios[ifile] = (TH1D*)hDcandidatesCorrectedFONLLnorm[ifile]->Clone(Form("hDcandidatesRatios_%d",ifile));
  }
  

  const int binstotal=9;
  double ptBinsTotal[binstotal+1] = {10.,15.,20.,25,30.,40.,50.,60.,80,100};
  double ptBinsTotalCenter[binstotal] = {12.5,17.5,22.5,27.5,35.,45.,55.,70.,90};
  
  int assignment[binstotal]={0,0,2,2,2,3,3,4,4};
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
  
    for (int i=4;i<binstotal;i++){
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
  TH2F* hemptyRatioTrigger=new TH2F("hemptyRatioTrigger","",50,5,100.,10.,0.,3);
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
  TH2F* hemptyRatioCountingTrigger=new TH2F("hemptyRatioCountingTrigger","",50,5,100.,10.,0.,3);
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
  TH2F* hemptyMBfocus=new TH2F("hemptyMBfocus","",50,8,20.,10.,0.5,1.5);
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
    
  hDcandidatesRatios[1] ->SetLineColor(1);
  hDcandidatesRatios[1] ->SetLineWidth(5);
  hDcandidatesRatios[1] ->SetLineWidth(6);
  hDcandidatesRatios[1] ->SetMarkerColor(2);
  hDcandidatesRatios[1] ->Draw("psame");  

  hYieldRatios[1] ->SetLineColor(2);
  hYieldRatios[1] ->SetLineWidth(3);
  hYieldRatios[1] ->SetLineWidth(6);
  hYieldRatios[1] ->SetMarkerColor(2);
  hYieldRatios[1] ->Draw("psame");  


  TH1D*hMBfocus=(TH1D*)hDcandidatesRatios[1]->Clone("hMBfocus");
  hMBfocus->Divide(hYieldRatios[1] );


  TLegend *legendSigmaMBfocus=new TLegend(0.311747,0.6945694,0.6401439,0.8740055,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigmaMBfocus->SetBorderSize(0);
  legendSigmaMBfocus->SetLineColor(0);
  legendSigmaMBfocus->SetFillColor(0);
  legendSigmaMBfocus->SetFillStyle(1001);
  legendSigmaMBfocus->SetTextFont(42);
  legendSigmaMBfocus->SetTextSize(0.045);
  
  TLegendEntry *myentry;
  myentry=legendSigmaMBfocus->AddEntry(hDcandidatesRatios[0] ,"Ratio MB/D8 with bin counting","f");
  myentry->SetTextFont(42);
  myentry->SetLineColor(1);
  myentry->SetMarkerColor(1);
  myentry=legendSigmaMBfocus->AddEntry(hYieldRatios[0] ,"Ratio MB/D8 with fit extraction","f");
  myentry->SetTextFont(42);
  myentry->SetLineColor(2);
  myentry->SetTextColor(2);
  myentry->SetMarkerColor(2);
  legendSigmaMBfocus->Draw();
  
  TLine *lunity = new TLine(8,1,20,1);
  lunity->SetLineWidth(3);
  lunity->SetLineStyle(2);
  lunity->Draw();

  cMBfocus->cd(2);
  TH2F* hemptyMBfocus2=new TH2F("hemptyMBfocus2","",50,8,30.,10.,0.5,1.5);
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
  canvasPrescale->SaveAs("TriggerTests/canvasPrescaleDataDrivenPP.pdf");
  //cTriggerEff->SaveAs("TriggerTests/TriggerEffPP.pdf");
  //canvasLumi->SaveAs("TriggerTests/canvasLumiPP.pdf");
  //cSigma->SaveAs("TriggerTests/TriggerCrossSectionPP.pdf");
  cSigmaRatioTrigger->SaveAs("TriggerTests/TriggerCrossSectionRatioPP.pdf");
  }
  else{
  canvasPrescale->SaveAs("TriggerTests/canvasPrescaleDataDrivenPP_TriggerUncorrected.pdf");
  //cTriggerEff->SaveAs("TriggerTests/TriggerEffPP_TriggerUncorrected.pdf");
  //canvasLumi->SaveAs("TriggerTests/canvasLumiPP_TriggerUncorrected.pdf");
  //cSigma->SaveAs("TriggerTests/TriggerCrossSectionPP_TriggerUncorrected.pdf");
  cSigmaRatioTrigger->SaveAs("TriggerTests/TriggerCrossSectionRatioPP_TriggerUncorrected.pdf");
  }
}



