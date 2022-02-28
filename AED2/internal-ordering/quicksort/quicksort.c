#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 16 //Tamanho máximo do nome (15 caracteres ocupáveis)
 
typedef struct { //Estrutura que armazena os dados de uma pessoa: nome, idade e ordem de inserção.
    char Nome[MAX];  
    int Idade; 
    int Ordem; 
} TPessoa;
 
//Cabeçalho de Funções
void Quicksort(TPessoa *V, int p, int r);
int  Partition(TPessoa *V, int p, int r);
void MedianaDeTres(TPessoa *V, int p, int r);
void swap(TPessoa *V, int x, int y);
void EhEstavel(TPessoa *A, int p, int ult);
void Imprime(TPessoa *V, int p_impresso, int quant_impresso);
 
int main() {
    TPessoa *Lista;
    int i, p=0, num_pessoas, p_impresso, quant_impresso;
    
    //printf("Entre com a quantidade de pessoas a serem listadas: ");
    scanf("%d", &num_pessoas);
    
    Lista = (TPessoa*)malloc(num_pessoas*sizeof(TPessoa)); //Aloca espaço para a lista de pessoas
    
    for(i=0; i<num_pessoas; i++) {
        scanf("%s %d", Lista[i].Nome, &Lista[i].Idade);  //lê os nomes e idades de cada uma das pessoas
        Lista[i].Ordem = i; //Define a ordem de inserção
    }
    
    //printf("\nEntre com a posição do primeiro nome a ser impresso e a quantidade de nomes a serem impressos: ");
    scanf("%d %d", &p_impresso, &quant_impresso);
    
    Quicksort(Lista, p, num_pessoas-1); //Ordena a lista de pessoas em ordem crescente de idades
    EhEstavel(Lista, p, num_pessoas-1); //Verifica se a ordenação é estável
    Imprime(Lista, p_impresso, quant_impresso); //Imprime a lista ordenada
    
    free(Lista); //Libera memória alocada
    return 0;
}
 
void Quicksort(TPessoa *V, int p, int r) { //Ordena os dados através do Quicksort
    int q;
    if(p<r) {
        q = Partition(V, p, r); //q recebe o índice do pivô já ordenado
        Quicksort(V, p, q-1); //Chama o Quicksort para ordenar os valores menores ou iguais ao pivô
        Quicksort(V, q+1, r); //Chama o Quicksort para ordenar os valores maiores que o pivô
    }
}
 
int Partition(TPessoa *V, int p, int r) { //Reparte o vetor em duas partes, à esquerda valores menores ou iguais ao pivô e à direita valores maiores que o pivô
    int i, j;
    MedianaDeTres(V, p, r); //Chamada da função MedianaDeTres
    i = p;
    for(j=p; j<r; j++) { //laço que realiza a partição dos dados
        if(V[j].Idade <= V[r].Idade) { 
            swap(V, i, j);
            i++;
        }
    }
    swap(V, i, r); //Coloca o pivô em seu devido lugar no arranjo
    return(i); //Retorna o índice do pivô
}
 
void MedianaDeTres(TPessoa *V, int p, int r) { //Define o pivô a partir do método de Mediana de Três.
    int meio, a, b, c, medianaIndice;
     
    meio = (p+r)/2; //Define o índice referente ao meio do arranjo
    a = V[p].Idade;
    b = V[meio].Idade;
    c = V[r].Idade;
    medianaIndice = 0;
    
    //Comparações para definir a melhor opção para ser o pivô, o valor de início do arranjo, o valor do meio ou o valor do fim 
    if (a < b) 
        if (b < c)
            medianaIndice = meio;
        else
            if (a < c)
                medianaIndice = r;
            else
                medianaIndice = p;
               
    else
        if (c < b)
            medianaIndice = meio;
        else
            if (c < a)
                medianaIndice = r;
            else
                medianaIndice = p;
       
    swap(V, medianaIndice, r); //Coloca o pivô na última posição do arranjo
}
 
void swap(TPessoa *V, int x, int y) { //Troca a posição de duas pessoas na lista
    if(x!=y) {
        int aux1; //Troca das idades
        aux1 = V[x].Idade;
        V[x].Idade = V[y].Idade;
        V[y].Idade = aux1;
       
        char aux2[MAX]; //Troca dos nomes
        strcpy(aux2, V[x].Nome);
        strcpy(V[x].Nome, V[y].Nome);
        strcpy(V[y].Nome, aux2);
        
        int aux3; //Troca da ordem de inserção
        aux3 = V[x].Ordem;
        V[x].Ordem = V[y].Ordem;
        V[y].Ordem = aux3;
    }
}
 
void EhEstavel(TPessoa *V, int p, int ult) { //Verifica se a ordenação é estável
    int i, j, cont=0, estavel=0;
 
    for(i=0; i<ult; i++) {
        for(j=i+1; j<=ult; j++) { 
            if(V[i].Idade == V[j].Idade) { //Compara se há duas pessoas com mesma idade
                cont++; //Em caso afirmativo a contagem de pessoas iguais é incrementada
                if(V[i].Ordem < V[j].Ordem) //Verifica se a primeira pessoa a aparecer na lista ordenada foi inserida primeiro no início
                    estavel++; //Em caso afirmativo, a variável estavel é incrementada
            }
        }
    }
      
    //Se o contador for igual a variavel estavel, isto quer dizer que todas as pessoas com a mesma idade foram mantidas na mesma ordem relativa da entrada
    if(estavel==cont) 
        printf("yes"); 
    else
        printf("no");
}
 
void Imprime(TPessoa *V, int p_impresso, int quant_impresso) { 
    int i;
    for(i=p_impresso-1; i<p_impresso+quant_impresso-1; i++) //Imprime os dados no intervalo determinado pelo usuário
        printf("\n%s %d", V[i].Nome, V[i].Idade);
}
