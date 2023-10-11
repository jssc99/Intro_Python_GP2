from ast import Module
import sys
sys.setrecursionlimit(100000)
from cmath import *

# SORT ARRAY (SELECTION)
def SortShell(t : list) :
    cpt = len(t)
    for i in range (cpt-1) :
        mini = i
        for j in range (i+1, cpt) :
            if t[j] < t[mini] :
                mini = j
        if mini != i :
            temp = t[mini]
            t[mini] = t[i]
            t[i] = temp

v = [1,5,2,4,3,8]
print("starting list :", v)
SortShell(v)
print("sorted: ", v)
v = [1,5,2,3,8]
print("starting list :", v)
SortShell(v)
print("sorted: ", v, "\n")

# HAPPY NUMBERS
def IsHappyNumber(numb : int, visited : set) :
    while numb > 1 and numb not in visited :
        visited.add(numb)
        numb = sum([int(c)**2 for c in str(numb)])
    return numb == 1
     
happyVisited = set()
n = 1
print(n, "is a happy number :", IsHappyNumber(n, happyVisited), ", number(s) visited :", happyVisited);
happyVisited.clear()
n = 10
print(n, "is a happy number :", IsHappyNumber(n, happyVisited), ", number(s) visited :", happyVisited);
happyVisited.clear()
n = 101
print(n, "is a happy number :", IsHappyNumber(n, happyVisited), ", number(s) visited :", happyVisited);
happyVisited.clear()
n = 23
print(n, "is a happy number :", IsHappyNumber(n, happyVisited), ", number(s) visited :", happyVisited);
happyVisited.clear()
n = 3
print(n, "is a happy number :", IsHappyNumber(n, happyVisited), ", number(s) visited :", happyVisited, "\n");

# HAPPY REC
def IsHappyNumberRecursive(numb : int, visited : set) :
    visited.add(numb)
    numb = sum([int(c)**2 for c in str(numb)])
    if numb > 1 and numb not in visited:
        return IsHappyNumberRecursive(numb, visited)
    else :
        return numb == 1
    
happyVisited = set()
n = 1
print(n, "is a happy number :", IsHappyNumberRecursive(n, happyVisited), ", number(s) visited :", happyVisited);
happyVisited.clear()
n = 10
print(n, "is a happy number :", IsHappyNumberRecursive(n, happyVisited), ", number(s) visited :", happyVisited);
happyVisited.clear()
n = 101
print(n, "is a happy number :", IsHappyNumberRecursive(n, happyVisited), ", number(s) visited :", happyVisited);
happyVisited.clear()
n = 23
print(n, "is a happy number :", IsHappyNumberRecursive(n, happyVisited), ", number(s) visited :", happyVisited);
happyVisited.clear()
n = 3
print(n, "is a happy number :", IsHappyNumberRecursive(n, happyVisited), ", number(s) visited :", happyVisited, "\n");

# HORNER
def Horner(p : list, x):
    result = 0
    for i in range(len(p)) :
        result += p[i] * (x ** i)
    return result

poly = [2,3,-5,0,1]
x = 1
print("for list:", poly, "with x =", x, "result is:", Horner(poly, x));
x = 2
print("for list:", poly, "with x =", x, "result is:", Horner(poly, x));
poly = [3,-3,-1,10,2]
x = 1
print("for list:", poly, "with x =", x, "result is:", Horner(poly, x));
x = 2
print("for list:", poly, "with x =", x, "result is:", Horner(poly, x));
x = 0
print("for list:", poly, "with x =", x, "result is:", Horner(poly, x), "\n");

# COMPLEX
def IsDiverging(f, z0 : complex, radius : float, n : int):
    z = z0
    for i in range(n) :
        z = f(z)
        if (abs(z) > radius) :
            return True
    return False

z = 3+5j
n = 3
rad = 3.1415
f = lambda z : z**2 - z + 0.1
fstr = "z**2 - z + 0.1"
print("for f:", fstr, "with z =", z, "and n =", n, "and radius", rad, "IsDiverging is:", IsDiverging(f, z, rad, n))
rad = 100
n = 1
print("for f:", fstr, "with z =", z, "and n =", n, "and radius", rad, "IsDiverging is:", IsDiverging(f, z, rad, n))
