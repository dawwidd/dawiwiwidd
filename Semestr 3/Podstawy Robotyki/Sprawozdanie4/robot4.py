import numpy as np
import math
import matplotlib.pyplot as plot

T = [0] # Czas
Fi = [0] # Orientacje robota
X = [0] # Pozycje X robota
Y = [0] # Pozycje Y robota
W = [0] # Prędkość kątowa robota
V = [0] # Prędkość liniowa robota
U1 = [] # Lista macierzy stanu u = [w v]
U2 = [] # Lista macierzy stanu u = [wp wl]

Tp = 0.01 # Okres próbkowania
R = 0.021 # Promień kół robota
D = 0.073 # Szerokość robota

with open("profile_prędkości_V2.txt") as file:
    lines = file.readlines()
    i = 0
    for line in lines:
        t, wl, wp = line.split("\t")

        T.append(t)
        W.append((float(wp)-float(wl))*R/D) # Wyprowadzenie zależności w(t) oraz v(t)
        V.append((float(wp)+float(wl))*R/2) # na podstawie danych

        U1.append([[W[-1]],[V[-1]]])         # Utworzenie listy kolejnych
        U2.append([[float(wp)],[float(wl)]]) # macierzy sterowań

    # Ustalenie funkcji fi(t), x(t), y(t)
    for i in range(1, len(lines)):
        Fi.append(Fi[i - 1] + Tp * (W[i]))
        X.append(X[i - 1] + Tp * (V[i]*math.cos(Fi[i])))
        Y.append(Y[i - 1] + Tp * (V[i]*math.sin(Fi[i])))


def WyznaczMacierzStanu1(fi, u):
    m = [[1, 0],
         [0, math.cos(fi)],
         [0, math.sin(fi)]]

    q = np.matmul(m, u)
    return q

def WyznaczMacierzStanu2(fi, u):
    m = [[R/D, -R/D],
         [R*math.cos(fi)/2, R*math.cos(fi)/D],
         [R*math.sin(fi)/2, R*math.sin(fi)/D]]

    q = np.matmul(m, u)
    return q


q1 = WyznaczMacierzStanu1(Fi[-1], U1[-1])
q2 = WyznaczMacierzStanu2(Fi[-1], U2[-1])
print(q1)
print(q2)
print(Fi[-1], X[-1], Y[-1])
plot.plot(X, Y)
plot.show()



