import sys
import cv2
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc

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
fft = 100 * (np.log(np.abs(fft)))

plt.tick_params(
    axis='both',
    which='both',
    bottom=False,
    top=False,
    left=False,
    right=False,
    labelbottom=False,
    labelleft=False)

plt.xlabel('$f_x$', fontsize=38, labelpad=17)
plt.ylabel('$f_y$', fontsize=38)

plt.imshow(fft, cmap='gray', origin='lower')
plt.show()
