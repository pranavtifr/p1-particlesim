#include "mpi.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC2.h"

using namespace Pythia8;

int main() {
  MPI_Init(NULL,NULL);
  int taskid,numtasks;
  MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
  MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

  // HepMC Stuff
 
  HepMC::Pythia8ToHepMC ToHepMC;
  //Process Specific Settings Files
  std::ostringstream filename;
  filename<<"events-"<<taskid<<".dat";
  std::string file;
  file = filename.str();
  mkfifo(file.c_str(),0666);
  HepMC::IO_GenEvent ascii_io(file.c_str(),std::ios::out);
  
  std::ostringstream setfilename;
  setfilename<<"settings-"<<taskid<<".cmnd";
  std::string file2;
  file2 = setfilename.str();

  //Process Specific Settings Files

  // Histogram
  // Generator
  Pythia pythia;
  int print_freq = 100;
  pythia.readFile(file2.c_str());
   int nEvent = pythia.mode("Main:numberOfEvents");
     
  pythia.init();

  // Begin event loop. Generate event. Skip if error.
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
     if(iEvent % print_freq == 0) cout<<"iEvent = "<<iEvent<<"   From    "<<taskid<<"     ("<<1.0*iEvent/nEvent<<")"<<endl;
    if (!pythia.next()) continue;


 //Allocate this dynamically if the events tend to be huge 
    HepMC::GenEvent *hepmcevent = new HepMC::GenEvent();
    ToHepMC.fill_next_event(pythia,hepmcevent);
    ascii_io<<hepmcevent;
    delete hepmcevent;
 //Event loop done
  }
  if(taskid == 0){ pythia.stat();}
  //unlink(file.c_str());
  MPI_Finalize();
  return 0;
}
