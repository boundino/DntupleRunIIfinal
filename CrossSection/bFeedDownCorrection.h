#include <TF1.h>

// Yen-Jie: B feeddown fraction

float bFeedDownCorrection(double pt, bool isPbPb, Float_t centmax=100)
{
  const int nptbins = 14;
  float ptbins[nptbins+1] = {2.,3.,4.,5.,6.,8.,10.,12.5,15.,20.,25.,30.,40.,60.,100.};
  int i=0;
  for(i=0;i<nptbins;i++)
    {
      if(pt>ptbins[i]&&pt<ptbins[i+1]) break;
    }
  if(i>=nptbins) return -1.;

  float val = -1.;
  float pfPP[nptbins] = {0.941776, 0.882223, 0.864745, 0.861659, 0.815929, 0.845055, 0.828901, 0.795887, 0.811673, 0.81499, 0.786084, 0.87234, 0.813225, 0.786747};
  float pfPbPb0100[nptbins] = {0.901768, 0.901768, 0.793895, 0.800215, 0.83203, 0.698313, 0.769196, 0.83085, 0.783632, 0.824826, 0.86682, 0.882473, 0.869404, 0.855763};
  float pfPbPb010[nptbins] = {0.939776, 0.939776, 0.866009, 0.668924, 0.597556, 0.630471, 0.766717, 0.782234, 0.767276, 0.762872, 0.89974, 0.809394, 0.904406, 0.831586};
  if(!isPbPb) val = pfPP[i];
  else
    {
      if(centmax==100) val = pfPbPb0100[i];
      else if(centmax==10) val = pfPbPb010[i];
    }

  return val;
}
