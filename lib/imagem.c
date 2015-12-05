#include <stdio.h>
#include <math.h>
#include <omp.h>

void
gera_imagem(float **h, int n, int m){
  FILE *pfile;
  int i, j;
  float hmax, pmax;
  float delta;

  pfile = fopen("imagem.ppm", "w");

  /* Calculando a altura máxima e mínima */
  hmax = - INFINITY;
  pmax = INFINITY;
  #pragma omp parallel for private(j, i) schedule(auto)
  for(i = 0; i < n; i++)
    for(j = 0; j < m; j++){
      hmax = h[i][j] > hmax ? h[i][j] : hmax;
      pmax = h[i][j] < pmax ? h[i][j] : pmax;
    }

  /* Calculando delta */
  delta = (hmax > -pmax ? hmax : -pmax) / 255;

  /* Escrevendo no arquivo */
  fprintf(pfile, "P3\n");
  fprintf(pfile, "%d %d\n", m, n);
  fprintf(pfile, "255\n");
  for(i = 0; i < n; i++)
    for(j = 0; j < m; j++){
      fprintf(pfile, "%d %d %d",
	      h[i][j] < 0 ? (int)(ceil(-h[i][j] / delta)) : 0, 0,
	      h[i][j] > 0 ? (int)(ceil(h[i][j] / delta)) : 0);
      fprintf(pfile, j != m - 1 ? " " : "\n");
    }
  
  fclose(pfile);
}
