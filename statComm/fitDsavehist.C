#include "uti.h"
#include "fitDdraw.h"
#include "parameters.h"

void fitDsavehist(TString inputdata, TString inputmc, TString trgselection, 
                  TString cut, TString collsyst, 
                  TString outputfilefitmass,
                  Float_t centmin=0., Float_t centmax=0.)
{
  Bool_t isPbPb = (collsyst=="PbPb" || collsyst=="PbPbMB")?true:false;

  TString seldata = isPbPb?Form("%s&&%s&&hiBin>=%f&&hiBin<=%f",trgselection.Data(),cut.Data(),centmin*2,centmax*2):Form("%s&&%s",trgselection.Data(),cut.Data());
  TString selmc = isPbPb?Form("%s&&hiBin>=%f&&hiBin<=%f",cut.Data(),centmin*2,centmax*2):Form("%s",cut.Data());

  TFile* inf = new TFile(inputdata.Data());
  TTree* nt = (TTree*)inf->Get("ntDkpi");
  nt->AddFriend("ntHlt");
  nt->AddFriend("ntHi");
  nt->AddFriend("ntSkim");

  TFile* infMC = new TFile(inputmc.Data());
  TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
  ntMC->AddFriend("ntHlt");
  ntMC->AddFriend("ntHi");
  ntMC->AddFriend("ntSkim");

  TH1D** ah = new TH1D*[nBins];
  TH1D** ahMCSignal = new TH1D*[nBins];
  TH1D** ahMCSwapped = new TH1D*[nBins];
  TH1D** ahMC = new TH1D*[nBins];
  TH1D** ahMCNocomb = new TH1D*[nBins];
  TH1D** ahMCNoswap = new TH1D*[nBins];
  TH1D** ahMCSwappedNoswap = new TH1D*[nBins];

  for(int i=0;i<nBins;i++)
    {
      ah[i] = new TH1D(Form("h_%d",i), "", nbinsmasshisto, minhisto, maxhisto);
      ahMCSignal[i] = new TH1D(Form("hMCSignal_%d",i), "", nbinsmasshisto, minhisto, maxhisto);
      ahMCSwapped[i] = new TH1D(Form("hMCSwapped_%d",i), "", nbinsmasshisto, minhisto, maxhisto);
      ahMC[i] = new TH1D(Form("hMC_%d",i), "", nbinsmasshisto, minhisto, maxhisto);
      ahMCNocomb[i] = new TH1D(Form("hMCNocomb_%d",i), "", nbinsmasshisto, minhisto, maxhisto);
      ahMCNoswap[i] = new TH1D(Form("hMCNoswap_%d",i), "", nbinsmasshisto, minhisto, maxhisto);
      ahMCSwappedNoswap[i] = new TH1D(Form("hMCSwappedNoswap_%d",i), "", nbinsmasshisto, minhisto, maxhisto);

      Float_t ptmin = ptBins[i];
      Float_t ptmax = ptBins[i+1];

      nt->Project(Form("h_%d",i),"Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f)","1",seldata.Data(),ptmin,ptmax));
      ntMC->Project(Form("hMCSignal_%d",i),"Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f&&(Dgen==23333))","1",selmc.Data(),ptmin,ptmax));   
      ntMC->Project(Form("hMCSwapped_%d",i),"Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f&&(Dgen==23344))","1",selmc.Data(),ptmin,ptmax));
      ntMC->Project(Form("hMC_%d",i),"Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f)","1",selmc.Data(),ptmin,ptmax));
      ntMC->Project(Form("hMCNocomb_%d",i),"Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f&&(Dgen==23333||Dgen==23344))","1",selmc.Data(),ptmin,ptmax));
      ntMC->Project(Form("hMCNoswap_%d",i),"Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f&&Dgen!=23344)","1",selmc.Data(),ptmin,ptmax));
      ntMC->Project(Form("hMCSwappedNoswap_%d",i),"Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f&&Dgen!=23344&&Dgen==23344)","1",selmc.Data(),ptmin,ptmax));      
    }

  //
  TString outputname = Form("%s.root",outputfilefitmass.Data());
  TFile* outputfitmass = new TFile(outputname,"recreate");
  outputfitmass->cd();
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
  if(argc==9)
    {
      fitDsavehist(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], atof(argv[7]), atof(argv[8]));
      return 0;
    }
  else if(argc==7)
    {
      fitDsavehist(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs: fitD.C" << std::endl;
      return 1;
    }
}



/*
  if(doweight==0) 
    {
      weightgen="1";
      weight="1";
    }
  // pp weight
  if(doweight==1)
    {
      weightgen="(pthatweight)*(maxDgenpt<pthat/1.2)*(0.0116437+Gpt*(0.0602697)+Gpt*Gpt*(-0.00226879)+Gpt*Gpt*Gpt*(3.91035e-05)+Gpt*Gpt*Gpt*Gpt*(-3.0699e-07)+Gpt*Gpt*Gpt*Gpt*Gpt*(8.73234e-10))";
      weight="(pthatweight)*(maxDgenpt<pthat/1.2)*(0.0116437+Dgenpt*(0.0602697)+Dgenpt*Dgenpt*(-0.00226879)+Dgenpt*Dgenpt*Dgenpt*(3.91035e-05)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*(-3.0699e-07)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*Dgenpt*(8.73234e-10))";
    }
  //PbPb weight
  if(doweight==2)
    {
      weightgen="(pthatweight)*(maxDgenpt<pthat/1.2)*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))";
      weight="(pthatweight)*(maxDgenpt<pthat/1.2)*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))";
    }
  //PbPb low pt weight
  if(doweight==3)
    {
      weightgen="(pthatweight)*(maxDgenpt<pthat/1.2)*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))*(-0.00600791+Gpt*(0.0838585)+Gpt*Gpt*(-0.00991096)+Gpt*Gpt*Gpt*(0.000496019)+Gpt*Gpt*Gpt*Gpt*(-8.50065e-06))";
      weight="(pthatweight)*(maxDgenpt<pthat/1.2)*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))*(-0.00600791+Dgenpt*(0.0838585)+Dgenpt*Dgenpt*(-0.00991096)+Dgenpt*Dgenpt*Dgenpt*(0.000496019)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*(-8.50065e-06))";
    }
  if(doweight<0 || doweight>4) std::cout<<"ERROR, this weighting option is not defined"<<std::endl;
  
  std::cout<<"we are using weight="<<weight<<std::endl;
  
*/
