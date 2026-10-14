#include <stdio.h>
#include <stdlib.h>

int merge(int array[], int esquerda, int meio, int direita) {
    int i, j, k;
    int tamanhoEsquerda = meio - esquerda;
    int tamanhoDireita = direita - meio;

    int *subarrayEsquerda = (int *)malloc(sizeof(int) * tamanhoEsquerda);
    int *subarrayDireita = (int *)malloc(sizeof(int) * tamanhoDireita);

    int inversoes = 0;

    for (i = 0; i < tamanhoEsquerda; i++)
        subarrayEsquerda[i] = array[esquerda + i];
    for (j = 0; j < tamanhoDireita; j++)
        subarrayDireita[j] = array[meio + j];

    i = 0, j = 0, k = esquerda;

    while (i < tamanhoEsquerda && j < tamanhoDireita) {
        if (subarrayEsquerda[i] <= subarrayDireita[j]) {
            array[k++] = subarrayEsquerda[i++];
        } else {
            array[k++] = subarrayDireita[j++];
            inversoes += (tamanhoEsquerda - i);
        }
    }

    while (i < tamanhoEsquerda)
        array[k++] = subarrayEsquerda[i++];
    while (j < tamanhoDireita)
        array[k++] = subarrayDireita[j++];

    free(subarrayEsquerda);
    free(subarrayDireita);

    return inversoes;
}

int mergeSort(int array[], int left, int right) {
    int totalInversoes = 0;

    if (right - left > 1) {
        int mid = left + (right - left) / 2;

        totalInversoes += mergeSort(array, left, mid);
        totalInversoes += mergeSort(array, mid, right);
        totalInversoes += merge(array, left, mid, right);
    }

    return totalInversoes;
}

int main() {
    int tamanho, *array;

    scanf("%d", &tamanho);

    array = (int *)malloc(sizeof(int) * tamanho);

    for (int i = 0; i < tamanho; i++) {
        scanf("%d", &array[i]);
    }

    int totalInversoes = mergeSort(array, 0, tamanho);

    printf("%d\n", totalInversoes);

    free(array);

    return 0;
}