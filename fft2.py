import sys
import cv2
import numpy as np
import matplotlib.pyplot as plt

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

plt.imshow(fft, cmap='gray')
plt.show()
