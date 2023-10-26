#include <iostream>

void quicksort(int *array, int l, int r);
int partition(int *array, int l, int r);
void swap(int *a, int *b);

int main() {

    int array[5] = {5, 4, 3, 2, 1};
    quicksort(array, 0, 4);
    for (int i = 0; i < 5; i++) {
        std::cout << array[i];
    }
    std::cout << '\n';

    return 0;
}

void quicksort(int *array, int l, int r) {
    if (l < r) { // checa se array nao eh unitario
        int p = partition(array, l, r); // retorna indice do pivo (p)
        // os elementos antes do pivo sao menores que ele e os depois sao maiores
        quicksort(array, l, p-1); // elementos antes do pivo
        quicksort(array, p+1, r); // elementos depois do pivo
    }
}

int partition(int *array, int l, int r) {
    int pivo = array[r]; // seta o pivo inicialmente como o ultimo elemento da particao
    int i = l - 1; // comeca antes do primeiro indice (i == -1)

    for (int j = l; j <= r - 1; j++) {
        if (array[j] < pivo) { // se for menor que o pivo e estiver a esquerda
            i++;
            swap(&array[i], &array[j]);
        }
    }
    i++; // quando j chega no pivo incrementa o i
    swap(&array[i], &array[r]);
    return i; // i agora eh o indice do pivo
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}