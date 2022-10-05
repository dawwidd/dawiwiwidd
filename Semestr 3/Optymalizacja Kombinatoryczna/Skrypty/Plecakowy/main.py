from algorithm import *
from math import sqrt
def imput():
    items=[]
    with open('input.txt') as f:
        content = f.readlines()
    content[0]=list(map(int,content[0].split()))
    capacity,amount=content[0]
    for i in range(amount):
        weight, price = list(map(int, content[i+1].split()))
        items.append(Item(i + 1, weight, price))
    return capacity,items

class Item(object):

    def __init__(self, id, weight, price):

        self.id = id
        self.weight = weight
        self.price = price
        self.val_per_unit = self.price/self.weight

    def __repr__(self):

        return str(self.id)

    def __str__(self):

        return self.__repr__()

while True:
    try:
        odp=int(input('0. Wczytaj dane z pliku\n1. Podaj dane\n2. Brute Force \n3. Zachłanny \n4. Tablica Dynamiczna\n'))
        if odp==0:
            capacity,items=imput()

        elif odp==1:
            items=[]
            capacity=int(input('Podaj pojemność plecaka: '))
            for i in range(int(input('Podaj ilość przedmiotów: '))):
                print('{rozmiar} {wartość} ')
                weight,price=list(map(int,input().split()))
                items.append(Item(i+1,weight,price))

            pass
        elif odp==2:
            if not items:
                print('Brak przedmiotów')
            else:
                lista=brute_force(items,capacity)
                ans=''
                waga=0
                cena=0
                for i in lista:
                    print(items[i-1])
                    waga+=items[i-1].weight
                    cena+=items[i-1].price
                print(f"cena {cena} waga {waga}")
        elif odp==3:
            if not items:
                print('Brak przedmiotów')
            else:
                lista=greedy(items,capacity)
                ans = ''
                waga = 0
                cena = 0
                for i in lista:
                    print(items[i - 1])
                    waga += items[i - 1].weight
                    cena += items[i - 1].price
                print(f"cena {cena} waga {waga}")
        elif odp==4:
            if not items:
                print('Brak przedmiotów')
            else:
                lista=dynamic(items,capacity)
                ans = ''
                waga = 0
                cena = 0
                for i in lista:
                    print(items[i - 1])
                    waga += items[i - 1].weight
                    cena += items[i - 1].price
                print(f"cena {cena} waga {waga}")
    except:
        print('Błąd danych')
