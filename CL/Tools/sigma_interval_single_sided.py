import numpy as np
from scipy.integrate import quad
# define gauss function
def norm_func(x, mu, sigma):
    y = 1/(sigma*np.sqrt(2*np.pi))*np.exp(-(x-mu)**2/(2*sigma**2))
    return y
# set mean and sigma of the gauss function
mean = 0
sigma = 1
# loop of number of sigmas
for x in range(0, 300):
    print (x/100.)," sigma corresponds to ",quad( norm_func, -np.inf, mean+x/100.*sigma, args=(0,1))[0]," % single-sided interval"
 
