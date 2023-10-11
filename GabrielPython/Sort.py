
def BubbleSort(list) : 
    swap = True
    while(swap is True ) :
        swap = False
        for i in list  :
            if list.index(i) == len(list) - 1: 
                 break

            if i > list[list.index(i)+1]:
                    temp = i
                    previndex = list.index(i) +1
                    list[list.index(i)] = list[list.index(i) + 1]
                    list[previndex] = temp
                    swap = True
                             




v = [1,4,2,5,3]
BubbleSort(v)
print(v)
     




