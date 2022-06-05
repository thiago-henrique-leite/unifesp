/*
  Algoritmo de Criptografia RC4
  Segurança Computacional - UNIFESP
  Thiago Henrique Leite da Silva, 139920
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTES 256

char* char_array(int nbytes) {
  return (char*) malloc(BYTES * sizeof(char));
}

unsigned char* unsigned_char_array(int nbytes) {
  return (unsigned char*) malloc(nbytes * sizeof(unsigned char));
}

void swap(unsigned char *array, int i, int j) {
    unsigned char aux = array[i];
    array[i] = array[j];
    array[j] = aux;
}

unsigned char* encripty_rc4(char *message, char *key) {
  unsigned char *s_array = unsigned_char_array(BYTES);
  unsigned char *response = unsigned_char_array(strlen(message));

  int i = 0, j = 0, k = 0;

  for(i = 0; i < BYTES; i++)
    s_array[i] = i;

  for(i = 0; i < BYTES; i++) {
    j = (j + s_array[i] + key[i % strlen(key)]) % BYTES;

    swap(s_array, i, j);
  }

  for(k = i = j = 0; k < strlen(message); k++) {
    i = (i + 1) % BYTES;
    j = (j + s_array[i]) % BYTES;

    swap(s_array, i, j);

    response[k] = s_array[(s_array[i] + s_array[j]) % BYTES] ^ message[k];
  }

  return response;
}

void show_encrypted_message(unsigned char *encripted_message, int lenght) {
  int i;

  for(i = 0; i < lenght; i++)
    printf("%x:", encripted_message[i]);

  printf("\n");
}

int main(int argc, char **argv) {
  char *message = char_array(BYTES);
  char *key = char_array(BYTES);

  scanf("%s", message);
  scanf("%s", key);

  unsigned char* encrypted_message = encripty_rc4(message, key);

  show_encrypted_message(encrypted_message, strlen(message));

  return 0;
}
