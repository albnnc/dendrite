import sys
import cv2
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
from matplotlib.colors import Normalize
from matplotlib.cm import ScalarMappable

rc('text', usetex=True)

if len(sys.argv) < 2:
    print('Unable to get image path from argv')
    exit(1)

image = cv2.imread(sys.argv[1], 0)

if image is None:
    print('Unable to load image')
    exit(1)

fft = np.fft.fft2(image)
fft = np.fft.fftshift(fft)
fft = np.abs(fft)
fft = np.log(fft)
fft *= 1.0 / fft.max()

plt.tick_params(
    axis='both',
    which='both',
    bottom=False,
    top=False,
    left=False,
    right=False,
    labelbottom=False,
    labelleft=False)

plt.xlabel('$f_x$', fontsize=24)
plt.ylabel('$f_y$', fontsize=24)

fft_min = np.min(fft)
fft_max = np.max(fft)

plt.imshow(fft, cmap='gray', origin='lower')
colorbar = plt.colorbar(ScalarMappable(
    norm=Normalize(vmin=0, vmax=1), cmap='gray'))
colorbar.ax.set_ylabel('$|A_f|$', fontsize=24)
colorbar.set_ticks([0, 1])
plt.show()
