#include "uti.h"
#include "config/parametersLowpt.h"

TString weightfunctiongen = "1";
TString weightfunctionreco = "1";
TString selmc;

void weightPbPbvertex(){

TFile*fMC=new TFile("/data/HeavyFlavourRun2/MC2015/Dntuple/PbPb/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root");
TTree *ntDkpiMC = (TTree*)fMC->Get("ntDkpi");
TTree *ntSkimMC = (TTree*)fMC->Get("ntSkim");
TTree *ntHiMC = (TTree*)fMC->Get("ntHi");
ntDkpiMC->AddFriend(ntSkimMC);
ntDkpiMC->AddFriend(ntHiMC);

TFile*fData=new TFile("/data/jisun/PbPb2015/HF2and_ncand_skim_Dntuple_crab_PbPb_HIMinimumBias1to7_ForestAOD_D0y1p1_tkpt0p7eta1p5_goldenjson_EvtPlaneCali_03182015.root");
TTree *ntDkpiData = (TTree*)fData->Get("ntDkpi");
TTree *ntSkimData = (TTree*)fData->Get("ntSkim");
TTree *ntHiData = (TTree*)fData->Get("ntHi");
TTree *ntHltData = (TTree*)fData->Get("ntHlt");
ntDkpiData->AddFriend(ntSkimData);
ntDkpiData->AddFriend(ntHiData);
ntDkpiData->AddFriend(ntHltData);

TH1F*hpzData=new TH1F("hpzData","hpzData",200,-15,15);
TH1F*hpzMC=new TH1F("hpzMC","hpzMC",200,-15,15);

TCut weighpthat="1";
TString cut="abs(PVz)<15&&pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3";
TString hlt="HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1";

TCut weighttest="1";
//TCut weighttest="1.26077+PVz*(0.00887442)+PVz*PVz*(-0.00782056)+PVz*PVz*PVz*(-3.51063e-05)+PVz*PVz*PVz*PVz*(-3.51063e-05)";

ntDkpiMC->Project("hpzMC","PVz",TCut(weighpthat)*(TCut(cut.Data()*TCut(weighttest))));
ntDkpiData->Project("hpzData","PVz",(TCut(cut.Data())*TCut(hlt.Data())));

hpzMC->Scale(1./hpzMC->Integral(hpzMC->FindBin(-15.),hpzMC->FindBin(15)));
hpzData->Scale(1./hpzData->Integral(hpzMC->FindBin(-15.),hpzMC->FindBin(15)));

TCanvas*cRatioVtx=new TCanvas("cRatioVtx","cRatioVtx",500,500);
cRatioVtx->Divide(2,1);
cRatioVtx->cd(1);
hpzMC->SetLineColor(2);
hpzMC->Draw();
hpzData->Draw("same");
cRatioVtx->cd(2);
TH1D*hRatioVertex=(TH1D*)hpzData->Clone("hRatioVertex");
hRatioVertex->Divide(hpzMC);
hRatioVertex->Draw();


TF1 *myfit = new TF1("myfit","[0]+[1]*x+x*x*[2]+x*x*x*[3]+x*x*x*x*[4]", -15, 15);  
hRatioVertex->Fit("myfit","","",-15,15);
double par0=myfit->GetParameter(0);
double par1=myfit->GetParameter(1);
double par2=myfit->GetParameter(2);
double par3=myfit->GetParameter(3);
double par4=myfit->GetParameter(4);
std::cout<<"weight="<<par0<<"+PVz*("<<par1<<")+PVz*PVz*("<<par2<<")+PVz*PVz*PVz*("<<par3<<")+PVz*PVz*PVz*PVz*("<<par4<<")"<<endl;

}

void weightPbPbFONLL(int minfit=2,int maxfit=100,TString pthat="pthatall")
{
  TString label;
  TString selmcgen="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))";
  TString myweightfunctiongen,myweightfunctionreco;
  
  //TCut weighpthat="pow(10,-0.075415*Gpt+1.748668+Gpt*Gpt*0.000388)+pow(10,-0.166406*Gpt+2.887856+Gpt*Gpt*0.000105) +0.003157";
  TCut weighpthat="1";

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
 
  TFile*infMC=new TFile("/data/HeavyFlavourRun2/MC2015/Dntuple/PbPb/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root");
  TTree* ntGen = (TTree*)infMC->Get("ntGen");
  TTree *ntHiMC = (TTree*)infMC->Get("ntHi");
  ntGen->AddFriend(ntHiMC);
  
  TH1D* hPtGenFONLL = new TH1D("hPtGenFONLL","",nBinsReweight,ptBinsReweight);
  ntGen->Project("hPtGenFONLL","Gpt",(TCut(weighpthat)*TCut(selmcgen.Data())));
  divideBinWidth(hPtGenFONLL);
    
  TString fonll="/afs/cern.ch/work/g/ginnocen/public/output_pp_d0meson_5TeV_y1.root";
  TFile* filePPReference = new TFile(fonll.Data());  
  TGraphAsymmErrors* gaeBplusReference = (TGraphAsymmErrors*)filePPReference->Get("gaeSigmaDzero");

  TH1D* hFONLL = new TH1D("hFONLL","",nBinsReweight,ptBinsReweight);
  double x,y;
  for(int i=0;i<nBinsReweight;i++){
    gaeBplusReference->GetPoint(i,x,y);
    hFONLL->SetBinContent(i+1,y);
  }
  TH1D* hFONLLOverPt=(TH1D*)hFONLL->Clone("hFONLLOverPt");
  TH1D* hFONLLOverPtWeight=(TH1D*)hFONLL->Clone("hFONLLOverPtWeight");

  hFONLLOverPt->Divide(hPtGenFONLL);

/*
  TF1 *myfit = new TF1("myfit","[0]+[1]*x+x*x*[2]+x*x*x*[3]+x*x*x*x*[4]+x*x*x*x*x*[5]",0, 100);  
  hFONLLOverPt->Fit("myfit","","",0,100);

  double par0=myfit->GetParameter(0);
  double par1=myfit->GetParameter(1);
  double par2=myfit->GetParameter(2);
  double par3=myfit->GetParameter(3);
  double par4=myfit->GetParameter(4);
  double par5=myfit->GetParameter(5);

  std::cout<<"weight="<<par0<<"+Gpt*("<<par1<<")+Gpt*Gpt*("<<par2<<")+Gpt*Gpt*Gpt*("<<par3<<")"<<"+Gpt*Gpt*Gpt*Gpt*("<<par4<<")+Gpt*Gpt*Gpt*Gpt*Gpt*("<<par5<<")"<<endl;
  std::cout<<"weight="<<par0<<"+Dgenpt*("<<par1<<")+Dgenpt*Dgenpt*("<<par2<<")+Dgenpt*Dgenpt*Dgenpt*("<<par3<<")"<<"+Dgenpt*Dgenpt*Dgenpt*Dgenpt*("<<par4<<")+Dgenpt*Dgenpt*Dgenpt*Dgenpt*Dgenpt*("<<par5<<")"<<endl;
  
  std::cout<<myweightfunctiongen<<std::endl;
  std::cout<<myweightfunctionreco<<std::endl;
  std::cout<<"fit function parameters="<<weightfunctiongen<<std::endl;
*/
    TF1 *myfit = new TF1("myfit","pow(10,[0]*x+[1]+x*x*[2])+pow(10,[3]*x+[4]+x*x*[5])+[6]", 2, 100);
    hFONLLOverPt->Fit("myfit","","",minfit,maxfit);
    double par0=myfit->GetParameter(0);
    double par1=myfit->GetParameter(1);
    double par2=myfit->GetParameter(2);
    double par3=myfit->GetParameter(3);
    double par4=myfit->GetParameter(4);
    double par5=myfit->GetParameter(5);
    double par6=myfit->GetParameter(6);

   myweightfunctiongen=Form("pow(10,%f*Gpt+%f+Gpt*Gpt*%f)+pow(10,%f*Gpt+%f+Gpt*Gpt*%f)+%f",par0,par1,par2,par3,par4,par5,par6);
   myweightfunctionreco=Form("pow(10,%f*Gpt+%f+Gpt*Gpt*%f)+pow(10,%f*Gpt+%f+Gpt*Gpt*%f)+%f",par0,par1,par2,par3,par4,par5,par6);
   std::cout<<myweightfunctiongen<<std::endl;
   std::cout<<myweightfunctionreco<<std::endl;

  TCanvas*canvasPtReweight=new TCanvas("canvasPtReweight","canvasPtReweight",1000.,500.); 
  canvasPtReweight->Divide(3,1);
  canvasPtReweight->cd(1);
  gPad->SetLogy();
  hPtGenFONLL->SetXTitle("Gen p_{T}");
  hPtGenFONLL->SetYTitle("#entries");
  hPtGenFONLL->SetMinimum(1e-4);  
  hPtGenFONLL->SetMaximum(1e11);  
  hPtGenFONLL->GetYaxis()->SetTitleOffset(1.4);
  hPtGenFONLL->Draw();
  canvasPtReweight->cd(2);
  gPad->SetLogy();
  hFONLL->SetXTitle("p_{T}");
  hFONLL->SetYTitle("FONLL, #entries");
  hFONLL->SetMinimum(1e-4);  
  hFONLL->SetMaximum(1e11);  
  hFONLL->GetYaxis()->SetTitleOffset(1.4);
  hFONLL->Draw();
  canvasPtReweight->cd(3);
  hFONLLOverPt->SetXTitle("Gen p_{T}");
  hFONLLOverPt->SetYTitle("FONLL/PYTHIA ");
  hFONLLOverPt->SetMinimum(0.01);  
  hFONLLOverPt->SetMaximum(10.);  
  hFONLLOverPt->GetYaxis()->SetTitleOffset(1.4);
  hFONLLOverPt->Draw();

}


void weightPbPbFONLLpthat(int minfit=2,int maxfit=100,TString pthat="pthatall")
{
  TString label;
  TString selmcgen="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))";
  TString myweightfunctiongen,myweightfunctionreco;
  
  //TCut weighpthat="pow(10,-0.075415*Gpt+1.748668+Gpt*Gpt*0.000388)+pow(10,-0.166406*Gpt+2.887856+Gpt*Gpt*0.000105) +0.003157";
  TCut weighpthat="pthatweight";

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
 
  TFile*infMC=new TFile("/data/HeavyFlavourRun2/MC2015/Dntuple/PbPb/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root");
  TTree* ntGen = (TTree*)infMC->Get("ntGen");
  TTree *ntHiMC = (TTree*)infMC->Get("ntHi");
  ntGen->AddFriend(ntHiMC);
  
  TH1D* hPtGenFONLL = new TH1D("hPtGenFONLL","",nBinsReweight,ptBinsReweight);
  ntGen->Project("hPtGenFONLL","Gpt",(TCut(weighpthat)*TCut(selmcgen.Data())));
  divideBinWidth(hPtGenFONLL);
    
  TString fonll="/afs/cern.ch/work/g/ginnocen/public/output_pp_d0meson_5TeV_y1.root";
  TFile* filePPReference = new TFile(fonll.Data());  
  TGraphAsymmErrors* gaeBplusReference = (TGraphAsymmErrors*)filePPReference->Get("gaeSigmaDzero");

  TH1D* hFONLL = new TH1D("hFONLL","",nBinsReweight,ptBinsReweight);
  double x,y;
  for(int i=0;i<nBinsReweight;i++){
    gaeBplusReference->GetPoint(i,x,y);
    hFONLL->SetBinContent(i+1,y);
  }
  TH1D* hFONLLOverPt=(TH1D*)hFONLL->Clone("hFONLLOverPt");
  TH1D* hFONLLOverPtWeight=(TH1D*)hFONLL->Clone("hFONLLOverPtWeight");

  hFONLLOverPt->Divide(hPtGenFONLL);


  TF1 *myfit = new TF1("myfit","[0]+[1]*x+x*x*[2]+x*x*x*[3]+x*x*x*x*[4]",0, 100);  
  hFONLLOverPt->Fit("myfit","","",0,30);

  double par0=myfit->GetParameter(0);
  double par1=myfit->GetParameter(1);
  double par2=myfit->GetParameter(2);
  double par3=myfit->GetParameter(3);
  double par4=myfit->GetParameter(4);

  std::cout<<"weight="<<par0<<"+Max$(Gpt)*("<<par1<<")+Max$(Gpt)*Max$(Gpt)*("<<par2<<")+Max$(Gpt)*Max$(Gpt)*Max$(Gpt)*("<<par3<<")"<<"+Max$(Gpt)*Max$(Gpt)*Max$(Gpt)*Max$(Gpt)*("<<par4<<")"<<endl;

  std::cout<<myweightfunctiongen<<std::endl;
  std::cout<<myweightfunctionreco<<std::endl;

  TCanvas*canvasPtReweight=new TCanvas("canvasPtReweight","canvasPtReweight",1000.,500.); 
  canvasPtReweight->Divide(3,1);
  canvasPtReweight->cd(1);
  gPad->SetLogy();
  hPtGenFONLL->SetXTitle("Gen p_{T}");
  hPtGenFONLL->SetYTitle("#entries");
  hPtGenFONLL->SetMinimum(1e-4);  
  hPtGenFONLL->SetMaximum(1e11);  
  hPtGenFONLL->GetYaxis()->SetTitleOffset(1.4);
  hPtGenFONLL->Draw();
  canvasPtReweight->cd(2);
  gPad->SetLogy();
  hFONLL->SetXTitle("p_{T}");
  hFONLL->SetYTitle("FONLL, #entries");
  hFONLL->SetMinimum(1e-4);  
  hFONLL->SetMaximum(1e11);  
  hFONLL->GetYaxis()->SetTitleOffset(1.4);
  hFONLL->Draw();
  canvasPtReweight->cd(3);
  hFONLLOverPt->SetXTitle("Gen p_{T}");
  hFONLLOverPt->SetYTitle("FONLL/PYTHIA ");
  hFONLLOverPt->SetMinimum(0.01);  
  hFONLLOverPt->SetMaximum(10.);  
  hFONLLOverPt->GetYaxis()->SetTitleOffset(1.4);
  hFONLLOverPt->Draw();

}



void weightPbPbCentrality(){

TFile*fMC=new TFile("/data/HeavyFlavourRun2/MC2015/Dntuple/PbPb/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root");
TTree *ntDkpiMC = (TTree*)fMC->Get("ntDkpi");
TTree *ntSkimMC = (TTree*)fMC->Get("ntSkim");
TTree *ntHiMC = (TTree*)fMC->Get("ntHi");
ntDkpiMC->AddFriend(ntSkimMC);
ntDkpiMC->AddFriend(ntHiMC);

TFile*fData=new TFile("/data/jisun/PbPb2015/HF2and_ncand_skim_Dntuple_crab_PbPb_HIMinimumBias1to7_ForestAOD_D0y1p1_tkpt0p7eta1p5_goldenjson_EvtPlaneCali_03182015.root");
TTree *ntDkpiData = (TTree*)fData->Get("ntDkpi");
TTree *ntSkimData = (TTree*)fData->Get("ntSkim");
TTree *ntHiData = (TTree*)fData->Get("ntHi");
TTree *ntHltData = (TTree*)fData->Get("ntHlt");
ntDkpiData->AddFriend(ntSkimData);
ntDkpiData->AddFriend(ntHiData);
ntDkpiData->AddFriend(ntHltData);

TH1F*hCenData=new TH1F("hCenData","hCenData",200,0,200);
TH1F*hCenMC=new TH1F("hCenMC","hCenMC",200,0,200);

//TCut weighpthat="6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09)";
TCut weighpthat="1";
TString cut="abs(PVz)<15&&pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3";
TString hlt="HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1";

ntDkpiMC->Project("hCenMC","hiBin",TCut(weighpthat)*(TCut(cut.Data())));
ntDkpiData->Project("hCenData","hiBin",(TCut(cut.Data())*TCut(hlt.Data())));

hCenMC->Scale(1./hCenMC->Integral(hCenMC->FindBin(0.),hCenMC->FindBin(200)));
hCenData->Scale(1./hCenData->Integral(hCenMC->FindBin(0.),hCenMC->FindBin(200)));

TCanvas*cRatioVtx=new TCanvas("cRatioVtx","cRatioVtx",500,500);
cRatioVtx->Divide(2,1);
cRatioVtx->cd(1);
hCenMC->SetLineColor(2);
hCenMC->Draw();
hCenData->Draw("same");
cRatioVtx->cd(2);
TH1D*hRatioVertex=(TH1D*)hCenData->Clone("hRatioVertex");
hRatioVertex->Divide(hCenMC);
hRatioVertex->Draw();

TF1 *myfit = new TF1("myfit","[0]+[1]*x+x*x*[2]+x*x*x*[3]+x*x*x*x*[4]", 0, 200);  
hRatioVertex->Fit("myfit","","",0, 200);
double par0=myfit->GetParameter(0);
double par1=myfit->GetParameter(1);
double par2=myfit->GetParameter(2);
double par3=myfit->GetParameter(3);
double par4=myfit->GetParameter(4);

TString myweight;
std::cout<<"weight="<<par0<<"+hiBin*("<<par1<<")+hiBin*hiBin*("<<par2<<")+hiBin*hiBin*hiBin*("<<par3<<")"<<"+hiBin*hiBin*hiBin*hiBin*("<<par4<<")"<<endl;
}
