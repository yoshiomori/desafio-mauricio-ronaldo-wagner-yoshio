#include <stdio.h> /* printf */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include "leitura_entrada.h" /* leia_entrada */
#include "matriz.h"

int main(int argc, char **argv){
  /* Variáveis armazenam dados do arquivo */
  int larg, alt, L, H, T, v, Niter, s, k;
  float eps, P;
  
  /* h é uma referencia para os dados de altura dos pontos no lago
   * cx e cy referencia para a coordenada do lago */
  float **h, **cx, **cy;

  /* i, j índice das matrizes */
  int i, j;

  /* Pegando os dados do arquivo */
  if (argc != 2){
    printf ("USO: ondas <nome do arquivo>\n");
    exit(EXIT_FAILURE);
  }
  leia_entrada(argv[1], &larg, &alt, &L, &H, &T, &v, &Niter, &s, &eps, &P);

  /* Montando matrizes de dados */
  h = matriz_float((H + 1), (L + 1));
  cx = matriz_float((H + 1), (L + 1));
  for(i = 0; i < (H + 1); i++)
    for(j = 0; j < (L + 1); j++)
      cx[i][j] = j * (float) larg / L;
  
  /* Faz as Niter iterações */
  for(k = 0; k < Niter; k++){
  }
  return 0;
}
