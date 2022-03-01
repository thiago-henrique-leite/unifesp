/***************************************************
 *                  Bibliotecas                    *
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************************
 *                    Funções                      *
 ***************************************************/

void   crossover(char personA[], char personB[], char crossA[], char crossB[], int cut_position);
double calculate_probability(char crossA[], char crossB[], char expectedPerson[], double prob);
double genetic_algorithm();

//***************************************************

/* Realiza o crossover de dois indíviduos fornecidos pelo usuário, dada  
   uma posição de corte também fornecida pelo usuário.                  */

void crossover(char personA[], char personB[], char crossA[], char crossB[], int cut_position) 
{
  int i;

  for(i = 0; i < strlen(personA); i++) 
  {
    if(i < cut_position)
    {
      crossA[i] = personA[i];
      crossB[i] = personB[i];
    } 
    else 
    {
      crossA[i] = personB[i];
      crossB[i] = personA[i];
    }
  }
}

/* Calcula a probabilidade de se obter um indivíduo fornecido pelo usuário a partir 
   dos indíviduos obtidos no crossover e uma probabilidade de mutação.             */

double calculate_probability(char crossA[], char crossB[], char expectedPerson[], double prob) 
{
  int i;
  double prob_final;
  double probA=1, probB=1;

  /* Calcula a probabilidade de se obter o resultado esperado para cada um dos dois indivíduos obtidos no crossover.
     Analisamos os indivíduos bit a bit, caso o bit precise mudar, multiplicamos pela probabilidade fornecida pelo usuário, 
     caso não precise mudar, multiplicamos por (1 - probabilidade fornecida), que seria a probabilidade do bit não mudar.  */

  for(i=0; i<strlen(expectedPerson); i++) 
  {
    if(crossA[i] != expectedPerson[i])
      probA *= prob;
    else
      probA *= 1 - prob;

    if(crossB[i] != expectedPerson[i]) 
      probB *= prob;
    else
      probB *= 1 - prob;
  }

  /* Calculamos a probabilidade de não obtermos o resultado: (1-probA) * (1-probB), para depois obtermos a probabilidade
     de chegarmos ao resultado final: 1 - ((1-probA) * (1-probB))                                                       */

  prob_final = 1 - ((1-probA) * (1-probB));

  return prob_final;
}

/* Recebe parâmetros do usuário */

double genetic_algorithm() 
{
  int bits_number, cut_position;
  double prob;

  // Quantidade de bits de cada indivíduo
  scanf("%d", &bits_number);

  // Posição de corte no crossover e probabilidade de mutação
  scanf("%d %lf", &cut_position, &prob);

  char personA[bits_number], personB[bits_number], expectedPerson[bits_number], crossA[bits_number], crossB[bits_number];

  scanf("%s %s %s", personA, personB, expectedPerson);

  crossover(personA, personB, crossA, crossB, cut_position);

  double response = calculate_probability(crossA, crossB, expectedPerson, prob);

  return response;
}

int main(int argc, char** argv) 
{
  int testes, i;

  // Quantidade de casos teste
  scanf("%d", &testes);

  double solutions[testes];

  for(i=0; i<testes; i++) 
    solutions[i] = genetic_algorithm();

  for(i=0; i<testes; i++) 
    printf("%.7lf\n", solutions[i]);

  return 0;
}
