import numpy as np

def normalizeArray(array, lowerBound = 0, upperBound = 1):
    result = array.astype('float32')
    arrayMin = np.min(result)
    arrayMax = np.max(result)
    result -= arrayMin
    result /= arrayMax
    result -= lowerBound
    result *= upperBound
    return result


def clipArray(array, lowerBound = 0, upperBound = 0):
    array[array < lowerBound] = lowerBound
    array[array > upperBound] = upperBound

    return array


# Based on: https://iqcode.com/code/python/python-bresenham-line-algorithm
def bresenham(startCoords, endCoords):
    sx, sy = startCoords
    ex, ey = endCoords
    dx = ex - sx
    dy = ey - sy

    isSteep = abs(dy) > abs(dx)

    if isSteep:
        sx, sy = sy, sx
        ex, ey = ey, ex

    swap = False
    if sx > ex:
        sx, ex = ex, sx
        sy, ey = ey, sy

    dx = ex - sx
    dy = ey - sy

    err = int(dx / 2.0)
    ystep = 1 if sy < ey else -1

    y = sy
    points = []
    for x in range(sx, ex+1):
        coord = (y, x) if isSteep else (x, y)
        points.append(coord)
        err -= abs(dy)
        if err < 0:
            y += ystep
            err += dx

    if swap:
        points.reverse()
    
    return np.transpose(points)