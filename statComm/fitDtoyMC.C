using namespace std;
#include "uti.h"
#include "parameters.h"
#include "fitDdraw.h"

void fitDtoyMC(TString input, TString output, TString collsyst, Float_t centmin=0., Float_t centmax=0.)
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
  TH1D** ahSmear = new TH1D*[nBins];
  TH1D* hWidthRatio = new TH1D("hWidthRatio","",nBins,ptBins);

  for(int i=0;i<nBins;i++)
    {
      TH1D* hMC = (TH1D*)inf->Get(Form("hMC_%d",i));
      TH1D* hMCSignal = (TH1D*)inf->Get(Form("hMCSignal_%d",i));
      TH1D* hMCSwapped = (TH1D*)inf->Get(Form("hMCSwapped_%d",i));
      TH1D* hMCBackground = new TH1D(Form("hMCBackground_%d",i),"",nbinsmasshisto,minhisto,maxhisto);
      hMCBackground->Add(hMC,hMCSignal,1,-1);
      hMCBackground->Add(hMCBackground,hMCSwapped,1,-1);
      TF1* fMCSignal = fit(hMC, hMCSignal, hMCSwapped, ptBins[i], ptBins[i+1], isPbPb, i+1, "plotToyMC/DMass_MCSignal", centmin, centmax);
      fMCSignal->SetName("fMCSignal");
      TF1* fMCSwapped = fit(hMC, hMCSignal, hMCSwapped, ptBins[i], ptBins[i+1], isPbPb, i+1, "", centmin, centmax, "massSwap", false, false);
      fMCSwapped->SetName("fMCSwapped");
      Int_t Nmatched = hMCSignal->Integral();
      Int_t Nswapped = hMCSwapped->Integral();
      Int_t NmatchedErr = TMath::Sqrt(Nmatched);
      Int_t Nsmear = 1000;
      cout<<endl<<"  -- Processing pT bin "<<ptBins[i]<<" - "<<ptBins[i+1]<<" GeV/c"<<endl;
      cout<<"   - # gen-matched"<<endl;
      cout<<"     "<<Nmatched<<endl;
      ahSmear[i] = new TH1D(Form("hSmear_%d",i),";(#fit-#gen-matched)/#sigma(fit);counts",100,-3,6);
      setth1d(ahSmear[i]);
      ahSmear[i]->GetXaxis()->SetNdivisions(-50205);
      ahSmear[i]->SetMarkerStyle(20);
      ahSmear[i]->SetMarkerSize(1.3);
      ahSmear[i]->SetMarkerColor(kBlack);
      ahSmear[i]->SetLineColor(kBlack);
      ahSmear[i]->SetStats(0);
      for(int j=0;j<Nsmear;j++)
        {
          if(j%100==0) cout<<left<<"   - Processing "<<setw(5)<<j<<"th smear"<<endl;
          Int_t Nmatchedsmear = gRandom->Gaus(Nmatched, NmatchedErr);
          Int_t Nswappedsmear = Nmatchedsmear*1.0*Nswapped/Nmatched;
          TH1D* hMCSignalsmear = new TH1D("hMCSignalsmear", "",nbinsmasshisto,minhisto,maxhisto);
          hMCSignalsmear->FillRandom("fMCSignal", Nmatchedsmear);
          TH1D* hMCSwappedsmear = new TH1D("hMCSwappedsmear", "",nbinsmasshisto,minhisto,maxhisto);
          hMCSwappedsmear->FillRandom("fMCSwapped", Nswappedsmear);
          TH1D* hMCsmear = new TH1D("hMCsmear","",nbinsmasshisto,minhisto,maxhisto);
          hMCsmear->Add(hMCBackground,hMCSignalsmear,1,1);
          hMCsmear->Add(hMCsmear,hMCSwappedsmear,1,1);
          //Bool_t ifsaveplot = j%100==0?true:false;
          Bool_t ifsaveplot = false;
          TF1* fMCSignalsmear = fit(hMCsmear, hMCSignalsmear, hMCSwapped, ptBins[i], ptBins[i+1], isPbPb, (i+1)*10000+j, "plotToyMC/DMass_MCsmear", centmin, centmax, "mass", ifsaveplot, false);
          Float_t Yield = fMCSignalsmear->Integral(minhisto,maxhisto)/binwidthmass;
          Float_t YieldErr = fMCSignalsmear->Integral(minhisto,maxhisto)/binwidthmass*fMCSignalsmear->GetParError(0)/fMCSignalsmear->GetParameter(0);
          ahSmear[i]->Fill((Yield-Nmatched)/YieldErr);
          //ahSmear[i]->Fill((Yield-Nmatchedsmear)/YieldErr);
          if(j%100==0) cout<<"     "<<Nmatchedsmear<<"  "<<hMCSignalsmear->Integral()<<"  "<<Yield<<endl;

          delete fMCSignalsmear;
          delete hMCsmear;
          delete hMCSwappedsmear;
          delete hMCSignalsmear;
        }

      TCanvas* csmear = new TCanvas("csmear","",600,600);
      csmear->SetLogy();
      ahSmear[i]->Draw("pe");
      ahSmear[i]->Fit("gaus","q");
      TLatex* texGaussMean = new TLatex(0.70,0.86,Form("#mu: %.3f",ahSmear[i]->GetFunction("gaus")->GetParameter(1)));
      settex(texGaussMean,0.045);
      texGaussMean->Draw();      
      TLatex* texGaussSigma = new TLatex(0.70,0.80,Form("#sigma: %.3f",ahSmear[i]->GetFunction("gaus")->GetParameter(2)));
      settex(texGaussSigma,0.045);
      texGaussSigma->Draw();
      TString csmearname = isPbPb?Form("plotToyMC/csmear_%s_%.0f_%.0f_%d",collisionsystem.Data(),centmin,centmax,i):Form("plotToyMC/csmear_%s_%d",collisionsystem.Data(),i+1);
      csmear->SaveAs(Form("%s.pdf",csmearname.Data()));

      hWidthRatio->SetBinContent(i+1,ahSmear[i]->GetFunction("gaus")->GetParameter(2));      

      delete csmear;
      delete hMCSignal;
      delete hMCSwapped;
      delete hMC;
      delete fMCSignal;
      delete fMCSwapped;
    }

  TFile* outf = new TFile(Form("%s.root",output.Data()),"recreate");
  outf->cd();
  hWidthRatio->Write();
  for(int i=0;i<nBins;i++) ahSmear[i]->Write();
  outf->Write();
  outf->Close();

}

int main(int argc, char *argv[])
{
  if(argc==6)
    {
      fitDtoyMC(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]));
      return 0;
    }
  else if(argc==4)
    {
      fitDtoyMC(argv[1], argv[2], argv[3]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs - fitDtoyMC" << std::endl;
      return 1;
    }
  
}
