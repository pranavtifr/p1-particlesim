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
## Grooming
   The jets were groomed using Soft-Drop algorithm

## E_2
  This was the formula used for the Calculating e2
  

![](http://latex.codecogs.com/svg.latex?e_2%20%3D%20%5CSigma_%7Bj%20%5Cin%20jet%7D%20z_i%20%5Ctheta_i%5E2)


Where,


![](http://latex.codecogs.com/svg.latex?z_i%20%5Cequiv%20%5Cfrac%7Bp_%7BTi%7D%7D%7B%5CSigma_%7Bj%20%5Cin%20jet%7D%20p_%7BTj%7D%20%7D%5Cquad%20%5Ctheta_i%20%3D%5Cfrac%7B%20R_%7Bi%20%5Chat%7Bn%7D%7D%7D%7BR%7D)


Reference for the formula of e_2 [[https://arxiv.org/pdf/1704.03878.pdf]]
# Plots
 For all the plots the histogram of e_2 was plotted in a logarithmic scale
##Reclustering after softdrop with the default CA algo.
### Quarks
![](./plots/1e5/zcut_0.2_beta_2/log_e2_quarks.jpg)
### Gluons
![](./plots/1e5/zcut_0.2_beta_2/log_e2_gluons.jpg)

# Using different parameters
using R = 0.8

Z_cut = 0.1 and beta = 0.1

and recluster using CA and WTA

### Quarks

![](./plots/1e5/zcut_0.1_beta_1/quarks.jpg)
### Gluons
![](./plots/1e5/zcut_0.1_beta_1/gluons.jpg)
# LOG
I have created a file called ![log.org](./log.org) . Progress will be updated there.
