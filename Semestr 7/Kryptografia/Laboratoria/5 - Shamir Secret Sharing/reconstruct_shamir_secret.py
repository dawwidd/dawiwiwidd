import numpy as np


def reconstruct(shares, prime):
    result = 0
    
    for i, share in enumerate(shares):
        prod = 1
        for j in np.array(shares)[:,0]:
            if(j != share[0]):
                prod *= j / (j - share[0])

        result += share[1] * prod
        
    return int(result % prime)


if __name__ == '__main__':
    numOfShares = int(input("Number of shares: "))
    prime = int(input("Prime: "))
    shares = []

    for i in range(numOfShares):
        share = input("Share " + str(i) + ": ")
        share = share.split(' ')
        shares.append([int(share[0]), int(share[1])])

    print("Reconstructed secret: " + str(reconstruct(shares, prime)))

