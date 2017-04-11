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

void CombineRAA(TString fileMB="ROOTfilesCent10/outputRAAMB.root", TString file="ROOTfilesCent10/outputRAA.root", Float_t centMin=0., Float_t centMax=10., Int_t isHadDupl=1, Int_t isBnNjpsi=1, Int_t isTheoryComparison=2, Bool_t verbose=false)
{
  gStyle->SetOptTitle(0);   
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  
  bool superimposedALICE = false;

  TFile* filePPMB = new TFile(fileMB.Data());  
  TGraphAsymmErrors* gNuclearModificationMB = (TGraphAsymmErrors*)filePPMB->Get("gNuclearModification");
  TH1D* hNuclearModificationMB = (TH1D*)filePPMB->Get("hNuclearModification");
  TFile* filePP = new TFile(file.Data());  
  TGraphAsymmErrors* gNuclearModification = (TGraphAsymmErrors*)filePP->Get("gNuclearModification");
  TH1D* hNuclearModification = (TH1D*)filePP->Get("hNuclearModification");
  
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
  canvasRAA->SetLogx();

  TH2F* hemptyEff;
  if(isHadDupl==1) hemptyEff = new TH2F("hemptyEff","",50,0.7,400.,10.,0,1.75); else hemptyEff=new TH2F("hemptyEff","",50,1.0,150.,10.,0,1.75);//50,-2,120.,10.,0,1.5
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

  TLine *line;
  if(isHadDupl==1) line = new TLine(0.7,1,400,1); else line = new TLine(1.0,1,150,1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();

  if(isHadDupl==1)
    {
      if(centMin==0&&centMax==100) RAA_0_100();
      else if(centMin==0&&centMax==10) RAA_0_10();
      else
        {
          cout<<"ERROR: Invalid Centrality range"<<endl;
        }
    }
  gNuclearModification->SetFillColor(5);//1
  gNuclearModification->SetFillStyle(3001);//0 
  gNuclearModification->SetLineWidth(1);//3
  gNuclearModification->SetMarkerSize(1);
  gNuclearModification->SetMarkerStyle(21);
  gNuclearModification->SetLineColor(1);//kGreen+4
  gNuclearModification->SetMarkerColor(1);//kGreen+4
  gNuclearModification->Draw("5same");
  gNuclearModificationMB->SetFillColor(5);//1
  gNuclearModificationMB->SetFillStyle(3001);//0 
  gNuclearModificationMB->SetLineWidth(1);//3
  gNuclearModificationMB->SetMarkerSize(1);
  gNuclearModificationMB->SetMarkerStyle(21);
  gNuclearModificationMB->SetLineColor(1);//kGreen+4
  gNuclearModificationMB->SetMarkerColor(1);//kGreen+4

  gNuclearModificationMB->Draw("5same");
  
  hNuclearModification->SetLineWidth(3);
  hNuclearModification->SetMarkerSize(1);
  hNuclearModification->SetMarkerStyle(21);
  hNuclearModification->SetLineColor(1);//kGreen+4
  hNuclearModification->SetMarkerColor(1);//kGreen+4

  hNuclearModification->Draw("psame");//same
  hNuclearModificationMB->SetLineWidth(3);
  hNuclearModificationMB->SetMarkerSize(1);
  hNuclearModificationMB->SetMarkerStyle(21);
  hNuclearModificationMB->SetLineColor(1);//kGreen+4
  hNuclearModificationMB->SetMarkerColor(1);//kGreen+4
  hNuclearModificationMB->Draw("psame");//same

  if(isBnNjpsi==1 && centMax==100)
    {
      canvasRAAPbPb_0_100_ThmRAA();
      expBeautyCMS_20170201();
    }

  Float_t systnormup = normalizationUncertaintyForRAA(centMin,centMax,true)*1.e-2;
  Float_t systnormlo = normalizationUncertaintyForRAA(centMin,centMax,false)*1.e-2;
  TBox* bSystnorm;
  if(isHadDupl==1)  bSystnorm = new TBox(0.7,1-systnormlo,0.9,1+systnormup);
  else bSystnorm= new TBox(1.0,1-systnormlo,1.2,1+systnormup);
  bSystnorm->SetLineColor(16);
  bSystnorm->SetFillColor(16);
  bSystnorm->Draw();

  TLatex* texlumi = new TLatex(0.19,0.936,"27.4 pb^{-1} (5.02 TeV pp) + 530 #mub^{-1} (5.02 TeV PbPb)");
  texlumi->SetNDC();
  texlumi->SetTextFont(42);
  texlumi->SetTextSize(0.038);
  texlumi->SetLineWidth(2);
  texlumi->Draw();
  TLatex* texcms = new TLatex(0.22,0.90,"CMS");
  texcms->SetNDC();
  texcms->SetTextAlign(13);
  texcms->SetTextFont(62);//61
  texcms->SetTextSize(0.06);
  texcms->SetLineWidth(2);
  texcms->Draw();
  TLatex* texpre = new TLatex(0.22,0.84,"Preliminary");
  texpre->SetNDC();
  texpre->SetTextAlign(13);
  texpre->SetTextFont(52);
  texpre->SetTextSize(0.04);
  texpre->SetLineWidth(2);
  texpre->Draw();

  TString texper="%";
  //TLatex * tlatexeff2=new TLatex(0.65,0.20,Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));//0.2612903,0.8425793
  TLatex * tlatexeff2 = new TLatex(0.95,0.20,Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));//0.2612903,0.8425793
  tlatexeff2->SetTextAlign(32);
  //TLatex * tlatexeff2 = new TLatex(0.41,0.58,Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));//0.2612903,0.8425793
  tlatexeff2->SetNDC();
  tlatexeff2->SetTextColor(1);
  tlatexeff2->SetTextFont(42);
  tlatexeff2->SetTextSize(0.045);
  tlatexeff2->SetLineWidth(2);
  tlatexeff2->Draw();
  //TLatex * texY = new TLatex(0.41,0.53,"|y| < 1");//0.2612903,0.8425793
  TLatex * texY = new TLatex(0.95,0.28,"|y| < 1");//0.2612903,0.8425793
  texY->SetTextAlign(32);
  texY->SetNDC();
  texY->SetTextColor(1);
  texY->SetTextFont(42);
  texY->SetTextSize(0.045);
  texY->SetLineWidth(2);
  //texY->Draw();

  TLegend* legendSigma;
  if(isHadDupl==0 && isTheoryComparison==0) legendSigma = new TLegend(0.5236242,0.7474695,0.942953,0.8457592,"");
  if(isHadDupl==1 && isBnNjpsi==0) legendSigma = new TLegend(0.4536242,0.7274695,0.912953,0.8657592,"");
  if(isHadDupl==1 && isBnNjpsi==1) legendSigma = new TLegend(0.4536242,0.6174695,0.912953,0.9057592,"");
  if(isTheoryComparison==2||isTheoryComparison==3) legendSigma = new TLegend(0.5236242,0.6474695,0.912953,0.9057592,"");
  if(isTheoryComparison==1) legendSigma = new TLegend(0.5236242,0.5974695,0.912953,0.9057592,"");
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(0);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.030);
  
  TLegendEntry *ent_Dhighpt = legendSigma->AddEntry(gNuclearModification,"D^{0} |y| < 1.0","pf");
  ent_Dhighpt->SetTextFont(42);
  ent_Dhighpt->SetLineColor(4);
  ent_Dhighpt->SetMarkerColor(4);
  ent_Dhighpt->SetTextSize(0.043);
  if(isTheoryComparison>0) ent_Dhighpt->SetTextSize(0.03);
  if(isBnNjpsi>0 || isHadDupl) ent_Dhighpt->SetTextSize(0.035);
  
  if(isHadDupl==1)
    {
      TGraphAsymmErrors* gTrackPt_leg = new TGraphAsymmErrors(1);
      gTrackPt_leg->SetMarkerStyle(20);
      gTrackPt_leg->SetMarkerSize(0.8);
      gTrackPt_leg->SetMarkerColor(kRed);
      gTrackPt_leg->SetLineColor(0);
      Int_t cl = TColor::GetColor("#ffcc00");
      gTrackPt_leg->SetFillColor(cl);
      TLegendEntry* ent_Charged = legendSigma->AddEntry(gTrackPt_leg,"charged hadrons |y| < 1.0","pf");
      ent_Charged->SetTextFont(42); 
      ent_Charged->SetTextSize(0.035);
    } 

  if(isBnNjpsi==1 && centMin==0 && centMax==100)
    {
      TLegendEntry* ent_BnNjpsi = legendSigma->AddEntry(grae,"B^{+} |y| < 2.4","pf");
      ent_BnNjpsi->SetTextFont(42);
      ent_BnNjpsi->SetTextSize(0.043);
      if(isBnNjpsi>0) ent_BnNjpsi->SetTextSize(0.035);
      TLegendEntry* ent_Njpsi = legendSigma->AddEntry((TObject*)0,"nonprompt J/#psi (2.76 TeV)",NULL);
      ent_Njpsi->SetTextFont(42);
      ent_Njpsi->SetTextSize(0.043);
      if(isBnNjpsi>0) ent_Njpsi->SetTextSize(0.035);
      TLegendEntry* ent_Njpsi1 = legendSigma->AddEntry(gre2,"1.6 < |y| < 2.4","pf");
      ent_Njpsi1->SetTextFont(42);
      ent_Njpsi1->SetTextSize(0.043);
      if(isBnNjpsi>0) ent_Njpsi1->SetTextSize(0.035);
      TLegendEntry* ent_Njpsi2 = legendSigma->AddEntry(gre,"|y| < 2.4","pf");
      ent_Njpsi2->SetTextFont(42);
      ent_Njpsi2->SetTextSize(0.043);
      if(isBnNjpsi>0) ent_Njpsi2->SetTextSize(0.035);
    } 

  if(isTheoryComparison && centMin==0. && centMax==100.)
    {
      drawTheory0100();
      legendSigma->AddEntry(gShanshanD5TeV,"S. Cao et al. 0-80%","l");
      legendSigma->AddEntry(gMagdalenaD5TeV,"M. Djordjevic","bf");
      legendSigma->AddEntry(gCUJETD5TeV,"CUJET 3.0","f");
      gADSCFT1D5TeV->SetLineColor(0);
      legendSigma->AddEntry(gADSCFT1D5TeV,"ADS/CFT HH D = const","f");
      gADSCFT2D5TeV->SetLineColor(0);
      legendSigma->AddEntry(gADSCFT2D5TeV,"ADS/CFT HH D(p)","f");
    }
  if(isTheoryComparison && centMin==0. && centMax==10.)
    {
      drawTheory010(isTheoryComparison);
      if(isTheoryComparison==1||isTheoryComparison==2)
        {
          legendSigma->AddEntry(gMagdalenaD5TeV,"M. Djordjevic","bf");
          legendSigma->AddEntry(gCUJETD5TeV,"CUJET 3.0","f");//pf
          legendSigma->AddEntry(gIvanD5TeV,"I. Vitev (g=1.8-2.0)","bf");
        }
      if (isTheoryComparison==1||isTheoryComparison==3)
        {
          legendSigma->AddEntry(gShanshanD5TeV,"S. Cao et al.","l");
          legendSigma->AddEntry(gPHSDWShadowing,"PHSD w/ shadowing ","l");
          legendSigma->AddEntry(gPHSDWOShadowing,"PHSD w/o shadowing ","l");
          gADSCFT1D5TeV->SetLineColor(0);
          legendSigma->AddEntry(gADSCFT1D5TeV,"ADS/CFT HH D = const","f");
          gADSCFT2D5TeV->SetLineColor(0);
          legendSigma->AddEntry(gADSCFT2D5TeV,"ADS/CFT HH D(p)","f");
        }
      
      if(superimposedALICE)
        {
          double p9059_d9x1y1_xval[9] = { 1.5, 2.5, 3.5, 4.5, 5.5, 7.0, 10.0, 14.0, 20.0 };
          double p9059_d9x1y1_xerrminus[9] = { 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 2.0, 2.0, 4.0 };
          double p9059_d9x1y1_xerrplus[9] = { 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 2.0, 2.0, 4.0 };
          double p9059_d9x1y1_yval[9] = { 0.695, 0.694, 0.385, 0.245, 0.186, 0.153, 0.155, 0.174, 0.219 };
          double p9059_d9x1y1_yerrminus[9] = { 0.3686583784481237, 0.29960307074527787, 0.123664869708418, 0.07561084578286371, 0.05500909015790027, 0.042485291572496, 0.0442944691807002, 0.06788225099390856, 0.137800580550301 };
          double p9059_d9x1y1_yerrplus[9] = { 0.3318870289722092, 0.2141074496602115, 0.09546203433826454, 0.06264982043070834, 0.05060632371551998, 0.03982461550347976, 0.043416586692184816, 0.06859300255857008, 0.11045361017187261 };
          double p9059_d9x1y1_ystatminus9[] = { 0.21, 0.079, 0.037, 0.026, 0.025, 0.019, 0.021, 0.048, 0.058 };
          double p9059_d9x1y1_ystatplus[9] = { 0.21, 0.079, 0.037, 0.026, 0.025, 0.019, 0.021, 0.048, 0.058 };
          int p9059_d9x1y1_numpoints = 9;
          TGraphAsymmErrors *p9059_d9x1y1 = new TGraphAsymmErrors(p9059_d9x1y1_numpoints, p9059_d9x1y1_xval, p9059_d9x1y1_yval, p9059_d9x1y1_xerrminus, p9059_d9x1y1_xerrplus, p9059_d9x1y1_yerrminus, p9059_d9x1y1_yerrplus);
          p9059_d9x1y1->SetName("/HepData/9059/d9x1y1");
          p9059_d9x1y1->SetLineColor(2);
          p9059_d9x1y1->SetMarkerColor(2);  
          p9059_d9x1y1->SetLineWidth(4);  
          p9059_d9x1y1->SetTitle("/HepData/9059/d9x1y1");
          p9059_d9x1y1->Draw("psame");
        }
    }

  legendSigma->Draw();  
  
  TLatex* texSystnorm = new TLatex(0.23,0.66,"T_{AA} and lumi.");
  //TLatex* texSystnorm = new TLatex(0.23,0.70,"T_{AA} and lumi.");
  texSystnorm->SetNDC();
  texSystnorm->SetTextColor(1);
  texSystnorm->SetTextFont(42);
  texSystnorm->SetTextSize(0.04);
  texSystnorm->SetLineWidth(2);
  texSystnorm->Draw();
  //texSystnorm = new TLatex(0.23,0.65,"uncertainty");
  texSystnorm = new TLatex(0.23,0.61,"uncertainty");
  texSystnorm->SetNDC();
  texSystnorm->SetTextColor(1);
  texSystnorm->SetTextFont(42);
  texSystnorm->SetTextSize(0.04);
  texSystnorm->SetLineWidth(2);
  texSystnorm->Draw();
  canvasRAA->Update();
  canvasRAA->RedrawAxis();
  
  if(isHadDupl==0&&isTheoryComparison==0) 
    {
      canvasRAA->SaveAs(Form("plotRAA/canvasRAA_cent_%.0f_%.0f.C",centMin,centMax));
    }

  TString texHadDupl = (isHadDupl==1)?"_charged":"";
  TString texBnNjpsi = (isBnNjpsi==1)?"_BnNjpsi":"";
  TString texTheories[3] = {"All","QCD","Transport"};
  TString texTheory = (isTheoryComparison>0)?Form("_theory%s",texTheories[isTheoryComparison-1].Data()):"";

  canvasRAA->SaveAs(Form("plotRAA/canvasRAA%s%s%s_cent_%.0f_%.0f.pdf",texHadDupl.Data(),texBnNjpsi.Data(),texTheory.Data(),centMin,centMax));

  if(verbose)
    {
      Int_t nbinsRaaMB = hNuclearModificationMB->GetSize()-2;
      Int_t nbinsRaa = hNuclearModification->GetSize()-2;
      cout<<nbinsRaaMB<<"  "<<nbinsRaa<<endl;
      for(int i=0;i<nbinsRaaMB;i++) cout<<hNuclearModificationMB->GetBinCenter(i+1)-hNuclearModificationMB->GetBinWidth(i+1)/2.<<" "<<hNuclearModificationMB->GetBinCenter(i+1)+hNuclearModificationMB->GetBinWidth(i+1)/2.<<" "<<hNuclearModificationMB->GetBinCenter(i+1)<<" "<<hNuclearModificationMB->GetBinContent(i+1)<<" "<<hNuclearModificationMB->GetBinError(i+1)<<" "<<gNuclearModificationMB->GetErrorYhigh(i)<<" "<<gNuclearModificationMB->GetErrorYlow(i)<<endl;
      for(int i=0;i<nbinsRaa;i++) cout<<hNuclearModification->GetBinCenter(i+1)-hNuclearModification->GetBinWidth(i+1)/2.<<" "<<hNuclearModification->GetBinCenter(i+1)+hNuclearModification->GetBinWidth(i+1)/2.<<" "<<hNuclearModification->GetBinCenter(i+1)<<" "<<hNuclearModification->GetBinContent(i+1)<<" "<<hNuclearModification->GetBinError(i+1)<<" "<<gNuclearModification->GetErrorYhigh(i)<<" "<<gNuclearModification->GetErrorYlow(i)<<endl;
    }
}

int main(int argc, char *argv[])
{
  if(argc==8)
    {
      CombineRAA(argv[1], argv[2], atof(argv[3]), atof(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
      return 0;
    }
  else
    { 
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}



