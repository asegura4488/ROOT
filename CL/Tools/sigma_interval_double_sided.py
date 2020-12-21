from scipy import stats
import numpy as np
from numpy import random
a = random.normal(0,1,100000)
mean, sigma = np.mean(a), np.std(a)
conf_int_a = stats.norm.interval(0.995, loc=mean, scale=sigma)

print "68%",stats.norm.interval(0.68, loc=mean, scale=sigma)
print "90%",stats.norm.interval(0.90, loc=mean, scale=sigma)
print "95%",stats.norm.interval(0.95, loc=mean, scale=sigma)
print "95.5%",stats.norm.interval(0.955, loc=mean, scale=sigma)
print "99.73%",stats.norm.interval(0.9973, loc=mean, scale=sigma)

