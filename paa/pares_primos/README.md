# Calcula a quantidade de pares primos que somados são iguais a N

## Motivação

- Um aluno curioso de matemática, notou que para todo número inteiro par maior que 2 que ele testou manualmente existe alguma forma de expressá-lo como a soma de dois números primos. Como Cristiano não sabe provar que a propriedade é válida para todo número maior que 2 e também não sabe programar, ele pediu a sua ajuda para escrever um programa para contar o número de pares de números primos cuja soma é igual a um número N.

- Um número natural P, maior que 1, é um número primo se é divisível apenas por dois números positivos: 1 e P. Por exemplo, os 6 menores números primos são: 2, 3, 5, 7, 11 e 13. Desta forma, para N=16, podemos expressar através de duas somas de primos: 3+13 e 5+11.

## Entrada

- A entrada consiste de um número inteiro N (N > 3) par.

## Saída

- Imprimir o número de pares de primos que somados resultam em N. Note que 3+5=8 e 5+3=8 são o mesmo par. Contar o número de pares distintos.
- Imprime o número de pares de primos distintos que somados resultam em N. 

## Comportamento

- O usuário fornece um número N
- O script percorre todos os números de 2 até N/2, caso encontre um primo, verifica se a diferença de N e o número encontrado também é primo, em caso afirmativo o contador é incrementado.
- Retorna a quantidade de pares primos que somados resultam no valor N fornecido.
