def swap(array, i, j):
    array[i], array[j] = array[j], array[i]

def partition(array, l, r):
    pivot = array[l]
    i = l
    j = r + 1

    while True:
        while True:
            i += 1
            if array[i] >= pivot or i >= r:
                break
        while True:
            j -= 1
            if array[j] <= pivot:
                break
        swap(array, i, j)
        if i >= j:
            break
    swap(array, i, j)
    swap(array, j, l)
    return j

def quickSort(array, l, r):
    if l < r:
        p = partition(array, l, r)
        quickSort(array, l, p - 1)
        quickSort(array, p + 1, r)
      
array = [5, 7, 1, 3, 2]

quickSort(array, 0, len(array) - 1)
print(array)
