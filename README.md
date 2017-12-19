# Pythia Settings
 The processes chosen were 


![](http://latex.codecogs.com/svg.latex?q%20&plus;%20%5Cbar%7Bq%7D%20%5Crightarrow%20Z%20&plus;%20g)
and,

![](http://latex.codecogs.com/svg.latex?q%20&plus;%20g%20%5Crightarrow%20Z%20&plus;%20q)

More details on the settings can be seen ![Here](./process-generation-code/settings-qgZ.cmnd)
Number of Events = 10000
# FastJet Settings
These plots were produced after the events are generated in pythia and then
clustered into jets using anti-kt algorithm using E-Scheme
# Jet Variables
## Grooming
   The jets were groomed using Soft-Drop algorithm

### E_2
  This was the formula used for the Calculating e2
  

![](http://latex.codecogs.com/svg.latex?e_2%20%3D%20%5CSigma_%7Bj%20%5Cin%20jet%7D%20z_i%20%5Ctheta_i%5E2)


Where,


![](http://latex.codecogs.com/svg.latex?z_i%20%5Cequiv%20%5Cfrac%7Bp_%7BTi%7D%7D%7B%5CSigma_%7Bj%20%5Cin%20jet%7D%20p_%7BTj%7D%20%7D%5Cquad%20%5Ctheta_i%20%3D%5Cfrac%7B%20R_%7Bi%20%5Chat%7Bn%7D%7D%7D%7BR%7D)


Reference for the formula of e_2 [[https://arxiv.org/pdf/1704.03878.pdf]]

### Girth
 The Formula for Girth

![](http://latex.codecogs.com/svg.latex?g%20%3D%20%5Csum%5Climits_%7B%20i%20%5Cin%20jet%7D%20%5Cfrac%7Bp_T%5Ei%7D%7Bp_T%5E%7Bjet%7D%7Dr_i)

We can see this is the same as the formula for e_alpha with alpha = 1 and R = 1

### Subjettiness
 Tau was calcualted using the routine from fastjet contrib
Subjettiness Normalized with Jet size of 0.6 and Beta = 0.5

### Mass of the Jet
### Count
  Number of Constituent tracks in the Jet
### Two Point Moment
![](http://latex.codecogs.com/gif.latex?T_%5Cbeta%20%3D%20%5Cfrac%7B1%7D%7B%28p_t%5E%7Bjet%7D%29%5E2%7D%5Csum%5Climits_%7Bi%2Cj%20%5Cin%20Jet%7D%28p_t%29_i%20%28p_t%29_j%20%5CDelta%20R%5E%5Cbeta)

# Plots

 For all the plots the are plotted in a logarithmic scale

## Varying the Value of Alpha_S in timelike showers 

For the Blue Lines Alpha_S = 0.1

For the Red Lines Alpha_S = 0.1383

For the Black Lines Alpha_S = 0.16
### Quarks
![](./plots/alphaSplots/quarks_alpha_S.jpg)

### Gluons
![](./plots/alphaSplots/gluons_alpha_S.jpg)


# Classification
For all the Plots the blue lines represent the Gluons and the Red lines represent the Quarks
Reclustering after softdrop with the defafault CA Algo

Now, Based on these Jet Variables, We try to calculate a gluon Jet and a Quark jet. The ROC Curve for such a classification is as follows

# JetImages
Jet Images were created based on references from these papers (https://arxiv.org/abs/1511.05190) and (https://arxiv.org/abs/1407.5675)

Seen below are the JetImages for Quark and Gluons. These images are pre-processed in such a way that the hardest jet is always centered to the center.
If we look at the JetImages below we see that the jets for gluons are broader than the jets for quarks. 
We knew this from the physics variables such as girth which were related to the radial moments of the jets

The JetImages seen below are average jet images over all the events.
For various parameters in the SoftDrop algorithm
### z_cut = 0.2 beta = 2
![Histograms](./plots/genparticle/z0.2z2/histograms.png)
![roc_curves](./plots/genparticle/z0.2z2/roc_curve.png)
#### Jet Image
![jet_image](./plots/genparticle/z0.2z2/jet-image.png)
#### Convolutional Neural Netowork
![neural_cnn](./plots/genparticle/z0.2z2/neural_cnn-.png)
#### MaxOut FC Neural Netowrk
![neural_maxout](./plots/genparticle/z0.2z2/neural_maxout-.png)
#### ReLU FC Neural Network
![neural_relu](./plots/genparticle/z0.2z2/neural_relu-.png)

### z_cut = 0.1 beta = 2
![Histograms](./plots/genparticle/z0.1z2/histograms.png)
![roc_curves](./plots/genparticle/z0.1z2/roc_curve.png)
#### Jet Image
![jet_image](./plots/genparticle/z0.1z2/jet-image.png)
#### Convolutional Neural Netowork
![neural_cnn](./plots/genparticle/z0.1z2/neural_cnn-.png)
#### MaxOut FC Neural Netowrk
![neural_maxout](./plots/genparticle/z0.1z2/neural_maxout-.png)
#### ReLU FC Neural Network
![neural_relu](./plots/genparticle/z0.1z2/neural_relu-.png)

### z_cut = 0.05 beta = 2
![Histograms](./plots/genparticle/z0.05z2/histograms.png)
![roc_curves](./plots/genparticle/z0.05z2/roc_curve.png)
#### Jet Image
![jet_image](./plots/genparticle/z0.05z2/jet-image.png)
#### Convolutional Neural Netowork
![neural_cnn](./plots/genparticle/z0.05z2/neural_cnn-.png)
#### MaxOut FC Neural Netowrk
![neural_maxout](./plots/genparticle/z0.05z2/neural_maxout-.png)
#### ReLU FC Neural Network
![neural_relu](./plots/genparticle/z0.05z2/neural_relu-.png)

### z_cut = 0.2 beta = 1
![Histograms](./plots/genparticle/z0.2z1/histograms.png)
![roc_curves](./plots/genparticle/z0.2z1/roc_curve.png)
#### Jet Image
![jet_image](./plots/genparticle/z0.2z1/jet-image.png)
#### Convolutional Neural Netowork
![neural_cnn](./plots/genparticle/z0.2z1/neural_cnn-.png)
#### MaxOut FC Neural Netowrk
![neural_maxout](./plots/genparticle/z0.2z1/neural_maxout-.png)
#### ReLU FC Neural Network
![neural_relu](./plots/genparticle/z0.2z1/neural_relu-.png)

### z_cut = 0.1 beta = 1
![Histograms](./plots/genparticle/z0.1z1/histograms.png)
![roc_curves](./plots/genparticle/z0.1z1/roc_curve.png)
#### Jet Image
![jet_image](./plots/genparticle/z0.1z1/jet-image.png)
#### Convolutional Neural Netowork
![neural_cnn](./plots/genparticle/z0.1z1/neural_cnn-.png)
#### MaxOut FC Neural Netowrk
![neural_maxout](./plots/genparticle/z0.1z1/neural_maxout-.png)
#### ReLU FC Neural Network
![neural_relu](./plots/genparticle/z0.1z1/neural_relu-.png)

### z_cut = 0.05 beta = 1
![Histograms](./plots/genparticle/z0.05z1/histograms.png)
![roc_curves](./plots/genparticle/z0.05z1/roc_curve.png)
#### Jet Image
![jet_image](./plots/genparticle/z0.05z1/jet-image.png)
#### Convolutional Neural Netowork
![neural_cnn](./plots/genparticle/z0.05z1/neural_cnn-.png)
#### MaxOut FC Neural Netowrk
![neural_maxout](./plots/genparticle/z0.05z1/neural_maxout-.png)
#### ReLU FC Neural Network
![neural_relu](./plots/genparticle/z0.05z1/neural_relu-.png)

### z_cut = 0.2 beta = 0
![Histograms](./plots/genparticle/z0.2z0/histograms.png)
![roc_curves](./plots/genparticle/z0.2z0/roc_curve.png)
#### Jet Image
![jet_image](./plots/genparticle/z0.2z0/jet-image.png)
#### Convolutional Neural Netowork
![neural_cnn](./plots/genparticle/z0.2z0/neural_cnn-.png)
#### MaxOut FC Neural Netowrk
![neural_maxout](./plots/genparticle/z0.2z0/neural_maxout-.png)
#### ReLU FC Neural Network
![neural_relu](./plots/genparticle/z0.2z0/neural_relu-.png)

### z_cut = 0.1 beta = 0
![Histograms](./plots/genparticle/z0.1z0/histograms.png)
![roc_curves](./plots/genparticle/z0.1z0/roc_curve.png)
#### Jet Image
![jet_image](./plots/genparticle/z0.1z0/jet-image.png)
#### Convolutional Neural Netowork
![neural_cnn](./plots/genparticle/z0.1z0/neural_cnn-.png)
#### MaxOut FC Neural Netowrk
![neural_maxout](./plots/genparticle/z0.1z0/neural_maxout-.png)
#### ReLU FC Neural Network
![neural_relu](./plots/genparticle/z0.1z0/neural_relu-.png)

### z_cut = 0.05 beta = 0
![Histograms](./plots/genparticle/z0.05z0/histograms.png)
![roc_curves](./plots/genparticle/z0.05z0/roc_curve.png)
#### Jet Image
![jet_image](./plots/genparticle/z0.05z0/jet-image.png)
#### Convolutional Neural Netowork
![neural_cnn](./plots/genparticle/z0.05z0/neural_cnn-.png)
#### MaxOut FC Neural Netowrk
![neural_maxout](./plots/genparticle/z0.05z0/neural_maxout-.png)
#### ReLU FC Neural Network
![neural_relu](./plots/genparticle/z0.05z0/neural_relu-.png)




## Plotting with the Ecal data 
Muons are elimated from the EFLowTracker based on PID
Better way will be made available soon as muon discrimation is done in Delphes
### E2
![](./plots/e2-eflow.png)
### Girth 
![](./plots/girth-eflow.png)
### Subjettiness
![](./plots/tau-eflow.png)

# Classification

## Random Forests
![roc_forest-eflow](./plots/ml-plots/roc_forest-eflow.png)

## Boosted Decision Trees
![roc_boostedDT-eflow](./plots/ml-plots/roc_boosted_DT-eflow.png)

# JetImages

![jetimage-eflow](./plots/jet_image-eflow.png)

# Neural Network Classification
Based on the JetImages provided above a neural network was employed to classify the images into 2 categories 
## CNN Network

![roc_cnn-eflow](./plots/ml-plots/roc_cnn-eflow.png)
Now, If we Look at the Learning rates of the Network. By Plotting the Accuracy and the Loss with respect to the number of Epochs

![acc_cnn-eflow](./plots/ml-plots/acc_cnn-eflow.png)
![loss_cnn-eflow](./plots/ml-plots/loss_cnn-eflow.png)
## FCC
### MaxOut

![roc_maxout-eflow](./plots/ml-plots/roc_maxout-eflow.png)
Learning Rates

![acc_maxout-eflow](./plots/ml-plots/acc_maxout-eflow.png)
![loss_maxout-eflow](./plots/ml-plots/loss_maxout-eflow.png)
### ReLU
and a Fully connected network with ReLU activation neural network got an accuracy of 66.7311%

![roc_relu-eflow](./plots/ml-plots/roc_relu-eflow.png)

Learning Rates

![acc_relu-eflow](./plots/ml-plots/acc_relu-eflow.png)
![loss_relu-eflow](./plots/ml-plots/loss_relu-eflow.png)

Now, I have to try to optimize the Hyper Parameters based on Validation sets

# LOG
I have created a file called ![log.org](./log.org) . Progress will be updated there.
