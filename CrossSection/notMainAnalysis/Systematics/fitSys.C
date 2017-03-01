#include <TGraph.h>
#include <TF1.h>

void fitSys(char *infname = "background_PbPb.dat")
{
  TGraph *g = new TGraph(infname);
  TF1 *f = new TF1("f","[0]+[1]/(x)+[2]/x/x+[3]*x");
  g->Draw("ap");
  g->Fit("f");
  g->Fit("f");
  g->Fit("f");
}
