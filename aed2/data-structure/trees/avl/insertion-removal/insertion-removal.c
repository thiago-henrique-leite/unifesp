//OPERAÇÕES EM ÁRVORE AVL

#include <stdio.h>
#include <stdlib.h>

typedef struct SNo *TAVL; //Ponteiro para Árvore AVL

typedef struct SNo { //Estrutura do Nó
    int Chave;
    TAVL Esq, Dir; //Ponteiros para subárvores esquerda e direita
    int fb; //Fator de balanceamento do nó
} TNo;

TAVL InicializaAVL() { //Inicializa uma árvore
    return NULL;
}

TAVL PesquisaAVL(TAVL Raiz, int x) { //Pesquisa um elemento na árvore 
    if(Raiz==NULL || Raiz->Chave == x) 
        return Raiz;
    else if (x < Raiz->Chave) 
        return PesquisaAVL(Raiz->Esq, x); 
    else return PesquisaAVL(Raiz->Dir, x); 
}

TAVL CriaNo(int Chave) {  //Cria um novo nó
    TAVL No;
    No = (TAVL)malloc(sizeof(TNo)); 
    No->Esq = No->Dir = NULL;
    No->Chave = Chave;
    No->fb = 0; //Fator de balanceamento inicial igual a zero
    return No; 
}

int altura(TAVL Raiz) { //Retorna a altura da árvore
    if(Raiz==NULL) return -1;
    else {
        int esq = altura(Raiz->Esq);
        int dir = altura(Raiz->Dir);
        if(esq>dir) return(1+esq);
        else return(1+dir);
    }
}

int FB(TAVL No) { //Função que será usada para atualizar o fator de balanceamento de um Nó
    return(altura(No->Esq)-altura(No->Dir));
}

void RotacaoLL(TAVL *Raiz) { //Realiza a rotação LL
    TAVL pB;
    pB = (*Raiz)->Esq;
    (*Raiz)->Esq = pB->Dir;
    pB->Dir = (*Raiz);
    (*Raiz)->fb = pB->fb = 0;
    (*Raiz) = pB;
}

void RotacaoRR(TAVL *Raiz) { //Realiza a rotação RR
    TAVL pB;
    pB = (*Raiz)->Dir;
    (*Raiz)->Dir = pB->Esq;
    pB->Esq = (*Raiz);
    (*Raiz)->fb = pB->fb = 0;
    (*Raiz) = pB;
}

void RotacaoLR(TAVL *Raiz) { //Realiza a rotação LR
    TAVL pB, pC;
    pB = (*Raiz)->Esq;
    pC = pB->Dir;
    pB->Dir = pC->Esq;
    pC->Esq = pB;
    (*Raiz)->Esq = pC->Dir;
    pC->Dir = (*Raiz);
    (*Raiz)->fb = FB(*Raiz);
    pB->fb = FB(pB);
    pC->fb = 0;
    (*Raiz) = pC;
}

void RotacaoRL(TAVL *Raiz) { //Realiza a rotação RL
    TAVL pB, pC;
    pB = (*Raiz)->Dir;
    pC = pB->Esq;
    pB->Esq = pC->Dir;
    pC->Dir = pB;
    (*Raiz)->Dir = pC->Esq;
    pC->Esq = (*Raiz);
    (*Raiz)->fb = FB(*Raiz);
    pB->fb = FB(pB);
    pC->fb = 0;
    (*Raiz) = pC;
}

void balancaArvore(TAVL *Raiz) { //Realiza o balanceamento de uma dada Árvore
    int fb = FB(*Raiz);
    if(fb>1) {
        int fb_esq = FB((*Raiz)->Esq);
        if(fb_esq>0)
            RotacaoLL(Raiz);
        else
            RotacaoLR(Raiz);
    }
   
    else if(fb<-1) {
        int fb_dir = FB((*Raiz)->Dir);
        if(fb_dir<0)
            RotacaoRR(Raiz);
        else
            RotacaoRL(Raiz);
    }
}

int Insere(TAVL *Raiz, TAVL *No) { //Insere um nó na árvore
    if(*Raiz==NULL) { //Se a raiz for nula
        *Raiz = (*No); //A raiz recebe o nó 
    }
    else {
        if((*No)->Chave < (*Raiz)->Chave) { //Se a chave do novo nó for menor que a chave da raiz, insere na esquerda 
            if((*Raiz)->fb == -1) {
                (*Raiz)->fb = 0;
                Insere(&(*Raiz)->Esq, No);
            }
            else if((*Raiz)->fb == 0) {
                (*Raiz)->fb++;
                Insere(&(*Raiz)->Esq, No);
            }
            else {
                Insere(&(*Raiz)->Esq, No);
                balancaArvore(Raiz);
            }
        }
        
        else if((*No)->Chave >= (*Raiz)->Chave) { //Se a chave do novo nó for menor que a chave da raiz, insere na direita 
            if((*Raiz)->fb == 1) {
                (*Raiz)->fb = 0;
                Insere(&(*Raiz)->Dir, No);
            }
            else if((*Raiz)->fb == 0) {
                (*Raiz)->fb--;
                Insere(&(*Raiz)->Dir, No);
            }
            else {
                Insere(&(*Raiz)->Dir, No);
                balancaArvore(Raiz);
            }
        }
    }
}

TAVL Sucessor(TAVL raiz) { //Encontra o sucessor do nó a ser removido, a menor chave dentre as maiores
    while(raiz->Esq != NULL) 
        raiz = raiz->Esq; 
    return raiz;
}

int Remove(TAVL *Raiz, int Chave) { //Remove um nó da árvore
    if(*Raiz == NULL) //Se a árvore for nula não tem o que remover
        return 0;
        
    if(Chave < (*Raiz)->Chave) { //Se a chave a ser retirada for menor que a chave da raiz, remove da sub arvore esquerda
        if((*Raiz)->fb == 1) { 
                (*Raiz)->fb = 0;
                Remove(&(*Raiz)->Esq, Chave);
            }
            else if((*Raiz)->fb == 0) {
                (*Raiz)->fb--;
                Remove(&(*Raiz)->Esq, Chave);
            }
            else { //Caso em que a árvore precisa ser balanceada após a inserção
                Remove(&(*Raiz)->Esq, Chave);
                balancaArvore(Raiz);
            }
    }
    
    else if(Chave > (*Raiz)->Chave) { //Se a chave a ser retirada for menor que a chave da raiz, remove da sub arvore direita
        if((*Raiz)->fb == -1) {
                (*Raiz)->fb = 0;
                Remove(&(*Raiz)->Dir, Chave);
            }
            else if((*Raiz)->fb == 0) {
                (*Raiz)->fb--;
                Remove(&(*Raiz)->Dir, Chave);
            }
            else { //Caso em que a árvore precisa ser balanceada após a inserção
                Remove(&(*Raiz)->Dir, Chave);
                balancaArvore(Raiz);
            }
    }
    
    else if(Chave == (*Raiz)->Chave) { //Caso em que a chave a ser retirada é igual a chave do nó analisado
        if((*Raiz)->Esq == NULL || (*Raiz)->Dir == NULL) { //Verifica se o nó possui só um descendente
            TAVL aux = (*Raiz);
            if((*Raiz)->Esq != NULL) //Verifica se esse único descendente é o nó da esquerda
                *Raiz = (*Raiz)->Esq; //Se sim, o nó a ser removido recebe sua sub arvore esquerda
            else *Raiz = (*Raiz)->Dir; //Se não, o nó a ser removido recebe sua sub arvore direita
            free(aux); //Libera o espaço alocado para o nó
        } else { //Caso em que o nó possui dois descendentes
            TAVL temp = Sucessor((*Raiz)->Dir); //Encontra o sucessor do nó a ser removido
            (*Raiz)->Chave = temp->Chave;
            Remove(&(*Raiz)->Dir, (*Raiz)->Chave); 
            if(FB(*Raiz) >= 2 || FB(*Raiz) <= -2) //Se após a remoção, Verifica se a árvore está desbalanceada
                balancaArvore(Raiz); //Em caso afirmativo, chama a função de balanceamento
        }
        return 1;
    }
    
    
}

void Imprime(TAVL No) { //Imprime a árvore na representação de parênteses aninhados
    if (No != NULL) {
        printf("(C%d", No->Chave);
        Imprime(No->Esq);
        Imprime(No->Dir);
        printf(")");
    }
    else printf("()");
}


int main(void) {
    TAVL *Raiz, Arvore, Pesquisa, No;
    int tam, n, chave;

    Arvore = InicializaAVL(); //Inicializa a árvore
    Raiz = &Arvore; //Ponteiro para ponteiro "Raiz" irá apontar para a Arvore
    
    printf("Digite o número de elementos da árvore: ");
    scanf("%d", &tam); //Recebe o número n de elementos da árvore 
   
    printf("Digite os %d elementos da árvore: ", tam);
    for(int i=0; i<tam; i++) { 
        scanf("%d", &n); //Lê os as chaves dos n elementos da árvore
        No = CriaNo(n); //Cria um nó com a chave inserida
        Insere(Raiz, &No); //Insere o nó criado na árvore
    }
    
    printf("Entre com a chave a ser pesquisada na árvore: ");
    scanf("%d", &chave); //Lê a chave a ser pesquisada

    Pesquisa = PesquisaAVL(Arvore, chave); //Pesquisa a chave inserida
    if(Pesquisa == NULL) { //Se a chave não for encontrada
        Pesquisa = CriaNo(chave); //Cria um nó tendo o valor inserido para busca como chave
        Insere(&Arvore, &Pesquisa); //Insere o nó criado na árvore
    }
    else Remove(&Arvore, chave); //Se a chave for encontrada, remove o nó com a chave da árvore
    printf("\n");
    Imprime(Arvore); //Imprime a árvore final
}
