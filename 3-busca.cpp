#include <iostream>

int sequentialSearch(int *array, int tam, int element);
int binarySearch(int *array, int l, int r, int element);

int main() {

    int array[5] = {1, 2, 3, 4, 5};
    int valor;
    std::cout << "Digite o valor que deseja encontrar na array: ";
    std::cin >> valor;
    int indice = binarySearch(array, 0, 4, valor);
    if (indice != -1) {
        for (int i = 0; i < 5; i++) {
            if (i == indice) {
                std::cout << array[i] << " ";
            }
            else {
                std::cout << "x ";
            }
        }
        std::cout << '\n';
        std::cout << array[indice] << " encontrado no indice " << indice << '\n';
    }
    else {
        std::cout << "Valor nao encontrado.\n";
    }

    return 0;
}

int sequentialSearch(int *array, int tam, int element) {
    for (int i = 0; i < tam; i++) { // passa por cada elemento ate achar (ou nao) o valor
        if (array[i] == element) {
            return i;
        }
    }
    return -1;
}

int binarySearch(int *array, int l, int r, int element) { // array deve estar ordenado previamente (nesse caso em ordem crescente)
    if (l <= r) { // ate o array ser repartido em um array unitario
        int m = (l + r) / 2; // indice do meio
        if (array[m] == element) { // achou
            return m;
        }
        else if (element > array[m]) { // se o elemento for maior vai pra parte direita
            return binarySearch(array, m+1, r, element);
        }
        else { // se for menor vai pra esquerda
            return binarySearch(array, l, m-1, element);
        }
    }
    return -1; // nao achou o elemento
}
