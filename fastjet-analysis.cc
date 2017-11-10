#include <fstream>
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
void root_to_fastjet(Float_t *px,Float_t *py,Float_t *pz,Float_t *e,Int_t *particle_status,
        Int_t n_event_size ,std::vector<float> &e2,double *a){
  std::ifstream fjetin("settings-fastjet.txt");
  double alpha = a[0];
  double z_cut = a[1];
  double beta  = a[2];
  double ptcutoff = a[3];
  std::vector <fastjet::PseudoJet> fjInputs;
  double Rparam = 0.4;
  fastjet::Strategy               strategy = fastjet::Best;
  fastjet::RecombinationScheme    recombScheme = fastjet::E_scheme;
  fastjet::JetDefinition jetDef = fastjet::JetDefinition(fastjet::kt_algorithm, Rparam,
                                      recombScheme, strategy);

    // Reset Fastjet input
    fjInputs.resize(0);
    // Loop over event record to decide what to pass to FastJet
    for (int i = 0; i < n_event_size; ++i) {
      // Store as input to Fastjet
      if(particle_status[i] == 1){
      fjInputs.push_back( fastjet::PseudoJet( px[i],py[i],pz[i],e[i]));
    }

    if (fjInputs.size() == 0) {
      std::cout << "Error: event with no final state particles" << std::endl;
      continue;
    }

    // Run Fastjet algorithm
    fastjet::ClusterSequence clustSeq(fjInputs, jetDef);

    // For the first event, print the FastJet details
    if (false) {
      std::cout<<"FastJet Details"<<std::endl;
      std::cout << "Ran " << jetDef.description() << std::endl;
      std::cout << "Strategy adopted by FastJet was "
                << clustSeq.strategy_string() << std::endl << std::endl;
      //fj = false;
    }
    std::vector<fastjet::PseudoJet> jets = fastjet::sorted_by_pt(clustSeq.inclusive_jets(0.0));
  
  fastjet::contrib::SoftDrop sd(beta, z_cut);
  //std::cout << "SoftDrop groomer is: " << sd.description() << std::endl;

  std::vector<fastjet::PseudoJet> soft_jets_temp;
  for (unsigned ijet = 0; ijet < jets.size(); ijet++) {
    // Run SoftDrop and examine the output
    fastjet::PseudoJet sd_jet = sd(jets[ijet]);
    
    assert(sd_jet != 0); //because soft drop is a groomer (not a tagger), it should always return a soft-dropped jet
    soft_jets_temp.push_back(sd_jet); 
    /*
    if(iEvent% print_freq == 0 ){
    std::cout << "original    jet: " << jets[ijet].E()<<","<<jets[ijet].px() <<","<< jets[ijet].py()<<"," <<jets[ijet].pz() <<std::endl;
    std::cout << "soft  jet: " <<sd_jet.E()<<","<<sd_jet.px() <<","<< sd_jet.py()<<"," <<sd_jet.pz() <<std::endl;
    std::cout << "  delta_R between subjets: " << sd_jet.structure_of<fastjet::contrib::SoftDrop>().delta_R() << std::endl;
    std::cout << "  symmetry measure(z):     " << sd_jet.structure_of<fastjet::contrib::SoftDrop>().symmetry() << std::endl;
    std::cout << "  mass drop(mu):           " << sd_jet.structure_of<fastjet::contrib::SoftDrop>().mu() << std::endl;
    }
    */
    //Softdrop loop
  }
// Calculating e_2
  std::vector<fastjet::PseudoJet> soft_jets = fastjet::sorted_by_pt(soft_jets_temp);
  double e_2 = 0;
  for( unsigned ijet = 0; ijet < soft_jets.size();ijet++){
    if(soft_jets[ijet].pt() < ptcutoff) continue;
    e_2 = 0;
    std::vector<fastjet::PseudoJet> constituents = soft_jets[ijet].constituents();
    for( unsigned iconst = 0;iconst < constituents.size();iconst++){
    e_2 += constituents[iconst].pt()/soft_jets[ijet].pt() * pow(soft_jets[ijet].delta_R(constituents[iconst])/Rparam,alpha);
    }
   e2.push_back(-log(e_2));
  }//Jet Constituent Loop 
 }//Event Loop
}//Function Ends here

