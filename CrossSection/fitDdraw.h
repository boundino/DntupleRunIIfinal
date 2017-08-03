#include "uti.h"
#include "PaperDraw.h"

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

  TCanvas* c = new TCanvas(Form("c%d",count), "", 600, 600);
  TF1* f = new TF1(Form("f%d",count),"[0]*([7]*([9]*Gaus(x,[1],[2]*(1+[11]))/(sqrt(2*3.14159)*[2]*(1+[11]))+(1-[9])*Gaus(x,[1],[10]*(1+[11]))/(sqrt(2*3.14159)*[10]*(1+[11])))+(1-[7])*Gaus(x,[1],[8]*(1+[11]))/(sqrt(2*3.14159)*[8]*(1+[11])))+[3]+[4]*x+[5]*x*x+[6]*x*x*x", 1.7, 2.0);

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

  float fixparam7 = hMCSignal->Integral(0,1000)/(hMCSwapped->Integral(0,1000)+hMCSignal->Integral(0,1000));

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

  f->FixParameter(7,fixparam7);
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

  TLegend* leg = new TLegend(0.65, 0.58, 0.82, 0.88,NULL,"brNDC");
  setleg(leg, 0.04);
  leg->AddEntry(h,"Data","pl");
  leg->AddEntry(f,"Fit","l");
  leg->AddEntry(mass,"D^{0}+#bar{D^{#lower[0.2]{0}}} Signal","f");
  leg->AddEntry(massSwap,"K-#pi swapped","f");
  leg->AddEntry(background,"Combinatorial","l");
  leg->Draw("same");

  TLatex* texcms = new TLatex(0.18, 0.93, "#scale[1.25]{CMS} Preliminary");
  settex(texcms, 0.04, 12);
  texcms->Draw();

  TString ttexcol = (collisionsystem=="PP"||collisionsystem=="PPMB")?Form("%s #sqrt{s_{NN}} = 5.02 TeV","pp"):Form("%s #sqrt{s_{NN}} = 5.02 TeV","PbPb");
  TLatex* texlumi = new TLatex(0.96, 0.93, ttexcol.Data());
  settex(texlumi, 0.04, 32);
  texlumi->Draw();

  TLatex* texPt = new TLatex(0.22, 0.78, Form("%.1f < p_{T} < %.1f GeV/c",ptmin,ptmax));
  settex(texPt, 0.04);
  texPt->Draw();
  TLatex* texcent = new TLatex(0.22, 0.71, Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));
  settex(texcent, 0.045);
  if(isPbPb) texcent->Draw();
  TLatex* texY = new TLatex(0.22, 0.83, "|y| < 1.0");
  settex(texY, 0.04);
  texY->Draw();

  total = f;

  h->GetFunction(Form("f%d",count))->Delete();
  TH1F* histo_copy_nofitfun = (TH1F*)h->Clone("histo_copy_nofitfun");
  histo_copy_nofitfun->Draw("esame");

  if(!isPbPb) c->SaveAs(Form("plotFits/DMass%s_%d.pdf",collisionsystem.Data(),count));
  else if(collisionsystem=="PbPbMB") c->SaveAs(Form("plotFits/DMass%s_%.0f_%.0f_%d.pdf",collisionsystem.Data(),centMin,centMax,count));
  else c->SaveAs(Form("plotFits/DMass%s_%.0f_%.0f_%d_%s.pdf",collisionsystem.Data(),centMin,centMax,count,tGJ.Data()));

  //

  TCanvas* c_yield = new TCanvas(Form("c_yield%d",count), "", 600, 600);
  h->Draw("e");
  background->Draw("same");
  mass->SetRange(minhisto,maxhisto);
  mass->Draw("same");
  massSwap->SetRange(minhisto,maxhisto);
  massSwap->Draw("same");
  f->Draw("same");
  leg->Draw("same");
  texcms->Draw();
  texlumi->Draw();
  texPt->Draw();
  if(isPbPb) texcent->Draw();
  texY->Draw();
  TLatex* texyield = new TLatex(0.22, 0.65, Form("N = %.0f #pm %.0f", yield, yieldErr));
  settex(texyield, 0.04);
  texyield->Draw();
  TLine* lsigregl = new TLine(1.8649-0.025, 0, 1.8649-0.025, background->Eval(1.8649-0.025));
  lsigregl->SetLineWidth(2);
  lsigregl->SetLineStyle(2);
  lsigregl->SetLineColor(kGray+1);
  lsigregl->Draw();
  TLine* lsigregh = new TLine(1.8649+0.025, 0, 1.8649+0.025, background->Eval(1.8649+0.025));
  lsigregh->SetLineWidth(2);
  lsigregh->SetLineStyle(2);
  lsigregh->SetLineColor(kGray+1);
  lsigregh->Draw();

  Float_t Ssig = mass->Integral(1.8649-0.025, 1.8649+0.025)/binwidthmass;
  Float_t Bsig = background->Integral(1.8649-0.025, 1.8649+0.025)/binwidthmass + massSwap->Integral(1.8649-0.025, 1.8649+0.025)/binwidthmass;
  Float_t sig = Ssig/TMath::Sqrt(Ssig+Bsig);
  TLatex* texsig = new TLatex(0.22, 0.59, Form("S/#sqrt{S+B} = %.1f", sig));
  settex(texsig, 0.04);
  texsig->Draw();
  TLatex* texbkg = new TLatex(0.22, 0.53, Form("S = %.0f, B = %.0f", Ssig, Bsig));
  settex(texbkg, 0.04);
  texbkg->Draw();
  TLatex* texswap = new TLatex(0.22, 0.47, Form("sgl/(sgl+swap) = %.2f", fixparam7));
  settex(texswap, 0.04);
  texswap->Draw();

  histo_copy_nofitfun->Draw("esame");

  if(!isPbPb) c_yield->SaveAs(Form("plotFitsYield/DMass%s_%d.pdf",collisionsystem.Data(),count));
  else if(collisionsystem=="PbPbMB") c_yield->SaveAs(Form("plotFitsYield/DMass%s_%.0f_%.0f_%d.pdf",collisionsystem.Data(),centMin,centMax,count));
  else c_yield->SaveAs(Form("plotFitsYield/DMass%s_%.0f_%.0f_%d_%s.pdf",collisionsystem.Data(),centMin,centMax,count,tGJ.Data()));

  //

  TGaxis::SetMaxDigits(3);
  if(h->GetMaximum()>1.e+5) TGaxis::SetMaxDigits(4);
  else if(h->GetMaximum()<1.e+3) TGaxis::SetMaxDigits(1);
  TCanvas* c_paper = new TCanvas(Form("c_paper%d",count), "", 600, 600);
  c_paper->cd();
  c_paper->SetFillColor(0);
  c_paper->SetBorderMode(0);
  c_paper->SetBorderSize(2);
  c_paper->SetLeftMargin(0.185);
  c_paper->SetRightMargin(0.025);
  c_paper->SetTopMargin(0.080);
  c_paper->SetBottomMargin(0.150);
  c_paper->SetFrameBorderMode(0);

  sethemptystyle(h, xtitleoffsetpFit, ytitleoffsetpFit, xtitlesizepFit, ytitlesizepFit, xlabelsizepFit, ylabelsizepFit);
  h->GetXaxis()->SetLabelOffset(0.013); // 0.013
  h->SetMarkerSize(msizepFit);
  h->SetMarkerStyle(20);
  h->SetLineColor(1);
  h->SetLineWidth(lwidthpFit);
  h->GetXaxis()->SetNdivisions(-50205);
  h->GetXaxis()->SetTickLength(0.04);
  h->Draw("e");
  background->SetLineStyle(7);
  background->SetLineWidth(lwidthpFit);
  background->Draw("same");
  mass->SetFillStyle(3002);
  mass->SetLineWidth(lwidthpFit);
  mass->SetLineStyle(7);
  mass->Draw("same");
  massSwap->SetLineStyle(1);
  massSwap->SetFillStyle(3005);
  massSwap->SetLineWidth(lwidthpFit);
  massSwap->Draw("same");
  f->SetNpx(5000);
  f->SetLineWidth(5);
  f->Draw("same");
  h->Draw("esame");
  TLegend* leg_paper = new TLegend(0.62, 0.58, 0.90, 0.90, NULL, "brNDC");
  setleg(leg_paper, 0.047);
  leg_paper->AddEntry(h,"Data","pl");
  leg_paper->AddEntry(f,"Fit","l");
  leg_paper->AddEntry(mass,"Signal","f");
  leg_paper->AddEntry(background,"Combinatorial","l");
  leg_paper->AddEntry(massSwap,"K-#pi swapped","f");
  leg_paper->Draw("same");
  TLatex* texcms_paper = new TLatex(CMSxposFit, CMSyposFit, "CMS");
  settex(texcms_paper, CMSsizeFit, 13, 62);
  texcms_paper->Draw();
  TString ttexcol_paper = (collisionsystem=="PP"||collisionsystem=="PPMB")?"27.4 pb^{-1} (5.02 TeV pp)":"530 #mub^{-1} (5.02 TeV PbPb)";
  TLatex* texlumi_paper = new TLatex(LumixposFit, LumiyposFit, ttexcol_paper.Data());
  settex(texlumi_paper, LumisizeFit, 31);
  texlumi_paper->Draw();
  TLatex* texDzero_paper = new TLatex(DZEROxposFit, DZEROyposFit, "D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}");
  settex(texDzero_paper, DZEROsizeRAA, 13, 62);
  texDzero_paper->Draw();

  Float_t xpostex_paper = 0.218, ypostex_paper = 0.72/*0.69*/, dypostex_paper = 0.06;
  TString ttexPt_paper = Form("%.0f < p_{T} < %.0f GeV/c",ptmin,ptmax);
  if(ptmin>12 && ptmin<13) ttexPt_paper = Form("%.1f < p_{T} < %.0f GeV/c",ptmin,ptmax);
  if(ptmax>12 && ptmax<13) ttexPt_paper = Form("%.0f < p_{T} < %.1f GeV/c",ptmin,ptmax);
  TLatex* texPt_paper = new TLatex(xpostex_paper, ypostex_paper, ttexPt_paper.Data());
  settex(texPt_paper, 0.048, 12);
  texPt_paper->Draw();
  TLatex* texY_paper = new TLatex(xpostex_paper, ypostex_paper=(ypostex_paper-dypostex_paper), "|y| < 1.0");
  settex(texY_paper, 0.048, 12);
  texY_paper->Draw();
  TLatex* texcent_paper = new TLatex(xpostex_paper, ypostex_paper=(ypostex_paper-dypostex_paper), Form("Cent. %.0f-%.0f%s",centMin,centMax,texper.Data()));
  settex(texcent_paper, 0.048, 12);
  if(isPbPb) texcent_paper->Draw();

  TPad* pzero = new TPad("pzero","",0.,0.,1.,1.); pzero->SetFillStyle(0); pzero->Draw(); pzero->cd();
  TBox* bzero = new TBox(0.15,0.13,0.176,0.175);
  bzero->SetFillStyle(1001);
  bzero->SetFillColor(0);
  bzero->SetLineWidth(0);
  bzero->Draw();
  c_paper->cd();

  if(!isPbPb) c_paper->SaveAs(Form("plotFitsPaper/DMass%s_%d.pdf",collisionsystem.Data(),count));
  else if(collisionsystem=="PbPbMB") c_paper->SaveAs(Form("plotFitsPaper/DMass%s_%.0f_%.0f_%d.pdf",collisionsystem.Data(),centMin,centMax,count));
  else c_paper->SaveAs(Form("plotFitsPaper/DMass%s_%.0f_%.0f_%d_%s.pdf",collisionsystem.Data(),centMin,centMax,count,tGJ.Data()));

  return mass;
}

