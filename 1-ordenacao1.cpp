#include <iostream>

void printArray(int *array, int tam);
void swap(int *a, int *b);
void bubbleSort(int *array, int tam);
void selectionSort(int *array, int tam);
void insertionSort(int *array, int tam);
void mergeSort(int *array, int l, int r);
void merge(int *array, int l, int r);

int main() {

    int array[5] = {5, 4, 3, 2, 1};
    //bubbleSort(array, 5);
    //selectionSort(array, 5);
    //insertionSort(array, 5);
    mergeSort(array, 0, 4);
    printArray(array, 5);

    return 0;
}

void printArray(int *array, int tam) {
    for (int i = 0; i < tam; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << '\n';
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int *array, int tam) {
    for (int i = 0; i < tam - 1; i++) { // passa por cada elemento da array ate o penultimo
        for (int j = 0; j < tam - 1 - i; j++) { // passa novamente por todos os elementos com reducao de i a cada iteracao (o maior ja fica no ultimo e nao precisa comparar mais)
            if (array[j] > array[j+1]) { // compara cada par de elementos adjacentes -> se o da esquerda for maior
                swap(&array[j], &array[j+1]); // troca eles de posicao
            }
        }
    } // repete ate comparar todo mundo com todo mundo e checar se todos estao ordenados com todos
}

void selectionSort(int *array, int tam) {
    for (int i = 0; i < tam - 1; i++) {// passa por todos os elementos ate o penultimo
        int min = i; // supor que o indice desse elemento eh o indice do menor elemento
        for (int j = i + 1; j < tam; j++) { // comparar com os elementos da direita ate o fim
            if (array[j] < array[min]) { // se houver algum elemento menor (e j eh o indice dele)
               min = j; // o indice do elemento menor agora eh j
            } 
        } // se nao houver elemento menor alem de i, entao i ja esta na posicao certa e o swap nao muda nada
        swap(&array[i], &array[min]); // troca as posicoes do elemento originalmente menor (ind = i) com o do real menor (ind = min)
    }
}

void insertionSort(int *array, int tam) {
    for (int i = 1; i < tam; i++) { // comeca a partir do segundo elemento da array
        int key = array[i]; // seleciona o elemento qur vai comparar
        int j = i - 1; // inicia o indice no primeiro a esquerda da key
        while (j >= 0 && array[j] >= key) { // compara ate o fim da array ou ate achar um elemento menor ou igual
            array[j+1] = array[j]; // empurra os elementos para a direita (abrir espaco para inserir a key)
            j--; // reduz o indice (prox elemento a esquerda)
        } // se j == -1, entao key eh o menor elemento (insere no indice 0 da array)
        array[j+1] = key;// se saiu pq array[j] < key, entao insere a key a direita dele
    }
}

void mergeSort(int *array, int l, int r) { // 'l' eh o limite esquerdo (indice 0) e 'r' o limite direito (indice tam-1)
    if (l < r) { // checa se o array nao eh unitario
        int m = (int) ((l + r) / 2); // o meio eh o floor de (l+r)/2
        mergeSort(array, l, m); // chamada recursiva pra esquerda
        mergeSort(array, m+1, r); // chamada recursiva pra direita
        merge(array, l, r); // quando acabar o loop recursivo ocorre o merge entre as duas metades que ja estao ordenadas
    }    
    // as chamadas recursivas vao ocorrer ate o fragmento da esquerda ser unitario e depois ele faz o caminho inverso e executa a recursao na segunda metade
    // quando a segunda recursao acabar, vao ter duas metades ordenadas (ou dois fragmentos unitarios) e o merge vai cuidar em juntar eles de forma ordenada
}

void merge(int *array, int l, int r) {
    int *temp = new int[r+1]; // criar um array temporario
    for (int i = l; i <= r; i++) { // copia os elementos do array do argumento
        temp[i] = array[i];
    }
    int m = (int) ((l+r) / 2); // calcular o meio
    int i1 = l, i2 = m+1; // indices das posicoes iniciais de cada metade
    for (int curr = l; curr <= r; curr++) { // usa um cursor que preenche o array com os elementos ordenados
    // i1 e i2 sao indices que passam pelos elementos de seus respectivos fragmentos e comparam eles entre si
        if (i1 == m+1) { // copiou todos os valores do primeiro fragmento
            array[curr] = temp[i2];
            i2++;
        }
        else if (i2 > r) { // copiou todos os valores do segundo fragmento
            array[curr] = temp[i1];
            i1++;
        }
        else if (temp[i1] <= temp[i2]) {
            array[curr] = temp[i1];
            i1++;
        }
        else {
            array[curr] = temp[i2];
            i2++;
        }
    }
    delete[] temp;
}
