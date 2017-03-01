#include "uti.h"
#include "TString.h"
#include "TMath.h"
#include "TLegendEntry.h"


void PtShapeSystematic(TString noweight="ROOTfiles/pthatallPP.root",TString weight="ROOTfiles/pthatallPPptreweighted.root",TString label="PP",int isHigherPoli=1){
  TFile *filenoweight=new TFile(noweight.Data());
  TFile *fileweight=new TFile(weight.Data());
  TH1F*hEffNoWeight=(TH1F*)filenoweight->Get("hEff");
  TH1F*hEffWeight=(TH1F*)fileweight->Get("hEff");

  hEffWeight->Divide(hEffNoWeight);
  hEffWeight->Draw();

  TCanvas*canvas=new TCanvas("canvas","canvas",500.,500);
  canvas->cd();
  hEffWeight->GetXaxis()->CenterTitle();
  hEffWeight->GetYaxis()->CenterTitle();
  hEffWeight->GetXaxis()->SetTitleOffset(1.0);
  hEffWeight->GetYaxis()->SetTitleOffset(1.15);
  hEffWeight->GetXaxis()->SetTitleSize(0.04);
  hEffWeight->GetYaxis()->SetTitleSize(0.04);
  hEffWeight->GetXaxis()->SetTitleFont(42);
  hEffWeight->GetYaxis()->SetTitleFont(42);
  hEffWeight->GetXaxis()->SetLabelFont(42);
  hEffWeight->GetYaxis()->SetLabelFont(42);
  hEffWeight->GetXaxis()->SetLabelSize(0.035);
  hEffWeight->GetYaxis()->SetLabelSize(0.035);  
  hEffWeight->SetMinimum(0.8);
  hEffWeight->SetMaximum(1.2);
  hEffWeight->SetXTitle("Gen p_{T}");
  hEffWeight->SetYTitle("Efficiency p_{T} weight/no weight");
  hEffWeight->Draw();
  
  TF1 *fSignalExtractionSig;

  if(isHigherPoli==0){
    fSignalExtractionSig= new TF1("fSignalExtractionSig","[0]+[1]/(x)+[2]/x/x");
    hEffWeight->Fit("fSignalExtractionSig","L q","",2,100);
    std::cout<<"parameter 0="<<fSignalExtractionSig->GetParameter(0)<<std::endl;
    std::cout<<"parameter 1="<<fSignalExtractionSig->GetParameter(1)<<std::endl;
    std::cout<<"parameter 2="<<fSignalExtractionSig->GetParameter(2)<<std::endl;
  }
  
  if(isHigherPoli==1){
    fSignalExtractionSig= new TF1("fSignalExtractionSig","[0]+[1]/(x)+[2]/x/x+[3]*x");
    hEffWeight->Fit("fSignalExtractionSig","L q","",2,100);
    std::cout<<"parameter 0="<<fSignalExtractionSig->GetParameter(0)<<std::endl;
    std::cout<<"parameter 1="<<fSignalExtractionSig->GetParameter(1)<<std::endl;
    std::cout<<"parameter 2="<<fSignalExtractionSig->GetParameter(2)<<std::endl;
    std::cout<<"parameter 3="<<fSignalExtractionSig->GetParameter(3)<<std::endl; 
  }
  canvas->SaveAs(Form("plotEff/canvasPtreweightedComparison%s.pdf",label.Data()));

  for (int index=1;index<=hEffWeight->GetNbinsX();index++){
  double value=TMath::Abs(1-fSignalExtractionSig->Eval(hEffWeight->GetBinCenter(index)));
  TString form=Form("%.02f",value);
  std::cout<<"pt bin="<<hEffWeight->GetBinCenter(index)<<", systematic="<<form.Data()<<std::endl;
  }
}


int main(int argc, char *argv[])
{

  if(argc==5)
    {
      PtShapeSystematic(argv[1], argv[2], argv[3], atoi(argv[4]));
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
  return 1;
}
