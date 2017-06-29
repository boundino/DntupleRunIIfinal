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
  TH1D* hPt = new TH1D("hPt","",nBins,ptBins);
  TH1D* hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  TH1D* hPtMCNoswap = new TH1D("hPtMCNoswap","",nBins,ptBins);
  TH1D* hPtMCNocomb = new TH1D("hPtMCNocomb","",nBins,ptBins);
  TH1D* hPtMCNocombNoswap = new TH1D("hPtMCNocombNoswap","",nBins,ptBins);

  for(int i=0;i<nBins;i++)
    {
      TH1D* h = (TH1D*)inf->Get(Form("h_%d",i));
      TH1D* hMCSignal = (TH1D*)inf->Get(Form("hMCSignal_%d",i));
      TH1D* hMCSwapped = (TH1D*)inf->Get(Form("hMCSwapped_%d",i));
      TF1* f = fit(h,hMCSignal,hMCSwapped,ptBins[i],ptBins[i+1],isPbPb,i,"plotFits/DMass",centmin,centmax);
      hPt->SetBinContent(i+1,f->Integral(minhisto,maxhisto)/binwidthmass);
      hPt->SetBinError(i+1,f->Integral(minhisto,maxhisto)/binwidthmass*f->GetParError(0)/f->GetParameter(0));
      TH1D* hMC = (TH1D*)inf->Get(Form("hMC_%d",i));
      TF1* fMC = fit(hMC,hMCSignal,hMCSwapped,ptBins[i],ptBins[i+1],isPbPb,i,"plotFitsMC/DMass",centmin,centmax);
      hPtMC->SetBinContent(i+1,fMC->Integral(minhisto,maxhisto)/binwidthmass);
      hPtMC->SetBinError(i+1,fMC->Integral(minhisto,maxhisto)/binwidthmass*fMC->GetParError(0)/fMC->GetParameter(0));
      TH1D* hMCNoswap = (TH1D*)inf->Get(Form("hMCNoswap_%d",i));
      TH1D* hMCSwappedNoswap = (TH1D*)inf->Get(Form("hMCSwappedNoswap_%d",i));
      TF1* fMCNoswap = fit(hMCNoswap,hMCSignal,hMCSwappedNoswap,ptBins[i],ptBins[i+1],isPbPb,i,"plotFitsMCNoswap/DMass",centmin,centmax);
      hPtMCNoswap->SetBinContent(i+1,fMCNoswap->Integral(minhisto,maxhisto)/binwidthmass);
      hPtMCNoswap->SetBinError(i+1,fMCNoswap->Integral(minhisto,maxhisto)/binwidthmass*fMCNoswap->GetParError(0)/fMCNoswap->GetParameter(0));
      TH1D* hMCNocomb = (TH1D*)inf->Get(Form("hMCNocomb_%d",i));
      TF1* fMCNocomb = fit(hMCNocomb,hMCSignal,hMCSwapped,ptBins[i],ptBins[i+1],isPbPb,i,"plotFitsMCNocomb/DMass",centmin,centmax);
      hPtMCNocomb->SetBinContent(i+1,fMCNocomb->Integral(minhisto,maxhisto)/binwidthmass);
      hPtMCNocomb->SetBinError(i+1,fMCNocomb->Integral(minhisto,maxhisto)/binwidthmass*fMCNocomb->GetParError(0)/fMCNocomb->GetParameter(0));
      TF1* fMCNocombNoswap = fit(hMCSignal,hMCSignal,hMCSwappedNoswap,ptBins[i],ptBins[i+1],isPbPb,i,"plotFitsMCNocombNoswap/DMass",centmin,centmax);
      hPtMCNocombNoswap->SetBinContent(i+1,fMCNocombNoswap->Integral(minhisto,maxhisto)/binwidthmass);
      hPtMCNocombNoswap->SetBinError(i+1,fMCNocombNoswap->Integral(minhisto,maxhisto)/binwidthmass*fMCNocombNoswap->GetParError(0)/fMCNocombNoswap->GetParameter(0));

      delete h;
      delete hMCSignal;
      delete hMCSwapped;
      delete hMC;
      delete hMCNoswap;
      delete hMCSwappedNoswap;
      delete hMCNocomb;
      delete f;      
      delete fMC;
      delete fMCNoswap;
      delete fMCNocomb;
      delete fMCNocombNoswap;
    }
  
  TFile* outf = new TFile(Form("%s.root",output.Data()),"recreate");
  outf->cd();
  hPt->Write();
  hPtMC->Write();
  hPtMCNoswap->Write();
  hPtMCNocomb->Write();
  hPtMCNocombNoswap->Write();
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
