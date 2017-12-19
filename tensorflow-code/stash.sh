#!/bin/bash
f='cnn-'
file1='neural_'
ext='.png'
python networktrain.py
mv roc_curve.png ./$file1$f$ext
echo 'CNN done'

f='maxout-'
python networktrain2.py
mv roc_curve.png ./$file1$f$ext
echo 'Maxout done'

f='relu-'
python networktrain3.py
mv roc_curve.png ./$file1$f$ext
echo 'ReLU done'
