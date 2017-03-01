#include "uti.h"

void studySignalShape(bool isPP=false)
{
  
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  const int nHistos=4;
  const int nFiles=4;
  int colors[4]={1,1,2,2};
  
  TString myfiles[nFiles];
  
  if(isPP){
  myfiles[0] ="ROOTfiles/hPtSpectrumDzeroPP.root";
  myfiles[1] ="ROOTfiles/hPtSpectrumDzeroPPMB.root";
  myfiles[2] ="ROOTfiles/hPtSpectrumDzeroPPMCClosure.root";
  myfiles[3] ="ROOTfiles/hPtSpectrumDzeroPPMBMCClosure.root";
  }
  else{
  myfiles[0] ="ROOTfiles/hPtSpectrumDzeroPbPb.root";
  myfiles[1] ="ROOTfiles/hPtSpectrumDzeroPbPbMB.root";
  myfiles[2] ="ROOTfiles/hPtSpectrumDzeroPbPbMCClosure.root";
  myfiles[3] ="ROOTfiles/hPtSpectrumDzeroPbPbMBMCClosure.root";
  }
  
  double minhisto[nHistos] = { 1.86, 0,0,0};
  double maxhisto[nHistos] ={ 1.87, 0.04,0.3,1};
  double minxhisto=0.;
  double maxxhisto=100.;
  

  TString histofiles[nHistos] = { "hMean", "hSigmaGaus2","hSigmaGausRefl","hRelMagnReflOverSignal"};
  TString label[nHistos] = {"mean signal (GeV)", "dominant sigma width (GeV)", "width of swapped signal (GeV)","relative magnitude swapped/signal"};
  
  TH1D* hHistos[nHistos][nFiles];
  TH1D* hempty[nHistos];
  TFile* files[nFiles];
  

  for (int ifile=0;ifile<nFiles;ifile++){
    files[ifile]=new TFile(myfiles[ifile].Data());  
    for (int ihisto=0;ihisto<nHistos;ihisto++){
      hHistos[ihisto][ifile] = (TH1D*)files[ifile]->Get(histofiles[ihisto]);
    }
  }

  TCanvas* canvas = new TCanvas("canvas","",1000,600);
  canvas->Divide(2,2);
  gPad->SetLogx();

  for (int ihisto=0;ihisto<nHistos;ihisto++){
    canvas->cd(ihisto+1);
    gPad->SetLogx();
     hempty[ihisto]=new TH1D(Form("hempty_%d",ihisto),"",100,0,100);
     hempty[ihisto]  ->Draw();
    for (int ifile=0;ifile<2;ifile++){
      cout<<"ihisto="<<ihisto<<",ifile="<<ifile<<endl;
      hempty[ihisto]  ->SetLineWidth(3);
      hempty[ihisto]->GetYaxis()->CenterTitle();
      hempty[ihisto]->GetYaxis()->SetTitle(label[ihisto].Data());
      hempty[ihisto]->GetYaxis()->SetRangeUser(minhisto[ihisto],maxhisto[ihisto]);//1.
      hempty[ihisto]->GetXaxis()->SetRangeUser(-10,100);//1.
      hempty[ihisto]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
      hempty[ihisto]->GetXaxis()->SetTitleOffset(0.95);//0.9
      hempty[ihisto]->GetYaxis()->SetTitleOffset(1.25);//1.
      hempty[ihisto]->GetXaxis()->SetTitleSize(0.060);//0.045
      hempty[ihisto]->GetYaxis()->SetTitleSize(0.060);//0.045
      hempty[ihisto]->GetXaxis()->SetTitleFont(42);
      hempty[ihisto]->GetYaxis()->SetTitleFont(42);
      hempty[ihisto]->GetXaxis()->SetLabelFont(42);
      hempty[ihisto]->GetYaxis()->SetLabelFont(42);  
      hempty[ihisto]->GetXaxis()->SetLabelSize(0.050);//0.035
      hempty[ihisto]->GetYaxis()->SetLabelSize(0.050);//0.035  
      
      hHistos[ihisto][ifile]  ->SetLineColor(colors[ifile]);
      hHistos[ihisto][ifile]  ->SetMarkerColor(colors[ifile]);
      hHistos[ihisto][ifile]  ->Draw("psame");  
      if(ihisto>0){
      hHistos[ihisto][ifile]  ->SetMarkerSize(1);
      hHistos[ihisto][ifile]  ->SetMarkerStyle(22);
      }
      else{
       TLine* l = new TLine(0,1.865,100,1.865);
        l->SetLineWidth(1);
        l->SetLineStyle(2);
        l->Draw();
        TLine* llow = new TLine(0,1.860,100,1.860);
        llow->SetLineWidth(1);
        llow->SetLineStyle(2);
        llow->Draw();
        TLine* lup = new TLine(0,1.870,100,1.870);
        lup->SetLineWidth(1);
        lup->SetLineStyle(2);
        lup->Draw();
      }
      }
  }
  if(isPP) canvas->SaveAs("canvasSignalShapePP.pdf");
  else canvas->SaveAs("canvasSignalShapePbPb.pdf");

}
