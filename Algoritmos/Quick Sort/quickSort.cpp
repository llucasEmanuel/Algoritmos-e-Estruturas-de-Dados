#include <iostream>

void quickSort(int *array, int l, int r);
int partition(int *array, int l, int r);
void swap(int *a, int *b);

int main() {

    int array[5] = {5, 7, 1, 3, 2};
    quickSort(array, 0, 4);
    for (int element : array) {
        std::cout << element << ' ';
    }
    std::cout << '\n';

    return 0;
}

void quickSort(int *array, int l, int r) {
    if (l < r) {
        int p = partition(array, l, r);
        quickSort(array, l, p-1);
        quickSort(array, p+1, r);
    }
}

int partition(int *array, int l, int r) {
    int pivot = array[l];
    int i = l;
    int j = r+1;
    do {
        do {
            i++;
        } while (array[i] < pivot && i <= r);
        do {
            j--;
        } while (array[j] > pivot);
        swap(&array[i], &array[j]);
    } while (i < j);
    swap(&array[i], &array[j]);
    swap(&array[j], &array[l]);
    return j;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp; 
}
