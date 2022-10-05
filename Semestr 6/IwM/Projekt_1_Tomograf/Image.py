import matplotlib.pyplot as plt
from skimage.io import imread
import numpy as np

class Image:
    def __init__(self, pathToImage):
        self.image = imread(pathToImage, as_gray=True)
        self.height = self.image.shape[0]
        self.width = self.image.shape[1]
        self.size = self.height if self.height <= self.width else self.width
        self.center = tuple(x//2 for x in self.image.shape)

        
        self.paddedImage = self.getImageWithPadding()
        self.centerWithPadding = tuple(x//2 for x in self.paddedImage.shape)
        self.sizeWithPadding = self.paddedImage.shape[0]

    def getSize(self):
        return (self.height, self.width)

    def getCenter(self):
        return self.center

    def getImage(self):
        return self.image

    def getImageWithPadding(self):
        outsideCircleRadius = int(((self.height**2 + self.width**2)**0.5)//2)
        widthToAdd = outsideCircleRadius - self.width//2
        heightToAdd = outsideCircleRadius - self.height//2

        if widthToAdd < 0: widthToAdd = 0
        if heightToAdd < 0: heightToAdd = 0

        imageWithPadding = np.pad(self.image, ((heightToAdd, heightToAdd), (widthToAdd, widthToAdd)), mode='constant', constant_values=0)

        return imageWithPadding

    def getEmptyImage(self, shape):
        return np.zeros(shape)


    def plot(self):
        fig, ax = plt.subplots()
        ax.imshow(self.image, cmap="gray")
        plt.show()