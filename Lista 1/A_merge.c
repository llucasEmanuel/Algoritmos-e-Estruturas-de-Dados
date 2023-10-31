#include <stdio.h>

void mergeSort(int *array, int l , int r);
void merge(int *array, int l , int r);

int main() {
    int n;
    scanf("%d", &n);
    int precos[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &precos[i]);
    }
    mergeSort(precos, 0, n-1);

    int m;
    scanf("%d", &m);
    int qtdBarrasCupom[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &qtdBarrasCupom[i]);
    }

    int soma = 0;
    for (int i = 0; i < m; i++) {
        int j;
        for (j = 0; j < qtdBarrasCupom[i] - 1; j++) {
            soma += precos[j];
        }
        j++;
        while (j < n) {
            soma += precos[j];
            j++;
        }
        printf("%d\n", soma);
        soma = 0;
    }
    return 0;
}

void mergeSort(int *array, int l , int r) {
    if (l < r) {
        int m = (l+r)/2;
        mergeSort(array, l, m);
        mergeSort(array, m+1, r);
        merge(array, l, r);
    }
}
void merge(int *array, int l , int r) {
    int m = (l+r)/2;
    int i1 = l;
    int i2 = m+1;
    int temp[r+1];
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
            array[curr] = temp[i2++];
        }
        else {
            array[curr] = temp[i1++];
        }
    }
}
