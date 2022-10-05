from matplotlib.pyplot import imshow
from matplotlib import gridspec
import skimage.io as io
from pylab import *
import skimage
from skimage import data, filters, exposure, feature
from skimage.filters import rank
from skimage.util.dtype import convert
from skimage import img_as_float, img_as_ubyte
from skimage.color import rgb2hsv, hsv2rgb, rgb2gray
from skimage.filters.edges import convolve
from matplotlib import pylab as plt  
import numpy as np
from numpy import array
from IPython.display import display
from ipywidgets import interact, interactive, fixed
from IPython.core.display import clear_output

def show_gray(img):
    imshow(img, cmap='gray')


planes = [img_as_float(io.imread('samolot00.jpg')), img_as_float(io.imread('samolot01.jpg')), img_as_float(io.imread('samolot14.jpg')),
          img_as_float(io.imread('samolot10.jpg')), img_as_float(io.imread('samolot05.jpg')), img_as_float(io.imread('samolot17.jpg')),
          ]

nrow = len(planes)
ncol = len(planes[0])

f, axis = plt.subplots(2,3, gridspec_kw={'wspace': 0, 'hspace': -0.6}, figsize=(15,15))

for i in range(6):
    axis.ravel()[i].imshow(skimage.feature.canny(rgb2gray(planes[i]**0.35), sigma=3), cmap='gray')

[ax.set_axis_off() for ax in axis.ravel()]
plt.subplots_adjust()
plt.show()