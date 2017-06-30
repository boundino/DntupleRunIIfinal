#ifndef _FITDTOYMC_H_
#define _FITDTOYMC_H_

#include "uti.h"
#include "fitDdraw.h"

#define MAX_XB       20000
#define MAX_MUON     10000
#define MAX_TRACK    6000
#define MAX_GEN      6000
#define MAX_BX       150
#define MAX_Vertices 4000
#define MAX_TRIGGER  30

int     Dsize;
float   PVz;
float   Dmass[MAX_XB];
float   Dpt[MAX_XB];
float   Dy[MAX_XB];
float   Dchi2cl[MAX_XB];
float   Dalpha[MAX_XB];
float   DsvpvDistance[MAX_XB];
float   DsvpvDisErr[MAX_XB];
float   DlxyBS[MAX_XB];
float   DlxyBSErr[MAX_XB];
float   Dtrk1Pt[MAX_XB];
float   Dtrk2Pt[MAX_XB];
float   Dtrk1Eta[MAX_XB];
float   Dtrk2Eta[MAX_XB];
float   Dtrk1PtErr[MAX_XB];
float   Dtrk2PtErr[MAX_XB];
bool    Dtrk1highPurity[MAX_XB];
bool    Dtrk2highPurity[MAX_XB];
float   Dgen[MAX_XB];

void setDbranchaddress(TTree* nt)
{
  nt->SetBranchStatus("*", 0);
  nt->SetBranchStatus("Dsize", 1);
  nt->SetBranchStatus("PVz", 1);
  nt->SetBranchStatus("Dmass", 1);
  nt->SetBranchStatus("Dpt", 1);
  nt->SetBranchStatus("Dy", 1);
  nt->SetBranchStatus("Dchi2cl", 1);
  nt->SetBranchStatus("Dalpha", 1);
  nt->SetBranchStatus("DsvpvDistance", 1);
  nt->SetBranchStatus("DsvpvDisErr", 1);
  nt->SetBranchStatus("DlxyBS", 1);
  nt->SetBranchStatus("DlxyBSErr", 1);
  nt->SetBranchStatus("Dtrk1Pt", 1);
  nt->SetBranchStatus("Dtrk2Pt", 1);
  nt->SetBranchStatus("Dtrk1Eta", 1);
  nt->SetBranchStatus("Dtrk2Eta", 1);
  nt->SetBranchStatus("Dtrk1PtErr", 1);
  nt->SetBranchStatus("Dtrk2PtErr", 1);
  nt->SetBranchStatus("Dtrk1highPurity", 1);
  nt->SetBranchStatus("Dtrk2highPurity", 1);
  nt->SetBranchStatus("Dgen", 1);

  nt->SetBranchAddress("Dsize", &Dsize);
  nt->SetBranchAddress("PVz", &PVz);
  nt->SetBranchAddress("Dmass", Dmass);
  nt->SetBranchAddress("Dpt", Dpt);
  nt->SetBranchAddress("Dy", Dy);
  nt->SetBranchAddress("Dchi2cl", Dchi2cl);
  nt->SetBranchAddress("Dalpha", Dalpha);
  nt->SetBranchAddress("DsvpvDistance", DsvpvDistance);
  nt->SetBranchAddress("DsvpvDisErr", DsvpvDisErr);
  nt->SetBranchAddress("DlxyBS", DlxyBS);
  nt->SetBranchAddress("DlxyBSErr", DlxyBSErr);
  nt->SetBranchAddress("Dtrk1Pt", Dtrk1Pt);
  nt->SetBranchAddress("Dtrk2Pt", Dtrk2Pt);
  nt->SetBranchAddress("Dtrk1Eta", Dtrk1Eta);
  nt->SetBranchAddress("Dtrk2Eta", Dtrk2Eta);
  nt->SetBranchAddress("Dtrk1PtErr", Dtrk1PtErr);
  nt->SetBranchAddress("Dtrk2PtErr", Dtrk2PtErr);
  nt->SetBranchAddress("Dtrk1highPurity", Dtrk1highPurity);
  nt->SetBranchAddress("Dtrk2highPurity", Dtrk2highPurity);
  nt->SetBranchAddress("Dgen", Dgen);
}

//
int     Gsize;
float   Gy[MAX_GEN];
float   Gpt[MAX_GEN];
int     GisSignal[MAX_GEN];

void setGenbranchaddress(TTree* nt)
{
  nt->SetBranchAddress("Gsize", &Gsize);
  nt->SetBranchAddress("Gy", Gy);
  nt->SetBranchAddress("Gpt", Gpt);
  nt->SetBranchAddress("GisSignal", GisSignal);
}

//
int   pBeamScrapingFilter;
int   pPAprimaryVertexFilter;
int   pclusterCompatibilityFilter;
int   pprimaryVertexFilter;
int   phfCoincFilter3;

void setSkimbranchaddress(TTree* nt)
{
  nt->SetBranchStatus("*",0);
  if(collisionsystem=="PP" || collisionsystem=="PPMB")
    {
      nt->SetBranchStatus("pBeamScrapingFilter", 1);
      nt->SetBranchStatus("pPAprimaryVertexFilter", 1);
      nt->SetBranchAddress("pBeamScrapingFilter", &pBeamScrapingFilter);
      nt->SetBranchAddress("pPAprimaryVertexFilter", &pPAprimaryVertexFilter);
    }
  else if(collisionsystem=="PbPb" || collisionsystem=="PbPbMB")
    {
      nt->SetBranchStatus("pclusterCompatibilityFilter", 1);
      nt->SetBranchStatus("pprimaryVertexFilter", 1);
      nt->SetBranchStatus("phfCoincFilter3", 1);
      nt->SetBranchAddress("pclusterCompatibilityFilter", &pclusterCompatibilityFilter);
      nt->SetBranchAddress("pprimaryVertexFilter", &pprimaryVertexFilter);
      nt->SetBranchAddress("phfCoincFilter3", &phfCoincFilter3);
    }
  else
    {
      std::cout<<"  error: invalid collisionsystem value - setSkimbranchaddress()"<<std::endl;
    }
}

//
int   hiBin;

void setHibranchaddress(TTree* nt)
{
  nt->SetBranchStatus("*", 0);
  nt->SetBranchStatus("hiBin", 1);
  nt->SetBranchAddress("hiBin", &hiBin);
}

//
bool pass_selections(int j)
{
  bool ifpass = false;
  if(abs(PVz)<15 && 
     Dtrk1highPurity[j] && Dtrk2highPurity[j] &&  abs(Dtrk1Eta[j])<1.5 && abs(Dtrk2Eta[j])<1.5 && Dtrk1PtErr[j]/Dtrk1Pt[j]<0.3 && Dtrk2PtErr[j]/Dtrk2Pt[j]<0.3 &&
     (DlxyBS[j]/DlxyBSErr[j])>2.5 && Dy[j]>-1. && Dy[j]<1.)
    {
      if(collisionsystem=="PP" && 
         Dtrk1Pt[j]>2.0 && Dtrk2Pt[j]>2.0 &&
         Dalpha[j]<0.12 &&
         (DsvpvDistance[j]/DsvpvDisErr[j])>3.5 && Dchi2cl[j]>0.05) ifpass = true;
      if(collisionsystem=="PbPb" &&
         Dtrk1Pt[j]>8.5 && Dtrk2Pt[j]>8.5 &&
         Dalpha[j]<0.12 && 
         ((Dpt[j]>20 && Dpt[j]<25 && (DsvpvDistance[j]/DsvpvDisErr[j])>3.25 && Dchi2cl[j]>0.054) ||
          (Dpt[j]>25 && (DsvpvDistance[j]/DsvpvDisErr[j])>2.97 && Dchi2cl[j]>0.050))) ifpass = true;
      if((collisionsystem=="PPMB" || collisionsystem=="PbPbMB") &&
         Dtrk1Pt[j]>1.0 && Dtrk2Pt[j]>1.0 && 
         Dalpha[j]<0.12 &&
         ((Dpt[j]>1 && Dpt[j]<2 && (DsvpvDistance[j]/DsvpvDisErr[j])>6.0 && Dchi2cl[j]>0.25) ||
          (Dpt[j]>2 && Dpt[j]<3 && (DsvpvDistance[j]/DsvpvDisErr[j])>4.62 && Dchi2cl[j]>0.161) ||
          (Dpt[j]>3 && Dpt[j]<4 && (DsvpvDistance[j]/DsvpvDisErr[j])>4.80 && Dchi2cl[j]>0.197) ||
          (Dpt[j]>4 && Dpt[j]<5 && (DsvpvDistance[j]/DsvpvDisErr[j])>4.63 && Dchi2cl[j]>0.141) ||
          (Dpt[j]>5 && Dpt[j]<6 && (DsvpvDistance[j]/DsvpvDisErr[j])>4.53 && Dchi2cl[j]>0.172) ||
          (Dpt[j]>6 && Dpt[j]<8 && (DsvpvDistance[j]/DsvpvDisErr[j])>4.09 && Dchi2cl[j]>0.120) ||
          (Dpt[j]>8 && Dpt[j]<10 && (DsvpvDistance[j]/DsvpvDisErr[j])>4.02 && Dchi2cl[j]>0.098) ||
          (Dpt[j]>10 && Dpt[j]<12.5 && (DsvpvDistance[j]/DsvpvDisErr[j])>3.66 && Dchi2cl[j]>0.099) ||
          (Dpt[j]>12.5 && Dpt[j]<15 && (DsvpvDistance[j]/DsvpvDisErr[j])>3.70 && Dchi2cl[j]>0.084) ||
          (Dpt[j]>15 && Dpt[j]<20 && (DsvpvDistance[j]/DsvpvDisErr[j])>3.53 && Dchi2cl[j]>0.047) ||
          (Dpt[j]>20 && Dpt[j]<25 && (DsvpvDistance[j]/DsvpvDisErr[j])>3.25 && Dchi2cl[j]>0.054) ||
          (Dpt[j]>25 && (DsvpvDistance[j]/DsvpvDisErr[j])>2.97 && Dchi2cl[j]>0.050))) ifpass = true;
    }
  return ifpass;
}


#endif
