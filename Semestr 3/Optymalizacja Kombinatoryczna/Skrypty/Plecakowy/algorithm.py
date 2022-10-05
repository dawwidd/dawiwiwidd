# Przenieś klasę do maina
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


def get_bin(x, n=0):  # funkcja do tworzenia prawidłowej liczby binarnej
    return format(x, 'b').zfill(n)


def brute_force(items, capacity):
    n = len(items)
    fmax = 0
    k = 2**n  # max liczba zajmująca n bitów

    for i in range(k):
        suma = 0
        waga = 0
        knapsack = []
        mask = list(map(int, list(get_bin(i, n))))

        for j in range(n):
            if mask[j]:
                suma += items[j].price
                waga += items[j].weight
        if suma > fmax and waga <= capacity:
            fmax = suma
            ans = mask

    for i in range(len(ans)):
        if ans[i]:
            knapsack.append(items[i].id)

    return knapsack


def greedy(items, capacity):
    items = sorted(items, key=lambda x: x.weight)
    items = sorted(items, key=lambda x: x.val_per_unit, reverse=True)
    knapsack = []
    waga = 0
    i = 0
    n = len(items)

    while waga < capacity and i < n:
        if items[i].weight <= capacity - waga:
            knapsack.append(items[i].id)
            waga += items[i].weight
        i += 1

    return knapsack


def make_dynamic_matrix(items, capacity):
    matrix = [[0]*(capacity+1) for x in range(len(items)+1)]

    for i in range(1, len(items)+1):

        for j in range(1, capacity+1):
            if items[i-1].weight > j:
                matrix[i][j] = matrix[i-1][j]
            else:
                if j-items[i-1].weight > capacity:
                    matrix[i][j] = max(matrix[i-1][j], (matrix[i-1][capacity]+items[i-1].price))
                else:
                    matrix[i][j] = max(matrix[i-1][j], (matrix[i-1][j-items[i-1].weight]+items[i-1].price))

    return matrix


def find_max_value(matrix):
    max_ = 0

    for i in range(1, len(matrix)):

        for j in range(1, len(matrix[0])):
            if max_ < matrix[i][j]:
                max_ = matrix[i][j]
                k = i
                l = j

    return [k, l]


def find_optimal_knapsack(matrix, items, capacity):
    knapsack = []
    [i, j] = find_max_value(matrix)
    knapsack.append(i)
    j -= items[i-1].weight
    i -= 1
    while i > 0 and j > 0:
        if j > capacity:
            j = capacity
        if (matrix[i][j] == matrix[i-1][j]) and i > 0:
            i -= 1
            continue
        if i:
            knapsack.append(i)
            j -= items[i-1].weight
            i -= 1
    return knapsack


# tutaj zaczyna się dynamiczna
def dynamic(items, capacity):
    matrix = make_dynamic_matrix(items, capacity)
    for line in matrix:print(line)
    knapsack = find_optimal_knapsack(matrix, items, capacity)
    return knapsack
