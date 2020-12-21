#!/usr/bin/python
import scipy.stats
import math

# standard deviations
sigma = [   1.0,
            math.sqrt(scipy.stats.chi2.ppf(0.8,1)),
            math.sqrt(scipy.stats.chi2.ppf(0.9,1)),
            math.sqrt(scipy.stats.chi2.ppf(0.95,1)),
            2.0,
            math.sqrt(scipy.stats.chi2.ppf(0.99,1)),
            3.0,
            math.sqrt(scipy.stats.chi2.ppf(0.999,1)),
            4.0,
            5.0]
# confidence intervals
conf_int = [ scipy.stats.chi2.cdf( s**2,1) for s in sigma ]

print "sigma     \t" + "\t".join(["%1.2f"%(s) for s in sigma])
print "conf_int  \t" + "\t".join(["%1.5f%%"%(100*ci) for ci in conf_int])
print "p-value   \t" + "\t".join(["%1.8f"%(1-ci) for ci in conf_int])
