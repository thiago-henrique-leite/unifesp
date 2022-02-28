//Problema 2 - PAA - Código feito por Thiago Henrique Leite da Silva - UNIFESP 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  int v1, v2, v3;
} TVoto;

void perform();
bool EleicaoEhValida(TVoto*, int, int);
bool VotoEhValido(int, int);
int  MaisVotado(int*, int);
int  SegundoMaisVotado(int*, int, int);
int  PrimeiroTurno(TVoto*, int, int);
int  SegundoTurnoVirtual(TVoto*, int, int, int);
bool EleicaoTerminou(int*, int, int);
void ImprimeResultadoDoTurno(int, float, int);

// A função perform é uma função sem parâmetros e sem retorno, ela é útil para que o leitor do código saiba exatamente o que o programa faz.
// Ela também serve para limitarmos o acesso do usuário a alguns trechos do script.

void perform() {
  int num_candidatos, num_eleitores, i;

  printf("Entre com o número de eleitores e candidatos: ");
  scanf("%d %d", &num_eleitores, &num_candidatos);

  TVoto *votos = (TVoto*)malloc(num_eleitores*sizeof(TVoto));

  for(i=0; i<num_eleitores; i++)
    scanf("%d %d %d", &votos[i].v1, &votos[i].v2, &votos[i].v3);

  if(EleicaoEhValida(votos, num_candidatos, num_eleitores)) {
    PrimeiroTurno(votos, num_candidatos, num_eleitores);
  }
}

bool EleicaoEhValida(TVoto *votos, int num_candidatos, int num_eleitores) {
  int i;

  for(i=0; i<num_eleitores; i++) 
    if(VotoEhValido(votos[i].v1, num_candidatos))
      return true;

  printf("0");
  return false;
}

bool VotoEhValido(int voto, int num_candidatos) {
  return (voto >= 1 && voto <= num_candidatos) ? true : false;
}

int MaisVotado(int *contagem_votos, int num_candidatos) {
  int i, maisVotado=0;

  for(i=1; i<num_candidatos; i++)
    if(contagem_votos[i] > contagem_votos[maisVotado])
      maisVotado = i;

  return maisVotado+1;
}

int SegundoMaisVotado(int *contagem_votos, int num_candidatos, int maisVotado) {
  int i, segundoMaisVotado=0;

  if(maisVotado == segundoMaisVotado)
    segundoMaisVotado++;

  for(i=1; i<num_candidatos; i++)
    if(contagem_votos[i] > contagem_votos[segundoMaisVotado] && i != maisVotado)
      segundoMaisVotado = i;

  return segundoMaisVotado+1;
}

int PrimeiroTurno(TVoto *votos, int num_candidatos, int num_eleitores) {
  int i, j, votosValidos=0, maisVotado, *contagem_votos, voto;

  contagem_votos = (int*)malloc(num_candidatos*sizeof(int));

  for(j=0; j<num_eleitores; j++) {
    voto = votos[j].v1;
    if(VotoEhValido(voto, num_candidatos)) {
      contagem_votos[voto-1]++;
      votosValidos += 1;
    }
  }

  maisVotado = MaisVotado(contagem_votos, num_candidatos);
  ImprimeResultadoDoTurno(contagem_votos[maisVotado-1], votosValidos, maisVotado);

  if(EleicaoTerminou(contagem_votos, maisVotado, votosValidos))
    return 0;

  int segundoMaisVotado = SegundoMaisVotado(contagem_votos, num_candidatos, maisVotado-1);
  SegundoTurnoVirtual(votos, num_eleitores, maisVotado, segundoMaisVotado);

  free(contagem_votos);
  return 1;
}

int MenorElemento(int a, int b) {
  return (a < b) ? a : b;
}

int SegundoTurnoVirtual(TVoto *votos, int num_eleitores, int candidato1, int candidato2) {
  int i;
  float votos1=0, votos2=0, votosValidos=0, porcentagem=0;
  
  for(i=0; i<num_eleitores; i++) { 
    if(votos[i].v1 == candidato1 || votos[i].v1 == candidato2) {
            if(votos[i].v1 == candidato1) 
                votos1++;
            else
                votos2++;
        votosValidos++;

    } else if(votos[i].v2 == candidato1 || votos[i].v2 == candidato2) {
            if(votos[i].v2 == candidato1) 
                votos1++;  
            else
                votos2++;
        votosValidos++;
        
    } else if(votos[i].v3 == candidato1 || votos[i].v3 == candidato2) {
            if(votos[i].v3 == candidato1)
                votos1++;
            else
                votos2++;
        votosValidos++;
    }
  }
  
  int eleito, quant_votos=votos1;

  if(votos1 > votos2)
    eleito = candidato1;
  else if(votos1 < votos2)
    eleito = candidato2;
  else 
    eleito = MenorElemento(candidato1, candidato2);

  if(eleito != candidato1)
    quant_votos = votos2;
  
  ImprimeResultadoDoTurno(quant_votos, votosValidos, eleito);

  return 1;
}

bool EleicaoTerminou(int *contagem_votos, int maisVotado, int votosValidos) {
  return (contagem_votos[maisVotado-1] > (votosValidos / 2)) ? true : false;
}

void ImprimeResultadoDoTurno(int quant_votos, float votosValidos, int candidato) {
  float porcentagemVotos = (quant_votos * 100) / votosValidos;
  printf("%d %.2f\n", candidato, porcentagemVotos);
}

int main() {
  perform();
  return 0;
} 