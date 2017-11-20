#!/bin/bash
if [ -f "event.root" ]; then 
  echo "Event files and classes already exist.. Removing them"
  rm event.*
fi

for f in ~/work-stuff/data/*_1e5_13tev.root
do
  echo "$f"
  ln -s $f ./event.root
  sleep 5
  MakeClass event.root
  hepgcc main-analysis.cc
  mpiexec -np 16 ./a.out
  mv histos_2_0.2_2_500.root ../plots/tau/$(basename "$f")
  rm event.*
done
root -l root_code.C
echo "removing root_files.."
rm ../plots/tau/*
display plot.png
echo "moving plots"
mv plot.png ../plots/girth.png
echo "Done"
