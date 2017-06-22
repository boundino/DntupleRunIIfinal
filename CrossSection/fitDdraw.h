using namespace std;
#include "uti.h"

Double_t setparam0=100.;
Double_t setparam1=1.865;
Double_t setparam2=0.03;
Double_t setparam10=0.005;
Double_t setparam8=0.1;
Double_t setparam9=0.1;
Double_t fixparam1=1.865;
Double_t minhisto=1.7;
Double_t maxhisto=2.0;
Double_t nbinsmasshisto=60;
Double_t binwidthmass=(maxhisto-minhisto)/nbinsmasshisto;

TString collisionsystem;
Float_t hiBinMin,hiBinMax,centMin,centMax;
TString tGJ;

TF1* fit(TH1D* h, TH1D* hMCSignal, TH1D* hMCSwapped, Double_t ptmin, Double_t ptmax, bool isPbPb, TF1* &total, Float_t centmin, Float_t centmax)
{
  static int count=0;
  count++;

  TCanvas* c = new TCanvas(Form("c%d",count),"",600,600);
  TF1* f = new TF1(Form("f%d",count),"[0]*([7]*([9]*Gaus(x,[1],[2]*(1+[11]))/(sqrt(2*3.14159)*[2]*(1+[11]))+(1-[9])*Gaus(x,[1],[10]*(1+[11]))/(sqrt(2*3.14159)*[10]*(1+[11])))+(1-[7])*Gaus(x,[1],[8]*(1+[11]))/(sqrt(2*3.14159)*[8]*(1+[11])))+[3]+[4]*x+[5]*x*x+[6]*x*x*x",1.7, 2.0);

  f->SetParLimits(4,-1000,1000);
  f->SetParLimits(10,0.001,0.05);
  f->SetParLimits(2,0.01,0.5);
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
  f->FixParameter(11,0);
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

  h->Fit(Form("f%d",count),"q","",minhisto,maxhisto);
  h->Fit(Form("f%d",count),"q","",minhisto,maxhisto);
  f->ReleaseParameter(1);
  f->SetParLimits(1,1.86,1.87);
  f->ReleaseParameter(11);
  f->SetParLimits(11,-1.,1.);
  h->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  h->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  h->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  h->Fit(Form("f%d",count),"L m","",minhisto,maxhisto);

  TF1* background = new TF1(Form("background%d",count),"[0]+[1]*x+[2]*x*x+[3]*x*x*x");
  background->SetParameter(0,f->GetParameter(3));
  background->SetParameter(1,f->GetParameter(4));
  background->SetParameter(2,f->GetParameter(5));
  background->SetParameter(3,f->GetParameter(6));
  background->SetLineColor(4);
  background->SetRange(minhisto,maxhisto);
  background->SetLineStyle(2);

  TF1* mass = new TF1(Form("fmass_%.0f_%.0f",ptmin,ptmax),"[0]*([3]*([4]*Gaus(x,[1],[2]*(1+[6]))/(sqrt(2*3.14159)*[2]*(1+[6]))+(1-[4])*Gaus(x,[1],[5]*(1+[6]))/(sqrt(2*3.14159)*[5]*(1+[6]))))");
  mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10),f->GetParameter(11));
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

  TF1* massSwap = new TF1(Form("fmassSwap_%.0f_%.0f",ptmin,ptmax),"[0]*(1-[2])*Gaus(x,[1],[3]*(1+[4]))/(sqrt(2*3.14159)*[3]*(1+[4]))");
  massSwap->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(7),f->GetParameter(8),f->GetParameter(11));
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
  h->SetAxisRange(0,h->GetMaximum()*1.55*1.3,"Y");
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
  Double_t yieldErr = mass->Integral(minhisto,maxhisto)/binwidthmass*mass->GetParError(0)/mass->GetParameter(0);

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

  TLatex* texCms = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  texCms->Draw();

  TLatex* texCol;
  if(collisionsystem=="PP"||collisionsystem=="PPMB") texCol= new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV","pp"));
  else texCol= new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV","PbPb"));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);
  texCol->Draw();

  TLatex* tex = new TLatex(0.22,0.78,Form("%.1f < p_{T} < %.1f GeV/c",ptmin,ptmax));
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();
  TLatex* texcent;
  if(isPbPb)
    {
      TString texper="%";
      texcent = new TLatex(0.22,0.71,Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));//0.2612903,0.8425793
      texcent->SetNDC();
      texcent->SetTextColor(1);
      texcent->SetTextFont(42);
      texcent->SetTextSize(0.045);
      texcent->SetLineWidth(2);
      texcent->Draw();
    }
  TLatex* texrap = new TLatex(0.22,0.83,"|y| < 1.0");
  texrap->SetNDC();
  texrap->SetTextFont(42);
  texrap->SetTextSize(0.04);
  texrap->SetLineWidth(2);
  texrap->Draw();

  total=f;

  h->GetFunction(Form("f%d",count))->Delete();
  TH1F* histo_copy_nofitfun = (TH1F*)h->Clone("histo_copy_nofitfun");
  histo_copy_nofitfun->Draw("esame");

  //
  if(!isPbPb) c->SaveAs(Form("plotFits/DMass%s_%d.pdf",collisionsystem.Data(),count));
  else if(collisionsystem=="PbPbMB") c->SaveAs(Form("plotFits/DMass%s_%.0f_%.0f_%d.pdf",collisionsystem.Data(),centMin,centMax,count));
  else c->SaveAs(Form("plotFits/DMass%s_%.0f_%.0f_%d_%s.pdf",collisionsystem.Data(),centMin,centMax,count,tGJ.Data()));

  TCanvas* cyield = new TCanvas(Form("cyield%d",count),"",600,600);
  h->Draw("e");
  background->Draw("same");
  mass->SetRange(minhisto,maxhisto);
  mass->Draw("same");
  massSwap->SetRange(minhisto,maxhisto);
  massSwap->Draw("same");
  f->Draw("same");
  leg->Draw("same");
  texCms->Draw();
  texCol->Draw();
  tex->Draw();
  if(isPbPb)
    {
      texcent->Draw();
    }
  texrap->Draw();
  TLatex* texyield = new TLatex(0.22,0.65,Form("N = %.0f #pm %.0f",yield,yieldErr));
  texyield->SetNDC();
  texyield->SetTextFont(42);
  texyield->SetTextSize(0.04);
  texyield->SetLineWidth(2);
  texyield->Draw();
  histo_copy_nofitfun->Draw("esame");

  if(!isPbPb) cyield->SaveAs(Form("plotFitsYield/DMass%s_%d.pdf",collisionsystem.Data(),count));
  else if(collisionsystem=="PbPbMB") cyield->SaveAs(Form("plotFitsYield/DMass%s_%.0f_%.0f_%d.pdf",collisionsystem.Data(),centMin,centMax,count));
  else cyield->SaveAs(Form("plotFitsYield/DMass%s_%.0f_%.0f_%d_%s.pdf",collisionsystem.Data(),centMin,centMax,count,tGJ.Data()));

  //
  TGaxis::SetMaxDigits(3);
  if(h->GetMaximum()>1.e+5) TGaxis::SetMaxDigits(4);
  else if(h->GetMaximum()<1.e+3) TGaxis::SetMaxDigits(1);
  TCanvas* cpaper = new TCanvas(Form("cpaper%d",count),"",600,600);
  h->GetXaxis()->SetTitleOffset(0.95); //0.9, 0.85
  h->GetYaxis()->SetTitleOffset(1.3); //1.3, 1.2
  h->GetXaxis()->SetTitleSize(0.062); //0.07
  h->GetYaxis()->SetTitleSize(0.062); //0.07
  h->GetXaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleFont(42);
  h->GetXaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelSize(0.045); //0.06
  h->GetYaxis()->SetLabelSize(0.045); //0.06
  h->GetXaxis()->SetLabelOffset(0.013);
  h->SetMarkerSize(1.55);
  h->SetMarkerStyle(20);
  h->SetLineColor(1);
  h->SetLineWidth(5);
  h->SetStats(0);
  h->GetXaxis()->SetNdivisions(-50205);
  h->GetXaxis()->SetTickLength(0.04);
  h->Draw("e");
  background->SetLineStyle(7);
  background->SetLineWidth(9);
  background->Draw("same");
  mass->SetFillStyle(3002);
  mass->SetLineWidth(9);
  mass->SetLineStyle(7);
  mass->Draw("same");
  massSwap->SetLineStyle(1);
  massSwap->SetFillStyle(3005);
  massSwap->SetLineWidth(9);
  massSwap->Draw("same");
  f->SetNpx(5000);
  f->SetLineWidth(5);
  f->Draw("same");
  h->Draw("esame");
  //TLegend* legpaper = new TLegend(0.20,0.56,0.55,0.88,NULL,"brNDC");
  TLegend* legpaper = new TLegend(0.62,0.56,0.90,0.88,NULL,"brNDC");
  legpaper->SetBorderSize(0);
  legpaper->SetTextSize(0.047);
  legpaper->SetTextFont(42);
  legpaper->SetFillStyle(0);
  legpaper->AddEntry(h,"Data","pl");
  legpaper->AddEntry(f,"Fit","l");
  //legpaper->AddEntry(mass,"D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}","f");
  legpaper->AddEntry(mass,"Signal","f");
  legpaper->AddEntry(background,"Combinatorial","l");
  legpaper->AddEntry(massSwap,"K-#pi swapped","f");
  legpaper->Draw("same");
  TLatex* texcms = new TLatex(0.215,0.87,"CMS");
  texcms->SetTextAlign(13);
  //TLatex* texcms = new TLatex(0.93,0.87,"CMS");
  //texcms->SetTextAlign(33);
  texcms->SetNDC();
  texcms->SetTextFont(62);//61
  texcms->SetTextSize(0.08);
  texcms->SetLineWidth(2);
  texcms->Draw();
  TString ttexcol = (collisionsystem=="PP"||collisionsystem=="PPMB")?Form("27.4 pb^{-1} (%s 5.02 TeV)","pp"):Form("530 #mub^{-1} (%s 5.02 TeV)","PbPb");
  TLatex* texcol = new TLatex(0.945, 0.94, ttexcol.Data());
  //if(collisionsystem=="PP"||collisionsystem=="PPMB") texcol= new TLatex(0.945,0.94, Form("27.4 pb^{-1} (%s 5.02 TeV)","pp"));
  //else texcol= new TLatex(0.945,0.94, Form("530 #mub^{-1} (%s 5.02 TeV)","PbPb"));
  texcol->SetNDC();
  texcol->SetTextAlign(32);
  texcol->SetTextSize(0.06);
  texcol->SetTextFont(42);
  texcol->Draw();
  TLatex* texpaper = new TLatex(0.218, 0.77, "D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}");
  texpaper->SetNDC();
  //texpaper->SetTextAlign(32);
  texpaper->SetTextAlign(12);
  texpaper->SetTextFont(62);
  texpaper->SetTextSize(0.057);
  texpaper->SetLineWidth(2);
  texpaper->Draw();
  TString ttexpaper = Form("%.0f < p_{T} < %.0f GeV/c",ptmin,ptmax);
  if(ptmin>12 && ptmin<13) ttexpaper = Form("%.1f < p_{T} < %.0f GeV/c",ptmin,ptmax);
  if(ptmax>12 && ptmax<13) ttexpaper = Form("%.0f < p_{T} < %.1f GeV/c",ptmin,ptmax);
  //TLatex* texpaper = new TLatex(0.93, 0.76, ttexpaper.Data());
  texpaper = new TLatex(0.218, 0.69, ttexpaper.Data());
  texpaper->SetNDC();
  //texpaper->SetTextAlign(32);
  texpaper->SetTextAlign(12);
  texpaper->SetTextFont(42);
  texpaper->SetTextSize(0.048);
  texpaper->SetLineWidth(2);
  texpaper->Draw();
  //texpaper = new TLatex(0.93,0.71, "|y| < 1.0");
  texpaper = new TLatex(0.218, 0.63, "|y| < 1.0");
  texpaper->SetNDC();
  //texpaper->SetTextAlign(32);
  texpaper->SetTextAlign(12);
  texpaper->SetTextFont(42);
  texpaper->SetTextSize(0.048);
  texpaper->SetLineWidth(2);
  texpaper->Draw();
  if(isPbPb)
    {
      TString texper="%";
      //texpaper = new TLatex(0.93,0.66,Form("Cent. %.0f-%.0f%s",centMin,centMax,texper.Data()));
      texpaper = new TLatex(0.218,0.58,Form("Cent. %.0f-%.0f%s",centMin,centMax,texper.Data()));
      texpaper->SetNDC();
      //texpaper->SetTextAlign(32);
      texpaper->SetTextAlign(12);
      texpaper->SetTextFont(42);
      texpaper->SetTextSize(0.048);
      texpaper->SetLineWidth(2);
      texpaper->Draw();
    }

  TPad* pzero = new TPad("pzero","",0.,0.,1.,1.); pzero->SetFillStyle(0); pzero->Draw(); pzero->cd();
  TBox* bzero = new TBox(0.15,0.125,0.176,0.17);
  bzero->SetFillStyle(1001);
  bzero->SetFillColor(0);
  bzero->SetLineWidth(0);
  bzero->Draw();
  cpaper->cd();

  if(!isPbPb) cpaper->SaveAs(Form("plotFitsPaper/DMass%s_%d.pdf",collisionsystem.Data(),count));
  else if(collisionsystem=="PbPbMB") cpaper->SaveAs(Form("plotFitsPaper/DMass%s_%.0f_%.0f_%d.pdf",collisionsystem.Data(),centMin,centMax,count));
  else cpaper->SaveAs(Form("plotFitsPaper/DMass%s_%.0f_%.0f_%d_%s.pdf",collisionsystem.Data(),centMin,centMax,count,tGJ.Data()));

  return mass;
}

