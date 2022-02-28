## Aplicação

### *• Descrição:*
Implemente as operações basicas de um algoritmo de pesquisa para Arvores Binarias de Busca conforme as especificações abaixo. Escreva 
um programa que contenha os procedimentos a seguir: (1) inicialização, (2) pesquisa, (3) inserção e (4) remoção. Não é permitido o uso 
de algoritmos de ordenação para manter os dados ordenados, caso seja necessário. Na operação de remoção, se necessário, dê a preferência
para a promoção da menor chave da subárvore à direita, ou seja, o sucessor.

### *• Entrada:*
A primeira linha da entrada consiste de uma sequência de números inteiros positivos separados por espaços. A sequência termina quando 
for digitado um número inteiro negativo. A linha seguinte contém um numero inteiro positivo que sera utilizado como chave a ser 
pesquisada no dicionário. No caso de uma pesquisa sem sucesso, esse numero deverá ser inserido no dicionário, caso contrário, ele deverá
ser removido do dicionário.

### *• Saída:*
Imprima duas linhas, cada qual com dois números inteiros, onde o primeiro valor representa tamanho do dicionário de dados, ou seja, 
a quantidade de dados armazenados, e o segundo valor deve exibir a altura máxima da árvore a partir da raiz. A primeira linha exibe 
a quantidade de elementos e altura da árvore após a inserção dos dados, e a segunda linha deve exibir as mesmas informações após a 
pesquisa, oque poderá causar aumento ou diminuição na quantidade de elementos e/ou na altura da árvore.

### *Exemplos de entradas e saídas*

##### Entrada 1

4 10 12 5 8 -1                   {Números a serem inseridos no dicionario}

5                                {Número a ser pesquisado no dicionario}

##### Saida 1

tamanho inicial: 5 

altura inicial: 4                {Tamanho do dicionario e altura da arvore no inicio}

tamanho final: 4 

altura final: 3                  {Tamanho do dicionario e altura da arvore no final}
______________________________________________________________________________________

##### Entrada 2

4 10 12 5 8 -1                   {Números a serem inseridos no dicionario}

7                                {Número a ser pesquisado no dicionario}

##### Saida 2

tamanho inicial: 5 

altura inicial: 4                {Tamanho do dicionario e altura da arvore no início}

tamanho final: 6 

altura final: 5                  {Tamanho do dicionario e altura da arvore no final}
