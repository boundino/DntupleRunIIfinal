void canvasRAA_cent_0_100()
{
//=========Macro generated from canvas: canvasRAA/canvasRAA
//=========  (Mon Jun 12 16:49:38 2017) by ROOT version6.02/13
   TCanvas *canvasRAA = new TCanvas("canvasRAA", "canvasRAA",0,0,600,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   canvasRAA->SetHighLightColor(2);
   canvasRAA->Range(-0.509591,-0.3409091,2.244955,1.931818);
   canvasRAA->SetFillColor(0);
   canvasRAA->SetBorderMode(0);
   canvasRAA->SetBorderSize(2);
   canvasRAA->SetLogx();
   canvasRAA->SetLeftMargin(0.185);
   canvasRAA->SetRightMargin(0.025);
   canvasRAA->SetTopMargin(0.08);
   canvasRAA->SetBottomMargin(0.15);
   canvasRAA->SetFrameBorderMode(0);
   canvasRAA->SetFrameBorderMode(0);
   
   TH2F *hemptyEff1 = new TH2F("hemptyEff1","",50,1,150,10,0,1.75);
   hemptyEff1->SetMinimum(0);
   hemptyEff1->SetMaximum(2);
   hemptyEff1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hemptyEff1->SetLineColor(ci);
   hemptyEff1->SetMarkerStyle(20);
   hemptyEff1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   hemptyEff1->GetXaxis()->CenterTitle(true);
   hemptyEff1->GetXaxis()->SetLabelFont(42);
   hemptyEff1->GetXaxis()->SetLabelOffset(0.01);
   hemptyEff1->GetXaxis()->SetLabelSize(0.05);
   hemptyEff1->GetXaxis()->SetTitleSize(0.06);
   hemptyEff1->GetXaxis()->SetTitleOffset(1.15);
   hemptyEff1->GetXaxis()->SetTitleFont(42);
   hemptyEff1->GetYaxis()->SetTitle("R_{AA}");
   hemptyEff1->GetYaxis()->CenterTitle(true);
   hemptyEff1->GetYaxis()->SetLabelFont(42);
   hemptyEff1->GetYaxis()->SetLabelSize(0.05);
   hemptyEff1->GetYaxis()->SetTitleSize(0.06);
   hemptyEff1->GetYaxis()->SetTitleOffset(1.15);
   hemptyEff1->GetYaxis()->SetTitleFont(42);
   hemptyEff1->GetZaxis()->SetLabelFont(42);
   hemptyEff1->GetZaxis()->SetLabelSize(0.035);
   hemptyEff1->GetZaxis()->SetTitleSize(0.035);
   hemptyEff1->GetZaxis()->SetTitleFont(42);
   hemptyEff1->Draw("");
   TLine *line = new TLine(1,1,150,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   TBox *box = new TBox(1,0.9543382,1.2,1.041388);
   box->SetFillColor(16);
   box->SetLineColor(16);
   box->Draw();
   TLatex *   tex = new TLatex(0.19,0.936,"27.4 pb^{-1} (5.02 TeV pp) + 530 #mub^{-1} (5.02 TeV PbPb)");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.038);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.22,0.9,"CMS");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.22,0.85,"D#scale[0.6]{#lower[-0.7]{0}} + #bar{D}#scale[0.6]{#lower[-0.7]{0}}");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.95,0.2,"Centrality 0-100%");
tex->SetNDC();
   tex->SetTextAlign(32);
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t gNuclearModification_fx3001[5] = {
   22.5,
   27.5,
   35,
   50,
   80};
   Double_t gNuclearModification_fy3001[5] = {
   0.4551899,
   0.512747,
   0.6125222,
   0.754522,
   0.814098};
   Double_t gNuclearModification_felx3001[5] = {
   2.5,
   2.5,
   5,
   10,
   20};
   Double_t gNuclearModification_fely3001[5] = {
   0.08052206,
   0.09584959,
   0.1095826,
   0.1312031,
   0.1489133};
   Double_t gNuclearModification_fehx3001[5] = {
   2.5,
   2.5,
   5,
   10,
   20};
   Double_t gNuclearModification_fehy3001[5] = {
   0.08052206,
   0.09584959,
   0.1095826,
   0.1312031,
   0.1489133};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(5,gNuclearModification_fx3001,gNuclearModification_fy3001,gNuclearModification_felx3001,gNuclearModification_fehx3001,gNuclearModification_fely3001,gNuclearModification_fehy3001);
   grae->SetName("gNuclearModification");
   grae->SetTitle("Graph");

   ci = 924;
   color = new TColor(ci, 0.6, 1, 0.6, " ", 0.7);
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#006600");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(21);
   
   TH1F *Graph_gNuclearModification3001 = new TH1F("Graph_gNuclearModification3001","Graph",100,12,108);
   Graph_gNuclearModification3001->SetMinimum(0.3158335);
   Graph_gNuclearModification3001->SetMaximum(1.021846);
   Graph_gNuclearModification3001->SetDirectory(0);
   Graph_gNuclearModification3001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gNuclearModification3001->SetLineColor(ci);
   Graph_gNuclearModification3001->SetMarkerStyle(20);
   Graph_gNuclearModification3001->GetXaxis()->SetLabelFont(42);
   Graph_gNuclearModification3001->GetXaxis()->SetLabelSize(0.035);
   Graph_gNuclearModification3001->GetXaxis()->SetTitleSize(0.035);
   Graph_gNuclearModification3001->GetXaxis()->SetTitleFont(42);
   Graph_gNuclearModification3001->GetYaxis()->SetLabelFont(42);
   Graph_gNuclearModification3001->GetYaxis()->SetLabelSize(0.035);
   Graph_gNuclearModification3001->GetYaxis()->SetTitleSize(0.035);
   Graph_gNuclearModification3001->GetYaxis()->SetTitleFont(42);
   Graph_gNuclearModification3001->GetZaxis()->SetLabelFont(42);
   Graph_gNuclearModification3001->GetZaxis()->SetLabelSize(0.035);
   Graph_gNuclearModification3001->GetZaxis()->SetTitleSize(0.035);
   Graph_gNuclearModification3001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_gNuclearModification3001);
   
   grae->Draw("5");
   
   Double_t gNuclearModification_fx3002[9] = {
   2.5,
   3.5,
   4.5,
   5.5,
   7,
   9,
   11.25,
   13.75,
   17.5};
   Double_t gNuclearModification_fy3002[9] = {
   0.722896,
   0.5732674,
   0.3865571,
   0.2820465,
   0.3188086,
   0.2576483,
   0.3069068,
   0.33705,
   0.3534133};
   Double_t gNuclearModification_felx3002[9] = {
   0.5,
   0.5,
   0.5,
   0.5,
   1,
   1,
   1.25,
   1.25,
   2.5};
   Double_t gNuclearModification_fely3002[9] = {
   0.1374051,
   0.1045885,
   0.06609773,
   0.04765142,
   0.05363675,
   0.0428774,
   0.05110495,
   0.05612468,
   0.06414565};
   Double_t gNuclearModification_fehx3002[9] = {
   0.5,
   0.5,
   0.5,
   0.5,
   1,
   1,
   1.25,
   1.25,
   2.5};
   Double_t gNuclearModification_fehy3002[9] = {
   0.1374051,
   0.1045885,
   0.06609773,
   0.04765142,
   0.05363675,
   0.0428774,
   0.05110495,
   0.05612468,
   0.06414565};
   grae = new TGraphAsymmErrors(9,gNuclearModification_fx3002,gNuclearModification_fy3002,gNuclearModification_felx3002,gNuclearModification_fehx3002,gNuclearModification_fely3002,gNuclearModification_fehy3002);
   grae->SetName("gNuclearModification");
   grae->SetTitle("Graph");

   ci = 925;
   color = new TColor(ci, 0.6, 1, 0.6, " ", 0.7);
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#006600");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(21);
   
   TH1F *Graph_gNuclearModification3002 = new TH1F("Graph_gNuclearModification3002","Graph",100,0.2,21.8);
   Graph_gNuclearModification3002->SetMinimum(0.1502179);
   Graph_gNuclearModification3002->SetMaximum(0.9248542);
   Graph_gNuclearModification3002->SetDirectory(0);
   Graph_gNuclearModification3002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gNuclearModification3002->SetLineColor(ci);
   Graph_gNuclearModification3002->SetMarkerStyle(20);
   Graph_gNuclearModification3002->GetXaxis()->SetLabelFont(42);
   Graph_gNuclearModification3002->GetXaxis()->SetLabelSize(0.035);
   Graph_gNuclearModification3002->GetXaxis()->SetTitleSize(0.035);
   Graph_gNuclearModification3002->GetXaxis()->SetTitleFont(42);
   Graph_gNuclearModification3002->GetYaxis()->SetLabelFont(42);
   Graph_gNuclearModification3002->GetYaxis()->SetLabelSize(0.035);
   Graph_gNuclearModification3002->GetYaxis()->SetTitleSize(0.035);
   Graph_gNuclearModification3002->GetYaxis()->SetTitleFont(42);
   Graph_gNuclearModification3002->GetZaxis()->SetLabelFont(42);
   Graph_gNuclearModification3002->GetZaxis()->SetLabelSize(0.035);
   Graph_gNuclearModification3002->GetZaxis()->SetTitleSize(0.035);
   Graph_gNuclearModification3002->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_gNuclearModification3002);
   
   grae->Draw("5");
   Double_t xAxis1[6] = {20, 25, 30, 40, 60, 100}; 
   
   TH1D *hNuclearModification2 = new TH1D("hNuclearModification2","",5, xAxis1);
   hNuclearModification2->SetBinContent(1,0.4551899);
   hNuclearModification2->SetBinContent(2,0.512747);
   hNuclearModification2->SetBinContent(3,0.6125222);
   hNuclearModification2->SetBinContent(4,0.754522);
   hNuclearModification2->SetBinContent(5,0.814098);
   hNuclearModification2->SetBinError(1,0.04426721);
   hNuclearModification2->SetBinError(2,0.04092095);
   hNuclearModification2->SetBinError(3,0.04786103);
   hNuclearModification2->SetBinError(4,0.03945874);
   hNuclearModification2->SetBinError(5,0.05862706);
   hNuclearModification2->SetEntries(908.2131);
   hNuclearModification2->SetLineWidth(3);

   ci = TColor::GetColor("#006600");
   hNuclearModification2->SetMarkerColor(ci);
   hNuclearModification2->SetMarkerStyle(21);
   hNuclearModification2->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
   hNuclearModification2->GetXaxis()->SetLabelFont(42);
   hNuclearModification2->GetXaxis()->SetLabelSize(0.035);
   hNuclearModification2->GetXaxis()->SetTitleSize(0.035);
   hNuclearModification2->GetXaxis()->SetTitleFont(42);
   hNuclearModification2->GetYaxis()->SetTitle("Uncorrected dN(D^{0})/dp_{T}");
   hNuclearModification2->GetYaxis()->SetLabelFont(42);
   hNuclearModification2->GetYaxis()->SetLabelSize(0.035);
   hNuclearModification2->GetYaxis()->SetTitleSize(0.035);
   hNuclearModification2->GetYaxis()->SetTitleFont(42);
   hNuclearModification2->GetZaxis()->SetLabelFont(42);
   hNuclearModification2->GetZaxis()->SetLabelSize(0.035);
   hNuclearModification2->GetZaxis()->SetTitleSize(0.035);
   hNuclearModification2->GetZaxis()->SetTitleFont(42);
   hNuclearModification2->Draw("psame");
   Double_t xAxis2[10] = {2, 3, 4, 5, 6, 8, 10, 12.5, 15, 20}; 
   
   TH1D *hNuclearModification3 = new TH1D("hNuclearModification3","",9, xAxis2);
   hNuclearModification3->SetBinContent(1,0.722896);
   hNuclearModification3->SetBinContent(2,0.5732674);
   hNuclearModification3->SetBinContent(3,0.3865571);
   hNuclearModification3->SetBinContent(4,0.2820465);
   hNuclearModification3->SetBinContent(5,0.3188086);
   hNuclearModification3->SetBinContent(6,0.2576483);
   hNuclearModification3->SetBinContent(7,0.3069068);
   hNuclearModification3->SetBinContent(8,0.33705);
   hNuclearModification3->SetBinContent(9,0.3534133);
   hNuclearModification3->SetBinError(1,0.09654749);
   hNuclearModification3->SetBinError(2,0.0524576);
   hNuclearModification3->SetBinError(3,0.02582015);
   hNuclearModification3->SetBinError(4,0.02210658);
   hNuclearModification3->SetBinError(5,0.01992371);
   hNuclearModification3->SetBinError(6,0.01468762);
   hNuclearModification3->SetBinError(7,0.01875186);
   hNuclearModification3->SetBinError(8,0.02502153);
   hNuclearModification3->SetBinError(9,0.02869018);
   hNuclearModification3->SetEntries(800.5086);
   hNuclearModification3->SetLineWidth(3);

   ci = TColor::GetColor("#006600");
   hNuclearModification3->SetMarkerColor(ci);
   hNuclearModification3->SetMarkerStyle(21);
   hNuclearModification3->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
   hNuclearModification3->GetXaxis()->SetLabelFont(42);
   hNuclearModification3->GetXaxis()->SetLabelSize(0.035);
   hNuclearModification3->GetXaxis()->SetTitleSize(0.035);
   hNuclearModification3->GetXaxis()->SetTitleFont(42);
   hNuclearModification3->GetYaxis()->SetTitle("Uncorrected dN(D^{0})/dp_{T}");
   hNuclearModification3->GetYaxis()->SetLabelFont(42);
   hNuclearModification3->GetYaxis()->SetLabelSize(0.035);
   hNuclearModification3->GetYaxis()->SetTitleSize(0.035);
   hNuclearModification3->GetYaxis()->SetTitleFont(42);
   hNuclearModification3->GetZaxis()->SetLabelFont(42);
   hNuclearModification3->GetZaxis()->SetLabelSize(0.035);
   hNuclearModification3->GetZaxis()->SetTitleSize(0.035);
   hNuclearModification3->GetZaxis()->SetTitleFont(42);
   hNuclearModification3->Draw("psame");
   
   TLegend *leg = new TLegend(0.5236242,0.7474695,0.942953,0.8457592,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.03);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("gNuclearModification","D^{0} |y| < 1.0","pf");

   ci = 924;
   color = new TColor(ci, 0.6, 1, 0.6, " ", 0.7);
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#006600");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry->SetTextSize(0.043);
   leg->Draw();
      tex = new TLatex(0.23,0.66,"T_{AA} and lumi.");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.23,0.61,"uncertainty");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TH2F *hemptyEff_copy4 = new TH2F("hemptyEff_copy4","",50,1,150,10,0,1.75);
   hemptyEff_copy4->SetMinimum(0);
   hemptyEff_copy4->SetMaximum(2);
   hemptyEff_copy4->SetDirectory(0);
   hemptyEff_copy4->SetStats(0);

   ci = TColor::GetColor("#000099");
   hemptyEff_copy4->SetLineColor(ci);
   hemptyEff_copy4->SetMarkerStyle(20);
   hemptyEff_copy4->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   hemptyEff_copy4->GetXaxis()->CenterTitle(true);
   hemptyEff_copy4->GetXaxis()->SetLabelFont(42);
   hemptyEff_copy4->GetXaxis()->SetLabelOffset(0.01);
   hemptyEff_copy4->GetXaxis()->SetLabelSize(0.05);
   hemptyEff_copy4->GetXaxis()->SetTitleSize(0.06);
   hemptyEff_copy4->GetXaxis()->SetTitleOffset(1.15);
   hemptyEff_copy4->GetXaxis()->SetTitleFont(42);
   hemptyEff_copy4->GetYaxis()->SetTitle("R_{AA}");
   hemptyEff_copy4->GetYaxis()->CenterTitle(true);
   hemptyEff_copy4->GetYaxis()->SetLabelFont(42);
   hemptyEff_copy4->GetYaxis()->SetLabelSize(0.05);
   hemptyEff_copy4->GetYaxis()->SetTitleSize(0.06);
   hemptyEff_copy4->GetYaxis()->SetTitleOffset(1.15);
   hemptyEff_copy4->GetYaxis()->SetTitleFont(42);
   hemptyEff_copy4->GetZaxis()->SetLabelFont(42);
   hemptyEff_copy4->GetZaxis()->SetLabelSize(0.035);
   hemptyEff_copy4->GetZaxis()->SetTitleSize(0.035);
   hemptyEff_copy4->GetZaxis()->SetTitleFont(42);
   hemptyEff_copy4->Draw("sameaxis");
   canvasRAA->Modified();
   canvasRAA->cd();
   canvasRAA->SetSelected(canvasRAA);
}
