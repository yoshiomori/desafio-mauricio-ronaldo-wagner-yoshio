#include <stdio.h>
#include <math.h>

void
gera_imagem(double **h, int n, int m){
  FILE *pfile;
  int i, j;
  double hmax, pmax;
  double delta;

  pfile = fopen("imagem.ppm", "w");

  /* Calculando a altura máxima e mínima */
  hmax = pmax = h[0][0]; /* Tratamento especial para o primeiro elemento */
  for(i = 0; i < n; i++)
    for(j = 1; j < m; j++){
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
