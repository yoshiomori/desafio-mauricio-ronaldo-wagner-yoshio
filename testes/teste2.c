#include <stdio.h> /* printf */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include "../lib/leitura_entrada.h" /* leia_entrada */
#include "../lib/matriz.h" /* matriz_double */
#include "../lib/alloc_safe.h" /* malloc_safe */
#include "../lib/ondas_lib.h" /* nova_gota */
#include "../lib/imagem.h" /* gera_imagem */

extern double eps;
extern int larg, alt, L, H, v;

int
main(int argc, char **argv){
  /* h é uma referencia para os dados de altura dos pontos no lago */
  double **h;

  /* i, j índice das matrizes */
  int i, j;
  
  larg = 1024;
  alt = 768;
  L = 1024;
  H = 768;
  v = 10;
  eps = 0.001;
  
  /* Montando matriz de alturas inicialmente com tudo 0 */
  h = calloc_matriz_double(H, L);
  
  /* Verificando se nessa iteração será gerada uma nova gota */
  nova_gota(512, 384, 0);

  /* Para cada ponto no lago calcula a altura da água */
  for(i = 0; i < H; i++)
    for(j = 0; j < L; j++)
      h[i][j] = calcula_altura(cx(j), cy(i), 10);
  
  gera_imagem(h, H, L);
  return 0;
}
