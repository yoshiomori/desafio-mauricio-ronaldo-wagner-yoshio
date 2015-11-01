#include <stdio.h> /* printf */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include "lib/leitura_entrada.h" /* leia_entrada */
#include "lib/matriz.h" /* matriz_double */
#include "lib/alloc_safe.h" /* malloc_safe */
#include "lib/ondas_lib.h" /* nova_gota, calcula_altura, cx, cy */
#include "lib/imagem.h" /* gera_imagem */

/* Variáveis armazenam dados do arquivo */
extern int larg, alt, L, H, v;
extern double eps;

int
main(int argc, char **argv){ 
  /* h é uma referencia para os dados de altura dos pontos no lago */
  double **h, t, dt, P;

  /* i, j índice das matrizes */
  int i, j, k, s, Niter, T;

  /* Pegando os dados do arquivo */
  if (argc != 2){
    printf ("USO: ondas <nome do arquivo>\n");
    exit(EXIT_FAILURE);
  }
  leia_entrada(argv[1], &larg, &alt, &L, &H, &T, &v, &Niter, &s, &eps, &P);

  /* Configurando a semente */
  srand(s);

  /* Montando matriz de alturas inicialmente com tudo 0 */
  h = calloc_matriz_double(H, L);

  /* Variação do tempo por iteração */
  dt = (double)T / Niter;
  
  /* Faz as Niter iterações */
  /* Atualizando tempo para cada iteração */
  for(k = 0, t = 0; k < Niter; k++, t += dt){
    /* Para cada ponto no lago calcula a altura da água */
    for(i = 0; i < H; i++)
      for(j = 0; j < L; j++)
	h[i][j] = calcula_altura(cx(j), cy(i), t);
    
    /* Verificando se nessa iteração será gerada uma nova gota */
    if((double)rand() / RAND_MAX < P / 100)
      nova_gota((double)(rand() % larg), (double)(rand() % alt), t);
  }

  gera_imagem(h, H, L);
  return 0;
}
