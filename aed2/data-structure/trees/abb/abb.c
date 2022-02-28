//PESQUISA INTERNA EM ÁRVORES BINÁRIAS DE BUSCA

#include <stdio.h>
#include <stdlib.h>

typedef struct SNO TABB;  //Árvore Binária de Busca

typedef struct SNO { //Estrutura de um nó: ponteiros para subárvores esquerda e direita, e para o pai.
    int chave;
    TABB *esq, *dir, *pai;
} TNo;

//Cabeçalho de funções
    TABB* IniciaABB();
    TABB* CriaNo(int chave);
    void adicionaABB(TABB **raiz, TABB **z);
    void TRANSPLANT(TABB **raiz, TABB **u, TABB **v);
    TABB* Minimo(TABB *raiz);
    void retiraABB(TABB **raiz, TABB **z);
    TABB* buscaElemento(TABB *raiz, int x);
    int alturaABB(TABB *arv);
    int tamanhoABB(TABB *raiz);

TABB* IniciaABB() { //Inicializa uma árvore
    return NULL;
}

TABB* CriaNo(int chave) { //Cria um nó a partir de um valor chave
    TABB *arv;
    arv = (TABB*)malloc(sizeof(TNo)); //Aloca espaço para o novo nó
    arv->esq = arv->dir = arv->pai = NULL; //Os ponteiros das subárvores e do pai recebem null
    arv->chave = chave; //A chave do nó recebe o valor fornecido
    return arv; //Retorna o nó criado
}

void adicionaABB(TABB **raiz, TABB **z) { //Adiciona um novo nó a árvore
    TABB *y, *x;
    y = NULL;
    x = (*raiz);
    while(x != NULL) { //Se x não for a raiz da árvore executa o loop
        y = x;
        if((*z)->chave < x->chave) //Compara os valores das chaves da raiz e do novo nó, e decide se vai para esquerda ou direita
            x = x->esq;
        else x = x->dir;
    }
    (*z)->pai = y;
    if(y==NULL) //Verifica se o nó a ser inserido é a raiz da árvore
        (*raiz) = (*z); //Em caso afirmativo, o nó raiz recebe o nó a ser inserido
    else if((*z)->chave < y->chave) //Verifica as chaves para saber para qual lado deve ir
        y->esq = (*z);
    else y->dir = (*z);
}

void TRANSPLANT(TABB **raiz, TABB **u, TABB **v) { //Remove um nó "u" da árvore e coloca outro nó "v" no lugar
    if((*u)->pai == NULL) //Se "u" for a raiz, a raiz agora passa a ser "v"
        (*raiz) = (*v);
    else if((*u)==((*u)->pai->esq)) //Verifica se o nó a ser removido está a esquerda ou direita de seu pai
        (*u)->pai->esq = (*v);
    else (*u)->pai->dir = (*v);
    if((*v) != NULL)
        (*v)->pai = (*u)->pai; //Atualiza o pai de "v"
}

TABB* Minimo(TABB *raiz) { //Encontra o menor elemento da árvore, ou seja, o que está mais a esquerda
    while(raiz->esq != NULL) //Realiza o loop enquanto o elemento a esquerda do nó a ser analisado não for nulo
        raiz = raiz->esq; //O nó recebe sua subárvore da esquerda
    return raiz;
}

void retiraABB(TABB **raiz, TABB **z) { //Retira um elemento "z" da árvore 
    if((*z)->esq == NULL) //Se "z" não tiver subárvore esquerda
        TRANSPLANT(&(*raiz), &(*z), &((*z)->dir)); //Ele é removido e é colocada sua subárvore direita em seu lugar
    else if((*z)->dir == NULL) //Se "z" não tiver subárvore direita
        TRANSPLANT(&(*raiz), &(*z), &((*z)->esq)); //Ele é removido e é colocada sua subárvore esquerda em seu lugar
    else { //Caso em "z" possui dois descendentes
        TABB *y;
        y = Minimo(((*z)->dir)); //"y" recebe a menor chave dentre as maiores que a chave do elemento "z"
        if(y->pai != (*z)) { //Verifica se o pai de "y" é diferente de "z"
            TRANSPLANT(&(*raiz), &y, &y->dir); //Se for diferente, o elemento que está a direita de "y" assume seu lugar 
            y->dir = (*z)->dir; //A subárvore direita de "y" recebe a subárvore direita de "z"
            y->dir->pai = y; //O pai da subárvore direita de "y" recebe "y"
        }
        TRANSPLANT(&(*raiz), &(*z), &y); //Remove o elemento "z" e coloca "y" devidamente organizado no lugar
        y->esq = (*z)->esq; //A subárvore esquerda de "y" recebe a subárvore esquerda de "z"
        y->esq->pai = y; //O pai da subárvore esquerda de "y" recebe y
    }
}

TABB* buscaElemento(TABB *raiz, int x) { //Realiza a busca de um elemento com chave x
    if(raiz==NULL || raiz->chave == x) //Verifica se a raiz for nula ou se a chave da raiz é igual a x
        return raiz; //Se sim, retorna a raiz
    else if (x < raiz->chave) //Se não, verifica se o valor x é menor que a chave da raiz
        return buscaElemento(raiz->esq, x); //Se for menor chama recursivamente a função para a subárvore esquerda da raiz
    else return buscaElemento(raiz->dir, x); //Se for maior chama recursivamente a função para a subárvore direita da raiz
}

int alturaABB(TABB *arv) { //Retorna a altura de uma árvore
   if (arv == NULL) return 0; //Se a árvore for nula a altura é 0
   else { //Caso não seja nula
      int esq = alturaABB(arv->esq); //Calcula a altura da subárvore da esquerda 
      int dir = alturaABB(arv->dir); //Calcula a altura da subárvore da direita
      if (esq<dir) return dir + 1; //Compara e retorna a altura da maior subárvore somada com 1 da raiz  
      else return esq + 1; 
   }
}

int tamanhoABB(TABB *raiz) { //Retorna o tamanho da árvore
   if(raiz == NULL) return 0; //Tamanho caso a árvore seja vazia
   else return 1 + tamanhoABB(raiz->esq) + tamanhoABB(raiz->dir); 
}

int main(void) {
    int num_pesq, alt, tam, nums=0;
    TABB *raiz, *elemento, *aux;

    raiz = IniciaABB(); //Inicia a árvore
    
    printf("Digite os elementos da árvore (critério de parada: número negativo):\n");
    while(nums>=0) { //Lê os números do usuário até ele digitar um número negativo
        scanf("%d", &nums);
        if(nums>=0) {
            aux = CriaNo(nums); //Cria um nó com a chave fornecida pelo usuário
            adicionaABB(&raiz, &aux); //Adiciona o nó criado a árvore
        }
    }
    
    printf("Digite o número a ser pesquisado na árvore: ");
    scanf("%d", &num_pesq); //Lê o número a ser pesquisado na árvore
    
    tam = tamanhoABB(raiz);
    alt = alturaABB(raiz);
    printf("\ntamanho inicial: %d\naltura inicial: %d\n", tam, alt); //Imprime o tamanho e altura originais da árvore
    
    elemento = buscaElemento(raiz, num_pesq); //A variável elemento recebe o resultado da busca do valor inserido
    
    if(elemento == NULL) { //Se o elemento não for encontrado
        aux = CriaNo(num_pesq); //Cria um nó tendo o valor inserido como chave
        adicionaABB(&raiz, &aux); //Adiciona ele a árvore
    }
    else retiraABB(&raiz, &(elemento)); //Se for encontrado, o elemento é removido da árvore
   
    tam = tamanhoABB(raiz);
    alt = alturaABB(raiz);
    printf("\ntamanho final: %d\naltura final: %d", tam, alt); //Imprime o tamanho e altura da árvore após as alterações
}
