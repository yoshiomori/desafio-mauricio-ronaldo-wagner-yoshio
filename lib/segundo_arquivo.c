#include <stdio.h> /* fopen, perror */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include <math.h> /* sqrt */
#include "matriz.h" /* calloc_matriz_double */
#include "ondas_lib.h" /* cx, cy */

void gera_segundo_arquivo(int Niter, int nlin, int ncol, double ***amostra){
  double **media, **desvio;
  int i, j, k;
  FILE *pfile;
  media = calloc_matriz_double(nlin, ncol);

  /* Fazendo o calculo da média das alturas para cada ponto */
  for(k = 0; k < Niter; k++)
    for(i = 0; i < nlin; i++)
      for(j = 0; j < ncol; j++)
	media[i][j] += amostra[k][i][j];
  for(i = 0; i < nlin; i++)
    for(j = 0; j < ncol; j++)
      media[i][j] /= Niter;

  desvio = calloc_matriz_double(nlin, ncol);

  /* Fazendo o calculo do desvio padrão das alturas para cada ponto */
  for(k = 0; k < Niter; k++)
    for(i = 0; i < nlin; i++)
      for(j = 0; j < ncol; j++)
	desvio[i][j] += (amostra[k][i][j] - media[i][j])
	  * (amostra[k][i][j] - media[i][j]);
  for(i = 0; i < nlin; i++)
    for(j = 0; j < ncol; j++)
      desvio[i][j] = sqrt(desvio[i][j] / (Niter - 1));

  pfile = fopen("segundo_arquivo.txt", "w");
  if(!pfile){
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  fprintf(pfile, "x\t\ty\t\tmedia\n");
  for(i = 0; i < nlin; i++)
    for(j = 0; j < ncol; j++)
      fprintf(pfile, "%lf\t%lf\t%12.7lf\t%12.7lf\n",
	      cx(j), cy(i), media[i][j], desvio[i][j]);
  fclose(pfile);
}
