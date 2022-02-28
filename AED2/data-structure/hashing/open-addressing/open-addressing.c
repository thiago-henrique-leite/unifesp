//Pesquisa Interna - Hashing com Endereçamento Aberto

#include <stdio.h>
#include <stdlib.h>
 
int h1(int k, int m) { //Função 1
    return(k % m);
}
 
int h2(int k, int m) { //Função 2
    return(1 + (k % (m-2)));
}
 
int FunctionHash(int k, int i, int m) { //Função de duplo Hashing
    int ind = h1(k, m) + i * h2(k, m);
    if(ind<m) return ind;
    else {
        while(ind>=m)
            ind = ind-m;
        return ind;
    }
}
 
int Inserir_Hash_Aberto(int *T, int k, int m) { //Insere um elemento na Tabela
    int i=0, j;
    do {
        j = FunctionHash(k, i, m);
        if(T[j] == NULL) {
            T[j] = k;
            return j;
        }
        else i++;
    } while(i!=m);
    return -1;
}
 
int Buscar_Hash_Aberto(int *T, int k, int m) { //Busca um elemento na Tabela
    int i=0, j;
    do {
        j = FunctionHash(k, i, m);
        if(T[j] == k)
            return j;
        i++;
    } while(T[j]!=NULL && i!=m);
    return -1;
}
 
int main() {
    int *TabelaHash;
    int tam, quant, num, chaveBusca, Pesquisa, i;
   
    //printf("Entre com o tamanho da tabela Hash: ");
    scanf("%d", &tam);
   
    TabelaHash = (int*)malloc(tam*sizeof(int));
   
    //printf("Entre com a quantidade de números de entrada: ");
    scanf("%d", &quant);
   
    for(i=0; i<quant; i++) {
        scanf("%d", &num);
        Inserir_Hash_Aberto(TabelaHash, num, tam);
    }
   
    //printf("Entre com a chave a ser pesquisada na tabela: ");
    scanf("%d", &chaveBusca);
   
    Pesquisa = Buscar_Hash_Aberto(TabelaHash, chaveBusca, tam);
   
    if(Pesquisa==-1) //Verifica se o elemento pesquisado não foi encontrado
        Inserir_Hash_Aberto(TabelaHash, chaveBusca, tam);  //Em caso afirmativo, Insere o elemento na Tabela
 
    for(i=0; i<tam; i++) { //Imprime a Tabela e seus elementos
        printf("[%d] ", i);
        if(TabelaHash[i] != NULL)
            printf("%d\n", TabelaHash[i]);
        else printf("\n");
    }
}

