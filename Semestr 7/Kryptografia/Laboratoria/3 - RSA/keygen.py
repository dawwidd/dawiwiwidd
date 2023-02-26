import numpy as np
import math

def is_prime(x):
    if x == 2:
        return True
    if x % 2 == 0 or x <= 1:
        return False

    sqrt_x = int(math.sqrt(x))+1

    for n in range(3, sqrt_x, 2):
        if x % n == 0:
            return False
        
    return True

def moduloInverse(a,b):
    if math.gcd(a,b) != 1:
        return None
    x, y, z = 1, 0, a
    k, l, m = 0, 1, b
    
    while m != 0:
        q = z//m
        k, l, m, x, y, z = (x - q*k), (y - q*l), (z - q*m), k, l, m
    
    return x % b

if __name__ == '__main__':
    p, q = int(input("p: ")), int(input("q: "))
    if not (is_prime(p) and is_prime(q)):
        print("p i q muszą być liczbami pierwszymi")
    
    n = p*q
    phi = (p-1)*(q-1)
    e = 2
    while math.gcd(e, phi) != 1:
        e += 1
        
    d = moduloInverse(e, phi)
    
    print("phi: " + str(phi))
    print("n (p*q): " + str(p*q))
    print("public key: " + str(e))
    print("private key: " + str(d))
 
