import sys
import glob
import numpy as np
import matplotlib.pyplot as plt

def gaussian(x, mu, sig):
    return (
      1 / (sig * np.sqrt(2*np.pi)) *
      np.exp(-(x - mu)**2 / (2 * sig**2))
    )

x = np.linspace(1.2, 2, 500)

plt.tick_params(direction='in')
plt.yticks([])
plt.xlabel('D')

plt.plot(x, gaussian(x, 1.535, 0.07), label="Sn")
plt.plot(x, gaussian(x, 1.555, 0.057), label="Cu")
plt.plot(x, gaussian(x, 1.575, 0.042), label="Ag")


plt.legend()
plt.show()
