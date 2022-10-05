import copy
wektorBezpieczny = []

def main(numer, wektor, A, H, m):
    global wektorBezpieczny
    liczbaProcesow = len(A[0])
    liczbaRodzajow = len(A)
    listaProcesow = [x+1 for x in range(len(A[0]))]   #[1, 2, 3...n]

    #wyliczenie wektora wolnych zasobów + inicjalizacja
    f = []
    zakleszczenie = False
    count = len(listaProcesow)
    for i in range(len(A)):
        f.append(m[i] - sum(A[i]))
    wektorStartowy = copy.deepcopy(f)
    print("==============================================")
    print("WARUNKI STANU POCZATKOWEGO:")
    print(f'D :=', listaProcesow, end="    ")
    print(f'f :=', f, "\n")
    print("SPRAWDZANIE BEZPIECZENSTWA:")
    numerWyboru = 1

    #start algorytmu
    while(zakleszczenie == False):
        count = len(listaProcesow)
        for i in range(liczbaProcesow):
            aktualnyProces = liczbaRodzajow
            count -= 1
            for j in range(liczbaRodzajow):
                sprawdz =  f[j] - H[j][i]
                if sprawdz >= 0:
                    aktualnyProces -= 1
            if aktualnyProces == 0:
                for x in range(liczbaRodzajow):
                    f[x] += A[x][i]
                    A[x].pop(i)
                    H[x].pop(i)
                choose = listaProcesow.pop(i)
                liczbaProcesow -= 1
                print(f'Krok {numerWyboru},  wybrano proces P{choose}')
                print(f'D :=', listaProcesow, end="    ")
                print(f'f :=', f, "\n")
                count = len(listaProcesow)
                numerWyboru += 1
                break

        if listaProcesow == []:
            wektorBezpieczny = wektorStartowy
            print(f"Liczba procesów, którym udało się przydzielić zasoby: {numerWyboru-1}")
            print("Stan jest bezpieczny, istnieje bezpieczna sekwencja procesow.")
            print(f"Ostatni bezpieczny wektor f: {wektorBezpieczny}")
            print("==============================================")
            return False

        if count == 0:
            zakleszczenie = True
            print(f"Liczba procesów, którym udało się przydzielić zasoby: {numerWyboru-1}")
            print("Wystapilo zakleszczenie systemu.")
            print(f"Ostatni bezpieczny wektor f: {wektorBezpieczny}")
            print("==============================================")
            return True


################################################################################################################
################################################################################################################
#TU WSZYSTKO WPISUJEMY

A = [[0,2,2,1,2],
     [0,0,1,0,1],
     [3,0,0,1,3]
     ]


C = [[6,4,5,5,2],
     [2,7,3,2,6],
     [7,5,6,4,3]
     ]


m = [9,8,8]


#PONIZSZA ZMIENNA SLUZY DO WPISYWANIA ŻĄDAŃ. JESLI NIE BEDA POTRZEBNE TO DAC NA 0
liczbaDodatkowychZadan = 10

#FORMAT WPISYWANIA ŻĄDAŃ:
#NAJPIERW NUMER PROCESU OD 1 DO N, A POTEM
#DLA RO<ALPHA> NP: 1 0 1
#DLA RO<R> NP: -1 -1 0 (W TRESCI ZADANIA BYLOBY 1 1 0)


#made by Tomasz aka Kejdul
################################################################################################################
################################################################################################################

dodatkowe = liczbaDodatkowychZadan
H = [[0 for _ in range(len(A[0]))] for _ in range(len(A))]

def aktualizujH():
    for i in range(len(A)):
        for j in range(len(A[0])):
            H[i][j] = (C[i][j] - A[i][j])



aktualizujH()
kopiaA = copy.deepcopy(A)
kopiaH = copy.deepcopy(H)


numer = 1
wektor = [0,0,0]

################################################
main(numer, wektor, A, H, m)
A = copy.deepcopy(kopiaA)
H = copy.deepcopy(kopiaH)
################################################

for i in range(dodatkowe):
    print("\n\nNumer procesu, który proces żąda: ", end="")
    numer = int(input())
    print("Wektor procesu, który proces żąda: ", end="")
    wektor = list(map(int, input().split()))
    print("\n\n")
    for i in range(len(wektor)):
        A[i][numer - 1] += wektor[i]
    aktualizujH()

    if main(numer, wektor, A, H, m) == False:
        print("Po przydzieleniu zasobów, system w stanie bezpiecznym.")
        print("Aktualizacja stanu zasobów")
        print("==============================================")
        A = copy.deepcopy(kopiaA)
        H = copy.deepcopy(kopiaH)
        for i in range(len(wektor)):
            A[i][numer - 1] += wektor[i]
        aktualizujH()
        kopiaA = copy.deepcopy(A)
        kopiaH = copy.deepcopy(H)

    else:
        A = copy.deepcopy(kopiaA)
        H = copy.deepcopy(kopiaH)
        kopiaA = copy.deepcopy(A)
        kopiaH = copy.deepcopy(H)
        # aktualizujH()
        print("Przydzielone zasoby spowodowały stan niebezpieczny.")
        print("Powrót do poprzedniego bezpiecznego stanu.")
        print("==============================================")











