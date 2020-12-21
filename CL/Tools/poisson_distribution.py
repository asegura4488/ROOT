import numpy as np
from scipy.stats import poisson
from matplotlib import pyplot as plt

#------------------------------------------------------------
# Define the distribution parameters to be plotted
mu_values = [1, 5, 15]
linestyles = ['-', '--', ':']
colours = ['black', 'blue', 'red']

#------------------------------------------------------------
# plot the distributions
#   we generate it using scipy.stats.poisson().  Once the distribution
#   object is created, we have many options: for example
#   - dist.pmf(x) evaluates the probability mass function in the case of
#     discrete distributions.
#   - dist.pdf(x) evaluates the probability density function for
#   evaluates
fig, ax = plt.subplots(figsize=(5, 3.75))

for mu, ls, cs in zip(mu_values, linestyles, colours):
    # create a poisson distribution
    dist = poisson(mu)
    # we could generate a random sample from this distribution using, e.g.
    # rand = dist.rvs(1000)
    x = np.arange(-1, 200)

    plt.plot(x, dist.pmf(x), ls=ls, color=cs,
             label=r'$\lambda=%i$' % mu, linestyle='steps-mid')

plt.xlim(-0.5, 30)
plt.ylim(0, 0.4)

plt.xlabel('$k$')
plt.ylabel(r'$P(k|\lambda)$')
plt.title('Poisson Distribution')

plt.legend()
plt.savefig('poisson_distribution.png', bbox_inches='tight')
plt.show()
