import numpy as np
from scipy.stats import binom
from matplotlib import pyplot as plt

#------------------------------------------------------------
# Define the distribution parameters to be plotted
n_values = [20, 20, 40] # number of trials
b_values = [0.2, 0.4, 0.4]# probability of success
linestyles = ['-', '--', ':']
colours = ['black', 'blue', 'red']
x = np.arange(-1, 200)

#------------------------------------------------------------
# plot the distributions
fig, ax = plt.subplots(figsize=(5, 3.75))

for (n, b, ls, cs) in zip(n_values, b_values, linestyles, colours):
    # create a binomial distribution
    dist = binom(n, b)

    plt.plot(x, dist.pmf(x), ls=ls, c=cs,
             label=r'$p=%.1f,\ n_{trials}=%i$' % (b, n), linestyle='steps-mid')

plt.xlim(-0.5, 35)
plt.ylim(0, 0.25)

plt.xlabel('$x$')
plt.ylabel(r'$B(x|p, n)$')
plt.title('Binomial Distribution')

plt.legend()
plt.savefig('binomial_distribution.png', bbox_inches='tight')
plt.show()

# binomial probability density function that x accures 
# with probability p in n_trials
