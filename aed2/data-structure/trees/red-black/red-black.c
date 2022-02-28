//Inserçãoo e Remoção em Árvores Rubro-Negras

#include <stdio.h>
#include <stdlib.h>

typedef struct SNO *TARN;  //Árvore Rubro Negra

typedef struct SNO { //Estrutura de um nó da árvore
    int chave;
    TARN Esq, Dir, Pai;
    int cor; //Se 0 = Negra, Se 1 = Rubro
} TNo;

TARN IniciaARN() { //Inicializa a árvore
    return NULL;
}

TARN CriaNo(int Chave) { //Cria um novo nó, inicialmente todos rubros
    TARN No;
    No = (TARN)malloc(sizeof(TNo));
    No->Esq = No->Dir = No->Pai = NULL;
    No->chave = Chave;
    No->cor = 1;
    return No;
}

int EhNegro(TARN No) { //Verifica se o nó é negro
    return (No == NULL) || (No->cor == 0);
}

int EhRubro(TARN No) { //Verifica se o nó é rubro
    return (No != NULL) && (No->cor == 1);
}

TARN PesquisaChave(TARN raiz, int x) { //Busca um elemento na árvore
    if(raiz==NULL || raiz->chave == x)
        return raiz;
    else if (x < raiz->chave)
        return PesquisaChave(raiz->Esq, x);
    else return PesquisaChave(raiz->Dir, x);
}

void RotacaoDireita(TARN *Raiz, TARN No) { //Realiza o movimento de rotação para a direita
    TARN Esq = No->Esq;
    No->Esq = Esq->Dir;
    if (Esq->Dir != NULL)
        Esq->Dir->Pai = No;
    Esq->Pai = No->Pai;
    if (No->Pai != NULL) {
        if (No == No->Pai->Dir) 
            No->Pai->Dir = Esq;
        else  
            No->Pai->Esq = Esq;
    } 
    else 
        (*Raiz) = Esq;
    Esq->Dir = No;
    No->Pai = Esq;
}

void RotacaoEsquerda(TARN *Raiz, TARN No) { //Realiza o movimento de rotação para a esquerda
    TARN Dir = No->Dir;
    No->Dir = Dir->Esq;
    if (Dir->Esq != NULL)
        Dir->Esq->Pai = No;
    Dir->Pai = No->Pai;
    if(No->Pai != NULL) {
        if (No == No->Pai->Esq) 
            No->Pai->Esq = Dir;
        else 
            No->Pai->Dir = Dir;
    }
    else 
        (*Raiz) = Dir;
    Dir->Esq = No;
    No->Pai = Dir;
}

void RB_INSERT_FIXUP(TARN *Raiz, TARN z) { //Verifica as propriedades da Árvore RN após uma inserção e corrige se necessário
    TARN y;
   
    while(z!=(*Raiz) && z->Pai->cor == 1) {
       
        if(z->Pai == z->Pai->Pai->Esq) {
            y = z->Pai->Pai->Dir;
            if(EhRubro(y) == 1) { //Case1
                    z->Pai->cor = 0;
                    y->cor = 0;
                    z->Pai->Pai->cor = 1;
                    z = z->Pai->Pai;
            }
            else if(z == z->Pai->Dir) { //Case2
                z = z->Pai;
                RotacaoEsquerda(Raiz, z);
            } else { //Case3
            z->Pai->cor = 0;
            z->Pai->Pai->cor = 1;
            RotacaoDireita(Raiz, z->Pai->Pai);
            }
        }
       
        else {
            y = z->Pai->Pai->Esq;
            if(EhRubro(y) == 1) { //Case1
                z->Pai->cor = 0;
                y->cor = 0;
                z->Pai->Pai->cor = 1;
                z = z->Pai->Pai;
            }
            else if(z == z->Pai->Esq) { //Case2
                z = z->Pai;
                RotacaoDireita(Raiz, z);
            } else { //Case3
            z->Pai->cor = 0;
            z->Pai->Pai->cor = 1;
            RotacaoEsquerda(Raiz, z->Pai->Pai);
            }
        }
    }
    (*Raiz)->cor = 0;
}


void InsereNo(TARN *Raiz, TARN z) { //Insere um novo nó na árvore
    TARN y, x;
    y = NULL;
    x = (*Raiz);
    while(x != NULL) {
        y = x;
        if(z->chave < x->chave)
            x = x->Esq;
        else x = x->Dir;
    }
    z->Pai = y;
    if(y==NULL)
        (*Raiz) = z;
    else if(z->chave < y->chave)
        y->Esq = z;
    else y->Dir = z;
   
    RB_INSERT_FIXUP(Raiz, z);
}

void RB_DELETE_FIXUP(TARN *Raiz, TARN x, TARN xpai) { //Verifica as propriedades da Árvore RN após uma remoção e corrige se necessário
    TARN w;
    while(x!=(*Raiz) && EhNegro(x) == 1)
        if (x == xpai->Esq) {
            w = xpai->Dir;
            if (EhRubro(w) == 1) { //Case1
                w->cor = 0;
                xpai->cor = 1;
                RotacaoEsquerda(Raiz, xpai);
                w = xpai->Dir;
            }
            if(EhNegro(w->Esq)==1 && EhNegro(w->Dir)==1) { //Case2
                w->cor = 1;
                x = xpai;
            } else { 
                if(EhNegro(w->Dir)==1) { //Case3
                    w->Esq->cor = 0;
                    w->cor = 1;
                    RotacaoDireita(Raiz, w);
                }
                //Case 4
                w = xpai->Dir;
                w->cor = xpai->cor;
                xpai->cor = 0;
                w->Dir->cor = 0;
                RotacaoEsquerda(Raiz, xpai);
                x = (*Raiz);
            
            } 
        }
       
        else {
            w = xpai->Esq;
            if (EhRubro(w) == 1) { //Case1
                w->cor = 0;
                xpai->cor = 1;
                RotacaoDireita(Raiz, xpai);
                w = xpai->Esq;
            }
            if(EhNegro(w->Dir)==1 && EhNegro(w->Esq)==1) { //Case2
                w->cor = 1;
                x = xpai;
            } else {  
                if(EhNegro(w->Esq)==1) { //Case3
                    w->Dir->cor = 0;
                    w->cor = 1;
                    RotacaoEsquerda(Raiz, w);
                }
                //Case 4
                w = xpai->Esq;
                w->cor = xpai->cor;
                xpai->cor = 0;
                w->Esq->cor = 0;
                RotacaoDireita(Raiz, xpai);
                x = (*Raiz);
      
            } 
        }
    if(x!=NULL) x->cor = 0;
}

TARN Sucessor(TARN Raiz) { //Encontra o sucessor do elemento a ser removido, o menor dentre os maiores
    while(Raiz->Esq != NULL)
        Raiz = Raiz->Esq;
    return Raiz;
}

void RB_DELETE(TARN *Raiz, TARN z) { //Remove um nó da árvore
    TARN x, y, xpai;
    if(z->Esq==NULL || z->Dir==NULL)
        y = z;
    else y = Sucessor(z->Dir);
   
    if(y->Esq != NULL)
        x = y->Esq;
    else x = y->Dir;
   
    if(x!=NULL)
        x->Pai = y->Pai;
    else xpai = y->Pai; //A variável xpai é utilizada quando se está removendo um nó folha
   
    if(y->Pai==NULL)
        *Raiz = x;
    else if(y == y->Pai->Esq)
        y->Pai->Esq = x;
    else y->Pai->Dir = x;
   
    if(y!=z)
        z->chave = y->chave;
       
    if(y->cor==0)
        if(x!=NULL)
          RB_DELETE_FIXUP(Raiz, x, x->Pai);
        else
          RB_DELETE_FIXUP(Raiz, x, xpai);
}

int AlturaNegra(TARN No) { //Calcula a altura negra, ou seja, por quantos nós negros passamos para chegar até um nó folha (NILL) a partir da raiz
    if(No == NULL) return 0;
    else {
        if(No->cor == 0)
            return (1 + AlturaNegra(No->Esq));
        else return(AlturaNegra(No->Esq));
    }
}

void Imprime(TARN No) { //Imprime a árvore
    if (No != NULL) {
        if (EhNegro(No))
            printf("(N%d", No->chave);
        else
            printf("(R%d", No->chave);
        Imprime(No->Esq);
        Imprime(No->Dir);
        printf(")");
    }
    else
    printf("()");
}

int main () {
    TARN *Raiz, Arvore, Elemento;
    int tam, nums, chaveBusca;
   
    Arvore = IniciaARN();
    Raiz = &Arvore;
   
    scanf("%d", &tam); //Lê o tamanho da árvore
   
    for(int i=0; i<tam; i++) { //Lê seus elementos e os inserem na árvore
        scanf("%d", &nums);
        InsereNo(Raiz, CriaNo(nums));
    }
   
    scanf("%d", &chaveBusca); //Lê a chave de busca
   
    printf("\n%d\n", AlturaNegra(Arvore)); //Imprime a altura negra inicial
   
    Imprime(Arvore); //Imprime a árvore inicial
   
    Elemento = PesquisaChave(Arvore, chaveBusca); //Verifica se existe algum elemento com a chave de busca na árvore
    if(Elemento != NULL) 
        RB_DELETE(Raiz, Elemento); //Caso exista, remove este elemento
   
    printf("\n%d\n", AlturaNegra(Arvore)); //Imprime a altura negra da árvore final
    Imprime(Arvore); //Imprime a árvore final
    
}
