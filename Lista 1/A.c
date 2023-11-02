#include <stdio.h>
#include <stdlib.h>

void mergeSort(long long int *array, int l , int r);
void merge(long long int *array, int l , int r);

int main() {
    int n;
    scanf("%d", &n);
    long long int *precos = (long long int *) malloc(n * sizeof(long long int));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &precos[i]);
    }
    mergeSort(precos, 0, n-1); // ordena de forma decrescente

    int m;
    scanf("%d", &m);
    long long int *somas = (long long int *) malloc((n+1) * sizeof(long long int));
    somas[0] = 0;
    for (int i = 0; i < n; i++) {
        somas[i+1] = precos[i] + somas[i];
    }
    int qtdBarrasCupom;
    for (int i = 0; i < m; i++) {
        scanf("%d", &qtdBarrasCupom);
        printf("%lld\n", somas[n] - precos[qtdBarrasCupom-1]);
    }

    free(somas);
    free(precos);
    return 0;
}

void mergeSort(long long int *array, int l , int r) {
    if (l < r) {
        int m = (l+r)/2;
        mergeSort(array, l, m);
        mergeSort(array, m+1, r);
        merge(array, l, r);
    }
}
void merge(long long int *array, int l , int r) {
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
            array[curr] = temp[i2++];
        }
        else {
            array[curr] = temp[i1++];
        }
    }
    free(temp);
}
