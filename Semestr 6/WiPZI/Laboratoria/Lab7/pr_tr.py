import numpy as np
import copy

#L1  = [0, 1, 1, 0, 0, 0, 0, 0, 0, 0]
L1  = [0, 1, 1, 0, 1, 0, 0, 0, 0, 0]
L2  = [1, 0, 0, 1, 0, 0, 0, 0, 0, 0]
#L3  = [0, 1, 0, 0, 0, 0, 0, 0, 0, 0]
L3  = [0, 1, 0, 0, 0, 0, 1, 0, 0, 0]
L4  = [0, 1, 1, 0, 0, 0, 0, 0, 0, 0]
L5  = [0, 0, 0, 0, 0, 1, 1, 0, 0, 0]
L6  = [0, 0, 0, 0, 0, 0, 1, 1, 0, 0]
L7  = [0, 0, 0, 0, 1, 1, 1, 1, 1, 1]
L8  = [0, 0, 0, 0, 0, 0, 1, 0, 1, 0]
L9  = [0, 0, 0, 0, 0, 0, 1, 0, 0, 1]
L10 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

L = np.array([L1, L2, L3, L4, L5, L6, L7, L8, L9, L10])

ITERATIONS = 100

def getM(L):
    M = np.zeros([10, 10], dtype=float)
    # number of outgoing links
    c = np.zeros([10], dtype=int)
    
    ## TODO 1 compute the stochastic matrix M
    for i in range(0, 10):
        c[i] = sum(L[i])
    
    for i in range(0, 10):
        for j in range(0, 10):
            if L[j][i] == 0: 
                M[i][j] = 0
            else:
                M[i][j] = 1.0/c[j]
    return M
    
print("Matrix L (indices)")
print(L)    

M = getM(L)

print("Matrix M (stochastic matrix)")
print(M)

### TODO 2: compute pagerank with damping factor q = 0.15
### Then, sort and print: (page index (first index = 1 add +1) : pagerank)
### (use regular array + sort method + lambda function)
print("\nPAGERANK")

q = 0.15
NUMBER_OF_PAGES = 10
pr = np.full(NUMBER_OF_PAGES, 1.0/float(NUMBER_OF_PAGES))
    
PR = [copy.copy(pr), copy.copy(pr)]
    
NUMBER_OF_ITERATIONS = 100

for i in range(NUMBER_OF_ITERATIONS):
    for j in range(NUMBER_OF_PAGES):
        PR[0][j] = q + (1-q) * sum(np.multiply(M[j], PR[1]))
        PR[1] = copy.copy(PR[0])
PR[0] = PR[0] / sum(PR[0])

sortedPageRanks = []
for i, rank in enumerate(PR[0]):
    sortedPageRanks.append([rank, i+1])

sortedPageRanks = list(reversed(sorted(sortedPageRanks)))

for rank in sortedPageRanks:
    print(f"PR({rank[1]}) = {rank[0]}")


    
### TODO 3: compute trustrank with damping factor q = 0.15
### Documents that are good = 1, 2 (indexes = 0, 1)
### Then, sort and print: (page index (first index = 1, add +1) : trustrank)
### (use regular array + sort method + lambda function)
print("\nTRUSTRANK (DOCUMENTS 1 AND 2 ARE GOOD)")

q = 0.15

d = np.zeros([NUMBER_OF_PAGES], dtype=float)
d[0] = 1
d[1] = 1
d = [x/sum(d) for x in d]

tr = [v for v in d]
tr_temp = copy.copy(tr)

for i in range(NUMBER_OF_ITERATIONS):
    for j in range(NUMBER_OF_PAGES):
        tr[j] = q*d[j] + (1-q) * sum(np.multiply(M[j], tr_temp))
    tr = tr / sum(tr)
    tr_temp = copy.copy(tr)


sortedTrustRanks = []
for i, rank in enumerate(tr):
    sortedTrustRanks.append([rank, i+1])

sortedTrustRanks = list(reversed(sorted(sortedTrustRanks)))

for rank in sortedTrustRanks:
    print(f"TR({rank[1]}) = {rank[0]}")
    
### TODO 4: Repeat TODO 3 but remove the connections 3->7 and 1->5 (indexes: 2->6, 0->4) 
### before computing trustrank

print("\nTRUSTRANK (LINKS 3->7 AND 1->5 REMOVED)")
L[2][6] = 0
L[0][4] = 0
M = getM(L)

q = 0.15

d = np.zeros([NUMBER_OF_PAGES], dtype=float)
d[0] = 1
d[1] = 1
d = [x/sum(d) for x in d]

tr = [v for v in d]
tr_temp = copy.copy(tr)

for i in range(NUMBER_OF_ITERATIONS):
    for j in range(NUMBER_OF_PAGES):
        tr[j] = q*d[j] + (1-q) * sum(np.multiply(M[j], tr_temp))
    tr = tr / sum(tr)
    tr_temp = copy.copy(tr)


sortedTrustRanks = []
for i, rank in enumerate(tr):
    sortedTrustRanks.append([rank, i+1])

sortedTrustRanks = list(reversed(sorted(sortedTrustRanks)))

for rank in sortedTrustRanks:
    print(f"TR({rank[1]}) = {rank[0]}")
