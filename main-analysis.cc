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
#include "classes/DelphesClasses.h"
#include "fastjet-analysis.cc"
#include "mpi.h"
#define MASTER_MPI 0
namespace dataevents {
#include "event.C"
}

void add_to_hist(std::vector<float> e2_main,TH1 *e2_hist);
void hist_to_file(TH1 *e2,double *a);
template <typename T>
void EventLoop(T &event,std::vector<float> &e2,double *a,int &taskid,int &numtasks)
{
   if (event.fChain == 0) return;
   Long64_t nentries = event.fChain->GetEntriesFast();
   MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
   Long64_t chunksize = nentries/numtasks;
   //Care is not taken to take all the events. The events are equally distributed to the processes and the left over is discarded.
   for (Long64_t k = 0; k<chunksize;k++) {
     Long64_t jentry = (taskid*chunksize) +  k ;
     if(jentry%100 == 0){
     std::cout<<std::setw(15)<<"Gathering event  "<<std::setw(10)<<jentry<<std::setw(15)<<
         " in the process "<<std::setw(2)<<taskid<<std::setw(5)<<"("<<(k*100.0)/chunksize<<"% )"<<std::endl;}
     event.GetEntry(jentry);
     root_to_fastjet(event.Particle_Px,event.Particle_Py,event.Particle_Pz,event.Particle_E,event.Particle_Status,event.Particle_size,e2,a);
   //  std::cout<<jentry<<"    "<<std::endl;
   }

}


//Main Function
int main(){
   MPI_Init(NULL,NULL);
   int taskid,numtasks;
   MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
   MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
     std::ifstream fjetin("settings-fastjet.txt");
     double a[4];
     fjetin>>a[0];
     fjetin>>a[1];
     fjetin>>a[2];
     fjetin>>a[3];
   if(taskid == MASTER_MPI){
     std::cout<<"SETTINGS:   "<<a[0]<<"_"<<a[1]<<"_"<<a[2]<<"_"<<a[3]<<".root"<<std::endl;
   }
   std::vector<float> e2;
  dataevents::event t;
  EventLoop(t,e2,a,taskid,numtasks);
  if(taskid != MASTER_MPI){
    std::cout<<"Outgoing Size  :"<<e2.size()<<"From   :"<<taskid<<std::endl;
    MPI_Send(&e2.front(),e2.size(),MPI_FLOAT,MASTER_MPI,0,MPI_COMM_WORLD);
  }
  if(taskid == MASTER_MPI){
     std::vector<float> e2_main;
     e2_main = e2;
     for(int k=1;k<numtasks;k++){
       std::vector<float> e2_temp;
       int incoming_size;
       MPI_Status status;
       MPI_Probe(k,0,MPI_COMM_WORLD,&status);
       MPI_Get_count(&status,MPI_FLOAT,&incoming_size);
       std::cout<<"Incoming Size   :"<<incoming_size<<std::endl;
       e2_temp.resize(incoming_size);
       MPI_Recv(&e2_temp.front(),incoming_size,MPI_FLOAT,k,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
       e2_main.insert(e2_main.end(),e2_temp.begin(),e2_temp.end());
     }
     std::cout<<"Size of main    :"<<e2_main.size()<<std::endl;
     std::cout<<"Max Size of main    :"<<e2_main.max_size()<<std::endl;
     TH1 *e2_hist = new TH1F("e2","e2",50,0,14);
     add_to_hist(e2_main,e2_hist);
     hist_to_file(e2_hist,a);
  } 
  MPI_Finalize();
}

void add_to_hist(std::vector<float> e2_main,TH1 *e2_hist){
     for(int n=0;n<e2_main.size();n++){
       e2_hist->Fill(e2_main[n]);
     }
}


void hist_to_file(TH1 *e2_hist,double *a){
     std::ostringstream filename;
     filename<<"histos_"<<a[0]<<"_"<<a[1]<<"_"<<a[2]<<"_"<<a[3]<<".root";
     std::string file;
     file = filename.str();
     TFile *f = new TFile(file.c_str(),"RECREATE");
     TCanvas *c1= new TCanvas("c1","e2",600,400);
     e2_hist->Draw();
     f->WriteTObject(c1,"e2");
}
