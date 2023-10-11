import math
import sys
sys.setrecursionlimit(100000) 

def IsHappyNumber(n,visited) :
    while True : 
        if n ==  1  : 
            return True,visited
        if n in visited  :
            return False,visited
        visited.append(n)
        n = sum([int(c) * int(c) for c in str(n)])


def RecursiveHappyNumber(n,visited) : 
    if n == 1 : 
        return True,visited
    if n in visited : 
        return False,visited
    visited.append(n)
    n = sum([int(c) * int(c) for c in str(n)])
    return IsHappyNumber(n,visited)
    


visited = []

isHappy,visited = IsHappyNumber(19,visited)
##isHappy,visited = RecursiveHappyNumber(19,visited)
print(isHappy)
print(visited)
    





