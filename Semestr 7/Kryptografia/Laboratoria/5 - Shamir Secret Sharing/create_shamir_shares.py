import random
import numpy as np


MAX_VALUE = 100

def generateShares(secret, numOfShares, threshold, prime):
    coefficients = []
    shares = []

    for i in range(threshold - 1):
        coefficient = random.randint(1, MAX_VALUE)
        coefficients.append(coefficient)

    for i in range(numOfShares):
        share = 0
        x = random.randint(1, MAX_VALUE)
        if len(shares) > 0:
            while x in list(np.array(shares)[:,0]):
                x = random.randint(1, MAX_VALUE)

        for j in range(threshold-1):
            share += coefficients[j] * (x) ** (j+1)
        share += secret
        
        share = share % prime
        shares.append([x, share])

    return shares
    

if __name__ == '__main__':
    secret = int(input("Secret: "))
    numOfShares = int(input("Number of shares: "))
    threshold = int(input("Threshold: "))
    prime = int(input("Prime: "))

    print("Shares: " + str(generateShares(secret, numOfShares, threshold, prime)))