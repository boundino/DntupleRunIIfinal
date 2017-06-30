using namespace std;
#include "uti.h"
#include "parameters.h"
#include "fitDdraw.h"

void fitDfithist(TString input, TString output, TString collsyst, Float_t centmin=0., Float_t centmax=0.)
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  collisionsystem = collsyst;
  Bool_t isPbPb = (collsyst=="PP" || collsyst=="PPMB")?false:true;

  TString infname = Form("%s.root",input.Data());
  TFile* inf = new TFile(infname.Data());
  TH1D* hPtMCtruth = new TH1D("hPtMCtruth","",nBins,ptBins);
  TH1D* hPtMCclosure = new TH1D("hPtMCclosure","",nBins,ptBins);
  TH1D* hPtMCclosure_3gaus = new TH1D("hPtMCclosure_3gaus","",nBins,ptBins);

  TH1D* hPt = new TH1D("hPt","",nBins,ptBins);
  TH1D* hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  TH1D* hPtMCSignal = new TH1D("hPtMCSignal","",nBins,ptBins);

  TH1D* hPt_3gaus = new TH1D("hPt_3gaus","",nBins,ptBins);
  TH1D* hPtMC_3gaus = new TH1D("hPtMC_3gaus","",nBins,ptBins);
  TH1D* hPtMCSignal_3gaus = new TH1D("hPtMCSignal_3gaus","",nBins,ptBins);

  TH1D* hPt_rela3gaus = new TH1D("hPt_rela3gaus","",nBins,ptBins);
  TH1D* hPtMC_rela3gaus = new TH1D("hPtMC_rela3gaus","",nBins,ptBins);
  TH1D* hPtMCSignal_rela3gaus = new TH1D("hPtMCSignal_rela3gaus","",nBins,ptBins);

  for(int i=0;i<nBins;i++)
    {
      TH1D* h = (TH1D*)inf->Get(Form("h_%d",i));
      TH1D* hMCSignal = (TH1D*)inf->Get(Form("hMCSignal_%d",i));
      TH1D* hMCSwapped = (TH1D*)inf->Get(Form("hMCSwapped_%d",i));
      TH1D* hMCSwappedNoswap = (TH1D*)inf->Get(Form("hMCSwappedNoswap_%d",i));
      TH1D* hMC = (TH1D*)inf->Get(Form("hMC_%d",i));

      TF1* f = fit(h,hMCSignal,hMCSwapped,ptBins[i],ptBins[i+1],isPbPb,i,"plotFits/DMass",centmin,centmax,"mass",true,false);
      hPt->SetBinContent(i+1,f->Integral(minhisto,maxhisto)/binwidthmass);
      hPt->SetBinError(i+1,f->Integral(minhisto,maxhisto)/binwidthmass*f->GetParError(0)/f->GetParameter(0));
      TF1* f_3gaus = fit3gaus(h,hMCSignal,hMCSwapped,ptBins[i],ptBins[i+1],isPbPb,i,"plotFits/DMass",centmin,centmax,"mass",true,false,false);
      hPt_3gaus->SetBinContent(i+1,f_3gaus->Integral(minhisto,maxhisto)/binwidthmass);
      hPt_3gaus->SetBinError(i+1,f_3gaus->Integral(minhisto,maxhisto)/binwidthmass*f_3gaus->GetParError(0)/f_3gaus->GetParameter(0));
      hPt_rela3gaus->Add(hPt_3gaus, hPt, 1, -1);
      hPt_rela3gaus->Divide(hPt);

      TF1* fMC = fit(hMC,hMCSignal,hMCSwapped,ptBins[i],ptBins[i+1],isPbPb,i,"plotFitsMC/DMass",centmin,centmax,"mass",true,false);
      hPtMC->SetBinContent(i+1,fMC->Integral(minhisto,maxhisto)/binwidthmass);
      hPtMC->SetBinError(i+1,fMC->Integral(minhisto,maxhisto)/binwidthmass*fMC->GetParError(0)/fMC->GetParameter(0));
      TF1* fMC_3gaus = fit3gaus(hMC,hMCSignal,hMCSwapped,ptBins[i],ptBins[i+1],isPbPb,i,"plotFitsMC/DMass",centmin,centmax,"mass",true,false,false);
      hPtMC_3gaus->SetBinContent(i+1,fMC_3gaus->Integral(minhisto,maxhisto)/binwidthmass);
      hPtMC_3gaus->SetBinError(i+1,fMC_3gaus->Integral(minhisto,maxhisto)/binwidthmass*fMC_3gaus->GetParError(0)/fMC_3gaus->GetParameter(0));
      hPtMC_rela3gaus->Add(hPtMC_3gaus, hPtMC, 1, -1);
      hPtMC_rela3gaus->Divide(hPtMC);

      TF1* fMCSignal = fit(hMCSignal,hMCSignal,hMCSwappedNoswap,ptBins[i],ptBins[i+1],isPbPb,i,"plotFitsMCSignal/DMass",centmin,centmax,"mass",true,false);
      hPtMCSignal->SetBinContent(i+1,fMCSignal->Integral(minhisto,maxhisto)/binwidthmass);
      hPtMCSignal->SetBinError(i+1,fMCSignal->Integral(minhisto,maxhisto)/binwidthmass*fMCSignal->GetParError(0)/fMCSignal->GetParameter(0));
      TF1* fMCSignal_3gaus = fit3gaus(hMCSignal,hMCSignal,hMCSwappedNoswap,ptBins[i],ptBins[i+1],isPbPb,i,"plotFitsMCSignal/DMass",centmin,centmax,"mass",true,false,false);
      hPtMCSignal_3gaus->SetBinContent(i+1,fMCSignal_3gaus->Integral(minhisto,maxhisto)/binwidthmass);
      hPtMCSignal_3gaus->SetBinError(i+1,fMCSignal_3gaus->Integral(minhisto,maxhisto)/binwidthmass*fMCSignal_3gaus->GetParError(0)/fMCSignal_3gaus->GetParameter(0));
      hPtMCSignal_rela3gaus->Add(hPtMCSignal_3gaus, hPtMCSignal, 1, -1);
      hPtMCSignal_rela3gaus->Divide(hPtMCSignal);

      hPtMCtruth->SetBinContent(i+1,hMCSignal->Integral());
      hPtMCclosure->Add(hPtMC, hPtMCtruth, 1, -1);
      hPtMCclosure->Divide(hPtMCtruth);
      hPtMCclosure_3gaus->Add(hPtMC_3gaus, hPtMCtruth, 1, -1);
      hPtMCclosure_3gaus->Divide(hPtMCtruth);

      delete fMCSignal_3gaus;
      delete fMCSignal;
      delete fMC_3gaus;
      delete fMC;
      delete f_3gaus;
      delete f;
      delete hMC;
      delete hMCSwapped;
      delete hMCSignal;
      delete h;
    }
  
  TFile* outf = new TFile(Form("%s.root",output.Data()),"recreate");
  outf->cd();
  hPtMCtruth->Write();
  hPtMCclosure->Write();
  hPtMCclosure_3gaus->Write();
  hPt->Write();
  hPtMC->Write();
  hPtMCSignal->Write();
  hPt_3gaus->Write();
  hPtMC_3gaus->Write();
  hPtMCSignal_3gaus->Write();
  hPt_rela3gaus->Write();
  hPtMC_rela3gaus->Write();
  hPtMCSignal_rela3gaus->Write();
  outf->Write();
  outf->Close();

}

int main(int argc, char *argv[])
{
  if(argc==6)
    {
      fitDfithist(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]));
      return 0;
    }
  else if(argc==4)
    {
      fitDfithist(argv[1], argv[2], argv[3]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs - fitDfithist" << std::endl;
      return 1;
    }
  
}
