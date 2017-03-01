#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"


void CombinePbPbYield(TString fileMB="ROOTfiles/CrossSectionFONLLPbPbMB.root", TString file="ROOTfiles/CrossSectionFONLLPbPb.root", bool isMerged=true)
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TFile* filePPMB = new TFile(fileMB.Data());  
  TGraphAsymmErrors* gaeRatioCrossFONLLstatMB = (TGraphAsymmErrors*)filePPMB->Get("gaeRatioCrossFONLLstat");
  TGraphAsymmErrors* gaeRatioCrossFONLLsystMB = (TGraphAsymmErrors*)filePPMB->Get("gaeRatioCrossFONLLsyst");
  TGraphAsymmErrors* gaeCrossSystMB = (TGraphAsymmErrors*)filePPMB->Get("gaeCrossSyst");
  TGraphAsymmErrors* gaeBplusReferenceMB = (TGraphAsymmErrors*)filePPMB->Get("gaeSigmaDzero");
  TGraphAsymmErrors* gaeRatioCrossFONLLunityMB = (TGraphAsymmErrors*)filePPMB->Get("gaeRatioCrossFONLLunity");
  TH1D* hSigmaPPStatMB = (TH1D*)filePPMB->Get("hPtSigma");

  TFile* filePP = new TFile(file.Data());  
  TGraphAsymmErrors* gaeRatioCrossFONLLstat = (TGraphAsymmErrors*)filePP->Get("gaeRatioCrossFONLLstat");
  TGraphAsymmErrors* gaeRatioCrossFONLLsyst = (TGraphAsymmErrors*)filePP->Get("gaeRatioCrossFONLLsyst");
  TGraphAsymmErrors* gaeCrossSyst = (TGraphAsymmErrors*)filePP->Get("gaeCrossSyst");
  TGraphAsymmErrors* gaeBplusReference = (TGraphAsymmErrors*)filePP->Get("gaeSigmaDzero");
  TGraphAsymmErrors* gaeRatioCrossFONLLunity = (TGraphAsymmErrors*)filePP->Get("gaeRatioCrossFONLLunity");
  TH1D* hSigmaPPStat = (TH1D*)filePP->Get("hPtSigma");

  TCanvas* cSigma = new TCanvas("cSigma","",600,600);
  gPad->SetLogy();
  cSigma->SetFrameBorderMode(0);
  cSigma->SetFrameBorderMode(0);
  cSigma->Range(-1.989924,-0.2917772,25.49622,2.212202);
  cSigma->SetFillColor(0);
  cSigma->SetBorderMode(0);
  cSigma->SetBorderSize(2);
  cSigma->SetLeftMargin(0.145);//0.1451613
  cSigma->SetRightMargin(0.025);//0.05443548
  cSigma->SetTopMargin(0.080);//0.08474576
  cSigma->SetBottomMargin(0.130);//0.1165254
  cSigma->SetFrameBorderMode(0);
  cSigma->SetFrameBorderMode(0);
  cSigma->SetLogx();
  cSigma->cd();

  TH2F* hemptySigma=new TH2F("hemptySigma","",50,0.,110.,10.,1e4,1.e15);  
  hemptySigma->GetXaxis()->CenterTitle();
  hemptySigma->GetYaxis()->CenterTitle();
  //hemptySigma->GetYaxis()->SetTitle("d#sigma / dp_{T}( pb GeV^{-1}c)");
  //hemptySigma->GetYaxis()->SetTitle("1/T_{AA} 1/N_{events} dN / dp_{T}( pb GeV^{-1}c)");
  hemptySigma->GetYaxis()->SetTitle("1/T_{AA} dN / dp_{T}( pb GeV^{-1}c)");
  hemptySigma->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptySigma->GetXaxis()->SetTitleOffset(1.2);
  hemptySigma->GetYaxis()->SetTitleOffset(1.35);//1.3
  hemptySigma->GetXaxis()->SetTitleSize(0.050);//0.045
  hemptySigma->GetYaxis()->SetTitleSize(0.050);//0.045
  hemptySigma->GetXaxis()->SetTitleFont(42);
  hemptySigma->GetYaxis()->SetTitleFont(42);
  hemptySigma->GetXaxis()->SetLabelFont(42);
  hemptySigma->GetYaxis()->SetLabelFont(42);
  hemptySigma->GetXaxis()->SetLabelSize(0.040);//0.04
  hemptySigma->GetYaxis()->SetLabelSize(0.040);//0.04  
  hemptySigma->SetMaximum(2);
  hemptySigma->SetMinimum(0.);
  hemptySigma->Draw();

  hSigmaPPStatMB->SetLineWidth(2);
  hSigmaPPStatMB->SetMarkerSize(1);//4
  hSigmaPPStatMB->SetMarkerStyle(20);
  if (isMerged) {
		hSigmaPPStatMB->SetLineColor(kTeal+4);//kGreen+4
		hSigmaPPStatMB->SetMarkerColor(kTeal+4);//kGreen+4
  }
  else {
		hSigmaPPStatMB->SetLineColor(kTeal+4);//kGreen+4
		hSigmaPPStatMB->SetMarkerColor(kTeal+4);//kGreen+4
  }
  hSigmaPPStatMB->Draw("epsame"); 

  hSigmaPPStat->SetLineWidth(2);
  hSigmaPPStat->SetMarkerSize(1);//4
  hSigmaPPStat->SetMarkerStyle(20);
  if (isMerged) {
		hSigmaPPStat->SetLineColor(kTeal+4);//kGreen+4
		hSigmaPPStat->SetMarkerColor(kTeal+4);//kGreen+4
  }
  else {
		hSigmaPPStat->SetLineColor(kAzure+1);//4
		hSigmaPPStat->SetMarkerColor(kAzure+1);//4
  }
  hSigmaPPStat->Draw("epsame"); 

  gaeCrossSystMB->SetFillColor(1);
  gaeCrossSystMB->SetFillStyle(0); 
  gaeCrossSystMB->SetLineWidth(2);
  if (isMerged) gaeCrossSystMB->SetLineColor(kTeal+4);//kGreen+4
  else gaeCrossSystMB->SetLineColor(kTeal+4);
  gaeCrossSystMB->Draw("5same");  

  gaeCrossSyst->SetFillColor(1);//4
  gaeCrossSyst->SetFillStyle(0); 
  gaeCrossSyst->SetLineWidth(2);
  if (isMerged) gaeCrossSyst->SetLineColor(kTeal+4);//kGreen+4
  else gaeCrossSyst->SetLineColor(kAzure+1);//4
  gaeCrossSyst->Draw("5same");  

  //TLegend *legendSigma=new TLegend(0.5100806,0.5868644,0.8084677,0.7605932,"");
  TLegend *legendSigma=new TLegend(0.60,0.65,0.90,0.80,"");
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);
  
  TLegendEntry *ent_SigmaPPMB=legendSigma->AddEntry(hSigmaPPStatMB,"PbPb MB","pf");
  ent_SigmaPPMB->SetTextFont(42);
  ent_SigmaPPMB->SetLineColor(2);
  ent_SigmaPPMB->SetMarkerColor(2);
  
  TLegendEntry *ent_SigmaPP=legendSigma->AddEntry(hSigmaPPStat,"PbPb triggered","pf");
  ent_SigmaPP->SetTextFont(42);
  ent_SigmaPP->SetLineColor(1);
  ent_SigmaPP->SetMarkerColor(1);
  if (!isMerged) legendSigma->Draw();
/*      
  TLatex * tlatex1=new TLatex(0.1612903,0.8625793,"CMS Preliminary     PbPb #sqrt{s_{NN}}= 5.02 TeV");
  tlatex1->SetNDC();
  tlatex1->SetTextColor(1);
  tlatex1->SetTextFont(42);
  tlatex1->SetTextSize(0.045);
  tlatex1->Draw();

  TLatex * tlatex1=new TLatex(0.55,0.94,"25.8 pb^{-1} (5.02 TeV pp)");
  tlatex1->SetNDC();
  tlatex1->SetTextColor(1);
  tlatex1->SetTextFont(42);
  tlatex1->SetTextSize(0.045);
  tlatex1->Draw();
*/

  TLatex * tlatex1=new TLatex(0.50,0.94,"404 #mub^{-1} (5.02 TeV PbPb)");
  tlatex1->SetNDC();
  tlatex1->SetTextColor(1);
  tlatex1->SetTextFont(42);
  tlatex1->SetTextSize(0.045);
  tlatex1->Draw();

  TLatex* texcms = new TLatex(0.18,0.90,"CMS");
  texcms->SetNDC();
  texcms->SetTextAlign(13);
  texcms->SetTextFont(62);//61
  texcms->SetTextSize(0.06);
  texcms->SetLineWidth(2);
  texcms->Draw();
  TLatex* texpre = new TLatex(0.18,0.84,"Preliminary");
  texpre->SetNDC();
  texpre->SetTextAlign(13);
  texpre->SetTextFont(52);
  texpre->SetTextSize(0.04);
  texpre->SetLineWidth(2);
  texpre->Draw();

  TLatex * tlatexeff2=new TLatex(0.18,0.18,"Centrality 0-100%");//0.65,0.20
  tlatexeff2->SetNDC();
  tlatexeff2->SetTextColor(1);
  tlatexeff2->SetTextFont(42);
  tlatexeff2->SetTextSize(0.04);
  tlatexeff2->SetLineWidth(2);
  tlatexeff2->Draw();

  cSigma->SaveAs("CrossSectionComparisonPbPb.pdf");
  cSigma->SaveAs("CrossSectionComparisonPbPb.png");
  }

int main(int argc, char *argv[])
{
  if((argc != 4))
  {
    std::cout << "Wrong number of inputs" << std::endl;
    return 1;
  }

  if(argc ==4)
    CombinePbPbYield(argv[1], argv[2], argv[3]);
  return 0;
}

