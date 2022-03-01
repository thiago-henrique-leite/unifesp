# Simulação de compras no mercado 

- Implemente um programa em linguagem assembly que simule o valor total de uma compra no mercado. O programa deve ler as entradas do teclado dadas pelo usuário e fornecer no final o valor total do pedido.
- Primeiramente, o Mars deve exibir a mensagem: "Digite o nome do produto: ".
- Depois, ele deve ler como entrada um texto (nome do produto) terminado no caractere ascii correspondente à tecla enter.
- Em seguida, o programa deve exibir a mensagem: "Insira o valor unitário deste produto: " e ler como entrada um número do tipo float.
- Posteriormente, o programa deve exibir a mensagem: "Insira a quantidade desejada deste produto: " e ler como entrada um número do tipo inteiro. Após o usuário passar estas informações sobre o produto, o programa deve exibir a seguinte mensagem: “Deseja comprar algo a mais? Se sim, digite 1. Caso contrário, digite 0. Resposta: ”. Em seguida, ele deve ler como entrada a resposta do usuário. 
- Se a resposta for “1”, o programa deve retornar às mensagens iniciais, pedindo nome, valor unitário e quantidade do produto. O usuário pode pedir até cinco produtos por compra. Após o quinto produto, o programa já deve encerrar a compra.
- Quando a resposta for “0” ou a compra for encerrada pelo programa, o Mars deve gerar como saída uma lista contendo a quantidade de cada produto pedido, com o respectivo valor unitário e valor total do produto, bem como o valor total do pedido de compra, conforme mostrado no exemplo abaixo. 

#### Exemplo:
- Input
```
Digite o nome do produto: caixa de uva
Insira o valor unitário deste produto: 6.25
Insira a quantidade desejada deste produto: 5

Deseja comprar algo a mais? Se sim, digite 1. Caso contrário, digite 0. Resposta: 1

Digite o nome do produto: leite
Insira o valor unitário deste produto: 4.30
Insira a quantidade desejada deste produto: 12

Deseja comprar algo a mais? Se sim, digite 1. Caso contrário, digite 0. Resposta: 0
```
- Output
```
Pedido:

5x caixa de uva
Valor unitário: R$ 6.25
Valor total do produto: R$ 31.25

12x leite
Valor unitário: R$ 4.30
Valor total do produto: 51.60
Valor total do pedido: R$ 82.85
```