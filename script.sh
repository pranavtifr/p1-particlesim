#!/bin/bash
for file in ./settings-fastjet/*.txt
do
  echo $file
  rm ./analysis-code/settings-fastjet.txt
  z_cut=$(sed '2!d' $file)
  beta=$(sed '3!d' $file)
  z=z
  detector=eflow
  folder=z$z_cut$z$beta
  echo $folder
  cp $file ./analysis-code/settings-fastjet.txt
  echo 'Changing to Analysis'
  cd ./analysis-code
  echo $PWD
  cat ./settings-fastjet.txt
  echo 'Running the Analysis code'
  ./running_code.sh
  echo 'Coming Back to the Main Directory'
  cd ..
  mkdir ./data_post_analysis/$detector/$folder
  echo 'Folder Created'
  cp ./plotting-code/*_1e6_13tev-eflow.* ./data_post_analysis/$detector/$folder/
  echo 'Change to Plotting Directory'
  cd ./plotting-code
  echo $PWD
  python ./histoviewer.py
  echo 'Histograms Plotted now loading images. THis might take a while'
  python ./imageviewer.py
  echo 'Images drawn'
  cd ..
  echo 'Coming Back to the Main Directory'
  mkdir ./plots/$detector/$folder
  cp ./plotting-code/histograms.png ./plots/$detector/$folder/
  cp ./plotting-code/jet-image.png ./plots/$detector/$folder/
  echo 'All images Moved'
  cp ./plotting-code/gluon_1e6_13tev-eflow.txt ./scikit-ml-code/gluon-phy.txt
  cp ./plotting-code/quark_1e6_13tev-eflow.txt ./scikit-ml-code/quark-phy.txt
  echo 'Change to Scikit directory'
  cd ./scikit-ml-code
  echo $PWD
  python ./random_forest.py
  cp roc_curve.png ../plots/$detector/$folder/
  echo 'ROC Curves plotted and Moved'
  cd ..
  cp ./plotting-code/quark_1e6_13tev-eflow.img ./tensorflow-code/quark.img
  cp ./plotting-code/gluon_1e6_13tev-eflow.img ./tensorflow-code/gluon.img

  cd ./tensorflow-code
  echo $PWD
  echo ' Now all tensorflow codes will run. This will be extremely slow. Go do something else'
  ./stash.sh
  cp *.png ../plots/$detector/$folder/
  echo 'Moved the Tensorflow Stuff'
  cd ..
  echo $PWD
  echo 'Done one Iteration'
done

echo 'Done'
