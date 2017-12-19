#include <fstream>
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
#include "fastjet/contrib/Njettiness.hh"
#include "fastjet/contrib/NjettinessPlugin.hh"
#include "fastjet/contrib/Nsubjettiness.hh"
#define RES 56 //Image resolution
#define PI 3.1415
#define RANGE 0.5
double girth(fastjet::PseudoJet this_jet);
double Nsubjet(fastjet::PseudoJet this_jet);
double e_alpha(fastjet::PseudoJet this_jet,double Rparam,double alpha);
int count(fastjet::PseudoJet jet);
double two_point_moment(fastjet::PseudoJet this_jet);
void jet_imagemaker(fastjet::PseudoJet jet){
  std::vector<fastjet::PseudoJet> jetconst = fastjet::sorted_by_pt(jet.constituents());
  double image[RES*RES];
  for(int i=0;i<RES;i++){
    for(int j=0;j<RES;j++){
      image[i*RES+ j] = 0;
    }
  }
 
  image[(RES/2)*RES + RES/2] = jetconst[0].pt();
  for(int k=1;k<jetconst.size();k++){
    int i = RES/2 +  int((jetconst[k].eta() - jetconst[0].eta() )/RANGE*RES);
    int j = RES/2 + int((jetconst[k].phi_std() - jetconst[0].phi_std() )/RANGE*RES);
    if( i >= 0 && j >=0 && i<RES && j<RES ){
      image[i*RES + j] += jetconst[k].pt();
    }
    else{
      continue;}
  }
  std::ofstream f("images.txt",std::ios::app); 
  for(int i=0;i<RES;i++){
  for(int j=0;j<RES;j++){
    f<<image[i*RES + j]<<"\t";
  }
  }
  f<<std::endl;

}
void root_to_fastjet(Float_t *px,Float_t *py,Float_t *pz,Float_t *e,Int_t *particle_status,Int_t *particle_PID,
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
  //fastjet::RecombinationScheme    recombScheme = fastjet::WTA_pt_scheme;
  fastjet::JetDefinition jetDef = fastjet::JetDefinition(fastjet::antikt_algorithm, Rparam,
                                      recombScheme, strategy);

    // Reset Fastjet input
    fjInputs.resize(0);
    // Loop over event record to decide what to pass to FastJet
    for (int i = 0; i < n_event_size; ++i) {
      // Store as input to Fastjet
      if((particle_status[i] == 1)&&(std::abs(particle_PID[i]) != 13) ){
      fjInputs.push_back( fastjet::PseudoJet( px[i],py[i],pz[i],e[i]));
    }
   }//Event Loop
    if (fjInputs.size() == 0) {
      std::cout << "Error: event with no final state particles" << std::endl;
      return;
    }

    // Run Fastjet algorithm
    fastjet::ClusterSequence clustSeq(fjInputs, jetDef);

    // For the first event, print the FastJet details
    if (false) {
      std::cout<<"FastJet Details"<<std::endl;
      std::cout << "Ran " << jetDef.description() << std::endl;
      std::cout << "Strategy adopted by FastJet was "
                << clustSeq.strategy_string() << std::endl << std::endl;
    }
    std::vector<fastjet::PseudoJet> jets = fastjet::sorted_by_pt(clustSeq.inclusive_jets(0.0));
  
  fastjet::contrib::SoftDrop sd(beta, z_cut);
  //std::cout << "SoftDrop groomer is: " << sd.description() << std::endl;

  std::vector<fastjet::PseudoJet> soft_jets_temp;
  for (unsigned ijet = 0; ijet < jets.size(); ijet++) {
    // Run SoftDrop and examine the output
    fastjet::PseudoJet sd_jet = sd(jets[ijet]);
    assert(sd_jet != 0);
    soft_jets_temp.push_back(sd_jet); 
    //Softdrop loop
  }
// Calculating e_2
  // Reclustering  Params
  /*Rparam = 0.8;
  strategy = fastjet::Best;
  recombScheme = fastjet::WTA_pt_scheme;
  jetDef = fastjet::JetDefinition(fastjet::cambridge_algorithm, Rparam,
                                      recombScheme, strategy);
   fastjet::ClusterSequence clustSeq2(soft_jets_temp, jetDef);
  std::vector<fastjet::PseudoJet> soft_jets = fastjet::sorted_by_pt(clustSeq2.inclusive_jets(0.0));
  */
   std::vector<fastjet::PseudoJet> soft_jets = fastjet::sorted_by_pt(soft_jets_temp);
  double e_2 = 42; //Angularity
  double tau = 42; //Subjettiness
  double g = 42; //Girth
  int cnt =0; //Count
  double m = 0;//Mass
  double m2p = 0;//Two Point Moment
  for( unsigned ijet = 0; ijet < soft_jets.size();ijet++){
    if(soft_jets[ijet].pt() < ptcutoff) continue;
    //if((soft_jets[ijet].m() < 100) && (soft_jets[ijet].m() > 80)) continue;
    jet_imagemaker(soft_jets[ijet]);
     e_2 = e_alpha(soft_jets[ijet],Rparam,alpha);
     tau = Nsubjet(soft_jets[ijet]);
     g = girth(soft_jets[ijet]);
      cnt = count(soft_jets[ijet]); 
      m = soft_jets[ijet].m();
      m2p = two_point_moment(soft_jets[ijet]);

     if(!std::isfinite(-log(e_2))) break;
     if(!std::isfinite(-log(tau))) break;
     if(!std::isfinite(-log(g))) break;
     if(!std::isfinite(m)) break;
     if(!std::isfinite(m2p)) break;
      
      e2.push_back(-log(e_2));
      e2.push_back(-log(tau));
      e2.push_back(-log(g));
      e2.push_back(cnt);
      e2.push_back(m);
      e2.push_back(m2p);
     break;
  }//Jet Constituent Loop 
}//Function Ends here

double two_point_moment(fastjet::PseudoJet this_jet){
    std::vector<fastjet::PseudoJet> constituents = this_jet.constituents();
    double m2p = 4;
    double beta = 0.2;
    double R = 0.6;
    for( unsigned iconst = 0;iconst < constituents.size();iconst++){
      for( unsigned jconst = 0;jconst < constituents.size();jconst++){
        m2p += constituents[iconst].pt()*constituents[jconst].pt()*pow(constituents[iconst].delta_R(constituents[jconst]),beta);
      }
    }
    m2p /= pow(this_jet.pt(),2);
    return m2p;
}
int count(fastjet::PseudoJet this_jet){
    std::vector<fastjet::PseudoJet> constituents = this_jet.constituents();
    return constituents.size();
}

double e_alpha(fastjet::PseudoJet this_jet,double Rparam,double alpha){
    double e_2 = 0;
    std::vector<fastjet::PseudoJet> constituents = this_jet.constituents();
    for( unsigned iconst = 0;iconst < constituents.size();iconst++){
    e_2 += constituents[iconst].pt()/this_jet.pt() * pow(this_jet.delta_R(constituents[iconst])/Rparam,alpha);
    }
    return e_2;
}

double Nsubjet(fastjet::PseudoJet this_jet){
  double beta = 0.5;
  //fastjet::contrib::Nsubjettiness nSub1_beta1(2,fastjet::contrib::MultiPass_Axes(100), fastjet::contrib::UnnormalizedMeasure(beta));
  fastjet::contrib::Nsubjettiness nSub1_beta1(2,fastjet::contrib::MultiPass_Axes(100), fastjet::contrib::NormalizedMeasure(beta,0.6));
  double  tau =  nSub1_beta1(this_jet);
  return tau;
}

double girth(fastjet::PseudoJet this_jet){
    return e_alpha(this_jet,1,1); 
}
