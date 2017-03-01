#include "uti.h"
#include "bFeedDown/bFeedDownCorrection.C"


void studyBfeed(bool isPP=false)
{
  
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  const int nFiles=2;

    
  TString mynamefilesEffP[nFiles];
  TString mynamefilesEffNP[nFiles];
  TString mynamefilesFONLLP[nFiles];
  TString mynamefilesFONLLNP[nFiles];
  
  
  if(isPP){
  mynamefilesEffP[0] ="ROOTfiles/MCstudiesPPMB.root";
  mynamefilesEffNP[0] ="ROOTfiles/MCstudiesNPPPMB.root";
  mynamefilesFONLLP[0] ="ROOTfiles/output_pp_d0meson_5TeV_y1MB.root";
  mynamefilesFONLLNP[0] ="ROOTfiles/output_pp_Btod0meson_5TeV_y1MB.root";

  mynamefilesEffP[1] ="ROOTfiles/MCstudiesPP.root";
  mynamefilesEffNP[1] ="ROOTfiles/MCstudiesNPPP.root";
  mynamefilesFONLLP[1] ="ROOTfiles/output_pp_d0meson_5TeV_y1.root";
  mynamefilesFONLLNP[1] ="ROOTfiles/output_pp_Btod0meson_5TeV_y1.root";
  }

  else{

  mynamefilesEffP[0] ="ROOTfiles/MCstudiesPbPbMB.root";
  mynamefilesEffNP[0] ="ROOTfiles/MCstudiesNPPbPbMB.root";
  mynamefilesFONLLP[0] ="ROOTfiles/output_pp_d0meson_5TeV_y1MB.root";
  mynamefilesFONLLNP[0] ="ROOTfiles/output_pp_Btod0meson_5TeV_y1MB.root";

  mynamefilesEffP[1] ="ROOTfiles/MCstudiesPbPb.root";
  mynamefilesEffNP[1] ="ROOTfiles/MCstudiesNPPbPb.root";
  mynamefilesFONLLP[1] ="ROOTfiles/output_pp_d0meson_5TeV_y1.root";
  mynamefilesFONLLNP[1] ="ROOTfiles/output_pp_Btod0meson_5TeV_y1.root";
  }

  
  TFile*fDCA=new TFile("../BtoDPackage/PbPb/bFeedDownResult.root");
  TGraphAsymmErrors* gDCA=(TGraphAsymmErrors*)fDCA->Get("grPromptFraction");
  
  TFile*fDecay=new TFile("bFeedDown/fpromptFractionDecay.root");
  TGraphAsymmErrors* gDecay=(TGraphAsymmErrors*)fDecay->Get("gPfrac_PbPb");

  TFile* filesEffP[nFiles];
  TFile* filesEffNP[nFiles];
  TFile* filesFONLLP[nFiles];
  TFile* filesFONLLNP[nFiles];
  
  TH1D* hEffP[nFiles];
  TH1D* hEffNP[nFiles];
  TGraphAsymmErrors* gFONLLP[nFiles];
  TGraphAsymmErrors* gFONLLNP[nFiles];
  TGraphAsymmErrors* correctedFONLLP[nFiles];
  TGraphAsymmErrors* correctedFONLLNP[nFiles];
  TGraphAsymmErrors* gratio[nFiles];

  for (int ifile=0;ifile<nFiles;ifile++){
  
     filesEffP[ifile]=new TFile(mynamefilesEffP[ifile].Data());  
     filesEffNP[ifile]=new TFile(mynamefilesEffNP[ifile].Data());  
     filesFONLLP[ifile]=new TFile(mynamefilesFONLLP[ifile].Data());  
     filesFONLLNP[ifile]=new TFile(mynamefilesFONLLNP[ifile].Data());  

    hEffP[ifile] = (TH1D*)filesEffP[ifile]->Get("hEff");
    hEffNP[ifile] = (TH1D*)filesEffNP[ifile]->Get("hEff");
    gFONLLP[ifile] = (TGraphAsymmErrors*)filesFONLLP[ifile]->Get("gaeSigmaDzero");
    gFONLLNP[ifile] = (TGraphAsymmErrors*)filesFONLLNP[ifile]->Get("gaeSigmaDzero");  
  }
  

  for (int ifile=0;ifile<nFiles;ifile++){
    correctedFONLLP[ifile]=(TGraphAsymmErrors*)gFONLLP[ifile]->Clone(Form("correctedFONLLP_%d",ifile));    
    correctedFONLLNP[ifile]=(TGraphAsymmErrors*)gFONLLNP[ifile]->Clone(Form("correctedFONLLNP_%d",ifile));    
    gratio[ifile]=(TGraphAsymmErrors*)gFONLLP[ifile]->Clone("gratio");    

    for (int ibin=0;ibin<correctedFONLLP[ifile]->GetN();ibin++){
    double x,yP,yNP;
    double yerrlowP,yerrhighP;
    double yerrlowNP,yerrhighNP;
    
    double effP=hEffP[ifile]->GetBinContent(ibin+1);
    double effNP=hEffNP[ifile]->GetBinContent(ibin+1);
    
    correctedFONLLP[ifile]->GetPoint(ibin,x,yP);
    correctedFONLLNP[ifile]->GetPoint(ibin,x,yNP);

    yerrlowP=correctedFONLLP[ifile]->GetErrorYlow(ibin);
    yerrhighP=correctedFONLLP[ifile]->GetErrorYhigh(ibin);
    yerrlowNP=correctedFONLLNP[ifile]->GetErrorYlow(ibin);
    yerrhighNP=correctedFONLLNP[ifile]->GetErrorYhigh(ibin);    

    correctedFONLLP[ifile]->SetPoint(ibin,x,yP*effP);
    correctedFONLLNP[ifile]->SetPoint(ibin,x,yNP*effP);
    correctedFONLLP[ifile]->SetPointEYlow(ibin,yerrlowP*effP);
    correctedFONLLP[ifile]->SetPointEYhigh(ibin,yerrhighP*effP);
    
   // cout<<"yP="<<yP<<endl;
   // cout<<"yNP="<<yNP<<endl;
   // cout<<"effP="<<effP<<endl;
   // cout<<"effNP="<<effNP<<endl;
    
    gratio[ifile]->SetPoint(ibin,x,yP*effP/(yNP*effNP+yP*effP));
    gratio[ifile]->SetPointEYlow(ibin,0.);
    gratio[ifile]->SetPointEYhigh(ibin,0.);
    
    if (!isPP) cout<<"PbPb"<<endl;
    if (isPP) cout<<"PP"<<endl;
    cout<<"xvalue="<<x<<", fprompt="<<yP*effP/(yNP*effNP+yP*effP)<<endl;
   }
}
   
  TCanvas* canvas = new TCanvas("canvas","",600,600);

  TH2F* hempty=new TH2F("hempty","",50,0.,100.,10,0,1.2);  
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetYaxis()->SetTitle("f_{prompt estimation}");
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
  
      gratio[ifile]  ->SetLineColor(1);
      gratio[ifile]  ->SetMarkerColor(1);
      gratio[ifile]  ->SetFillStyle(0);
      gratio[ifile]  ->Draw("psame");  
  }
      gDCA  ->SetLineColor(4);
      gDCA  ->SetLineWidth(2);
      gDCA  ->SetMarkerColor(4);
      gDCA  ->SetFillStyle(0);
      gDCA  ->Draw("psame");  
      gDecay  ->SetLineColor(6);
      gDCA  ->SetLineWidth(2);
      gDecay  ->SetMarkerColor(6);
      gDecay  ->SetFillStyle(0);
      gDecay  ->Draw("psame");  
      
      double x3,y3;
      double x4,y4;
      gDCA  ->GetPoint(3,x3,y3);
      gDCA  ->GetPoint(4,x4,y4);
      gDCA  ->SetPoint(4,x4,y3);
      
  TLegend *legend=new TLegend(0.2332215,0.2814685,0.5620805,0.4020979,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legend->SetBorderSize(0);
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->SetTextFont(42);
  legend->SetTextSize(0.04);

  entry=legend->AddEntry(gratio[0],"FONLL prompt fraction","f");
  entry->SetTextFont(42);
  entry->SetLineColor(1);
  entry->SetMarkerColor(1);
  entry=legend->AddEntry(gDecay,"Decay length data driven fraction","f");
  entry->SetTextFont(42);
  entry->SetLineColor(2);
  entry->SetMarkerColor(2);  
  legend->Draw();
  entry=legend->AddEntry(gDCA,"DCA data driven fraction","f");
  entry->SetTextFont(42);
  entry->SetLineColor(2);
  entry->SetMarkerColor(2);  
  legend->Draw();
  
  if(isPP) canvas->SaveAs("canvasNPfractionPP.pdf");
  else canvas->SaveAs("canvasNPfractionPbPb.pdf");

}
