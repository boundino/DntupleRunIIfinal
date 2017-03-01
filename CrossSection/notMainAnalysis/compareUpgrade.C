#include "uti.h"

Double_t setparam0=100.;
Double_t setparam1=1.865;
Double_t setparam2=0.03;
Double_t setparam10=0.005;
Double_t setparam8=0.1;
Double_t setparam9=0.1;
Double_t fixparam1=1.865;
Double_t minhisto=	1.7;
Double_t maxhisto=2.0;
Double_t nbinsmasshisto=60;
Double_t binwidthmass=(maxhisto-minhisto)/nbinsmasshisto;

TString weight = "pthatweight";
TString seldata;
TString selmc;
TString collisionsystem;
int scalefactor=6;
double bkgreduction=0.7;

int nBins=1;
//void testFit(int count=3,Double_t ptmin=30.,Double_t ptmax=40,TString sample="PbPb")
void compareUpgrade(int option=2)
{

  int count; Double_t ptmin; Double_t ptmax; TString sample;
  int nmin,nmax,mymaxhisto;
  
  if (option==1)
  {count=3; ptmin=30.; ptmax=40; sample="PbPb"; mymaxhisto=2000;  };
  if (option==2)
  {count=1; ptmin=2.; ptmax=3; sample="PbPbMB"; mymaxhisto=600000;};


  TCanvas* c= new TCanvas(Form("c%d",count),"",600,600);
  TFile *file=new TFile(Form("FitsFiles/Fits_%s_%d.root",sample.Data(), count));
  TH1D* h = (TH1D*)file->Get(Form("h-%d",count));
  TH1D* hMCSignal = (TH1D*)file->Get(Form("hMCSignal-%d",count));
  TH1D* hMCSwapped = (TH1D*)file->Get(Form("hMCSwapped-%d",count));
    
  TF1* f = new TF1(Form("f%d",count),"[0]*([7]*([9]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[9])*Gaus(x,[1],[10])/(sqrt(2*3.14159)*[10]))+(1-[7])*Gaus(x,[1],[8])/(sqrt(2*3.14159)*[8]))+[3]+[4]*x+[5]*x*x+[6]*x*x*x", 1.7, 2.0);

  f->SetParLimits(4,-1000,1000);
  f->SetParLimits(10,0.001,0.05);
  f->SetParLimits(2,0.01,0.1);
  f->SetParLimits(8,0.02,0.2);
  f->SetParLimits(7,0,1);
  f->SetParLimits(9,0,1);
  
  f->SetParameter(0,setparam0);
  f->SetParameter(1,setparam1);
  f->SetParameter(2,setparam2);
  f->SetParameter(10,setparam10);
  f->SetParameter(9,setparam9);

  f->FixParameter(8,setparam8);
  f->FixParameter(7,1);
  f->FixParameter(1,fixparam1);
  f->FixParameter(3,0);
  f->FixParameter(4,0);
  f->FixParameter(5,0);
  f->FixParameter(6,0);
  h->GetEntries();
  
  hMCSignal->Fit(Form("f%d",count),"q","",minhisto,maxhisto);
  hMCSignal->Fit(Form("f%d",count),"q","",minhisto,maxhisto);
 
  f->ReleaseParameter(1);
  hMCSignal->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  hMCSignal->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  hMCSignal->Fit(Form("f%d",count),"L m","",minhisto,maxhisto);
  

  f->FixParameter(1,f->GetParameter(1));
  f->FixParameter(2,f->GetParameter(2));
  f->FixParameter(10,f->GetParameter(10));
  f->FixParameter(9,f->GetParameter(9));
  f->FixParameter(7,0);
  f->ReleaseParameter(8);
  f->SetParameter(8,setparam8);
  
  hMCSwapped->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(Form("f%d",count),"L m","",minhisto,maxhisto);
  
  f->FixParameter(7,hMCSignal->Integral(0,1000)/(hMCSwapped->Integral(0,1000)+hMCSignal->Integral(0,1000)));
  f->FixParameter(8,f->GetParameter(8));
  f->ReleaseParameter(3);
  f->ReleaseParameter(4);
  f->ReleaseParameter(5);
  f->ReleaseParameter(6);

  f->SetLineColor(kRed);
  

  /*
  TCanvas*mycanvas=new TCanvas("mycanvas","mycanvas",1000,500);
  mycanvas->Divide(2,1);
  mycanvas->cd(1);
  hMCSignal->Draw();
  mycanvas->cd(2);
  hMCSwapped->Draw();
  mycanvas->SaveAs("mycanvas.pdf");
*/
  
  h->Fit(Form("f%d",count),"q","",minhisto,maxhisto);
  h->Fit(Form("f%d",count),"q","",minhisto,maxhisto);
  f->ReleaseParameter(1);
  //f->ReleaseParameter(2);                                     // you need to release these two parameters if you want to perform studies on the sigma shape
  //f->ReleaseParameter(10);                                   // you need to release these two parameters if you want to perform studies on the sigma shape
  h->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  h->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  h->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  h->Fit(Form("f%d",count),"L m","",minhisto,maxhisto);
  
  std::cout<<"parameter 10="<<f->GetParameter(10)<<std::endl;

  TF1* background = new TF1(Form("background%d",count),"[0]+[1]*x+[2]*x*x+[3]*x*x*x");
  background->SetParameter(0,f->GetParameter(3));
  background->SetParameter(1,f->GetParameter(4));
  background->SetParameter(2,f->GetParameter(5));
  background->SetParameter(3,f->GetParameter(6));
  background->SetLineColor(4);
  background->SetRange(minhisto,maxhisto);
  background->SetLineStyle(2);
  
  TF1* mass = new TF1(Form("fmass%d",count),"[0]*([3]*([4]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[4])*Gaus(x,[1],[5])/(sqrt(2*3.14159)*[5])))");
  mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10));
  mass->SetParError(0,f->GetParError(0));
  mass->SetParError(1,f->GetParError(1));
  mass->SetParError(2,f->GetParError(2));
  mass->SetParError(3,f->GetParError(7));
  mass->SetParError(4,f->GetParError(9));
  mass->SetParError(5,f->GetParError(10));
  mass->SetFillColor(kOrange-3);
  mass->SetFillStyle(3002);
  mass->SetLineColor(kOrange-3);
  mass->SetLineWidth(3);
  mass->SetLineStyle(2);
  
  TF1* massSwap = new TF1(Form("fmassSwap%d",count),"[0]*(1-[2])*Gaus(x,[1],[3])/(sqrt(2*3.14159)*[3])");
  massSwap->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(7),f->GetParameter(8));
  massSwap->SetParError(0,f->GetParError(0));
  massSwap->SetParError(1,f->GetParError(1));
  massSwap->SetParError(2,f->GetParError(7));
  massSwap->SetParError(3,f->GetParError(8));
  massSwap->SetFillColor(kGreen+4);
  massSwap->SetFillStyle(3005);
  massSwap->SetLineColor(kGreen+4);
  massSwap->SetLineWidth(3);
  massSwap->SetLineStyle(1);
  
  h->SetXTitle("m_{#piK} (GeV/c^{2})");
  h->SetYTitle("Entries / (5 MeV/c^{2})");
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->SetAxisRange(0,h->GetMaximum()*1.4*1.2,"Y");
  h->GetXaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitleOffset(1.8);
  h->GetXaxis()->SetLabelOffset(0.007);
  h->GetYaxis()->SetLabelOffset(0.007);
  h->GetXaxis()->SetTitleSize(0.045);
  h->GetYaxis()->SetTitleSize(0.045);
  h->GetXaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleFont(42);
  h->GetXaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelSize(0.04);
  h->GetYaxis()->SetLabelSize(0.04);
  h->SetMarkerSize(0.8);
  h->SetMarkerStyle(20);
  h->SetStats(0);
  h->Draw("e");

  background->Draw("same");   
  mass->SetRange(minhisto,maxhisto);	
  mass->Draw("same");
  massSwap->SetRange(minhisto,maxhisto);
  massSwap->Draw("same");
  f->Draw("same");
  
  Double_t yield = mass->Integral(minhisto,maxhisto)/binwidthmass;
  Double_t yieldtotal = f->Integral(minhisto,maxhisto)/binwidthmass;
  Double_t yieldErr = mass->Integral(minhisto,maxhisto)/binwidthmass*mass->GetParError(0)/mass->GetParameter(0);
  
  std::cout<<"yield signal="<<yield<<std::endl;
  std::cout<<"total counts="<<yieldtotal<<std::endl;

  TLegend* leg = new TLegend(0.65,0.58,0.82,0.88,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry(h,"Data","pl");
  leg->AddEntry(f,"Fit","l");
  leg->AddEntry(mass,"D^{0}+#bar{D^{#lower[0.2]{0}}} Signal","f");
  leg->AddEntry(massSwap,"K-#pi swapped","f");
  leg->AddEntry(background,"Combinatorial","l");
  leg->Draw("same");

  TLatex Tl;
  Tl.SetNDC();
  Tl.SetTextAlign(12);
  Tl.SetTextSize(0.04);
  Tl.SetTextFont(42);
  Tl.DrawLatex(0.18,0.93, "#scale[1.25]{CMS} Performance");
  Tl.DrawLatex(0.65,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV",collisionsystem.Data()));

  TLatex* tex;

  tex = new TLatex(0.22,0.78,Form("%.1f < p_{T} < %.1f GeV/c",ptmin,ptmax));
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

  tex = new TLatex(0.22,0.83,"|y| < 1.0");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

  h->GetFunction(Form("f%d",count))->Delete();
  TH1F* histo_copy_nofitfun = ( TH1F * ) h->Clone("histo_copy_nofitfun");
  histo_copy_nofitfun->Draw("esame");

 TH1D* hTest = new TH1D("hTest","",nbinsmasshisto,minhisto,maxhisto);

 for (int m=0;m<yieldtotal;m++){
 double r = f->GetRandom();
 hTest->Fill(r);
 
 }

 TF1* ffaketotal=(TF1*)f->Clone("ffake");
 TF1* ffakemass=(TF1*)mass->Clone("ffakemass");
 TF1* ffakebackground=(TF1*)background->Clone("ffakebackground");
 TF1* ffakemassSwap=(TF1*)massSwap->Clone("ffakemassSwap");
 
 Double_t yieldtotal_original = ffaketotal->Integral(minhisto,maxhisto)/binwidthmass;
 Double_t yieldmass_original = ffakemass->Integral(minhisto,maxhisto)/binwidthmass;
 Double_t yieldbackground_original = ffakebackground->Integral(minhisto,maxhisto)/binwidthmass;
 Double_t yieldswapped_original = ffakemassSwap->Integral(minhisto,maxhisto)/binwidthmass;

 TH1D* hTestFake = new TH1D("hTestFake","",nbinsmasshisto,minhisto,maxhisto);
  ffakemass->SetParameter(2,ffaketotal->GetParameter(2)*0.8);
  ffakemass->SetParameter(10,ffaketotal->GetParameter(10)*0.8);
 
Double_t yieldmass_modified= ffakemass->Integral(minhisto,maxhisto)/binwidthmass;

cout<<"mass original="<<yieldmass_original<<endl;
cout<<"mass modified="<<yieldmass_modified<<endl;

 for (int m=0;m<yieldmass_original*scalefactor;m++){
   double r = ffakemass->GetRandom();
   hTestFake->Fill(r);
 }

  for (int m=0;m<(int)(yieldbackground_original*scalefactor*bkgreduction);m++){
   double r = ffakebackground->GetRandom();
   hTestFake->Fill(r);
 }
 
 for (int m=0;m<(int)(yieldswapped_original*scalefactor*bkgreduction);m++){
   double r = ffakemassSwap->GetRandom();
   hTestFake->Fill(r);
 }

 TCanvas*c2=new TCanvas("c2","c2",500,500);
 c2->cd();
 hTest->SetMaximum(2000);
  hTest->SetXTitle("m_{#piK} (GeV/c^{2})");
  hTest->SetYTitle("Entries / (5 MeV/c^{2})");
  hTest->GetXaxis()->CenterTitle();
  hTest->GetYaxis()->CenterTitle();
  hTest->SetAxisRange(0,hTest->GetMaximum()*1.*1.2,"Y");
  hTest->GetXaxis()->SetTitleOffset(1.3);
  hTest->GetYaxis()->SetTitleOffset(1.8);
  hTest->GetXaxis()->SetLabelOffset(0.007);
  hTest->GetYaxis()->SetLabelOffset(0.007);
  hTest->GetXaxis()->SetTitleSize(0.045);
  hTest->GetYaxis()->SetTitleSize(0.045);
  hTest->GetXaxis()->SetTitleFont(42);
  hTest->GetYaxis()->SetTitleFont(42);
  hTest->GetXaxis()->SetLabelFont(42);
  hTest->GetYaxis()->SetLabelFont(42);
  hTest->GetXaxis()->SetLabelSize(0.04);
  hTest->GetYaxis()->SetLabelSize(0.04);
  hTest->SetMarkerSize(0.8);
  hTest->SetMarkerStyle(20);
  hTest->SetStats(0);
  hTest->Draw("e");

 hTest->SetLineColor(1);
 hTest->SetMarkerColor(1);
  hTestFake->SetLineColor(2);
 hTestFake->SetMarkerColor(2);

 
 hTest->Draw("ep");
 hTestFake->Draw("epsame");

  TLegend* myleg = new TLegend(0.2177419,0.6292373,0.6633065,0.7266949,NULL,"brNDC");
  myleg->SetBorderSize(0);
  myleg->SetTextSize(0.04);
  myleg->SetTextFont(42);
  myleg->SetFillStyle(0);
  myleg->AddEntry(hTest,"Current CMS, |y|<1, L_{int}=0.5/nb","pl");
  myleg->AddEntry(hTestFake,"Upgraded CMS, |y|<2, L_{int}=1.5/nb","l");
  myleg->Draw("same");

  TLatex* mytex;

  mytex = new TLatex(0.22,0.83,Form("%.0f < p_{T} < %.0f GeV/c",ptmin,ptmax));
  mytex->SetNDC();
  mytex->SetTextFont(42);
  mytex->SetTextSize(0.04);
  mytex->SetLineWidth(2);
  mytex->Draw();
  
  TLatex* mychannel;

  mychannel = new TLatex(0.22,0.765,"D^{0} #rightarrow K#pi");
  mychannel->SetNDC();
  mychannel->SetTextFont(42);
  mychannel->SetTextSize(0.055);
  mychannel->SetLineWidth(2);
  mychannel->Draw();

  TLatex myTl;
  myTl.SetNDC();
  myTl.SetTextAlign(12);
  myTl.SetTextSize(0.04);
  myTl.SetTextFont(42);
  myTl.DrawLatex(0.2,0.90, "#scale[1.25]{CMS} Performance");
  myTl.DrawLatex(0.63,0.90, Form("%s #sqrt{s_{NN}} = 5.02 TeV",collisionsystem.Data()));
  
  
  TFile*foutput=new TFile(Form("foutput_%s.root",sample.Data()),"recreate");
  foutput->cd();
  hTest->SetName("hTest");
  hTestFake->SetName("hTestFake");
  hTest->SetMaximum(mymaxhisto);
  hTest->Write();
  hTestFake->SetMaximum(mymaxhisto);
  hTestFake->Write();
  hMCSignal->Write();
  hMCSwapped->Write();
  c2->SaveAs(Form("PlotsUpgrade/canvasPerformance%s.pdf",sample.Data()));
  c2->SaveAs(Form("PlotsUpgrade/canvasPerformance%s.png",sample.Data()));

 
}
