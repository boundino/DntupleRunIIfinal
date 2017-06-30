#include "uti.h"
#include "fitDdraw.h"
#include "parameters.h"

void fitDsavehistpickevt(TString inputmc,
                         TString cut, TString cutgen, TString collsyst, 
                         TString outputfileeff,
                         Float_t centmin=0., Float_t centmax=0.)
{
  Bool_t isPbPb = (collsyst=="PbPb" || collsyst=="PbPbMB")?true:false;

  TString selmc = isPbPb?Form("%s&&hiBin>=%f&&hiBin<=%f",cut.Data(),centmin*2,centmax*2):Form("%s",cut.Data());
  TString selgen = isPbPb?Form("%s&&hiBin>=%f&&hiBin<=%f",cutgen.Data(),centmin*2,centmax*2):Form("%s",cutgen.Data());

  TFile* infMC = new TFile(inputmc.Data());
  TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
  ntMC->AddFriend("ntHlt");
  ntMC->AddFriend("ntHi");
  ntMC->AddFriend("ntSkim");
  TTree* ntGen = (TTree*)infMC->Get("ntGen");
  ntGen->AddFriend("ntDkpi");
  ntGen->AddFriend("ntHlt");
  ntGen->AddFriend("ntHi");
  ntGen->AddFriend("ntSkim");

  TH1D* hPtMCSignal = new TH1D("hPtMCSignal","",nBins,ptBins);
  ntMC->Project("hPtMCSignal","Dpt",Form("%s*(%s&&Dgen==23333)","1",selmc.Data()));
  TH1D* hPtMCGen = new TH1D("hPtMCGen","",nBins,ptBins);
  ntGen->Project("hPtMCGen","Gpt",Form("%s*(%s)","1",selgen.Data()));
  TH1D* hPtMCEff = (TH1D*)hPtMCSignal->Clone("hPtMCEff");
  hPtMCEff->Divide(hPtMCGen);

  //
  TString outputname = Form("%s.root",outputfileeff.Data());
  TFile* outputeff = new TFile(outputname,"recreate");
  outputeff->cd();
  hPtMCSignal->Write();
  hPtMCGen->Write();
  hPtMCEff->Write();
  outputeff->Close();
}

int main(int argc, char *argv[])
{
  if(argc==8)
    {
      fitDsavehistpickevt(argv[1], argv[2], argv[3], argv[4], argv[5], atof(argv[6]), atof(argv[7]));
      return 0;
    }
  else if(argc==6)
    {
      fitDsavehistpickevt(argv[1], argv[2], argv[3], argv[4], argv[5]);
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
