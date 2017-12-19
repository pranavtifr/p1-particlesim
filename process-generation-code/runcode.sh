#!/bin/bash
rm events-*
if [ -f ../data/gluon_1e6_13tev-eflow.root ] ; then
  echo "Removing the preexisting root files"
  rm ../data/*1e6_13tev-eflow.root
fi

hepgcc qgZ.cc
echo "Compiling Done"
mpiexec -np 2 ./a.out & 
sleep 2
cat ./events-0.dat | DelphesHepMC  ./delphes_mycard.tcl ../data/gluon_1e6_13tev-eflow.root &
cat ./events-1.dat | DelphesHepMC  ./delphes_mycard.tcl ../data/quark_1e6_13tev-eflow.root 
