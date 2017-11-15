#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TChain.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TObject.h"
// Make sure that the first one is the signal and the second one is the background
int draw_roc_curve(TH1 *hist1,TH1 *hist2,TH1 *result){
  if(hist1->GetNbinsX() != hist2->GetNbinsX()){
    std::cout<<"Bin number mismatch ! Can't compare"<<std::endl;
    return -1;
  }
  int binx = hist1->GetNbinsX();
  TH1* result(hist1);
  result->Reset();
  for(int i=1;i<binx;i++){
    double c1=0;
    double c2=0;
    for(int k=i;k<binx;i++){
      c1+= hist1->GetBinContent(k);
      c2+= hist2->GetBinContent(k);
    }
    result->Fill(c1/(c2+ 1e-15));
  }
  return 1;
}

