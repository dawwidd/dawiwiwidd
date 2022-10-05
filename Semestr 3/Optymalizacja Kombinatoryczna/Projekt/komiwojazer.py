import random
import time
GENES_COUNT = 10
POP_COUNT =100
ELITE = 0.1
macierz = []
best = 99999999


def generate(ile):
    list = []
    for z in range(ile):
        list.append([random.randint(0, ile-1), random.randint(0, ile-1)])
    for y in range(ile):
        t = []
        for x in range(ile):
            t.append(((list[y][0] - list[x][0]) ** 2 + (list[y][1] - list[x][1]) ** 2) ** 0.5)
        macierz.append(t)
        print(t)
    return ile


def wczytaj():
    file = open("tsp500.txt", "r")
    list = []
    ile = int(file.readline())
    for line in file:
        line = line.split()
        list.append([int(float(line[1])), int(float(line[2]))])
    for y in range(ile):
        t = []
        for x in range(ile):
            t.append(((list[y][0] - list[x][0]) ** 2 + (list[y][1] - list[x][1]) ** 2) ** 0.5)
        macierz.append(t)
    return ile


class Chromosome:
    def __init__(self, size, var):
        if var == []:
            self.genes = random.sample(range(size), size)
        else:
            self.genes = var
        self.fit = 0
def greed():
    visit = [0]
    dist = 0
    while len(visit) < len(macierz):
        nextod = 999999999
        nextid = 0
        for x in range(len(macierz)):
            if 0<macierz[visit[-1]][x]<nextod and x not in visit:
                nextid = x
                nextod = macierz[visit[-1]][x]
        dist += macierz[visit[-1]][nextid]
        visit.append(nextid)
    print(visit)
    dist += macierz[visit[-1]][visit[0]]
    print(dist)


def crossover(par1, par2):
    #print(par1, par2)
    child1 = []
    for t in range(GENES_COUNT // 2):
        child1.append(par1[t])
    child2 = [q for q in par2 if q not in child1]
    child = child1 + child2
    #print(child)
    x = random.randint(0, len(par1))
    y = random.randint(0, len(par1))
    while x == y:
        y = random.randint(0, len(par1) - 1)
    if y<x: x,y=y,x
    t = [child[z] for z in reversed(range(x, y))]
    for z in range(x,y):
        child[z] = t[z-x]
    #print(child,x,y)
    return Chromosome(len(child), child)


class Population:
    def __init__(self, size):
        self.chromosomes = [Chromosome(size, []) for y in range(POP_COUNT)]

    def fitness(self):
        global best
        distances = []
        max = 0
        for z in self.chromosomes:
            dist = 0
            for q in range(len(z.genes) - 1):
                dist += macierz[z.genes[q]][z.genes[q + 1]]
            dist += macierz[z.genes[-1]][z.genes[0]]
            distances.append(dist)
            if dist > max: max = dist
            if dist < best: best = dist
        for z in range(len(self.chromosomes)):
            self.chromosomes[z].fit = max - distances[z]
            #print(self.chromosomes[z].genes, self.chromosomes[z].fit, distances[z])

    def select(self):
        next_gen = []
        self.chromosomes.sort(key=lambda w: w.fit, reverse=True)
        for t in range(int(POP_COUNT * ELITE)):
            next_gen.append(Chromosome(GENES_COUNT, self.chromosomes[t].genes.copy()))
        sum = 0
        for y in self.chromosomes:
            sum += y.fit
        for y in self.chromosomes:
            y.fit /= sum
        for y in reversed(range(len(self.chromosomes))):
            if y < len(self.chromosomes) - 1: self.chromosomes[y].fit += self.chromosomes[y + 1].fit
        while len(next_gen) < POP_COUNT:
            parent1 = ""
            number = random.randint(0, 9999)
            number /= 10000
            for z in reversed(range(len(self.chromosomes))):
                if self.chromosomes[z].fit > number:
                    parent1 = self.chromosomes[z].genes.copy()
                    break
            parent2 = []
            while parent2 == []:
                number = random.randint(0, 9999)
                number /= 10000
                for z in reversed(range(len(self.chromosomes))):
                    if self.chromosomes[z].fit > number:
                        if self.chromosomes[z].genes != parent1:
                            parent2 = self.chromosomes[z].genes.copy()
                        break
            child = crossover(parent1, parent2)
            next_gen.append(child)
        self.chromosomes = next_gen


end = False
population_count = 0
# GENES_COUNT = generate(500)
GENES_COUNT = wczytaj()
pops = Population(GENES_COUNT)
#for y in range(10):
#    print(macierz[y])
z = time.time()
i = 0
while time.time() - z < 60 * 2:
    pops.fitness()
    #for y in pops.chromosomes:
        #print((y.genes), y.fit)
    pops.select()
    print(best)
print(best)
# greed()
    # if population_count > 0: win = True
