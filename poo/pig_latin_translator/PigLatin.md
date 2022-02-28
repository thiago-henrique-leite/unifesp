# Tradutor de Inglẽs para PigLatin

## Motivação

- PigLatin é um jogo de linguagem que consiste em pegar uma palavra em inglês, colocar sua primeira letra no final, e acrescentar o sufixo 'ay'. Por exemplo, `beautiful` em PigLatin seria `eautifulbay`. Este jogo de linguagem pode ser usado como uma maneira de criptografia.

## Entrada

- A entrada consiste em uma frase em inglês.

## Saída

- Imprime a frase traduzida em PigLatin.

## Comportamento

- O usuário fornece a frase
- O script itera sobre todas as palavras da frase, repartindo cada palavra em três strings, a primeira letra, as letras remanescentes e o sufixo 'ay', e juntando-as da maneira adequada, remanescentes + primeira letra + sufixo. Por fim, a palavra resultante é concatenada em uma nova string, inicialmente vazia, que recebe a frase traduzida. 
- Retorna a frase traduzida em PigLatin.
