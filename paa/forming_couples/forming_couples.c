//Problema 3 - PAA - Código feito por Thiago Henrique Leite da Silva - UNIFESP 
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
// Estrutura de um casal, onde um participante (voter) define em quem tem interesse (voted)
typedef struct {
  int voter;
  int voted;
} Couple;
 
// Na primeira etapa recebemos os votos de cada um dos participantes
void FirstStep(Couple *casais, int n) {
  int i;
 
  for(i=0; i<n; i++) 
    scanf("%d %d", &casais[i].voter, &casais[i].voted);
 
  SecondStep(casais, n);
}
 
// Na segunda etapa econtramos quais serão os participantes convocados para a etapa final
void SecondStep(Couple *casais, int n)  {
  int *C = (int*)calloc(n+1, sizeof(int));     // Contagem de votos recebidos por pessoa
  int *S = (int*)malloc((n+1)*sizeof(int));    // Subconjunto final dos convocados
  int *fila = (int*)malloc((n+1)*sizeof(int)); // Fila de remoção
  
  int i, index_inp=0, index_out=0; 
  
  // De início, todos os participantes estão convocados para a última etapa
  for(i=1; i<=n; i++) 
    S[i] = i;
 
  // Setamos quantos votos cada participante recebeu
  for(i=1; i<=n; i++)
    C[casais[i-1].voted]++;
 
  // Adicionamos a fila todos os participantes não votados, estes estão fora da etapa final
  for(i=1; i<=n; i++) {
    if(C[i]==0) {
      fila[index_inp] = i;
      index_inp++;
    }
  }
 
  int element, x;
 
  // No laço principal, enquanto a fila não for vazia, retiramos do subconjunto S os elementos enfileirados
  // Após a retirada, decrementamos a contagem de votos no vetor C dos participantes votados pelos excluídos
  // Se após o decremento eles não tiverem mais votos, também são adicionados a fila para a remoção
 
  while(index_out!=index_inp) {
    element = fila[index_out];
    index_out++;
    S[element] = 0;
 
    x = casais[element-1].voted;
    C[x]--;
 
    if(C[x]==0) {
      fila[index_inp] = x;
      index_inp++;
    }
  }
 
  // Imprimos o subconjunto com os convocados
  print(S, n);
}
 
void print(int *S, int n) {
  int i;
  for(i=1; i<=n; i++) 
    if(S[i]!=0)
      printf("%d ", S[i]);
  printf("\n");
}
 
int main() {
  int n;
 
  //printf("Digite o número de participantes: ");
  scanf("%d", &n);
 
  Couple *casais = (Couple*)malloc(n*sizeof(Couple));
  FirstStep(casais, n);
 
  return 0;
}