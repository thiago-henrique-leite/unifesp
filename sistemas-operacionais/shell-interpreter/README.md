# Interpretador Shell em C

Implementar um interpretador de comandos em terminal para Linux.

Requisitos do protótipo

O interpretador de comandos deverá:

1. Executar comandos unitários, com múltiplos parâmetros. Exemplo:

- ```ls -la```

2. Executar comandos encadeados, utilizando o operador pipe “|” para combinar saída e entrada entre os comandos. Exemplo:

- ```ls -la | grep “teste” ```
- ```cat /proc/cpuinfo | grep "model name" | wc -l ```

3. Executar sequências de comandos independentes com o operador “;”. Exemplo:

- ```echo “SO 2021” ; echo “ADE Viva!”```

4. Executar comandos condicionados com operadores OR (||) e AND (&&). Exemplo:

- ```cat 12345 || echo "aquivo inexistente"```
- ```ping -c1 www.unifesp.br.br && echo "SERVIDOR DISPONIVEL" || echo "SERVIDOR INDISPONIVEL"```

5. Executar comandos em background, liberando o shell para receber novos comandos do usuário.

- ```ping -c5 www.unifesp.br &```

### Execução

Para testar o funcionamento do interpretador em seu ambiente de desenvolvimento Linux, basta seguir os passos abaixo:

```console
git clone git@github.com:thiago-henrique-leite/sistemas-operacionais.git 

cd shell-interpreter

gcc shell.c -o shell

./shell
```