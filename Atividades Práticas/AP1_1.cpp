#include <iostream>

void mergeSort(int *array, int l, int r);
void merge(int *array, int l, int r);

int main() {

    int c;
    std::cin >> c;
    int **listaArrays = new int *[c];
    int *tam = new int[c];
    for (int i = 0; i < c; i++) {
        std::cin >> tam[i];
        listaArrays[i] = new int[tam[i]];
        for (int j = 0; j  < tam[i]; j++) {
            std::cin >> listaArrays[i][j];
        }
        mergeSort(listaArrays[i], 0, tam[i]-1);
    }

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < tam[i]; j++) {
            std::cout << listaArrays[i][j] << ' ';
        }
        std::cout << '\n';
    }
    
    for (int i = 0; i < c; i++) {
        delete[] listaArrays[i];
    }
    delete[] listaArrays;

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
