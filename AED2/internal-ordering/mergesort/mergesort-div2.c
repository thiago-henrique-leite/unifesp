//MÉTODO DE ORDENAÇÃO MERGESORT

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void MERGE(int *A, int p, int q, int r) {
    int i, j, n1, n2;
    
    n1 = q - p + 1;
    n2 = r - q;
    
    int L[n1+1], R[n2+1];
    
    for(i=0; i<n1; i++)
        L[i] = A[p+i];
    for(j=0; j<n2; j++)
        R[j] = A[q+j+1];
    
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    
    i = j = 0;
    
    int k;
    for(k=p; k<=r; k++) {
        if(L[i]<=R[j]) {
            A[k] = L[i];
            i = i+1;
        } else {
            A[k] = R[j];
            j = j+1;
        }
    }
    
}

void MERGESORT(int *A, int p, int r) {
    int q;
    if(p<r) {
        q = (p+r)/2;
        MERGESORT(A, p, q);
        MERGESORT(A, q+1, r);
        MERGE(A, p, q, r);
    }
}

int main(void) {
    int *nums;
    int i, tamanho;
    
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);
    
    nums = (int*)malloc(tamanho*sizeof(int));
    
    for(i=0; i<tamanho; i++) 
        scanf("%d", &nums[i]);
    
    MERGESORT(nums, 0, tamanho-1);
    
    for(i=0; i<tamanho; i++) 
        printf("%d\n", nums[i]);
}
