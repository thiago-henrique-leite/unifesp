#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Definindo tamanho dos arquivos a serem lidos
#define UmMilhao 1000000
#define DezMilhoes 10000000

// Cabeçalho de funções
void OrdenacaoExterna(int, int);
void Swap(long int*, long int, long int);
int  Partition(long int*, long int, long int);
void Quicksort(long int*, long int, long int);
void DeletaArquivos(int);

void Swap(long int *V, long int x, long int y) { // Troca a posição de dois valores no array
    if(x!=y) {
        long int aux; 
        aux = V[x];
        V[x] = V[y];
        V[y] = aux;
    }
}
 
int Partition(long int *V, long int p, long int r) { // Reparte o vetor em duas partes, à esquerda valores menores ou iguais ao pivô e à direita valores maiores que o pivô
    int i, j;
    i = p;
    for(j=p; j<r; j++) { // Laço que realiza a partição dos dados
        if(V[j] <= V[r]) { 
            Swap(V, i, j);
            i++;
        }
    }
    Swap(V, i, r); // Coloca o pivô em seu devido lugar no arranjo
    return(i); // Retorna o índice do pivô
}

void Quicksort(long int *V, long int p, long int r) { //Ordena os dados através do Quicksort
    int q;
    if(p<r) {
        q = Partition(V, p, r); //q recebe o índice do pivô já ordenado
        Quicksort(V, p, q-1); //Chama o Quicksort para ordenar os valores menores ou iguais ao pivô
        Quicksort(V, q+1, r); //Chama o Quicksort para ordenar os valores maiores que o pivô
    }
}

int main () {

  //Modelo: OrnacaoExterna(Tamanho do arquivo em milhões, Quantidade de registros)

  OrdenacaoExterna(15, UmMilhao);
  OrdenacaoExterna(40, UmMilhao);
  OrdenacaoExterna(15, DezMilhoes);
  OrdenacaoExterna(40, DezMilhoes);

  return 0;
}

void DeletaArquivos(int soma) {
  char nome_arq[15];
  int i;

  for(i=1; i<soma; i++) {
    sprintf(nome_arq, "fita%d.txt", i);
    remove(nome_arq);
  }
}

void OrdenacaoExterna(int arquivo, int quant_registros) {
  FILE *arq, *temp;
  clock_t start;
  clock_t end;

  int i, j;
  long int tamanho;
  long int *registros;
  char nome_arq[15];

  printf("\nTamanho do Arquivo: %d Milhões. ", arquivo);
  if(quant_registros==UmMilhao) printf("Quantidade de Registros: 1 Milhão\n");
  else printf("Quantidade de Registros: 10 Milhões\n");

  sprintf(nome_arq, "arq%dM.txt", arquivo);

  arq = fopen(nome_arq, "r");
  fscanf(arq, "%ld", &tamanho);

  long int quant_fitas = tamanho / quant_registros;

  if(tamanho % 2 == 1)
    quant_fitas++;

  long int p=0, fita=1, cont=0;
  long int aux;

  start = clock();

  //Distribuição
  for(i=0; i<quant_fitas; i++) {

    registros = (long int*)malloc(quant_registros*sizeof(long int)); 
    cont = -1;

    for(j=0; j<quant_registros && !feof(arq); j++) {
      if(j==0 && i==0)
        aux = tamanho;
      else
        fscanf(arq, "%ld", &aux);
      registros[j] = aux;
      cont++;
    }

    Quicksort(registros, p, cont);

    sprintf(nome_arq, "fita%d.txt", fita);

    temp = fopen(nome_arq, "w");

    for(int k=0; k<cont; k++) {
        fprintf(temp, "%ld\n", registros[k]);
    }

    free(registros);
    fita++;
  }
  end = clock();
  
  printf("\tTempo de Distribuição: %.2Lf segundos.\n", (long double) (end - start) / CLOCKS_PER_SEC);

  FILE *fita1, *fita2, *fim;

  long int num1, num2, numero;
  long int final=quant_fitas, indice=0, contador=0, indice_fita=0;

  start = clock();

  //Intercalação
  while(final > 1) {
    for (j=0; j<final/2; j++) {
      indice_fita++;

      sprintf(nome_arq, "fita%d.txt", indice_fita);
      fita1 = fopen(nome_arq, "r");

      indice_fita++;

      sprintf(nome_arq, "fita%d.txt", indice_fita);
      fita2 = fopen(nome_arq, "r");

      sprintf(nome_arq, "fita%d.txt", fita); 
      fim = fopen(nome_arq, "w"); 
      fita++;

      fscanf(fita1, "%ld", &num1);
      fscanf(fita2, "%ld", &num2);  

      while(!feof(fita1) && !feof(fita2)) {
        if (num1 < num2) {
          fprintf(fim, "%ld\n", num1);
          fscanf(fita1, "%ld", &num1);
        } else {
            fprintf(fim, "%ld\n", num2);
            fscanf(fita2, "%ld", &num2);
        }
      }

      if(!feof(fita1)) {
        while(!feof(fita1)) { 
          fprintf(fim, "%ld\n", num1);
          fscanf(fita1, "%ld", &num1);
        }
      } 
      if(!feof(fita2)) {
        while(!feof(fita2)) { 
          fprintf(fim, "%ld\n", num2);
          fscanf(fita2, "%ld", &num2);
        } 
      }
    }
    if(final % 2 == 1) 
      final++;
      
    final = final/2;
  }
  end = clock();

  printf("\tTempo de Intercalação: %.2Lf segundos.\n", (long double) (end - start) / CLOCKS_PER_SEC);

  DeletaArquivos(fita-1);
}