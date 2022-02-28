## *Aplicação*
 
### *• Descrição:*
O Quicksort é um algoritmo considerado muito rápido para a maioria das situações.  Considere o algoritmo do 
Quicksort, em que o pivô escolhido como uma mediana de 3 valores, onde esses três valores devem ser definidos 
como: a) primeiro elemento do intervalo considerado do vetor, b) o elemento na posição do meio e c) o último elemento.

Implemente um programa que leia da entrada um conjunto de informações sobre N pessoas contendo o nome de cada pessoa 
com até 15 caracteres e a sua idade. O seu programa deverá utilizar o algoritmo do Quicksort com escolha do pivo por 
mediana de 3, e que ordene-os de forma crescente por idade. Posteriormente deve-se verificar se o resultado da ordenação 
é estável, ou seja, se pessoas com a mesma idade foram mantidas na mesma ordem relativa da entrada. Após a ordenação, você 
deve imprimir uma região indicada da lista ordenada. 

### *• Entrada:*
A primeira linha da entrada contém o número N (2 ≤ N ≤ 105.000) de pessoas a serem ordenadas. Nas próximas N linhas 
são apresentados, em cada linha, um nome de até 15 caracteres e um inteiro representando a idade.

### *• Saída:*
Na primeira linha da saída, imprima se a ordenação é ou não estável. Depois, imprima os nomes e idades presentes da 
lista ordenada, uma pessoa a cada linha. 

### *Exemplos de entradas e saídas*

##### Entrada 1

4

Alex 20

Gabriel 20

Joana 18

Rodrigo 18

##### Saída 1

no

Rodrigo 18

Joana 18

Alex 20

Gabriel 20

_______________________


##### Entrada 2

5

Daniel 25

Ana 21

Jose 22

Silvia 25

Joao 23

##### Saída 2

yes

Ana 21

Jose 22

Joao 23

Daniel 25

Silvia 25

