import math

#pierwszy (zerowy) element dajcie s=0 w=0 bo inaczej źle obliczy
s = [0,5,3,2,4,3]
w = [0,3,4,2,6,1]
b = 12

# # przykładowe dane z folii
# s = [0,5,3,2,4,3]
# w = [0,3,4,2,6,1]
# b = 10

i = len(s)
j = sum(w)

g = []


def oblicz(i,j):
    if j == 0:
         return 0
    elif(i == 0 and j!=0):
         return 100
    else:
        if w[i]<=j:
            return min(oblicz(i-1, j-w[i])+s[i], oblicz(i-1,j))
        else:
            return oblicz(i-1,j)


for x in range(i):
    g.append([])
    for y in range(j):
        g[x].append(oblicz(x,y))
    

# odkomentujcie jak chcecie bardziej czytelnie
# for x in range(i):
#     for y in range(j):
#         if(g[x][y] == 100):
#             g[x][y] = 0


for x in range(i):
    print(g[x])

