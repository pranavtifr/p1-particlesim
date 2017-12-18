#!/bin/bash
z_cut=0.05
beta=0
z=z
detector=genparticle
folder=z$z_cut$z$beta
echo $folder
echo 'Changing to Analysis'
cd ./analysis-code
cat ./settings-fastjet.txt
echo 'Running the Analysis code'
./running_code.sh
echo 'Coming Back to the Main Directory'
cd ..
mkdir ./data_post_analysis/$detector/$folder
echo 'Folder Created'
cp ./plotting-code/*_1e5_13tev-eflow.* ./data_post_analysis/$detector/$folder/
echo 'Change to Plotting Directory'
cd ./plotting-code
python ./histoviewer.py
cd ..
echo 'Coming Back to the Main Directory'
mkdir ./plots/$detector/$folder
cp ./plotting-code/histograms.png ./plots/$detector/$folder/
echo 'Histograms plotted and Moved'
cp ./plotting-code/gluon_1e5_13tev-eflow.txt ./scikit-ml-code/gluon-phy.txt
cp ./plotting-code/quark_1e5_13tev-eflow.txt ./scikit-ml-code/quark-phy.txt
echo 'Change to Scikit directory'
cd ./scikit-ml-code
python ./random_forest.py
cp roc_curve.png ../plots/$detector/$folder/
echo 'ROC Curves plotted and Moved'
cd ..
echo 'DONE!'
