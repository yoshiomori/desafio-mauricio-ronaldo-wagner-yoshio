#include <stdio.h> /* printf */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include <math.h> /* sqrt, exp */

/* Existe um número máximo de gotas que podem
 * ser geradas */
#define NMAXGOTAS 1000
/* Variáveis armazenam dados do arquivo */
int larg, alt, L, H, v;
float eps;

/* Cada gota tem sua componete x e y */
static float Gx[NMAXGOTAS];
static float Gy[NMAXGOTAS];
static float Gt[NMAXGOTAS]; /* Instante em que a gota caiu */

/* Número de gotas geradas */
static int N = 0;

/* Gera uma nova gota */
void
nova_gota(float x, float y, float t){
  if (N < NMAXGOTAS){
    Gx[N] = x;
    Gy[N] = y;
    Gt[N++] = t;
  }
  else{
    printf("Excedeu o número máximo de gotas\n");
    exit(EXIT_FAILURE);
  }
}

/* Calcula a distância entre dois pontos */
/* Na documentação, é representado com a letra grega ro */
static float
dist(float px, float py, float gx, float gy){
  return sqrt((double)((px - gx) * (px - gx) + (py - gy) * (py - gy)));
}

/* Calcula a altura gerada por cada gota em um ponto do lago especificado */
float
calcula_altura(float px, float py, float t){
  int n;
  float h = 0, aux, d;
  for(n = 0; n < N; n++){
    d = dist(px, py, Gx[n], Gy[n]) - v * (t - Gt[n]);
    aux = d * exp(-d * d - (t - Gt[n]) / 10);
    h += aux > eps || aux < -eps ? aux : 0;
  }
  return h;
}

/* Faz o calculo da coordenada do ponto (i, j) no eixo das abcissas*/
float
cx(int j){
  return j * (float)larg / (L - 1);
}

/* Faz o calculo da coordenada do ponto (i, j) no eixo das ordenadas */
float
cy(int i){
  return i * (float)alt / (H - 1);
}
