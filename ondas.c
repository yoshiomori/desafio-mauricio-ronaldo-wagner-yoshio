#include <stdio.h> /* printf */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include "leitura_entrada.h" /* leia_entrada */
#include "matriz.h" /* matriz_double */
#include "alloc_safe.h" /* malloc_safe */
#include "gotas.h" /* nova_gota */

/* Variáveis armazenam dados do arquivo */
static int larg, alt, L, H, T, v, Niter, s, k;
static double eps, P;

/* Faz o calculo da coordenada do ponto (i, j) no eixo das abcissas*/
static double
cx(int i){
  return i * (double)larg / L;
}

/* Faz o calculo da coordenada do ponto (i, j) no eixo das ordenadas */
static double
cy(int j){
  return j * (double)alt / H;
}

/* Calcula o tempo da simulação */
static double
t(int k){
  return k * (double)T / Niter;
}

int
main(int argc, char **argv){ 
  /* h é uma referencia para os dados de altura dos pontos no lago */
  double **h;

  /* i, j índice das matrizes */
  int i, j;

  /* Pegando os dados do arquivo */
  if (argc != 2){
    printf ("USO: ondas <nome do arquivo>\n");
    exit(EXIT_FAILURE);
  }
  leia_entrada(argv[1], &larg, &alt, &L, &H, &T, &v, &Niter, &s, &eps, &P);

  /* Configurando a semente */
  srand(s);

  /* Montando matriz de alturas inicialmente com tudo 0 */
  h = calloc_matriz_double((H + 1), (L + 1));
  
  /* Faz as Niter iterações */
  for(k = 0; k < Niter; k++){
    /* Verificando se nessa iteração será gerada uma nova gota */
    if((double)rand() / RAND_MAX < P / 100)
      nova_gota((double)(rand() % larg) / larg, (double)(rand() % alt) / alt);

    /* Para cada ponto no lago calcula a altura da água */
    for(i = 0; i < H + 1; i++)
      for(j = 0; j < L + 1; j++)
	calcula_altura(cx(i), cy(j), v, t(k), eps, &h[i][j]);
  }
  return 0;
}
