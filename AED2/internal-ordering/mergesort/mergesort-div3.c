//MÉTODO DE ORDENAÇÃO MERGESORT

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void MERGE(int *A, int p, int q, int t, int r) {
    int i, j, x, n1, n2, n3;
    
    n1 = q - p + 1;
    n2 = t - q;
    n3 = r - t;
    
    int L[n1+1], M[n2+1], R[n3+1];
    
    for(i=0; i<n1; i++)
        L[i] = A[p+i];
    for(j=0; j<n2; j++)
        M[j] = A[q+j+1];
    for(x=0; x<n3; x++)
        R[x] = A[t+x+1];
    
    L[n1] = INT_MAX;
    M[n2] = INT_MAX;
    R[n3] = INT_MAX;
    
    i=j=x=0;
    
    int k;
    for(k=p; k<=r; k++) {
        if(L[i]<=M[j] && L[i]<=R[x]) {
            A[k] = L[i];
            i = i+1;
        } else if(M[j]<=L[i] && M[j]<=R[x]) {
            A[k] = M[j];
            j = j+1;
        } else if(R[x]<=L[i] && R[x]<=M[j]) {
            A[k] = R[x];
            x = x+1;
        }
    }
    
}

void MERGE_SORT(int *A, int p, int r) {
    int q, t;
    if(p<r) {
        q = (p+r)/3;
        if(q<p) q = p;
        t = ((r+1)-q)/2 + q;
        MERGE_SORT(A, p, q);
        MERGE_SORT(A, q+1, t);
        MERGE_SORT(A, t+1, r);
        MERGE(A, p, q, t, r);
    }
}

int main(void) {
    int *nums;
    int i, tamanho;
    
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);
    
    nums = (int*)malloc(tamanho*sizeof(int));
    
    for(i=0; i<tamanho; i++) {
        scanf("%d", &nums[i]);
    }
    
    MERGE_SORT(nums, 0, tamanho-1);
    
    for(i=0; i<tamanho; i++) {
        printf("%d\n", nums[i]);
    }
}
