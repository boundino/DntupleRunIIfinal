#ifndef _COMBINECROSSSECTION_H_
#define _COMBINECROSSSECTION_H_

TString texper="%";

void scaleNsetCrossSection(TH1D* hSigmaStat, TGraphAsymmErrors* gaeCrossSyst, Double_t fscale, Int_t pcolor, Int_t pstyle, Bool_t verbose=false)
{
  Int_t ngrbins = gaeCrossSyst->GetN();
  for(int i=0;i<ngrbins;i++)
    {
      Double_t x,y;
      gaeCrossSyst->GetPoint(i,x,y);
      gaeCrossSyst->SetPoint(i,x,y*fscale);
      Double_t exl = gaeCrossSyst->GetErrorXlow(i);
      Double_t exh = gaeCrossSyst->GetErrorXhigh(i);
      Double_t eyl = gaeCrossSyst->GetErrorYlow(i);
      Double_t eyh = gaeCrossSyst->GetErrorYhigh(i);
      gaeCrossSyst->SetPointError(i,exl,exh,eyl*fscale,eyh*fscale);
      if(verbose)
        {
          std::cout<<std::setiosflags(std::ios::left)<<"  "<<std::setw(5)<<i;
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(8)<<x<<std::setw(15)<<y<<std::setw(15)<<hSigmaStat->GetBinContent(i+1);
          std::cout<<std::setiosflags(std::ios::left)<<std::setw(15)<<eyl<<std::setw(15)<<eyh<<std::endl;
        }
    }
  hSigmaStat->Scale(fscale);
  if(verbose) std::cout<<std::endl;

  hSigmaStat->SetLineWidth(2);
  hSigmaStat->SetMarkerSize(1.5);//1
  hSigmaStat->SetMarkerStyle(pstyle);
  hSigmaStat->SetLineColor(pcolor);
  hSigmaStat->SetMarkerColor(pcolor);

  gaeCrossSyst->SetMarkerSize(1.5);//1
  gaeCrossSyst->SetMarkerStyle(pstyle);
  gaeCrossSyst->SetFillColor(1);
  gaeCrossSyst->SetFillStyle(0);
  gaeCrossSyst->SetLineWidth(2);
  gaeCrossSyst->SetLineColor(pcolor);
}

#endif
