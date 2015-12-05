#include <stdio.h> /* printf */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include "../lib/leitura_entrada.h" /* leia_entrada */
#include "../lib/matriz.h" /* matriz_float */
#include "../lib/alloc_safe.h" /* malloc_safe */
#include "../lib/ondas_lib.h" /* nova_gota, calcula_altura, cx, cy */
#include "../lib/imagem.h" /* gera_imagem */

/* Variáveis armazenam dados do arquivo */
extern int larg, alt, L, H, v;
extern float eps;

int
main(int argc, char **argv){ 
  /* h é uma referencia para os dados de altura dos pontos no lago */
  float **h, t, dt, P;

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
  h = calloc_matriz_float(H, L);

  /* Variação do tempo por iteração */
  dt = (float)T / Niter;
  
  /* Faz as Niter iterações */
  for(k = 0, t = 0; k < Niter; k++){
    /* Verificando se nessa iteração será gerada uma nova gota */
    if(!(k % 2))
      nova_gota((float)(rand() % larg), (float)(rand() % alt), t);

    /* Para cada ponto no lago calcula a altura da água */
    for(i = 0; i < H; i++)
      for(j = 0; j < L; j++)
	h[i][j] = calcula_altura(cx(j), cy(i), t);

    /* Atualizando tempo para a próxima iteração */
    t += dt;
  }

  gera_imagem(h, H, L);
  return 0;
}
