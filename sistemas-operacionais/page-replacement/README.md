# Substituição de Páginas (Algoritmo de Envelhecimento)

### Descrição:

Em gerenciamento de memória virtual, duas tarefas são fundamentais:

##### 1. Mapeamento de Endereços. 

O endereço virtual em espaço de página virtual é mapeado para endereço físico em quadro de página na memória principal. Quando um endereço virtual é referenciado pela CPU, tal endereço é tratado pela MMU. Se o endereço virtual estiver indicado na tabela de páginas virtuais como ausente em memória, ocorre ausência de página (page miss), gerando uma interrupção (trap), para que o SO carregue a página requerida em memória e a mapeie na entrada na tabela de página virtual. Se não houver espaço para um novo mapeamento dentro do espaço de quadros de páginas físicas em memória, o SO (gerenciador de memória) tem que substituir uma moldura de página em memória, movendo-a temporariamente para o disco, de modo a liberar o espaço necessário para a nova página a ser carregada. Posteriormente, quando necessário, ou seja, quando houver uma referência à página substituída, o SO terá de trazer de forma íntegra essa página do disco de volta à memória. Vale destacar que pode ocorrer uma nova substituição de página nesse evento, caso não haja espaço novamente.

##### 2. Substituição de Página. 

Se a memória estiver cheia, ausência de página demanda a escolha de qual página física será substituída, tarefa a qual é realizada por algum algoritmo. O algoritmo pode ser baseado, por exemplo, na escolha da página menos utilizada recentemente ou menos utilizada frequentemente, filas, envelhecimento, relógios lógicos, grupos de trabalho, entre outros. Além da eficiência do algoritmo, que é medida pela frequência de ausência de páginas (quanto menor, melhor), o importante também é manter a persistência e integridade da página, de modo que um mesmo conteúdo e suas informações de gerenciamento não possam divergir entre diferentes espaços de endereçamento (página virtual, quadro de página em memória, quadro de página em disco). Neste trabalho, daremos foco prático ao conteúdo de substituição de página. A tarefa é implementar uma simulação do algoritmo MRU (Algoritmo de Envelhecimento - Aging). 

##### Requisitos

Para tanto, considere as seguintes premissas:

- Os tiques dos relógio são represados por eventos discretos.
- Uma memória real, MR, que está sempre cheia.
- Uma memória virtual, MV, onde |MV| > |MR|.
- Uma memória swap, MS, onde |MS| >= |MV| - |MR|
- A memória é representada por conjunto de páginas, onde cada página é representada por um registro (struct), contendo atributos de interesse.
- A cada tique, um subconjunto aleatório de páginas H, onde H ⊂ MV, o qual foi referenciado em memória.

### Funcionamento

A cada iteração, sorteamos uma página a ser acessada, caso ela esteja na memória principal, atualizamos seus bits, caso contrário, ocorreu um page miss, então decidimos qual página deve sair da memória principal, para dar lugar a página solicitada que se encontra na memória swap.

O limitador de número aleatório, serve para limitarmos o range do nosso sorteio, como uma forma de diminuir os page misses, portanto, sortearemos uma página no intervalo (1..Limitador).

### Execução

Os parâmetros necessários para executar o algoritmo ssão:

- Tamanho da memória virtual
- Tamanho da memória real
- Número de iterações (eventos de acesso a uma página)
- Limitador do número aleatório

Para testar o funcionamento do interpretador em seu ambiente de desenvolvimento Linux, basta seguir os passos abaixo:

```console
git clone git@github.com:thiago-henrique-leite/sistemas-operacionais.git 

cd page-replacement

gcc main.c -o main -lm
 
./main 100 50 10000 70
```
