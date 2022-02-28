#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
void CalculateTransactionsNumber(int n) {
  int v=n, x=0, c=0;
 
  while(v != x) {
     v = abs(x-v);
     x = pow(2, round(log2(v))); 
     c++;
  }
 
  printf("%d\n", c);
}
 
int main() {
  int transaction_value;
  
  //printf("Entre com o valor da transação: ");
  scanf("%d", &transaction_value);
 
  CalculateTransactionsNumber(transaction_value);
 
  return 0;
}