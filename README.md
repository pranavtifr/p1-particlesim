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

## Girth
 The Formula for Girth

![](http://latex.codecogs.com/svg.latex?g%20%3D%20%5Csum%5Climits_%7B%20i%20%5Cin%20jet%7D%20%5Cfrac%7Bp_T%5Ei%7D%7Bp_T%5E%7Bjet%7D%7Dr_i)

We can see this is the same as the formula for e_alpha with alpha = 1 and R = 1

## Tau
 Tau was calcualted using the routine from fastjet contrib

# Plots

 For all the plots the are plotted in a logarithmic scale

For all the Plots the blue lines represent the Gluons and the Red lines represent the Quarks
## Reclustering after softdrop with the defafault CA Algo

### E2

![](./plots/e2.png)
### Girth
![](./plots/girth.png)
### SubJettiness
Normalized with Jet size of 0.6 and Beta = 0.5
![](./plots/tau.png)

## Varying the Value of Alpha_S in timelike showers 

For the Blue Lines Alpha_S = 0.1

For the Red Lines Alpha_S = 0.1383

For the Black Lines Alpha_S = 0.16
### Quarks
![](./plots/alphaSplots/quarks_alpha_S.jpg)

### Gluons
![](./plots/alphaSplots/gluons_alpha_S.jpg)

# LOG
I have created a file called ![log.org](./log.org) . Progress will be updated there.
