#include "alloc_safe.h" /* malloc_safe, calloc_safe */

double **calloc_matriz_double(int nlin, int ncol){
  int i;
  double **m, *aux;
  m = malloc_safe(nlin * sizeof *m);
  aux = calloc_safe(nlin * ncol, sizeof *aux);
  for(i = 0; i < nlin; i++)
    m[i] = aux + i * ncol;
  return m;
}
