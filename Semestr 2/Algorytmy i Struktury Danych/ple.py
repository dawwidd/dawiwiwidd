import matplotlib.pyplot as plt
import time

file = open("dane.txt","r")
poj = int(file.readline())
file.readline()
wag = []
cen = []
for q in file:
    wag.append(int(q.split()[1]))
    cen.append(int(q.split()[0])) #wczytywanie z pliku

file.close()
def generate(name, c, n):
    f = open(name, "w")
    f.write(str(c)+"\n")
    f.write(str(n)+"\n")
    for z in range(n):
        f.write(str(z+1)+" "+str(z+1)+"\n")
    f.close() # generowanie

def bf():
    #start = time.time()
    fmax = 0
    najmask=0
    for x in range(2**len(cen)): #dla wszystkich mozliwych kombinacji
        mask = str(bin(x))[2:] # tworzy maske danego zbioru przedmiotow
        tenc = 0
        tenw = 0
        for z in reversed(range(len(mask))):
            if mask[-1-z]=="1": # jezeli dany bit jest ustawiony, przedmiot nalezy do rozwiazania
               tenw += wag[-1-z]# pobiera wage przedmiotu
               tenc += cen[-1-z]#pobiera wartosc przedmiotu
        if tenw <= poj and tenc > fmax:# jezeli suma wag jest <= pojemnosci i suma wartosci jest wieksza od poprzedniej najwiekszej
            fmax =tenc #zapisuje wartosc
            najmask = mask #zapisuje maske
    #end = time.time()
    return(najmask)

def pd():
    mac = []
    first = [0 for x in range(poj+1)]#pierwszy rzad macierzy z samych zer
    mac.append(first)
    for a in range(len(cen)):
        newrow = [0] # pierwsza kolumna jest zawsze zerem
        for b in range(1, poj+1):
            if wag[a]>b: #Jeśli i-ty element nie mieścis ię w plecaku,weź rozwiązanie optymalne obliczone,gdy tego elementu ni ebyło
                newrow.append(mac[a][b])
            else:
                if mac[a][b]>(mac[a][b-wag[a]]+cen[a]):#:Jeśli i - ty element mieści się w plecaku, weź maksimum z wartości 1. Plecaka bez i - tego elementu 2. Plecaka z i -tym elementem.Wówczas w plecaku musi być miejsce na ten element (zrób miejsce : pomniejsz j - aktualny rozmiar plecaka o wagę i - tego elementu i do rozwiązania optymalnego dodaj wartość i - tego elementu).
                    newrow.append(mac[a][b])
                else:
                    newrow.append(mac[a][b-wag[a]]+cen[a])
        mac.append(newrow)# dodaje wiersz do macierzy
    x = poj
    y = len(mac)-1
    rozw = []
    waga=0
    cena=0
    while True:# odczytanie rozwiazania
        if mac[y][x]==0: # jezeli element == 0 przerwij
            break
        elif mac[y][x]>mac[y-1][x]:#Porównanie wartości V[i][j] z wartością V[i-1][j] (wiersz powyżej) pozwala stwierdzić czy element i-ty jest w rozwiązaniu
            rozw.append(y)#zostal wybrany
            y-=1
            waga+=wag[y]
            cena+=cen[y]
            x-=wag[y]
        elif mac[y][x]==mac[y-1][x]: #Nie zostal wybrany
            y -= 1
    print(waga, cena, rozw)

