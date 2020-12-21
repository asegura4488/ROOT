import numpy as np

def poisson_interval(k, alpha=0.05): 
    """
    uses chisquared info to get the poisson interval. Uses scipy.stats 
    (imports in function). 
    """
    from scipy.stats import chi2
    a = alpha
    low, high = (chi2.ppf(a/2, 2*k) / 2, chi2.ppf(1-a/2, 2*k + 2) / 2)
    if k == 0: 
        low = 0.0
    return low, high

print poisson_interval(0)
print poisson_interval(1)
print poisson_interval(2)
print poisson_interval(3)
print poisson_interval(4)
print poisson_interval(5)
print poisson_interval(6)
print poisson_interval(7)

