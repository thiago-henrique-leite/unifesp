## Aplicação

### *• Descrição:*
Implemente as operações básicas do algoritmo de balanceamento em árvores AVL. Escreva um procedimento separado para as 
seguintes operações: (1) Altura: retorna à altura de um dado nó; (2) FB: retorna o fator de balanceamento de um dado nó; 
(3) ArvoreAVL: verifica se uma árvore é ou não AVL; (4) LL, RR, LR, RL: executa uma rotação em um dado nó; (5) BalancaNo: 
verifica um dado nó e efetua o seu balanceamento, caso necessário.

### *• Entrada:*
A entrada consiste de uma árvore binária de busca representada por parênteses aninhados.

### *• Saída:*
Imprima a altura da árvore binária de busca. Caso ela não seja uma árvore AVL, efetue o balanceamento de todos os nós da 
árvore de acordo com um percurso em pós-ordem e, em seguida, imprima a sua altura após balanceada e imprima a árvore 
balanceada usando a representação por parênteses aninhados.

### *Exemplo de entrada e saída*

##### • Exemplo de Entrada:

(C3(C2(C1()())())(C4()(C9(C5()(C8()()))())))   {Arvore binária de busca de entrada}

##### • Exemplo de Saída:

Altura inicial: 4                              {Altura da árvore antes das operações}

Altura final: 3                                {Altura da árvore depois das operações}

(C3(C2(C1()())())(C5(C4()())(C8()(C9()()))))   {Arvore binária de busca de saída}