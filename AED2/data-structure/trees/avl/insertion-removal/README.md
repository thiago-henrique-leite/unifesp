## Aplicação

### *• Descrição:*
Implemente as operações básicas de um algoritmo de pesquisa em árvores AVL, conforme as especificações abaixo. Escreva um procedimento 
(função) separado para as seguintes operações: (1) inicialização, (2) pesquisa, (3) inserção e (4) remoção. Se necessário, na operação 
de remoção, dê a preferência para a promoção da menor chave da subárvore à direita, ou seja, o sucessor. Calcular a altura da árvore, 
caso seja necessário.

### *• Entrada:*
A entrada consiste de vários números inteiros separados por espaços. Todos os números exceto o último serão inseridos na árvore AVL. 
O último número será utilizado como chave a ser pesquisada na árvore. No caso de uma pesquisa sem sucesso, esse número também será
inserido na árvore, caso contrário, ele deverá ser removido da árvore.

### *• Saída:*
Imprima a Árvore AVL representada por parênteses aninhados.

### *Exemplo de entrada e saída:*

##### Entrada:

7                {Quantidade de números de entrada}

3 4 9 2 5 1 8    {Números a serem inseridos na árvore}

5                {Número a ser pesquisado na árvore}

##### Saída:

(C4(C2(C1()())(C3()()))(C8()(C9()())))  {Arvore AVL de saída}
