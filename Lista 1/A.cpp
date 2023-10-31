#include <iostream>

// void mergeSort(int *array, int l, int r);
// void merge(int *array, int l, int r);
void quickSort(int *array, int l, int r);
int HoarePartition(int *array, int l, int r);
void swap(int *a, int *b);

int main() {

    // n barras de chocolate
    // a barra de indice i custa a[i]
    // comprar todas as barras
    // m cupons para comprar barras
    // a barra mais barata sai de graca
    int n; // numero de barras de chocolate 
    std::cin >> n;
    //if (n < 2 || n > 30000) return 0;
    int *precos = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> precos[i];
    }
    quickSort(precos, 0, n-1); // o mais barato eh o do primeiro indice

    int m; // numero de cupons
    std::cin >> m;
    int *qtdBarrasCupom = new int[m];
    for (int i = 0; i < m; i++) {
        std::cin >> qtdBarrasCupom[i];
    }

    int soma = 0;
    for (int i = 0; i < m; i++) { // output qd i == 0 é o preco de comprar qtdBarrasCupom[i] barras
        // comecar a contar o preco a partir da segunda barra
        // funcionamento do cupom:
            // escolhe as barras mais caras
            // voce nao paga a mais barata desse conjunto das mais caras
        // as outras barras alem do numero do cupom sao pagas integralmente
        for (int j = 0; j < n; j++) {
            if (j == qtdBarrasCupom[i] - 1)
                soma += precos[j];
        }
        std::cout << soma << '\n';
        soma = 0;
    }

    delete[] qtdBarrasCupom;
    delete[] precos;
    return 0;
}

void quickSort(int *array, int l, int r) {
    if (l < r) {
        int p = HoarePartition(array, l, r); // p eh o indice  do pivot
        quickSort(array, l, p-1); // parte antes do pivot
        quickSort(array, p+1, r); // parte depois do pivot
    }
}

int HoarePartition(int *array, int l, int r) {
    int pivot = array[l]; // pivot eh o elemento mais a esquerda
    int i = l; // incrementado (i inicia no indice inicial do pivo, que eh o mais a esquerda)
    int j = r + 1; // decrementado (incicia um indice depois do ultimo elemento do array)
    do {
        do {
            i++;
        } while (array[i] > pivot && i < r); // ate encontrar o primeiro elemento maior que o pivot
        do {
            j--;
        } while (array[j] < pivot); // ate encontrar o primeiro elemento menor que o pivot
        swap(&array[i], &array[j]); // quando i>= j o swap eh executado por ser checar depois
    } while (i < j); // repetir ate o i cruzar o j
    swap(&array[i], &array[j]); // desfaz o ultimo swap
    // j armazena um elemento que eh menor que o pivo
    // logo array[j] deve ficar a esquerda do pivot (que esta no indice l)
    swap(&array[l], &array[j]);// pivot posicionado no indice j com o swap
    return j; // retorna o indice em que o pivot ficou
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
