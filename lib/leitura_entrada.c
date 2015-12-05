#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static char linha[100];

static float pega_float(FILE *file){
  fscanf(file, "%s", linha);
  return atof(linha);
}

static int pega_int(FILE *file){
  fscanf(file, "%s", linha);
  return atoi(linha);
}

static void pega_tupla(FILE *file, int *a, int *b){
  fscanf(file, "%s", linha);
  *a = atoi(strtok(linha, "(,)"));
  *b = atoi(strtok('\0', "(,)"));
}

void leia_entrada(char *nome_arquivo, int *larg, int *alt, int *L, int *H, int *T, int *v, int *Niter, unsigned int *s, float *eps, float *P){
  FILE *file;
  file = fopen(nome_arquivo, "r");
  if(!file){
    perror("Arquivo de entrada");
    exit(EXIT_FAILURE);
  }
  pega_tupla(file, larg, alt);
  pega_tupla(file, L, H);
  *T = pega_int(file);
  *v = pega_int(file);
  *eps = pega_float(file);
  *Niter = pega_int(file);
  *P = pega_float(file);
  *s = (unsigned int)pega_int(file);
  fclose(file);
}
