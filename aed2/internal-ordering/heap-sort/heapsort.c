#include <stdio.h>
#include <stdlib.h>
#define MAX 10000 //Tamanho máximo de um array
 
//Cabeçalho de Funções
void HEAPSORT(int V[], int tam);
void BUILD_MAX_HEAP(int V[], int tam);
void MAX_HEAPFY(int V[], int i, int tam);
int  HEAP_EXTRACT_MAX(int V[], int tam);
int  swap(int *x, int *y);
void ImprimeVetor(int V[], int tam);
 
int main() {
    int V[MAX], n, i;
   
    //printf("Digite a quantidade de valores do vetor: ");
    scanf("%d", &n);
   
    for(i=1; i<n+1; i++) //Lê os n valores do array lado a lado
        scanf("%d", &V[i]);
   
    HEAPSORT(V, n);
    return 0;
}
 
//Método de ordenação interna HEAPSORT
void HEAPSORT(int V[], int tam) {
    BUILD_MAX_HEAP(V, tam);
    ImprimeVetor(V, tam); //Imprime o array após a construção o heap
    int n = tam;
    int A[n+1];
    while (n>0) {
        A[n] = HEAP_EXTRACT_MAX(V, n);
        n--;
    }
    ImprimeVetor(A, tam); //Imprime o vetor já ordenado
}
 
//Constrói um heap máximo
void BUILD_MAX_HEAP(int V[], int tam) {
    int i, n;
    n = tam;
    for(i=n/2; i>0; i--)
        MAX_HEAPFY(V, i, tam);
}
 
//Encontra o maior elemento do heap
void MAX_HEAPFY(int V[], int i, int tam) {
    int max, l, r;
    l = 2*i;
    r = 2*i+1;
   
    if(l<=tam && V[l]>V[i])
        max = l;
    else max = i;
    if(r<=tam && V[r]>V[max])
        max = r;
   
    if(max!=i) {
        swap(&V[i], &V[max]);
        MAX_HEAPFY(V, max, tam);
    }
}
 
//Retira o maior elemento do array e decrementa seu tamanho
int HEAP_EXTRACT_MAX(int V[], int tam) {
    int max, last;
    if(tam<1)
        return 0;
    max = V[1];
    last = tam;
    V[1] = V[last];
    tam--;
    MAX_HEAPFY(V, 1, tam);
    return max;
}
 
//Troca dois elementos do array de lugar
int swap(int *x, int *y) {
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}
 
//Imprime o array
void ImprimeVetor(int V[], int tam) {
    int j;
    for(j=1; j<tam+1; j++)
        printf("%d ", V[j]);
    printf("\n");
}