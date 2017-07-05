using namespace std;
#include "uti.h"
#include "parameters.h"
#include "fitDdraw.h"
#include "fitDtoyMC.h"

void fitDtoyMCpickevt(TString inputMC, TString inputEff, TString output, TString collsyst, Float_t ptmin, Float_t ptmax, Int_t Nsmear=100, Int_t Ngen=1000, Float_t centmin=0., Float_t centmax=0., Bool_t ifplot=true)
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

  Int_t nentries = ntDkpi->GetEntries();

  cout<<endl<<" -- Processing ptbin: "<<ptmin<<" - "<<ptmax<<" GeV/c"<<endl;
  int i=0;
  for(i=0;i<nBins;i++)
    {
      if(ptmin>=ptBins[i] && ptmax<=ptBins[i+1]) break;
    }

  Int_t effGen=0, effSignal=0, nSignal=0;
  for(int k=0;k<nentries;k++)
    {
      Bool_t findgen = false;
      ntSkim->GetEntry(k);
      if((!isPbPb && pBeamScrapingFilter && pPAprimaryVertexFilter) ||
         (isPbPb && pclusterCompatibilityFilter && pprimaryVertexFilter && phfCoincFilter3))
        {
          ntHi->GetEntry(k);
          if(!isPbPb || (hiBin>=centmin*2 && hiBin<=centmax*2))
            {
              ntGen->GetEntry(k);
              for(int j=0;j<Gsize;j++)
                {
                  if((GisSignal[j]==1 || GisSignal[j]==2) && 
                     TMath::Abs(Gy[j])<1 && Gpt[j]>ptmin && Gpt[j]<ptmax) 
                    {
                      effGen++;
                      findgen = true;
                    }
                }                  
              if(findgen)
                {
                  ntDkpi->GetEntry(k);
                  for(int j=0;j<Dsize;j++)
                    {
                      if(!pass_selections(j) || 
                         Dpt[j]<ptmin || Dpt[j]>ptmax) continue;
                      if(Dgen[j]==23333) effSignal++;
                    }
                }
              
              ntDkpi->GetEntry(k);
              for(int j=0;j<Dsize;j++)
                {
                  if(!pass_selections(j) ||
                     Dpt[j]<ptmin || Dpt[j]>ptmax) continue;
                  if(Dgen[j]==23333) nSignal++;
                }
            }      
        }
    }
  Int_t NmatchedEff = Ngen*hPtMCEff->GetBinContent(i+1);
  Int_t Nmatched = Ngen*1.*nSignal/effGen;
  cout<<Ngen*hPtMCEff->GetBinContent(i+1)<<"  "<<Ngen*1.*effSignal/effGen<<"  "<<Ngen*1.*nSignal/effGen<<endl;

  TH1D* hSmear = new TH1D("hSmear",";(#fit-#gen-matched)/#sigma(fit);counts",100,-5,5);
  setth1d(hSmear);
  hSmear->GetXaxis()->SetNdivisions(-50205);
  hSmear->SetMarkerStyle(20);
  hSmear->SetMarkerSize(1.3);
  hSmear->SetMarkerColor(kBlack);
  hSmear->SetLineColor(kBlack);
  hSmear->SetStats(0);
  
  TH1D* hSmearTruth = new TH1D("hSmearTruth",";(#truth-#gen-matched)/#sigma(gen-matched);counts",100,-5,5);
  setth1d(hSmearTruth);
  hSmearTruth->GetXaxis()->SetNdivisions(-50205);
  hSmearTruth->SetMarkerStyle(20);
  hSmearTruth->SetMarkerSize(1.3);
  hSmearTruth->SetMarkerColor(kBlack);
  hSmearTruth->SetLineColor(kBlack);
  hSmearTruth->SetStats(0);
  
  TH1D* hGen = new TH1D("hGen",";#gen number variation;counts",100,-5,5);
  setth1d(hGen);
  hGen->GetXaxis()->SetNdivisions(-50205);
  hGen->SetMarkerStyle(20);
  hGen->SetMarkerSize(1.3);
  hGen->SetMarkerColor(kBlack);
  hGen->SetLineColor(kBlack);
  hGen->SetStats(0);
  
  Int_t evttype = 1;
  gRandom->SetSeed(0);
  Int_t initevt = gRandom->Uniform(1, nentries-2);
  Int_t ievt = initevt;
  for(int n=0;n<Nsmear;n++)
    {
      if(n%Nsmearshow==0) cout<<left<<"\033[0;36m >> Processing "<<setw(7)<<Form("\033[1;33m%d",n)<<" \033[0;36mth smearing\033[0m"<<endl;
      
      TH1D* hMCsmear = new TH1D("hMCsmear", "",nbinsmasshisto,minhisto,maxhisto);
      TH1D* hMCSignalsmear = new TH1D("hMCSignalsmear", "",nbinsmasshisto,minhisto,maxhisto);
      TH1D* hMCSwappedsmear = new TH1D("hMCSwappedsmear", "",nbinsmasshisto,minhisto,maxhisto);
      
      gRandom->SetSeed(0);
      Int_t Ngensmear = gRandom->Gaus(Ngen, NgenErr);
      hGen->Fill((Ngensmear-Ngen)*1.0/NgenErr);
      Int_t ctgen = 0;
      Int_t cttruth = 0;
      while(ctgen<Ngensmear)
        {
          //gRandom->SetSeed(0);
          //Int_t ievt = gRandom->Uniform(0, nentries-1);

          Bool_t findgen = false;

          ntSkim->GetEntry(ievt);
          if((!isPbPb && pBeamScrapingFilter && pPAprimaryVertexFilter) ||
             (isPbPb && pclusterCompatibilityFilter && pprimaryVertexFilter && phfCoincFilter3))
            {
              ntHi->GetEntry(ievt);
              if(!isPbPb || (hiBin>=centmin*2 && hiBin<=centmax*2))
                {
                  ntGen->GetEntry(ievt);
                  for(int j=0;j<Gsize;j++)
                    {
                      if((GisSignal[j]==1 || GisSignal[j]==2) && 
                         TMath::Abs(Gy[j])<1 && Gpt[j]>ptmin && Gpt[j]<ptmax) 
                        {
                          if(n%Nsmearshow==0 && ctgen%(Ngen/10)==0) cout<<"    Find "<<(ctgen+1)<<" gen D(s)"<<endl;
                          ctgen++;
                          findgen = true;
                        }
                    }                  
                  
                  //if(findgen)
                  //  {
                      ntDkpi->GetEntry(ievt);
                      for(int j=0;j<Dsize;j++)
                        {
                          if(!pass_selections(j) || 
                             Dpt[j]<ptmin || Dpt[j]>ptmax) continue;
                          hMCsmear->Fill(Dmass[j]);
                          if(Dgen[j]==23333) 
                            {
                              hMCSignalsmear->Fill(Dmass[j]);
                              cttruth++;
                            }
                          if(Dgen[j]==23344) hMCSwappedsmear->Fill(Dmass[j]);
                        }
                      //  }
                }
            }

          if(ievt < initevt && ((ievt+evttype)%nentries) >= initevt)
            {
              gRandom->SetSeed(0);
              initevt = gRandom->Uniform(1, nentries-2);
              ievt = initevt;
              if(evttype<5) evttype++;
              cout<<"  "<<evttype<<" "<<initevt<<endl;
            }
          else ievt = (ievt+evttype)%nentries;
        }
      
      Bool_t ifsaveplot = n%Nsmearshow==0?true:false;
      TF1* fMCSignalsmear = fit(hMCsmear, hMCSignalsmear, hMCSwappedsmear, ptmin, ptmax, isPbPb, (ptmin*100+ptmax)*Nsmear*10+n, "plotToyMCpickevt/DMass_MCsmear", centmin, centmax, "mass", ifsaveplot, false);
      Float_t Yield = fMCSignalsmear->Integral(minhisto,maxhisto)/binwidthmass;
      Float_t YieldErr = fMCSignalsmear->Integral(minhisto,maxhisto)/binwidthmass*fMCSignalsmear->GetParError(0)/fMCSignalsmear->GetParameter(0);
      hSmear->Fill((Yield-Nmatched)/YieldErr);
      hSmearTruth->Fill((cttruth-Nmatched)*1./(NgenErr*1.*nSignal/effGen));
      cout<<Nmatched<<endl;
      if(n%Nsmearshow==0) cout<<"\033[0m     "<<Ngensmear*hPtMCEff->GetBinContent(i+1)<<"  "<<hMCSignalsmear->Integral()<<"  "<<Yield<<endl;
      
      delete hMCSwappedsmear;
      delete hMCSignalsmear;
      delete hMCsmear;
    }
  
  if(ifplot)
    {
      TCanvas* csmear = new TCanvas("csmear","",600,600);
      csmear->SetLogy();
      hSmear->Draw("pe");
      hSmear->Fit("gaus","q");
      TLatex* texGaussMean = new TLatex(0.70,0.86,Form("#mu: %.3f",hSmear->GetFunction("gaus")->GetParameter(1)));
      settex(texGaussMean,0.045);
      texGaussMean->Draw();      
      TLatex* texGaussSigma = new TLatex(0.70,0.80,Form("#sigma: %.3f",hSmear->GetFunction("gaus")->GetParameter(2)));
      settex(texGaussSigma,0.045);
      texGaussSigma->Draw();
      TString csmearname = isPbPb?Form("plotToyMCpickevt/csmear_%s_pt_%.0f_%.0f_cent_%.0f_%.0f",collisionsystem.Data(),ptmin,ptmax,centmin,centmax):Form("plotToyMCpickevt/csmear_%s_pt_%.0f_%.0f",collisionsystem.Data(),ptmin,ptmax);
      csmear->SaveAs(Form("%s.pdf",csmearname.Data()));
    }

  TFile* outf = new TFile(Form("%s.root",output.Data()),"recreate");
  outf->cd();
  hSmear->Write();
  hSmearTruth->Write();
  hGen->Write();
  outf->Write();
  outf->Close();

}

int main(int argc, char *argv[])
{
  if(argc==11)
    {
      fitDtoyMCpickevt(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]), atoi(argv[7]), atoi(argv[8]), atof(argv[9]), atof(argv[10]));
      return 0;
    }
  else if(argc==9)
    {
      fitDtoyMCpickevt(argv[1], argv[2], argv[3], argv[4], atof(argv[5]), atof(argv[6]), atoi(argv[7]), atoi(argv[8]));
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs - fitDtoyMCpickevt" << std::endl;
      return 1;
    }  
}
