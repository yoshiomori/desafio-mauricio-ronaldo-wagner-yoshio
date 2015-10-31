/* Faz uma alocação segura de um bloco na memória 
 * emitindo error quando necessário */

#include <stdio.h>
#include <stdlib.h>

static void safe(void *block, char *message){
  if(!block){
    perror(message);
    exit(EXIT_FAILURE);
  }
}

void *malloc_safe(size_t size){
  void *block = malloc(size);
  safe(block, "malloc_safe");
  return block;
}

void *calloc_safe(size_t nobj, size_t size){
  void *block = calloc(nobj, size);
  safe(block, "calloc_safe");
  return block;
}
