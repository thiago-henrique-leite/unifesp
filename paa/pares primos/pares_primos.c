//Problema 1 - PAA - Código feito por Thiago Henrique Leite da Silva, UNIFESP 
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
  
int EhPrimo(int);
int QuantParesPrimos(int);
 
// Função que verifica se um número positivo é primo baseada no método das divisões sucessivas
// O Crivo de Eratóstenes nos garante que todo número composto é divisível por um número k>1 menor ou igual que sua raiz quadrada
// Número composto é um número maior que 1 não primo
 
int EhPrimo(int n) {
  int i;
 
  for(i=2; i<=sqrt(n); i++)
      if (n%i == 0)
        return 0;
  
  return 1;
}
 
// Calcula a quantidade de combinações de números primos que, somados, são iguais ao valor fornecido
 
int QuantParesPrimos(int n) {
  int i, j, cont=0;
 
  for(i=2; i<=n/2; i++) 
    if(EhPrimo(i)) 
      if(EhPrimo(n-i)) 
        cont++;

  return cont;
 }
 
int main() {
  int n;
 
  printf("\nDigite um valor N: ");
  scanf("%d", &n);
 
  if(n >= 3)
    printf("Quantidade de pares primos: %d\n", QuantParesPrimos(n));
 
  return 0;
}