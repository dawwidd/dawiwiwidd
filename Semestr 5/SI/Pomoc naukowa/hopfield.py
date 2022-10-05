
##### for my dear I3 group
### korzystajcie
#####wrzucic do np pycharma
###### zmienic tablice matrix (69 linika NICE !) na swoją z zadania
### cieszyc sie rozwiazaniem



def DecimalToBinary(num, fuck):
    list = []
    while num >= 1:
        list.append(num % 2)
        num = num // 2

    if len(list) != fuck:
        for z in range(fuck - len(list)):
            list.append(0)
    list.reverse()
    return list
def list_2_dec(lis):
    suma = 0
    i = 0
    lis.reverse()

    for item in lis:
        suma = suma + 2**i * item
        i= i +1
    return suma
def get_next_state_for_x(list12, next_state):
    final = []
    state = list12
    for g in range (len(next_state)):
        temp = state[g]
        state[g] = next_state[g]
        # print(state)
        final.append(state.copy())
        state[g] = int(temp)
    return (final)




class Stan():
    def __init__(self, stan):
        self.stan = stan
        self.states_after = []

    def get_next_state(self, gay_matrix):
        last = []
        for list in gay_matrix:

            var = [i * j for i, j in zip(list, self.stan)]
            im_ur_sum = sum(var)
            if im_ur_sum >= 0:
                ww = 1
            else:
                ww = 0
            last.append(ww)
        return last
        # self.get_next_state_for_x(self.stan, last)





"""TUTAJ WPISAC SWOJA MACIERZ"""
#matrix = [[0, 1, -1, 1], [1, 0, -1, 1], [-1, -1, 0, -1], [1, 1, -1, 0]]
# matrix = [[0, -1, 1], [-1, 0, 1], [1, 1, 0]]
matrix = [[0, 1, 1, -1], 
          [1, 0, 1, -1],
          [1, 1, 0, -1], 
          [-1, -1, -1, 0]]

# matrix = [
#           [0, -1, -3, 0, 0, 0], 
#           [-1, 0, 1, -2, -1 , 0],
#           [-3, 1, 0, 0, -2, 3], 
#           [0, -2, 0, 0, 1, 0], 
#           [0, -1, -2, 1, 0, -1], 
#           [0, 0, 3, 0, -1, 0],
#           ]

jd = 1
gowno = len(matrix[0])
for h in range(gowno):
    jd = jd*2
stan_count = jd




list_of_states = []
for g in range(stan_count):
    list_of_states.append(Stan(DecimalToBinary(g, len(matrix[0]))))

for f in range(stan_count):
    list_of_states[f].get_next_state(matrix)
    my_next_state = get_next_state_for_x(list_of_states[f].stan, list_of_states[f].get_next_state(matrix))

    last_one_i_promis =[]
    for state in my_next_state:
        last_one_i_promis.append(list_2_dec(state))
    
    print("STAN:",f , " " , DecimalToBinary(f,len(matrix[0])) ,"następne stany:",last_one_i_promis)
    if(last_one_i_promis.count(last_one_i_promis[0]) == len(last_one_i_promis)):
            print(f, "is STABLE")
print("stany stabilne idzie wyczytać z outputu ")

#made by Piotr Szymański