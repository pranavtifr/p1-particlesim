import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
kkk=cm.gist_stern
ran = 0.25
temp = np.loadtxt('quark_1e5_13tev.img')
temp2 = np.loadtxt('gluon_1e5_13tev.img')
nrows, ncols = 25, 25
#
k = np.average(temp.T,axis=1)
grid = k.reshape((nrows, ncols))
k2 = np.average(temp2.T,axis=1)
grid2 = k2.reshape((nrows, ncols))
#
plt.figure(1)
plt.subplot(121)
plt.ylabel('Azimuthal Angle')
plt.xlabel('Rapidity')
plt.title('Quark Jet Image')
plt.imshow(grid,extent=(-ran,ran,-ran,ran),interpolation='nearest', cmap=kkk)
plt.colorbar()
#
plt.subplot(122)
plt.xlabel('Rapidity')
plt.title('Gluon Jet Image')
plt.imshow(grid2,extent=(-ran,ran,-ran,ran),interpolation='nearest', cmap=kkk)
plt.colorbar()
#
#plt.show()
plt.savefig('jet_image.png', bbox_inches='tight')
print('Done')
