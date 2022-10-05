import cv2
import glob
import os
import math
import numpy as np
import pdb
from matplotlib import pyplot as plt
from scipy.ndimage.morphology import binary_fill_holes
from scipy import ndimage
from skimage import img_as_ubyte, morphology, filters, io, color, exposure
from skimage.feature import canny
from skimage.morphology import binary_dilation, square, disk, diamond, binary_opening


COLORS = [ (114, 97, 68),     # 10 PLN
           (255, 204, 204),   # 20 PLN
           (142, 161, 226),   # 50 PLN
           (115, 175, 114),   # 100 PLN
           (230, 184, 0),     # 200 PLN
        ]


def avgColorDifference(image):
    differences = []
    for row in image:
        for (b, g, r) in row:
            if(b != 0 and g != 0 and r != 0):
                value = abs(int(b) - int(g)) + abs(int(b) - int(r)) + abs(int(r) - int(g))

                differences.append(value)

    differences = np.array(differences, dtype="int")

    avg = np.average(differences)
    return avg


def banknoteDecision(avgColor):
    if(avgColor > 50.0):
        money = 50.00
    elif(avgColor > 40.0 and avgColor <= 50.0):
        money = 200.00
    elif(avgColor > 28.0 and avgColor <= 40.0):
        money = 10.00
    elif(avgColor > 22.5 and avgColor <= 28.0):
        money = 20.00
    elif(avgColor > 10.0 and avgColor <= 22.5):
        money = 100.00

    return money


def colorise(money):
    if(money == 10.00):
        color = COLORS[0]
    if(money == 20.00):
        color = COLORS[1]
    elif(money == 50.00):
        color = COLORS[2]
    elif(money == 100.00):
        color = COLORS[3]
    elif(money == 200.00):
        color = COLORS[4]

    return color[::-1]


def intersectionBoolean(a, b):
    if (a[0] <= b[0]):
        w = b[0] - (a[0] + a[2])
    else:
        w = a[0] - (b[0] + b[2])
    if (a[1] <= b[1]):
        h = b[1] - (a[1] + a[3])
    else:
        h = a[1] - (b[1] + b[3])

    if (w <= 0 or h <= 0):
        return True
    else:
        return False


def findRectangle(img):
    maxArea = (img.shape[0] - 30) * (img.shape[1] - 30)
    img = cv2.GaussianBlur(img, (5, 5), 0)
    rectangle = []
    for gray in cv2.split(img):
        for thrs in range(0, 255, 26):
            if thrs == 0:
                bin = cv2.Canny(gray, 0, 50, apertureSize = 5)
                bin = cv2.dilate(bin, None)
            else:
                _retval, bin = cv2.threshold(gray, thrs, 255, cv2.THRESH_BINARY)
            contours, _hierarchy = cv2.findContours(bin, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

            for cnt in contours:
                isIntersection = False
                cnt_len = cv2.arcLength(cnt, True)
                cnt = cv2.approxPolyDP(cnt, 0.02*cnt_len, True)
                if len(cnt) == 4 and cnt.all() != 0 and cv2.contourArea(cnt) > 110000 and cv2.contourArea(cnt) < maxArea and cv2.isContourConvex(cnt):
                    x, y, width, height = cv2.boundingRect(cnt)
                    r1 = (x, y, width, height)
                    for r in rectangle:
                        xr, yr, widthr, heightr = cv2.boundingRect(r)
                        r2 = (xr, yr, widthr, heightr)
                        if intersectionBoolean(r1,r2):
                            isIntersection = True
                            break

                    if(isIntersection == False):
                        cnt = cnt.reshape(-1, 2)
                        max_cos = np.max([angleCos( cnt[i], cnt[(i+1) % 4], cnt[(i+2) % 4] ) for i in range(4)])
                        if max_cos < 0.05:
                            rectangle.append(cnt)
    return rectangle


def angleCos(p0, p1, p2):
    d1, d2 = (p0-p1).astype('float'), (p2-p1).astype('float')
    return abs( np.dot(d1, d2) / np.sqrt( np.dot(d1, d1)*np.dot(d2, d2) ) )


if __name__ == '__main__':
    resultsFolder = "rezultat/"

    # Create new directory when not exists
    if not os.path.exists(resultsFolder):
      os.makedirs(resultsFolder)

    # Find files to read
    files = glob.glob("data/*")

    # Read files
    images = list(map(cv2.imread, files))

    # Iterate on images
    for index, image in enumerate(images):
        print(str(files[index]))
        allMoney = [0]
        output = image.copy()
        overlay = image.copy()

        rx = None
        ry = None
        rw = None
        rh = None

        # Find banknotes
        banknoteImage = image.copy()
        rectangle = findRectangle(banknoteImage)
        for img in rectangle:
            x, y, width, height = cv2.boundingRect(img)
            rx = x
            ry = y
            rw = width
            rh = height

            king = banknoteImage[y + int(height / 5) : y + 4 * int(height / 5), x + int(width / 3) : x + 3 * int(width / 4)].copy()
            kingColorDifference = avgColorDifference(king)
            money = banknoteDecision(kingColorDifference)

            cv2.rectangle(overlay, (x, y), (x + width, y + height), colorise(money), -1)
            cv2.addWeighted(overlay, 0.25, output, 0.75, 0, output)
            cv2.rectangle(output, (x, y), (x + width, y + height), colorise(money), 10)
            cv2.putText(output, "{:.2f} PLN".format(money), (int(x + width / 2), int(y + height / 2)), cv2.FONT_HERSHEY_SIMPLEX, 1.2, (204, 119, 0), 3)
            allMoney.append(money)

            cv2.putText(output, "TOTAL: {:.2f} PLN".format(sum(allMoney)), (10,50), cv2.FONT_HERSHEY_SIMPLEX, 1.2, (0, 255, 255), 4)
            path = resultsFolder + files[index].split('/')[1]
            cv2.imwrite(path,output)
            print('Saved')