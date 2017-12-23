#!/bin/bash
if [ -f "event.root" ]; then 
  echo "Event files and classes already exist.. Removing them"
  rm event.*
fi

for f in ~/work-stuff/data/*_1e6_13tev-eflow.root
do
  echo "$f"
  ln -s $f ./event.root
  echo "Files Linked"
  sleep 5
  MakeClass event.root
  echo "Class Made"
  hepgcc main-analysis.cc
  echo "Compiled"
  mpiexec -np 16 ./a.out
  filename=$(basename "$f")
  #mv histos_2_0.2_2_500.root ../plots/tau/$filename
  ext='.txt'
  img='.img'
  filename="${filename%.*}"
  txtname=$filename$ext
  imgname=$filename$img
  mv data.txt ../plotting-code/$txtname
  mv images.txt ../plotting-code/$imgname
  rm event.*
done
echo "Running Code Done"
#root -l root_code.C
#echo "removing root_files.."
#rm ../plots/tau/*
#display plot.png
#echo "moving plots"
#mv plot.png ../plots/tau-eflow.png
#echo "Done"
