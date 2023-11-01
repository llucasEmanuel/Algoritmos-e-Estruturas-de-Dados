#include <iostream>

void mergeSort(int *array, int l, int r);
void merge(int *array, int l, int r);

int main() {

    int array[5] = {5, 7, 1, 3, 2};
    mergeSort(array, 0, 4);
    for (int element : array) {
        std::cout << element << ' ';
    }
    std::cout << '\n';
 
    return 0;
}

void mergeSort(int *array, int l, int r) {
    if (l < r) {
        int m = (l+r) / 2;
        mergeSort(array, l, m);
        mergeSort(array, m+1, r);
        merge(array, l, r);
    }
}

void merge(int *array, int l, int r) {
    int *temp = new int[r+1];
    for (int i = l; i < r + 1; i++) {
        temp[i] = array[i];
    }
    int m = (l+r) / 2;
    int i1 = l;
    int i2 = m+1;
    for (int curr = l; curr < r + 1; curr++) {
        if (i1 == m+1) {
            array[curr] = temp[i2];
            i2++;
        }
        else if (i2 > r) {
            array[curr] = temp[i1];
            i1++;
        }
        else if (temp[i1] >= temp[i2]) {
            array[curr] = temp[i2];
            i2++;
        }
        else {
            array[curr] = temp[i1];
            i1++;
        }
    }
    delete[] temp;
}
