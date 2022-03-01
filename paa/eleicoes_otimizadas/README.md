# Eleições com turno único

## Motivação

- Eleições que permitem a realização de até 2 turnos, por exemplo, poderiam ser reduzidas para eventos de apenas 1 turno. Porém, a não realização de um segundo turno tem o potencial de
eleger um candidato que tenha um alto percentual de rejeição e que possivelmente não ganharia um segundo turno.

- Com o objetivo de tornar eleições com 2 turnos mais econômica, uma universidade está propondo a realização de um único dia de eleições para reitor em que um eleitor pode votar em até 3 candidatos, em ordem de sua preferência, ou seja, o primeiro candidato escolhido é o de maior preferência. Para contabilização de votos no primeiro turno apenas os votos em primeira opção são contabilizados. Caso não haja vencedor no primeiro turno com pelo menos 50% dos votos válidos, um segundo turno virtual é realizado entre os 2 primeiros candidatos do primeiro turno sem realizar outra consulta, porém, a escolha em qualquer das 3 opções feitas pelos eleitores pode ser contabilizada como um voto válido no segundo turno.

- Uma eleição sem nenhum voto válido no primeiro turno não possui um resultado válido. Empates em número de votos são
resolvidos de acordo com o candidato de maior idade e, portanto, de maior prioridade.

- Caso nenhum candidato tenha conquistado pelo menos 50% dos votos em primeira opção, então um segundo turno virtual é realizado. No segundo turno, o voto de cada eleitor pode ser contabilizado no máximo uma vez. Se o eleitor não votou em nenhum dos 2 candidatos que disputam o segundo turno em nenhuma das 3 opções, então o seu voto não é computado como voto válido no segundo turno. Caso contrário, o voto de sua maior preferência em algum candidato que concorre no segundo turno é contado como voto válido ao candidato escolhido. Por exemplo, em um segundo turno disputado entre os candidatos 2 e 3, se um eleitor votou nos candidatos 1 2 3, então o seu voto vai para o candidato 2 apenas, pois, em caso do candidato 1 não passar do primeiro turno, considera-se que o eleitor escolheria o candidato 2 em um segundo turno com a participação do candidato 2 e qualquer outro candidato.

## Entrada

- A primeira linha de um caso de teste contém os inteiros V (1 ≤ V ≤ 10.000), indicando o número de eleitores votantes, e C, indicando o número de candidatos (1 ≤ C ≤ 100).
- Nas próximas V linhas, são apresentados os votos de cada eleitor votante. Em cada uma dessas linhas, são fornecidos 3 inteiros com as escolhas, em ordem de preferência, de um eleitor.

## Saída

- Se a eleição é inválida, o número 0 é impresso na tela.
- Caso contrário, deve ser impresso na primeira linha da saída o número do candidato vencedor do primeiro turno e a porcentagem de votos.
- Caso o vencedor do primeiro turno tenha vencido com menos de 50% dos votos válidos, deve ser impresso na segunda linha o número do vencedor do segundo turno e sua porcentagem de votos.

Obs. Para os cálculos da porcentagem, deve-se considerar apenas os votos válidos.

## Comportamento

```
# Entrada

10 3    //Número de eleitores e candidatos
1 2 3   //Votos
1 2 4
2 1 4
2 3 1
3 2 1
3 2 1
1 3 2
4 3 2
2 1 3
1 2 4

# Saída

1 44.44  //Vencedor do primeiro turno
2 60.00  //Vencedor do segundo turno
```