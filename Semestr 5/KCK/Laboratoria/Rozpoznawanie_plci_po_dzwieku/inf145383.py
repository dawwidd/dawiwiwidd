from scipy.fftpack import fft, fftfreq
from scipy.signal import decimate
import numpy as np
import soundfile
import sys, os

def readWav(path):
    wav, rate = soundfile.read(path, always_2d=True)
    if wav.shape[1] == 2:
        wav = (wav[:,0] + wav[:,1]) / 2
    else:
        wav = wav[:,0]
    return wav, rate


def harmonicProductSpectrum(fy, repeat):
    fy_copy = fy.copy()

    for k in range(2, repeat+1):
        d = decimate(fy, k)
        fy_copy[:len(d)] *= d

    fy_copy[:10] = 0
    return fy_copy

    
def processY(wav):
    fy = wav * np.kaiser(len(wav), 50)
    fy = abs(fft(fy))
    fy = harmonicProductSpectrum(fy, 4)
    return fy


def predict(path):
    wav, rate = readWav(path)
    fx = fftfreq(len(wav), d=1/rate)
    fy = processY(wav)

    m_lower = 85
    m_upper = 175
    k_lower = 175
    k_upper = 355
    remove_out_of_bounds = (fx >= m_lower) & (fx <= k_upper)
    freq = fx[remove_out_of_bounds][np.argmax(fy[remove_out_of_bounds])]

    if m_lower <= freq < m_upper: return 'M'
    if k_lower <= freq < k_upper: return 'K'
    return 'M'
    


def actual(path):
    for i in path:
        if i == 'K' or i == 'M':
            return i


def getFilename(name):
    path = ''
    for i in range(len(name)):
        if name[i] == '0':
            path += name[i:-2]
            break
    return 'train/'+path

def accuracy(dirname):
    count = 0
    count_good = 0
    dir = dirname
    for file in os.scandir(dir):
        if file.is_file():
            if predict(getFilename(str(file))) == actual(getFilename(str(file))):
                count_good += 1
    return count_good/91


path = sys.argv[1]
label = predict(path)
print(label)
# print(accuracy("train"))