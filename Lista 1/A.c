#include <stdio.h>

void quickSort(int *array, int l, int r);
int HoarePartition(int *array, int l, int r);

int main() {
    int n;
    scanf("%d", &n);
    int precos[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &precos[i]);
    }
    quickSort(precos, 0, n-1);

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

void quickSort(int *array, int l, int r) {
    if (l < r) {
        int p = HoarePartition(array, l, r);
        quickSort(array, l, p-1);
        quickSort(array, p+1, r); 
    }
}

int HoarePartition(int *array, int l, int r) {
    int pivot = array[l];
    int i = l;
    int j = r + 1;
    int temp;
    do {
        do {
            i++;
        } while (array[i] > pivot && i < r);
        do {
            j--;
        } while (array[j] < pivot);
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    } while (i < j);

    temp = array[i];
    array[i] = array[j];
    array[j] = temp;

    temp = array[l];
    array[l] = array[j];
    array[j] = temp;
    return j;
}
