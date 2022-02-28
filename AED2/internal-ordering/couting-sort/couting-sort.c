//Método de Ordenação Interna Linear Estável - Couting Sort

#include <stdio.h>
#include <stdlib.h>

//Funções
void Couting_Sort(int *A, int *B, int k, int n);
void Imprime(int *Final, int n);

void Couting_Sort(int *A, int *B, int k, int n) {
    int C[k], i, j, aux; 
    
    for(i=0; i<k; i++) 
        C[i] = 0;
   
    for(j=0; j<n; j++) 
        C[A[j]]++;
   
    for(i=1; i<k; i++) 
        C[i] = C[i]+C[i-1]; 
       
    for(j=n-1; j>=0; j--) { 
        B[C[A[j]]-1] = A[j];
        C[A[j]]--; 
    }
}

void Imprime(int *Final, int n) {
    int i;
    for(i=0; i<n; i++) 
        printf("%d ", Final[i]);
    printf("\n");
}

int main() {
    int n, i, aux=0, maior=0, k;
    int *Vetor, *Final;
   
    printf("Digite a quantidade de números a serem ordenados: ");
    scanf("%d", &n); 
    
    Vetor = (int*)malloc(n*sizeof(int));
    Final = (int*)malloc(n*sizeof(int));
   
    for(i=0; i<n; i++) {
        scanf("%d", &Vetor[i]);
        aux = Vetor[i];
        if(aux > maior)
            maior = aux;
    }
    
    Couting_Sort(Vetor, Final, maior+1, n); 
    Imprime(Final, n); 
    
    free(Vetor);
    free(Final);

    return 0;
}
