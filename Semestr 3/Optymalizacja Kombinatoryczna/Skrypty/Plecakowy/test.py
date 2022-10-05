from math import sqrt


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


def get_bin(x, n=0):
    return format(x, 'b').zfill(n)


def brute_force(items, capacity):
    n = len(items)
    fmax = 0
    k = 2**n  #max liczba zajmująca n bitów

    for i in range(k):
        suma = 0
        waga = 0
        x = []
        mask = list(map(int, list(get_bin(i, n))))
        
        for j in range(n):
            if mask[j]:
                suma += items[j].price
                waga += items[j].weight
        if suma > fmax and waga <= capacity:
            fmax = suma
            ans = mask
    for i in range(len(mask)):
        if mask[i]:
            x.append(items[i])
    return x


def greedy(items, capacity):
    items = sorted(items, key=lambda x: x.weight)
    items = sorted(items, key=lambda x: x.val_per_unit,reverse=True)
    print(items)


brute_force([Item(1,1,1),Item(2,1,2),Item(3,1,3)],10)
