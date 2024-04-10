import math

def bsearch(arr, target):
    l = 0
    r = len(arr)-1
    while l <= r:
        m = math.floor((l+r)/2)
        if target == arr[m]:
            return m
        elif target < arr[m]:
            r = m-1
        else:
            l = m+1
    return -1
