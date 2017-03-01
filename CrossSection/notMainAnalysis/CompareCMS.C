using namespace std;
#include "uti.h"
#include "ChargedHad/RAA_0_10.C"
#include "ChargedHad/RAA_0_100.C"
#include "TLegendEntry.h"
#include "TGraphErrors.h"
#include "../Systematics/systematics.C"

void CompareCMS(TString fileMB="ROOTfiles/outputRAAMB.root", TString file="ROOTfiles/outputRAA.root",bool isALICE)
{

  double centMin=0.;
  double centMax=10.;
  
  gStyle->SetOptTitle(0);   
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  
  bool superimposedALICE=false;

  TFile* filePPMB = new TFile(fileMB.Data());  
  TGraphAsymmErrors* gNuclearModificationMB = (TGraphAsymmErrors*)filePPMB->Get("gNuclearModification");
  TH1D* hNuclearModificationMB = (TH1D*)filePPMB->Get("hNuclearModification");

  TFile* filePP = new TFile(file.Data());  
  TGraphAsymmErrors* gNuclearModification = (TGraphAsymmErrors*)filePP->Get("gNuclearModification");
  TH1D* hNuclearModification = (TH1D*)filePP->Get("hNuclearModification");
  
  TCanvas*canvasRAA=new TCanvas("canvasRAA","canvasRAA",600,600);//550,500
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

  TH2F* hemptyEff=new TH2F("hemptyEff","",50,0.5,150.,10.,0,1.7);//50,-2,120.,10.,0,1.5
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("D^{0} R_{AA}");
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


	TFile * input = new TFile("PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent0to100_ptbin12_y1_dataplusfonll.root");

	TGraphAsymmErrors * D0_fonll_raa_errorsys = ( TGraphAsymmErrors *) input->Get("D0_fonll_raa_errorsys");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll = ( TGraphAsymmErrors *) input->Get("D0_fonll_raa_errorfonll");//error from pp reference, not only fonll
	TGraphAsymmErrors * D0_fonll_raa_errordata_dataextraref = ( TGraphAsymmErrors *) input->Get("D0_fonll_raa_errordata_dataextraref");
	TGraphAsymmErrors * D0_fonll_raa_errordata_FONLLref = ( TGraphAsymmErrors *) input->Get("D0_fonll_raa_errordata_FONLLref");

	D0_fonll_raa_errorsys->SetLineColor(2);
	D0_fonll_raa_errorfonll->SetLineColor(2);
	D0_fonll_raa_errordata_dataextraref->SetLineColor(2);
	D0_fonll_raa_errordata_FONLLref->SetLineColor(2);
	
	D0_fonll_raa_errorsys->SetLineWidth(2);
	D0_fonll_raa_errorfonll->SetLineWidth(2);
	D0_fonll_raa_errordata_dataextraref->SetLineWidth(2);
	D0_fonll_raa_errordata_FONLLref->SetLineWidth(2);

	D0_fonll_raa_errorsys->SetMarkerColor(2);
	D0_fonll_raa_errorfonll->SetMarkerColor(2);
	D0_fonll_raa_errordata_dataextraref->SetMarkerColor(2);
	D0_fonll_raa_errordata_FONLLref->SetMarkerColor(2);
/*	
	D0_fonll_raa_errorfonll->Draw("[2same");
	D0_fonll_raa_errordata_dataextraref->Draw("2same");
    D0_fonll_raa_errordata_FONLLref->Draw("2same");
	D0_fonll_raa_errorsys->Draw("2psame");
*/

	D0_fonll_raa_errorsys->Draw("2same");
	D0_fonll_raa_errorfonll->Draw("2same");
	D0_fonll_raa_errordata_dataextraref->Draw("psame");
	D0_fonll_raa_errordata_FONLLref->Draw("psame");

  TLine *line = new TLine(0.5,1,150,1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();

  gNuclearModification->SetFillColor(5);//1
  gNuclearModification->SetFillStyle(0);//0 
  gNuclearModification->SetLineWidth(3);//3
  gNuclearModification->SetMarkerSize(1);
  gNuclearModification->SetMarkerStyle(21);
  gNuclearModification->SetLineColor(1);//kGreen+4
  gNuclearModification->SetMarkerColor(1);//kGreen+4
  gNuclearModification->Draw("5same");
  gNuclearModificationMB->SetFillColor(5);//1
  gNuclearModificationMB->SetFillStyle(0);//0 
  gNuclearModificationMB->SetLineWidth(3);//3
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

      // Plot: p9059_d1x1y1

  Float_t systnorm = normalizationUncertaintyForRAA(centMin,centMax)*1.e-2;
  TBox* bSystnorm= new TBox(0.5,1-systnorm,0.6,1+systnorm);
  bSystnorm->SetLineColor(16);
  bSystnorm->SetFillColor(16);
  bSystnorm->Draw();

  TLatex* texlumi = new TLatex(0.19,0.936,"25.8 pb^{-1} (5.02 TeV pp) + 404 #mub^{-1} (5.02 TeV PbPb)");
  texlumi->SetNDC();
  //texlumi->SetTextAlign(31);
  texlumi->SetTextFont(42);
  texlumi->SetTextSize(0.038);
  texlumi->SetLineWidth(2);
  texlumi->Draw();
  TLatex* texcms = new TLatex(0.22,0.895,"CMS Preliminary");
  texcms->SetNDC();
  texcms->SetTextAlign(13);
  texcms->SetTextFont(42);
  texcms->SetTextSize(0.045);
  texcms->SetLineWidth(2);
  texcms->Draw();

  TLegend *legendSigma=new TLegend(0.4436242,0.7474695,0.842953,0.8457592,"");//0.5100806,0.6268644,0.8084677,0.7805932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(0);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.031);//0.05

  TLegendEntry *ent_Dhighpt=legendSigma->AddEntry(gNuclearModification,"CMS, 5.02 TeV, |y|<1","pf");
   ent_Dhighpt->SetTextFont(42);
   ent_Dhighpt->SetLineColor(4);
   ent_Dhighpt->SetMarkerColor(4);
   ent_Dhighpt->SetTextSize(0.035);//0.03

   legendSigma->Draw();
   
  TLegendEntry *entALICE=legendSigma->AddEntry(D0_fonll_raa_errorsys,"CMS, 2.76 TeV, |y|<1","pf");
   entALICE->SetTextFont(42);
   entALICE->SetLineColor(4);
   entALICE->SetMarkerColor(4);
   entALICE->SetFillStyle(1);
   entALICE->SetTextSize(0.035);//0.03
   legendSigma->Draw();


  TLatex* texSystnorm = new TLatex(0.23,0.70,"T_{AA} and lumi.");
  texSystnorm->SetNDC();
  texSystnorm->SetTextColor(1);
  texSystnorm->SetTextFont(42);
  texSystnorm->SetTextSize(0.04);
  texSystnorm->SetLineWidth(2);
  texSystnorm->Draw();
  texSystnorm = new TLatex(0.23,0.65,"uncertainty");
  texSystnorm->SetNDC();
  texSystnorm->SetTextColor(1);
  texSystnorm->SetTextFont(42);
  texSystnorm->SetTextSize(0.04);
  texSystnorm->SetLineWidth(2);
  texSystnorm->Draw();
  canvasRAA->Update();
  canvasRAA->RedrawAxis();

    
  canvasRAA ->SaveAs(Form("plotRAA/canvasCMS_%.0f_%.0f.png",centMin,centMax));
  canvasRAA ->SaveAs(Form("plotRAA/canvasCMS_%.0f_%.0f.pdf",centMin,centMax));
  }

int main(int argc, char *argv[])
{
  if(argc==9)
    {
      CombineRAA(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]), atoi(argv[7]), atoi(argv[8]));
      return 0;
    }
  else if(argc==7)
    {
      CombineRAA(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]));
      return 0;
    }
  else
    { 
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
}



