from math import radians
import numpy as np
import matplotlib.pyplot as plt
from Algorithms import bresenham, normalizeArray, clipArray
from Image import *
from multiprocessing import Pool
from scipy.fft import fft, ifft, fftfreq
from copy import deepcopy

class CTScanner:
    def __init__(self, center, radius, rangeAngle, devicesCount, scanCount, image, upToAngle):
        self.center = center
        self.radius = radius
        self.rangeAngle = radians(rangeAngle)
        self.devicesCount = devicesCount
        self.scanCount = scanCount
        self.measurementAngles = np.linspace(0,180, self.scanCount)
        self.image = image
        self.resultImage = np.zeros(image.shape)
        self.normalizationMatrix = np.zeros(image.shape)
        self.transposedSinogram = None
        self.upToAngle = upToAngle
        self.measurementAngles = self.measurementAngles[self.measurementAngles <= self.upToAngle]

    def calcSinogramData(self):
        results = np.zeros((self.scanCount, self.devicesCount))

        for i, angle in enumerate(self.measurementAngles):
            results[i] = self.radonTransform(angle)

        self.transposedSinogram = np.transpose(results)
    
    def radonTransform(self, angle):
        emittersCoords = self.getEmittersCoords(angle)
        detectorsCoords = self.getDetectorsCoords(angle)
        lines = self.getLinesBetweenDevices(emittersCoords, detectorsCoords)

        result = normalizeArray(np.array([np.sum((self.image[tuple(line)])) for line in lines]))

        return result

    def calcResultData(self):
        for i, angle in enumerate(self.measurementAngles):
            self.inverseRadonTransform(angle)
            
        self.normalizationMatrix[self.normalizationMatrix == 0] = 1
        self.resultImage = normalizeArray(self.resultImage / self.normalizationMatrix)

    def inverseRadonTransform(self, angle):
        print(angle)
        emittersCoords = self.getEmittersCoords(angle)
        detectorsCoords = self.getDetectorsCoords(angle)
        lines = self.getLinesBetweenDevices(emittersCoords, detectorsCoords)

        for i, line in enumerate(lines):
            for point in np.transpose(line):
                if(int(angle/(180/self.scanCount)) < self.scanCount):
                    self.resultImage[point[0], point[1]] += np.transpose(self.transposedSinogram)[int(angle/(180/self.scanCount)),i]
                    self.normalizationMatrix[point[0], point[1]] += 1
                    
    def getEmittersCoords(self, angle):
        return self.getDevicesCoords(angle)

    def getDetectorsCoords(self, angle):
        return self.getDevicesCoords(angle+180)[::-1]

    def getDevicesCoords(self, angle):
        devicesAngles = np.linspace(0, self.rangeAngle, self.devicesCount) + radians(angle)
        centerX, centerY = self.center
        devicesX = (self.radius * np.cos(devicesAngles) - centerX).astype(int)
        devicesY = (self.radius * np.sin(devicesAngles) - centerY).astype(int)
        devicesCoords = list(zip(devicesX, devicesY))

        return devicesCoords

    def plotSinogram(self):
        plt.figure()
        plt.imshow(self.transposedSinogram, cmap="gray")
        plt.show()

    def plotResult(self):
        plt.figure()
        plt.imshow(self.resultImage, cmap="gray")
        plt.show()

    def getLinesBetweenDevices(self, emittersCoords, detectorsCoords):
        lines = [list(bresenham(emitterCoords, detectorCoords)) for emitterCoords, detectorCoords in zip(emittersCoords, detectorsCoords)]
        return lines

    def getImage(self):
        insideCircleRadius = int(self.image.shape[0]//2)
        sizeToSubstract = int(insideCircleRadius//np.sqrt(2))
        originalX = int(self.image.shape[0]//2 - sizeToSubstract)
        originalY = int(self.image.shape[0]//2 - sizeToSubstract)

        imageWithoutPadding = self.image[originalX:originalX+2*sizeToSubstract, originalY:originalY+2*sizeToSubstract]

        return imageWithoutPadding

    def getResultImage(self):
        insideCircleRadius = int(self.resultImage.shape[0]//2)
        sizeToSubstract = int(insideCircleRadius//np.sqrt(2))
        originalX = int(self.resultImage.shape[0]//2 - sizeToSubstract)
        originalY = int(self.resultImage.shape[0]//2 - sizeToSubstract)

        imageWithoutPadding = self.resultImage[originalX:originalX+2*sizeToSubstract, originalY:originalY+2*sizeToSubstract]

        return imageWithoutPadding

    def getSinogramHistory(self):
        print(self.sinogramHistory.shape)
        return self.sinogramHistory

    def getResultHistory(self):
        print(self.resultImageHistory.shape)
        return self.resultImageHistory

    def getTransposedSinogram(self):
        return self.transposedSinogram
