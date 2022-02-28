## Aplicação

### *• Descrição:*
O Counting sort é um algoritmo de ordenação adequado para ordenar N inteiros de valores 0 a k e k=O(N). Porém, este método apresenta 
restrição para ser aplicado na classificação de um conjunto de strings, pois para isso seria preciso realizar conversão de base numérica
e k se tornaria muito grande para strings compridas.

O Radix sort, por outro lado, pode ser aplicado para ordenação de strings utilizando o Counting sort para ordenar a entrada em relação 
a apenas uma posição das strings por vez, sendo que cada caracter seria considerado como um “dígito” do algoritmo. Considerando que 
strings podem ter comprimentos diferentes, um caractere adicional (espaço em branco, ou o número 32 da tabela ASCII em decimal, por 
exemplo) pode ser utilizado para preencher posições vazias de strings mais curtas, para que todas strings tenham o mesmo comprimento d 
(tamanho da maior string). 

Deve-se implementar um programa que leia da entrada um conjunto de nomes com até 15 caracteres cada (cada caractere é uma letra dentro 
dos intervalos [A, Z] e [a, z]) e que ordene-os em ordem alfabética. Você deverá converter todas as letras maiúsculas para letras 
minúsculas antes de realizar a ordenação. A ordenação deve ser realizada utilizando o algoritmo de ordenação Radix sort e o Counting
sort para ordenar cada posição das strings. O número de dígitos d deve ser o comprimento da maior string presente na entrada de cada 
caso de teste. O vetor C (utilizado no couting sort) deve ser de tamanho k=27, sendo a primeira posição destinada ao caractere adicional
(vazio) e as posições restantes referentes às 26 letras minúsculas em ordem crescente (a, …, z). Após a ordenação, você deve imprimir 
a lista ordenada com os nomes em letras minúsculas. 

### *• Entrada:*
A primeira linha da entrada contém o número N (2 ≤ N ≤ 100.000) referente a quantidade de nomes a serem ordenados. As próximas N linhas 
devem conter os respectivos nomes de acordo com a ordem de entrada, sendo um nome para cada linha. 

### *• Saída:*
Imprima os nomes em ordem alfabética. 

### *Exemplos de entradas e saídas*

##### Exemplo de Entrada 1:

5

Daniel

Ana

Jose

Silvia

Joao

##### Exemplo de Saída 1:

ana 

daniel

joao

jose

silvia

_____________________


##### Exemplo de Entrada 2:

10

Zurich

Zu

Wu

Hu

Zukemberg

Wei

Woo

Zoo

Zuu

aaaaa

##### Exemplo de Saída 2:

aaaaa

hu

wei

woo

wu

zoo 

zu

zukemberg

zurich

zuu 