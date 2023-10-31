#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *array, int l, int r);
void merge(int *array, int l, int r);
int binaryCounter(int *array, int l, int r, int val);

// contar todos os pares de numeros que a diferenca eh igual a k

int main() {

    int n, k;
    scanf("%d %d", &n, &k);
    int *numeros = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &numeros[i]);
    }
    mergeSort(numeros, 0, n-1);
    int cont = 0;
    for (int i = 0; i < n; i++) {
        int val = numeros[i] + k;
        cont += binaryCounter(numeros, 0, n-1, val);
    }
    printf("%d", cont);

    free(numeros);
    return 0;
}

void mergeSort(int *array, int l, int r) {
    if (l < r) {
        int m = (l+r)/2;
        mergeSort(array, l, m);
        mergeSort(array, m+1, r);
        merge(array, l, r);
    }
}
void merge(int *array, int l, int r) {
    int m = (l+r)/2;
    int i1 = l;
    int i2 = m+1;
    int *temp = (int *) malloc((r+1) * sizeof(int));
    for (int i = l; i <= r; i++) {
        temp[i] = array[i];
    }
    for (int curr = l; curr <= r; curr++) {
        if (i1 == m+1) {
            array[curr] = temp[i2++];
        }
        else if (i2 > r) {
            array[curr] = temp[i1++];
        }
        else if (temp[i1] <= temp[i2]) {
            array[curr] = temp[i1++];
        }
        else {
            array[curr] = temp[i2++];
        }
    }
    free(temp);
}

int binaryCounter(int *array, int l, int r, int val) {
    int cont = 0;
    while (l <= r) {
        int m = (l+r)/2;
        if (array[m] == val) {
            cont++;
            l = r+1;
        }
        else if (val > array[m]) {
            l = m+1;
        }
        else {
            r = m-1;
        }
    }
    return cont;
}