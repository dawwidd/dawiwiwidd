# http://www.framsticks.com/dev/files/hci_lab.html

import tkinter
import numpy as np
from io import StringIO

DELAY = 200  # 5 fps
DELAY_FAILED_READ = 10  # just some time for Framsticks to complete writing the file if opening failed
FILENAME = 'dump.txt'

DARKEN_WORLDSIZE = 30
DARKEN_DECREASE = 0.5


def tuple3xByteToString(rgb_tuple):
	return '#%02x%02x%02x' % rgb_tuple


def getX(x, y, z):
	return 10 + x * 16


def getY(x, y, z): # "top view": completely ignores vertical coordinates 'z', fix me!
	return 270 - y * 8


def getBrightness(y):
	return 1.0 # use DARKEN_WORLDSIZE, DARKEN_DECREASE to return 0..1 depending on how far 'y' is from the observer


def darken(rgb_array, brightness):
	pass # TODO return rgb_array that is darkened according to 'brightness'


def plot(arr):
	canvas.delete("all")
	gray = np.array([0.5, 0.5, 0.5])
	
	# draw grid
	for x in range(0, 30, 5):
		for y in range(0, 30, 5):
			# line = canvas.create_line(...gray...)
			pass


	for i in range(len(arr)):
		x1, y1, z1, x2, y2, z2, v, stress_lin, stress_rot = arr[i]
		stress_intensity = 100 + min(155, int(stress_lin * 1000))  # primitive scaling from 0 to 255 (just an example)
		rgb=(50, stress_intensity, 50)
		line = canvas.create_line(getX(x1, y1, z1), getY(x1, y1, z1), getX(x2, y2, z2), getY(x2, y2, z2), width=2, fill=tuple3xByteToString(rgb))


# TODO use hue to visualize stress_lin. When stress_lin changes 0..1, colors should change hex rgb "55,55,ff", "ff,55,55", "ff,ff,00", "ff,ff,ff".
# TODO add simple 3D perspective using 'y' coordinates added to x
# TODO apart from hue for stress, use brightness so that structures farther from the observer become slightly darker
# TODO before drawing structures, draw a grid for x in range(0,30,5) for y in range(0,30,5) at height z=0
# TODO optional: auto-scale so that structures always use the entire canvas (but scale proportionally, do not distort!) and are centered

def readAgain():
	try:  # trying to read a file that is likely being written by another process - what can possibly go wrong? everything!
		with open(FILENAME, 'rt') as f:
			file_contents = f.read()  # read everything as quickly as possible (a truncated file may be read)
	except Exception as e:
		print(e)
		return np.empty(0)  # array of size 0
	try:
		arr = np.loadtxt(StringIO(file_contents), ndmin=2)  # do the parsing after the file is read
	except Exception as e:  # e.g. ValueError: Wrong number of columns
		print(e)
		return np.empty(0)  # array of size 0
	return arr  # in this application, we are OK when we occasionally return partially read content, or reading fails.
	# Unfortunately, sometimes this function will successfully read nothing (without any exception) while the file is being written,
	# so we have no way to distinguish between a fully read empty file and a partially read file with no lines read.
	# We consider both cases as a reading failure, a side effect of which is never displaying the "empty world" with no structures.


def repeated():  # this function is called repeatedly to read the file with coordinates and to plot lines
	arr = readAgain()
	print(arr.shape)
	if arr.shape[0] > 0:
		plot(arr)
		window.title('Stress visualization: %d sticks' % arr.shape[0])
	window.after(DELAY if arr.shape[0] > 0 else DELAY_FAILED_READ, repeated)  # schedule calling self again


window = tkinter.Tk()
canvas = tkinter.Canvas(window, width=800, height=300, bg='black')
window.after(DELAY, repeated)
canvas.pack()
window.mainloop()
