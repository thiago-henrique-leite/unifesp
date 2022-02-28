//BALANCEAMENTO EM ÁRVORE AVL

#include <stdio.h>
#include <stdlib.h>

typedef struct SNo *TAVL; //Ponteiro para Árvore AVL

typedef struct SNo { //Estrutura do Nó
	int Chave; 
	TAVL Esq, Dir; //Ponteiros para subárvores direita e esquerda
} TNo;

int altura(TAVL Raiz) { //Retorna a altura da Árvore
    if(Raiz==NULL) return -1;
    else {
        int esq = altura(Raiz->Esq);
        int dir = altura(Raiz->Dir);
        if(esq>dir) return(1+esq);
        else return(1+dir);
    }
}

int FB(TAVL No) { //Calcula o Fator de Balanceamento do No
    return(altura(No->Esq)-altura(No->Dir));
}

int EhAVL(TAVL No) { //Verifica se a árvore é AVL
    while (No != NULL) {
        EhAVL(No->Esq);
        int fatbal = FB(No);
        if(fatbal < -1 || fatbal > 1)
            return 0;
        No = No->Dir;
    }
    return 1;
}

void rotacaoLL(TAVL *Raiz) { //Realiza a rotação LL
    TAVL pB;
    pB = (*Raiz)->Esq;
    (*Raiz)->Esq = pB->Dir;
    pB->Dir = (*Raiz);
    (*Raiz) = pB;
}

void rotacaoRR(TAVL *Raiz) { //Realiza a rotação RR
    TAVL pB;
    pB = (*Raiz)->Dir;
    (*Raiz)->Dir = pB->Esq;
    pB->Esq = (*Raiz);
    (*Raiz) = pB;
}

void rotacaoLR(TAVL *Raiz) { //Realiza a rotação LR
    TAVL pB, pC;
    pB = (*Raiz)->Esq;
    pC = pB->Dir;
    pB->Dir = pC->Esq;
    pC->Esq = pB;
    (*Raiz)->Esq = pC->Dir;
    pC->Dir = (*Raiz);
    (*Raiz) = pC;
}

void rotacaoRL(TAVL *Raiz) { //Realiza a rotação RL
    TAVL pB, pC;
    pB = (*Raiz)->Dir;
    pC = pB->Esq;
    pB->Esq = pC->Dir;
    pC->Dir = pB;
    (*Raiz)->Dir = pC->Esq;
    pC->Esq = (*Raiz);
    (*Raiz) = pC;
}

void balancaArvore(TAVL *Raiz) { //Realiza o balanceamento de uma dada Árvore
    int fb = FB(*Raiz);
    if(fb>1) {
        int fb_esq = FB((*Raiz)->Esq);
        if(fb_esq>0)
            rotacaoLL(Raiz);
        else
            rotacaoLR(Raiz);
    }
   
    else if(fb<-1) {
        int fb_dir = FB((*Raiz)->Dir);
        if(fb_dir<0)
            rotacaoRR(Raiz);
        else
            rotacaoRL(Raiz);
    }
}

void PosOrdem(TAVL *No) { //Percorre a Árvore no sentido Pós-Ordem
    if ((*No) != NULL) {
        PosOrdem(&((*No)->Esq));
        PosOrdem(&((*No)->Dir));
        int fatbal = FB(*No);
        if(fatbal < -1 || fatbal > 1) //Verifica se o nó analisado precisar ser balanceado
            balancaArvore(No); //Em caso afirmativo, realiza o balanceamento do Nó
    }
}

TAVL Carrega() { //Função que monta a árvore recebida pelo usuário representada por parênteses aninhados
	char c;
	TAVL No;
	scanf("%c", &c);
	if (c == '(') {
		scanf("%c", &c);
		if (c == 'C') {
			No = (TAVL) malloc(sizeof(TNo));
			scanf("%d", &No->Chave);
			No->Esq = Carrega();
			No->Dir = Carrega();
			scanf("%c", &c);
		}
		else if (c == ')')
			No = NULL;
	}
	return No;
}

void Imprime(TAVL No) { //Função que Imprime a árvore na representação por parênteses aninhados
	if (No != NULL) {
		printf("(C%d", No->Chave);
		Imprime(No->Esq);
		Imprime(No->Dir);
		printf(")");
	}
	else
		printf("()");
}


int main(void) {
	TAVL Arvore, *Raiz; 
  
  printf("Entre com a árvore na representação por parênteses aninhados:\n");
	Arvore = Carrega(); //Lê a Árvore do usuário
	printf("\nAltura inicial: %d\n", altura(Arvore)); //Imprime a altura inicial da árvore

	Raiz = &Arvore; //O ponteiro para ponteiro "Raiz" aponta para a árvore

	if(EhAVL(Arvore)==0) //Se a árvore não for AVL
	    PosOrdem(Raiz); //Percorre a árvore em pós-ordem e realiza o balanceamento nos nós necessários
	    
	printf("Altura final: %d\n", altura(Arvore)); //Imprime a altura da árvore novamente
	Imprime(Arvore); //Imprime a árvore
}


