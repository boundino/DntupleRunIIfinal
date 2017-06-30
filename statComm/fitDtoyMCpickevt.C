using namespace std;
#include "uti.h"
#include "parameters.h"
#include "fitDdraw.h"
#include "fitDtoyMC.h"

Int_t Nsmear = 100;
Int_t Ngen = 1000;

void fitDtoyMCpickevt(TString inputMC, TString inputEff, TString output, TString collsyst, Float_t centmin=0., Float_t centmax=0.)
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
  Int_t Nsmearshow = Nsmear/10;
  Float_t NgenErr = TMath::Sqrt(Ngen);

  TFile* infEff = new TFile(Form("%s.root",inputEff.Data()));
  TH1D* hPtMCEff = (TH1D*)infEff->Get("hPtMCEff");

  TFile* infMC = new TFile(inputMC.Data());
  TTree* ntDkpi = (TTree*)infMC->Get("ntDkpi");
  setDbranchaddress(ntDkpi);
  TTree* ntGen = (TTree*)infMC->Get("ntGen");
  setGenbranchaddress(ntGen);
  TTree* ntHi = (TTree*)infMC->Get("ntHi");
  setHibranchaddress(ntHi);
  TTree* ntSkim = (TTree*)infMC->Get("ntSkim");
  setSkimbranchaddress(ntSkim);

  TH1D** ahSmear = new TH1D*[nBins];
  Int_t nentries = ntDkpi->GetEntries();

  for(int i=0;i<nBins;i++)
    {
      cout<<endl<<" -- Processing ptbin: "<<ptBins[i]<<" - "<<ptBins[i+1]<<" GeV/c"<<endl;
      Int_t Nmatched = Ngen*hPtMCEff->GetBinContent(i+1);
      ahSmear[i] = new TH1D(Form("hSmear_%d",i),";(#fit-#gen-matched)/#sigma(fit);counts",100,-3,6);
      setth1d(ahSmear[i]);
      ahSmear[i]->GetXaxis()->SetNdivisions(-50205);
      ahSmear[i]->SetMarkerStyle(20);
      ahSmear[i]->SetMarkerSize(1.3);
      ahSmear[i]->SetMarkerColor(kBlack);
      ahSmear[i]->SetLineColor(kBlack);
      ahSmear[i]->SetStats(0);

      for(int n=0;n<Nsmear;n++)
        {
          cout<<left<<"\033[0;36m >> Processing "<<setw(7)<<Form("\033[1;33m%d",n)<<" \033[0;36mth smearing \033[0m"<<endl;
          //if(n%Nsmearshow==0) cout<<left<<"\033[0;36m >> Processing "<<setw(7)<<Form("\033[1;33m%d",n)<<" \033[0;36mth smearing"<<endl;

          TH1D* hMCsmear = new TH1D("hMCsmear", "",nbinsmasshisto,minhisto,maxhisto);
          TH1D* hMCSignalsmear = new TH1D("hMCSignalsmear", "",nbinsmasshisto,minhisto,maxhisto);
          TH1D* hMCSwappedsmear = new TH1D("hMCSwappedsmear", "",nbinsmasshisto,minhisto,maxhisto);

          Int_t Ngensmear = gRandom->Gaus(Ngen, NgenErr);
          Int_t ctgen = 0;
          while(ctgen<Ngensmear)
            {
              Int_t ievt = gRandom->Uniform(0, nentries-1);

              ntSkim->GetEntry(ievt);
              if(!((!isPbPb && pBeamScrapingFilter && pPAprimaryVertexFilter) ||
                   (isPbPb && pclusterCompatibilityFilter && pprimaryVertexFilter && phfCoincFilter3))) continue;

              ntHi->GetEntry(ievt);
              if(isPbPb && (hiBin<centmin*2 || hiBin>centmax*2)) continue;

              ntGen->GetEntry(ievt);
              for(int j=0;j<Gsize;j++)
                {
                  if((GisSignal[j]==1 || GisSignal[j]==2) && 
                     TMath::Abs(Gy[j])<1 && Gpt[j]>ptBins[i] && Gpt[j]<ptBins[i+1]) 
                    {
                      if(ctgen%(Ngen/10)==0) cout<<"    Find "<<(ctgen+1)<<" gen D(s)"<<endl;
                      ctgen++;
                    }
                }
              
              ntDkpi->GetEntry(ievt);
              for(int j=0;j<Dsize;j++)
                {
                  if(!pass_selections(j) || 
                     Dpt[j]<ptBins[i] || Dpt[j]>ptBins[i+1]) continue;
                  hMCsmear->Fill(Dmass[j]);
                  if(Dgen[j]==23333) hMCSignalsmear->Fill(Dmass[j]);
                  if(Dgen[j]==23344) hMCSwappedsmear->Fill(Dmass[j]);
                }
            }
          
          Bool_t ifsaveplot = n%Nsmearshow==0?true:false;
          TF1* fMCSignalsmear = fit(hMCsmear, hMCSignalsmear, hMCSwappedsmear, ptBins[i], ptBins[i+1], isPbPb, (i+1)*Nsmear*10+n, "plotToyMCpickevt/DMass_MCsmear", centmin, centmax, "mass", ifsaveplot, false);
          Float_t Yield = fMCSignalsmear->Integral(minhisto,maxhisto)/binwidthmass;
          Float_t YieldErr = fMCSignalsmear->Integral(minhisto,maxhisto)/binwidthmass*fMCSignalsmear->GetParError(0)/fMCSignalsmear->GetParameter(0);
          ahSmear[i]->Fill((Yield-Nmatched)/YieldErr);
          if(n%Nsmearshow==0) cout<<"\033[0m     "<<Ngensmear*hPtMCEff->GetBinContent(i+1)<<"  "<<hMCSignalsmear->Integral()<<"  "<<Yield<<endl;

          delete hMCSwappedsmear;
          delete hMCSignalsmear;
          delete hMCsmear;
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
      TString csmearname = isPbPb?Form("plotToyMCpickevt/csmear_%s_%.0f_%.0f_%d",collisionsystem.Data(),centmin,centmax,i):Form("plotToyMCpickevt/csmear_%s_%d",collisionsystem.Data(),i+1);
      csmear->SaveAs(Form("%s.pdf",csmearname.Data()));

    }

  TFile* outf = new TFile(Form("%s.root",output.Data()),"recreate");
  outf->cd();
  for(int i=0;i<nBins;i++) ahSmear[i]->Write();
  outf->Write();
  outf->Close();

}

int main(int argc, char *argv[])
{
  if(argc==7)
    {
      fitDtoyMCpickevt(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]));
      return 0;
    }
  else if(argc==5)
    {
      fitDtoyMCpickevt(argv[1], argv[2], argv[3], argv[4]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs - fitDtoyMCpickevt" << std::endl;
      return 1;
    }  
}
