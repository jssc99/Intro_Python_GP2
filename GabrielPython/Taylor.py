import math
import sys

def Factorial(value) :
    i = 1 
    if(value == 0 ):
        value = 1
        

    startvalue = value
    while(i != startvalue) :
         value *= i
         i += 1
    return value

    
def abs(absvalue):
    if absvalue < 0:
        absvalue = -absvalue

    return absvalue


def Cos(x,epsilon = sys.float_info.epsilon) : 
    rank = 0
    returnValue = 0 
    addvalue = sys.float_info.max; 
    while( abs(addvalue) > epsilon) : 
        term1 =  math.pow(float(-1),rank )
        term2 = 2 * rank
        term2 = Factorial(term2)
        term3 =  math.pow(x,(2 * rank )) 
        addvalue   = (term1 / term2 ) * term3
        returnValue +=  addvalue
        rank += 1
    
    return returnValue


def Sin(x,epsilon = sys.float_info.epsilon) : 
    rank = 0
    returnValue = 0 
    addvalue = sys.float_info.max; 
    while( abs(addvalue) > epsilon) : 
        term1 =  math.pow(float(-1),rank )
        term2 = 2 * rank + 1
        term2 = Factorial(term2)
        term3 =  math.pow(x,(2 * rank  + 1 )) 
        addvalue  = (term1 / term2 ) * term3
        returnValue +=  addvalue
        rank += 1
    
    return returnValue





myrad = math.radians(-20)

myrad = Cos(myrad)

print(myrad)

##print (math.cos(math.radians(60)))

