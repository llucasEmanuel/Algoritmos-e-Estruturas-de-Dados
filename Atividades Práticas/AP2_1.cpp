#include <iostream>

void quickSort(int *array, int l, int r);
int partition(int *array, int l, int r);
void swap(int *a, int *b);

int main() {

    int c;
    std::cin >> c;
    int **listaArrays = new int *[c]; // aloca c ponteiros
    int *tam = new int[c];
    for (int i = 0; i < c; i++) {
        std::cin >> tam[i];
        listaArrays[i] = new int[tam[i]]; // aloca a qtd de espacos de caad array
        for (int j = 0; j  < tam[i]; j++) {
            std::cin >> listaArrays[i][j];
        }
        quickSort(listaArrays[i], 0, tam[i]-1);
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
        } while (array[i] > pivot && i <= r);
        do {
            j--;
        } while (array[j] < pivot);
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
