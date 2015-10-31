#include <stdlib.h>
float **matriz_float(int nlin, int ncol){
  int i;
  float **m, *aux;
  m = malloc(nlin * sizeof *m);
  aux = calloc(nlin * ncol, sizeof *aux);
  for(i = 0; i < nlin; i++)
    m[i] = aux + i * ncol;
  return m;
}
