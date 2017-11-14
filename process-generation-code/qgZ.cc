/*
 *
 */

#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC2.h"
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"

using namespace Pythia8;

int main() {
  // HepMC Stuff
  HepMC::Pythia8ToHepMC ToHepMC;
  HepMC::IO_GenEvent ascii_io("events.dat",std::ios::out);

  // Histogram
  Hist e2("E_2 Histogram",100,0.,1.);
  // Settings
const double ptmin = 0;
  // Generator
  Pythia pythia;
  int print_freq = 100;
  pythia.readFile("settings-qgZ.cmnd");
   int nEvent = pythia.mode("Main:numberOfEvents");
     
  pythia.init();

  // Begin event loop. Generate event. Skip if error.
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
     if(iEvent % print_freq == 0) cout<<"iEvent = "<<iEvent<<endl;
    if (!pythia.next()) continue;

    int idxW = -1;
    for (int i = pythia.event.size() - 1; i > 0; i--) {
      if (pythia.event[i].idAbs() == 23) {
        idxW = i;
        break;
      }
    }
    if (idxW == -1) {
      cout << "Error: Could not find Z" << endl;
      continue;
    }

 //Allocate this dynamically if the events tend to be huge 
    HepMC::GenEvent *hepmcevent = new HepMC::GenEvent();
    ToHepMC.fill_next_event(pythia,hepmcevent);
    // The Following Commented Code is to store it in fastjet arrays
 /* 
    // Reset Fastjet input
    fjInputs.resize(0);

    // Loop over event record to decide what to pass to FastJet
    for (int i = 0; i < pythia.event.size(); ++i) {
      // Final state only
      if (!pythia.event[i].isFinal())        continue;

      // Store as input to Fastjet
      fjInputs.push_back( fastjet::PseudoJet( pythia.event[i].px(),
        pythia.event[i].py(), pythia.event[i].pz(), pythia.event[i].e() ) );
    }

    if (fjInputs.size() == 0) {
      cout << "Error: event with no final state particles" << endl;
      continue;
    }

    // Run Fastjet algorithm
    fastjet::ClusterSequence clustSeq(fjInputs, jetDef);

    // For the first event, print the FastJet details
    if (fj) {
      cout<<"FastJet Details"<<endl;
      cout << "Ran " << jetDef.description() << endl;
      cout << "Strategy adopted by FastJet was "
           << clustSeq.strategy_string() << endl << endl;
      fj = false;
    }
  vector<fastjet::PseudoJet> jets = fastjet::sorted_by_pt(clustSeq.inclusive_jets(ptmin));
  
  double z_cut = 0.10;
  double beta  = 1.0;
  fastjet::contrib::SoftDrop sd(beta, z_cut);
  //cout << "SoftDrop groomer is: " << sd.description() << endl;

  vector<fastjet::PseudoJet> soft_jets_temp;
  for (unsigned ijet = 0; ijet < jets.size(); ijet++) {
    // Run SoftDrop and examine the output
    fastjet::PseudoJet sd_jet = sd(jets[ijet]);
    
    assert(sd_jet != 0); //because soft drop is a groomer (not a tagger), it should always return a soft-dropped jet
    soft_jets_temp.push_back(sd_jet); 
    if(iEvent% print_freq == 0 && false){
    cout << "original    jet: " << jets[ijet].E()<<","<<jets[ijet].px() <<","<< jets[ijet].py()<<"," <<jets[ijet].pz() <<endl;
    cout << "soft  jet: " <<sd_jet.E()<<","<<sd_jet.px() <<","<< sd_jet.py()<<"," <<sd_jet.pz() <<endl;
    cout << "  delta_R between subjets: " << sd_jet.structure_of<fastjet::contrib::SoftDrop>().delta_R() << endl;
    cout << "  symmetry measure(z):     " << sd_jet.structure_of<fastjet::contrib::SoftDrop>().symmetry() << endl;
    cout << "  mass drop(mu):           " << sd_jet.structure_of<fastjet::contrib::SoftDrop>().mu() << endl;
    }
    //Softdrop loop
  }
// Calculating e_2
  vector<fastjet::PseudoJet> soft_jets = fastjet::sorted_by_pt(soft_jets_temp);
double e_2 = 0;
 for( unsigned ijet = 0; ijet < soft_jets.size();ijet++){
   e_2 = 0;
   vector<fastjet::PseudoJet> constituents = soft_jets[ijet].constituents();
   for( unsigned iconst = 0;iconst < constituents.size();iconst++){
    e_2 += constituents[iconst].pt()/soft_jets[ijet].pt() * pow(soft_jets[ijet].delta_R(constituents[iconst])/Rparam,2);
   }
   e2.fill(e_2);
 } 
 */
ascii_io<<hepmcevent;
//cout<<hepmcevent;
 delete hepmcevent;
 //Event loop done
  }

  pythia.stat();
cout<<e2;
//e2.table("e2_quarks_with_MPI.txt");
  // Done.
  return 0;
}
