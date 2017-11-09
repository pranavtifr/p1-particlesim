#include <iostream>
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
#include "classes/DelphesClasses.h"
#include "fastjet-analysis.cc"
namespace dataevents {
#include "event.C"
}

template <typename T>
void EventLoop(T &event,TH1 *e2,double *a)
{
   if (event.fChain == 0) return;
   Long64_t nentries = event.fChain->GetEntriesFast();
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     std::cout<<jentry<<std::endl;
     event.GetEntry(jentry);
     root_to_fastjet(event.Particle_Px,event.Particle_Py,event.Particle_Pz,event.Particle_E,event.Particle_Status,event.Particle_size,e2,a);
   //  std::cout<<jentry<<"    "<<std::endl;
   }
}


//Main Function
int main(){
  std::ifstream fjetin("settings-fastjet.txt");
  double a[4];
  fjetin>>a[0];
  fjetin>>a[1];
  fjetin>>a[2];
  fjetin>>a[3];
  std::ostringstream filename;
  std::string file;
  std::cout<<"SETTINGS:   "<<a[0]<<"_"<<a[1]<<"_"<<a[2]<<"_"<<a[3]<<".root"<<std::endl;
  filename<<"histos_"<<a[0]<<"_"<<a[1]<<"_"<<a[2]<<"_"<<a[3]<<".root";
  file = filename.str();
  TCanvas *c1= new TCanvas("c1","e2",600,400);
  TFile *f = new TFile(file.c_str(),"RECREATE");
  TH1* e2 = new TH1F("e2","e2 Title",50,0,14);
  dataevents::event t;
  EventLoop(t,e2,a);
  e2->Draw();
  f->WriteTObject(c1,"e2");
  //c1->Write("e2",TObject::kOverwrite);
}
