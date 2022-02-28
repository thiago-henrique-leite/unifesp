//Pesquisa Interna - Hashing com Encadeamento

#include <stdio.h>
#include <stdlib.h>

typedef struct SCelula *TCelula; //Define TCelula como um ponteiro para uma célula

typedef struct SCelula { //Estrutura de cada célula da lista
    TCelula ant, prox; //Ponteiros pras células anterior e próxima
    int chave; //Item a ser armazenado
} TLista;

TCelula Inicializa(TCelula Celula) { //Inicializa a Lista Encadeada
    Celula = malloc(sizeof(TLista));
    Celula->prox = NULL;
    Celula->ant = NULL;
}
 
void Insere(TCelula Celula, int chave){ //Insere um novo elemento na lista
    TCelula Novo, Aux;
    Aux = Celula;
    Novo = malloc(sizeof(TLista));
    Novo->chave = chave;
    Novo->prox = NULL;
    while(Aux->prox != NULL)
        Aux = Aux->prox;
    Aux->prox = Novo;
    Novo->ant = Aux;
   
}

void Remove(TCelula *Celula) { //Remove um elemento da lista
    TCelula Aux;
    (*Celula)->ant->prox = (*Celula)->prox;
    if((*Celula)->prox != NULL)
        (*Celula)->prox->ant = (*Celula)->ant;
    Aux = (*Celula);
    free(Aux);
}

int FunctionHash(int k, int tam) { //Retorna o resultado da Função Hash de divisão
    if(k>0) return(k%tam);
    else return 0;
}

void Imprime(TCelula Celula, int indice){ //Imprime a tabela hash
    TCelula Aux;
    printf("[%d] ", indice);
    if(Celula->prox != NULL){
        Aux = Celula->prox;
        while(Aux != NULL){
            printf("%d ", Aux->chave);
            Aux = Aux->prox;
        }
    }  
    printf("\n");
}

TCelula BuscaChave(TCelula Celula, int chave) { //Busca um determinado elemento em alguma das listas do hash
    if(Celula->ant==NULL && Celula->prox==NULL)
        return NULL;
       
    else if(Celula->chave == chave)
        return Celula;
       
    else if(Celula->prox != NULL)
        return BuscaChave(Celula->prox, chave);
   
    else
        return NULL;
}

int main() {
    TCelula Lista, Pesquisa, Aux;
    TCelula *Hash;

    int j, i, tam, quant, num, chaveBusca, indice;
   
    //printf("Entre com o tamanho da tabela Hash: ");
    scanf("%d", &tam);
   
    Hash = (TCelula*)malloc(tam*sizeof(TCelula)); //Inicializa a Tabela Hash
   
    for(j=0; j<tam; j++)
        Hash[j] = Inicializa(Aux); //Inicializa cada uma das listas encadeadas da tabela

    //printf("Entre com a quantidade de números de entrada: ");
    scanf("%d", &quant);

    for(i=0; i<quant; i++) {
         scanf("%d", &num);
         Insere(&Hash[FunctionHash(num, tam)], num); //Insere os elementos lidos na tabela
    }
   
    //printf("Entre com a chave a ser pesquisada na tabela: ");
    scanf("%d", &chaveBusca);
    
    indice = FunctionHash(chaveBusca, tam);
    Pesquisa = BuscaChave(&Hash[indice], chaveBusca); //Verifica se a chave de busca foi encontrada na tabela

    if(Pesquisa!=NULL)
        Remove(&Pesquisa); //Caso seja encontrada, a chave é removida da tabela
    else 
        Insere(&Hash[indice], chaveBusca); //Caso não seja encontrada, a chave é inserida na tabela

    
    for(i=0; i<tam; i++)
         Imprime(&Hash[i], i); //Imprime a Tabela Hash final

    return 0;
}
