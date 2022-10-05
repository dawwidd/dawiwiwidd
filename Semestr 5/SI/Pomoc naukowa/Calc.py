
TrueP = 15
FalseP = 2
FalseN = 1
TrueN = 0


print("Precyzja:", TrueP/(TrueP+FalseP))
print("Czulosc:", TrueP/(TrueP+FalseN))
print("Dokladnosc:", (TrueP+TrueN)/(TrueP+TrueN+FalseP+FalseN))
print("Ilosc poprawnych:", TrueP+TrueN)
print("Ilosc niepoprawnych:", FalseP+FalseN)

