import math

def binary_search(array, l, r, target):
    if l <= r:
        m = math.floor((l+r)/2)
        if array[m] == target:
            return m
        elif target > array[m]:
            return binary_search(array, m+1, r, target)
        else:
            return binary_search(array, l, m-1, target)
    return -1

array = [1, 2, 3, 5, 7]
index1 = binary_search(array, 0, len(array)-1, 5)
index2 = binary_search(array, 0, len(array)-1, 0)
print(index1, index2)
