import math

def mergesort(arr, l, r):
    if l < r:
        m = math.floor((l+r)/2)
        mergesort(arr, l, m)
        mergesort(arr, m+1, r)
        merge(arr, l, r)

def merge(arr, l, r):
    temp = arr.copy()
    m = math.floor((l+r)/2)
    i1 = l
    i2 = m+1
    for curr in range(l, r+1):
        if i1 == m+1:
            arr[curr] = temp[i2]
            i2 += 1
        elif i2 > r:
            arr[curr] = temp[i1]
            i1 += 1
        elif temp[i1] <= temp[i2]:
            arr[curr] = temp[i1]
            i1 += 1
        else:
            arr[curr] = temp[i2]
            i2 += 1


def quicksort(arr, l, r):
    if (l < r):
        s = partition(arr, l, r)
        quicksort(arr, l, s-1)
        quicksort(arr, s+1, r)

def partition(arr, l, r):
    p = arr[l]
    i = l
    j = r+1
    while True:
        while True:
            i += 1
            if arr[i] >= p or i >= r:
                break
        while True:
            j -= 1
            if arr[j] <= p:
                break
        arr[i], arr[j] = arr[j], arr[i]
        if i >= j:
            break
    arr[i], arr[j] = arr[j], arr[i]
    arr[l], arr[j] = arr[j], arr[l]
    return j


