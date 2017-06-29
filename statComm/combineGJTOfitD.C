using namespace std;
#include "uti.h"
#include "parameters.h"
#include "fitDdraw.h"

void combineGJTOfitD(TString inputGJ, TString inputTO, TString outputfilefitmass)
{
  TString infnameGJ = Form("%s.root",inputGJ.Data());
  TString infnameTO = Form("%s.root",inputTO.Data());
  TFile* fGJ = new TFile(infnameGJ.Data());
  TFile* fTO = new TFile(infnameTO.Data());

  TH1D** ah = new TH1D*[nBins];
  TH1D** ahMCSignal = new TH1D*[nBins];
  TH1D** ahMCSwapped = new TH1D*[nBins];
  TH1D** ahMC = new TH1D*[nBins];
  TH1D** ahMCNocomb = new TH1D*[nBins];
  TH1D** ahMCNoswap = new TH1D*[nBins];
  TH1D** ahMCSwappedNoswap = new TH1D*[nBins];

  TH1D** aGJh = new TH1D*[nBins];
  TH1D** aGJhMCSignal = new TH1D*[nBins];
  TH1D** aGJhMCSwapped = new TH1D*[nBins];
  TH1D** aGJhMC = new TH1D*[nBins];
  TH1D** aGJhMCNocomb = new TH1D*[nBins];
  TH1D** aGJhMCNoswap = new TH1D*[nBins];
  TH1D** aGJhMCSwappedNoswap = new TH1D*[nBins];

  TH1D** aTOh = new TH1D*[nBins];
  TH1D** aTOhMCSignal = new TH1D*[nBins];
  TH1D** aTOhMCSwapped = new TH1D*[nBins];
  TH1D** aTOhMC = new TH1D*[nBins];
  TH1D** aTOhMCNocomb = new TH1D*[nBins];
  TH1D** aTOhMCNoswap = new TH1D*[nBins];
  TH1D** aTOhMCSwappedNoswap = new TH1D*[nBins];

  for(int i=0;i<nBins;i++)
    {
      aGJh[i] = (TH1D*)fGJ->Get(Form("h_%d",i));
      aGJh[i]->SetName(Form("GJh_%d",i));
      aGJhMCSignal[i] = (TH1D*)fGJ->Get(Form("hMCSignal_%d",i));
      aGJhMCSignal[i]->SetName(Form("GJhMCSignal_%d",i));
      aGJhMCSwapped[i] = (TH1D*)fGJ->Get(Form("hMCSwapped_%d",i));
      aGJhMCSwapped[i]->SetName(Form("GJhMCSwapped_%d",i));
      aGJhMC[i] = (TH1D*)fGJ->Get(Form("hMC_%d",i));
      aGJhMC[i]->SetName(Form("GJhMC_%d",i)); 
      aGJhMCNocomb[i] = (TH1D*)fGJ->Get(Form("hMCNocomb_%d",i));
      aGJhMCNocomb[i]->SetName(Form("GJhMCNocomb_%d",i));
      aGJhMCNoswap[i] = (TH1D*)fGJ->Get(Form("hMCNoswap_%d",i));
      aGJhMCNoswap[i]->SetName(Form("GJhMCNoswap_%d",i));
      aGJhMCSwappedNoswap[i] = (TH1D*)fGJ->Get(Form("hMCSwappedNoswap_%d",i));
      aGJhMCSwappedNoswap[i]->SetName(Form("GJhMCSwappedNoswap_%d",i));

      aTOh[i] = (TH1D*)fTO->Get(Form("h_%d",i));
      aTOh[i]->SetName(Form("TOh_%d",i));
      aTOhMCSignal[i] = (TH1D*)fTO->Get(Form("hMCSignal_%d",i));
      aTOhMCSignal[i]->SetName(Form("TOhMCSignal_%d",i));
      aTOhMCSwapped[i] = (TH1D*)fTO->Get(Form("hMCSwapped_%d",i));
      aTOhMCSwapped[i]->SetName(Form("TOhMCSwapped_%d",i));
      aTOhMC[i] = (TH1D*)fTO->Get(Form("hMC_%d",i));
      aTOhMC[i]->SetName(Form("TOhMC_%d",i));
      aTOhMCNocomb[i] = (TH1D*)fTO->Get(Form("hMCNocomb_%d",i));
      aTOhMCNocomb[i]->SetName(Form("TOhMCNocomb_%d",i));
      aTOhMCNoswap[i] = (TH1D*)fTO->Get(Form("hMCNoswap_%d",i));
      aTOhMCNoswap[i]->SetName(Form("TOhMCNoswap_%d",i));
      aTOhMCSwappedNoswap[i] = (TH1D*)fTO->Get(Form("hMCSwappedNoswap_%d",i));
      aTOhMCSwappedNoswap[i]->SetName(Form("TOhMCSwappedNoswap_%d",i));

      ah[i] = (TH1D*)aGJh[i]->Clone(Form("h_%d",i));
      ah[i]->Add(aTOh[i]);
      ahMCSignal[i] = (TH1D*)aGJhMCSignal[i]->Clone(Form("hMCSignal_%d",i));
      ahMCSignal[i]->Add(aTOhMCSignal[i]);
      ahMCSwapped[i] = (TH1D*)aGJhMCSwapped[i]->Clone(Form("hMCSwapped_%d",i));
      ahMCSwapped[i]->Add(aTOhMCSwapped[i]);
      ahMC[i] = (TH1D*)aGJhMC[i]->Clone(Form("hMC_%d",i));
      ahMC[i]->Add(aTOhMC[i]);
      ahMCNocomb[i] = (TH1D*)aGJhMCNocomb[i]->Clone(Form("hMCNocomb_%d",i));
      ahMCNocomb[i]->Add(aTOhMCNocomb[i]);
      ahMCNoswap[i] = (TH1D*)aGJhMCNoswap[i]->Clone(Form("hMCNoswap_%d",i));
      ahMCNoswap[i]->Add(aTOhMCNoswap[i]);
      ahMCSwappedNoswap[i] = (TH1D*)aGJhMCSwappedNoswap[i]->Clone(Form("hMCSwappedNoswap_%d",i));
      ahMCSwappedNoswap[i]->Add(aTOhMCSwappedNoswap[i]);
    }  

  //
  TString outputname = Form("%s.root",outputfilefitmass.Data());
  TFile* outputfitmass = new TFile(outputname,"recreate");
  for(int i=0;i<nBins;i++)
    {
      ah[i]->Write();
      ahMCSignal[i]->Write();
      ahMCSwapped[i]->Write();
      ahMC[i]->Write();
      ahMCNocomb[i]->Write();
      ahMCNoswap[i]->Write();
      ahMCSwappedNoswap[i]->Write();
    }
  outputfitmass->Close();

}

int main(int argc, char *argv[])
{
  if(argc==4)
    {
      combineGJTOfitD(argv[1], argv[2], argv[3]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
  
}
