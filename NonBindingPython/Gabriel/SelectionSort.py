
def SelectionSort(list) :
    indexStart = 0 
    temp = 0 
    while indexStart < len(list) - 1  : 
        min = indexStart
        j = indexStart + 1
        while j < len(list) : 
            if list[j] < list[min] : 
                min = j
            j += 1
        if min != indexStart : 
            temp = list[min]
            list[min] = list[indexStart]
            list[indexStart] = temp
        indexStart += 1

            













l = [5,6,2,1,10,5,6,8,9,14]

SelectionSort(l)
print(l)