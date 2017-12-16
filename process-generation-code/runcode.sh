#!/bin/bash
rm events-*
if [ -f ../data/gluon_1e5_13tev-eflow.root ] ; then
  echo "Removing the preexisting root files"
  rm ../data/*-eflow.root
fi

hepgcc qgZ.cc
echo "Compiling Done"
mpiexec -np 2 ./a.out & 
sleep 2
cat ./events-0.dat | DelphesHepMC  ./delphes_mycard.tcl ../data/gluon_1e5_13tev-eflow.root &
cat ./events-1.dat | DelphesHepMC  ./delphes_mycard.tcl ../data/quark_1e5_13tev-eflow.root 
#cat ./events-2.dat | DelphesHepMC  ./delphes_mycard.tcl ../data/noth_1e5_13tev-eflow.root 
