import sys
import glob
import numpy as np
from scipy.stats import norm
import matplotlib.pyplot as plt


if len(sys.argv) < 2:
    print('Unable to get glob path from argv')
    exit(1)

paths = glob.glob(sys.argv[1])
dimensions = []
for path in paths:
  data = np.loadtxt(path)
  if len(data) < 3:
    continue
  last = data[-1][-1]
  dimensions.append(last)

mean = np.round(np.mean(dimensions), 3)
std = np.round(np.std(dimensions), 3)
print(str(mean) + ' +/- ' + str(std))

mu, std = norm.fit(dimensions)
x = np.linspace(1, 2, 200)
p = norm.pdf(x, mu, std)

plt.plot(x, p)
plt.show()
