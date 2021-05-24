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
  file = open(path, 'r')
  lines = file.readlines()
  data = [v.strip().split() for v in lines if len(v.strip()) > 0]
  if len(data) < 1:
    continue
  last = float(data[-1][-1])
  dimensions.append(last)

mu, std = norm.fit(dimensions)
print(str(mu) + ' +/- ' + str(std))

x = np.linspace(1, 2, 500)
p = norm.pdf(x, mu, std + 0.05)

plt.plot(x, p)
plt.show()
