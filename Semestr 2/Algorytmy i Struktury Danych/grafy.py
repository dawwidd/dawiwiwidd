import matplotlib.pyplot as plt
import time
import sys
import random
sys.setrecursionlimit(10000)
sas = []
nast = []
kraw = []
niesk = []
#set = set()
queue = []
def create(n):
    for x in range(n):
        z = list(map(int,input().split()))
        niesk.append(z)
def createnies(n, wsp):
    z = int(n*(n-1)/2*wsp)
    for y in range(n):
        if z <= 0 : break
        else:
            for g in range(y+1, n):
                if g>len(niesk) :
                    for h in range(g+1,n):
                        if h>len(niesk) :
                            if y ==0:
                                niesk.append([g,h])
                                niesk.append([y,h])
                                niesk.append([y,g])
                            else:
                                niesk[y].append(g)
                                niesk[y].append(h)
                                niesk.append([y, h])
                                niesk.append([y, g])
                            z-=3
                            break
                    break
    if z >0:
        while z>0:
            a = random.randint(0,n)
            b = random.randint(0,n)
            c = random.randint(0,n)
            if a!=b and b!=c and a!=c and( b not in niesk[a]) and( b not in niesk[c]) and( c not in niesk[a]):
                niesk[a].append(b)
                niesk[a].append(c)
                niesk[b].append(a)
                niesk[b].append(c)
                niesk[c].append(b)
                niesk[c].append(a)
                z-=3

def generate(n):
    sas.clear()
    z = n*(n-1)//4
    for x in range(n):
        t = []
        for y in range(n):
            if x<y and (y+x)%2==1 and z >0:
                t.append(1)
                z -=1
            else: t.append(0)
        sas.append(t)
    for d in range(n):
        print(sas[d])
def tonast(n):
    nast.clear()
    for x in range(n):
        t = []
        for y in range(n):
            if sas[x][y] == 1:
                t.append(y)
        nast.append(t)
    for d in range(n):
        print(nast[d])
def toniesk(n):
    for t in range(n):
        niesk.append(nast[n].copy())
    for x in range(n):
        for z in getnast(x,"q",n):
            niesk[z].append(x)
    for d in range(n):
        print(niesk[d])

def getnast(cur, type, siz ):
    if type == "s":
        na = []
        for x in range(siz):
            if sas[cur][x] == 1:
                na.append(x)
        return na
    elif type == "n":
        return nast[cur]
    elif type == "q":
        return niesk[cur]
    else:
        t = []
        for x in kraw:
            if x[0] == cur:
                t.append(x[1])
        return t

def tokraw(n):
    kraw.clear()
    for x in range(n):
        for y in range(n):
            if sas[x][y]==1:
                kraw.append([x,y])
    for d in kraw:
        print(d)
def wglab(v, siz, typ):
    set.add(v)
    print(v)
    nas = getnast(v, typ, siz)
    for x in nas:
        if x not in set:
            wglab(x, siz, typ)
def wglabini(siz,typ):
    for z in range(siz):
        if z not in set:
            wglab(z,siz,typ)

def wszerz(v, siz, typ):
    print(v)
    set.add(v)
    nas = getnast(v, typ, siz)
    for y in nas:
        if y not in set:
            queue.append(y)
    if len(queue) != 0:
        t = queue[0]
        queue.pop(0)
        if t not in set: wszerz(t, siz, typ)

def wszerzini(siz,typ):
    for z in range(siz):
        if z not in set:
            wszerz(z,siz,typ)

kol = {}
rozw = []

def topwglab(cur, siz, typ):
    if kol[str(cur)] == "b":
        kol[str(cur)] = "s"
        nas = getnast(cur, typ, siz)
        for y in nas:
            topwglab(y, siz, typ)
        kol[str(cur)] = "c"
        rozw.insert(0, cur)
def topwglabinit(cur, siz, typ):
    for x in range(siz):
        kol[str(x)] = "b"
    for z in range(siz):
        topwglab(z, siz, typ)
    print(" ".join(list(map(str, rozw))))

wyn = []
slo = {}
def topwszerz(siz,typ):
    for a in range(siz):
        slo[str(a)] = 0
    for x in range(siz):
        z = getnast(x,typ,siz)
        for t in z:
            slo[str(t)]+=1
    y = -1
    while len(wyn)<siz:
        y += 1
        if slo[str(y)] == 0:
            wyn.append(y)
            slo[str(y)] -=1
            z = getnast(y,typ,siz)
            for q in z:
                slo[str(q)]-=1
            y = -1

    print(wyn)
odw = set()
cykl = []
k = 1
def Hcykl(siz,element,start,vis):
    global k
    odw.add(element)
    vis += 1
    d = getnast(element,"q",siz)
    for i in d:
        if i ==start and vis ==siz:
            cykl[k]=element
            k+=1
            return True
        if i not in odw:
            if Hcykl(siz,i,start,vis):
                cykl[k]=element
                k+=1
                return True
    odw.remove(element)
    vis -=1
    return False

def Hinit(siz):
    global cykl
    cykl = [0 for x in range(siz+1)]
    start = 0
    Hcykl(siz,0,0,0)
    print(cykl)

cyk = []
def Ecykl(el):
    z = getnast(el,"q",3)
    for x in z:
        niesk[el].remove(x)
        niesk[x].remove(el)
        Ecykl(x)
    cyk.append(el)
    return True
def Einit(siz):
    new = []
    global niesk
    for t in range(siz):
        new.append(niesk[t].copy())
    ile = 0
    for d in range(siz):
        ile+=len(niesk[d])
    ile//=2
    Ecykl(0)
    niesk = new
    if len(cyk) == ile+1 and cyk[0]==cyk[-1]:
        print(cyk)
        return True
    else:
        return False

print("Podaj ilosc wierzcholkow")
il = int(input())
print("Podaj tabele sasiedztwa")
typ = "q"
for x in range(il):
    t = list(map(int,input().split()))
    niesk.append(t)
while True:
    print("1.Wyswietl graf")
    print("2.Znajdz cykl Hamiltona")
    print("3.Znajdz cykl Eulera")
    print("4.Zakoncz")
    cho = input()
    if cho =="1":
        for c in range(il):
            print(niesk[c])
    elif cho =="2":
        Hinit(il)
        cykl.clear()
        odw.clear()
    elif cho =="3":
        Einit(il)
        cyk.clear()
    else: break