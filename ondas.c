#include <stdio.h> /* printf */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include "lib/leitura_entrada.h" /* leia_entrada */
#include "lib/matriz.h" /* matriz_double */
#include "lib/alloc_safe.h" /* malloc_safe */
#include "lib/ondas_lib.h" /* nova_gota, calcula_altura, cx, cy */
#include "lib/imagem.h" /* gera_imagem */
#include "lib/segundo_arquivo.h" /* gera_segundo_arquivo */

/* Variáveis armazenam dados do arquivo */
extern int larg, alt, L, H, v;
extern double eps;

int
main(int argc, char **argv){ 
  /* h é uma referencia para os dados de altura dos pontos no lago */
  double **h, t, dt, P, ***amostra_h;

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

  /* Inicializando o vetor de amostras */
  amostra_h = malloc(Niter * sizeof *amostra_h);
  for(i = 0; i < Niter; i++)
    amostra_h[i] = calloc_matriz_double(H, L);
  
  /* Faz as Niter iterações */
  /* Atualizando tempo para cada iteração */
  for(k = 0, t = 0; k < Niter; k++, t += dt){
    /* Para cada ponto no lago calcula a altura da água */
    for(i = 0; i < H; i++)
      for(j = 0; j < L; j++)
	amostra_h[k][i][j] = h[i][j] = calcula_altura(cx(j), cy(i), t);
    
    /* Verificando se nessa iteração será gerada uma nova gota */
    if((double)rand() / RAND_MAX < P / 100)
      nova_gota((double)(rand() % larg), (double)(rand() % alt), t);
  }

  gera_imagem(h, H, L);
  gera_segundo_arquivo(Niter, H, L, amostra_h);
  return 0;
}
