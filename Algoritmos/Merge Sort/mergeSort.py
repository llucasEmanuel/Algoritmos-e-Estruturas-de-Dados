import math

def merge(array, l, r):
    m = math.floor((l + r) / 2)
    i1 = l
    i2 = m + 1

    temp = array.copy()

    for k in range(l, r + 1):
        if i1 == m + 1:
            array[k] = temp[i2]
            i2 += 1
        elif i2 > r:
            array[k] = temp[i1]
            i1 += 1
        elif temp[i1] <= temp[i2]:
            array[k] = temp[i1]
            i1 += 1
        else:
            array[k] = temp[i2]
            i2 += 1

def mergeSort(array, l, r):
    if l < r:
        m = math.floor((l + r) / 2)
        mergeSort(array, l, m)
        mergeSort(array, m + 1, r)
        merge(array, l, r)


array = [5, 7, 1, 3, 2]

mergeSort(array, 0, len(array) - 1)
print(array)
