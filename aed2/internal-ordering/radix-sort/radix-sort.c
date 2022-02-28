//Radix Sort utilizando o Couting Sort

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //Biblioteca da função "tolower"

char converte_pra_Minuscula(char letra) {
    letra = tolower(letra); //Converte uma letra maiúscula em minúscula
    return letra;
}

void EhMinusculo(char **nomes, int n, int maior) { //Verifica se todos os caracteres dos nomes são letras minúsculas
    int i, j, aux;
    for(i=0; i<n; i++) {
        for(j=0; j<maior; j++) {
            aux = nomes[i][j];
            if(aux>=65 && aux<=90)
                nomes[i][j] = converte_pra_Minuscula(nomes[i][j]); //Caso encontre uma letra maiúscula, chama a função que realiza a conversão
        }
    }
}

void Couting_Sort(char **A, char **B, int k, int n, int d) {
    int C[k], i, j, aux; //Inicia o vetor C com 26 espaços referentes as letras do alfabeto e o índice 0 para espaços vazios
    for(i=0; i<k; i++) //Zera o vetor C
        C[i] = 0;
   
    for(j=0; j<n; j++) {
        aux = A[j][d]-96; //A variável "aux" recebe o valor do caracter na tabela ASCII
        if(aux<1 || aux>26) //Se o caracter não for uma letra minúscula o campo do espaço é incrementado
            C[0]++;
        else
            C[aux]++; //Se não, a posição do vetor C no índice da respectiva posição da letra no alfabeto é incrementada
    }
   
    for(i=1; i<k; i++)
        C[i] = C[i]+C[i-1]; //Soma Pré-Fixa
       
    for(j=n-1; j>=0; j--) { //Loop para ordenar a coluna de caracteres
        aux = A[j][d]-96; //"aux" recebe a posicão do caracter na tabela ASCII
        if(aux>=1 && aux<=26) //Verifica se o caracter lido é uma letra
            B[C[aux]-1] = A[j];
        else {
            B[C[0]-1] = A[j];
            aux = 0;
        }
        C[aux]--; //O vetor C no índice de "aux" é decrementado
    }
   
    for(i=0; i<n; i++) //O vetor A recebe o vetor B já parcialmente organizado
        A[i] = B[i];
}

char** Radix_Sort(char **nomes, char **B, int d, int n) {
    int aux = d-1;
    for(int i=d; i>0; i--) {
        Couting_Sort(nomes, B, 27, n, aux); //Chama o CoutingSort para cada coluna de caracteres
        aux--;
    }
    return B; //Retorna o vetor com os nomes ordenados em ordem alfabética
}

int main() {
    int n, i, j, aux, maior=0;
    char **nomes, **final; //Ponteiros para ponteiro (vetor de strings)
   
    printf("Digite a quantidade de nomes a serem lidos: ");
    scanf("%d", &n); //n é referente ao número de nomes
   
    nomes = malloc(sizeof(char*)*n); //Aloca a memória do vetor "nomes", que receberá os nomes na ordem da entrada
    for(i=0;i<n;i++)
        nomes[i]=malloc(sizeof(char)*16);
   
    final =  malloc(sizeof(char*)*n); //Aloca a memória do vetor "final", que receberá os nomes devidamente ordenados
    for(i=0;i<n;i++)
        final[i]=malloc(sizeof(char)*16);
  
    printf("Entre com os %d nomes:\n", n);
    for(i=0; i<n; i++) { //Lê os nomes do usuário e grava o número de caracteres do maior nome
        scanf("%s", nomes[i]);
        aux = strlen(nomes[i]);
        if(aux > maior)
            maior = aux;
    }

    EhMinusculo(nomes, n, maior); //Verifica se todos os caracteres de cada string lida são minúsculos
    final = Radix_Sort(nomes, final, maior, n); //O vetor "final" recebe os nomes já ordenados pelo método RadixSort
   
    printf("\n");
    for(i=0; i<n; i++) //Imprime os nomes em ordem alfabética
        printf("%s\n", final[i]);
   
    for(i=0;i<n;i++) //Percorre o vetor
        free(nomes[i]); //Libera as strings
   
    free(nomes); //Ao término do loop, libera o vetor
}
