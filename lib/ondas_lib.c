#include <stdio.h> /* printf */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include <math.h> /* sqrt, exp */
#include <omp.h>

/* Existe um número máximo de gotas que podem
 * ser geradas */
#define NMAXGOTAS 1000
#define NUM_THREADS 32
/* Variáveis armazenam dados do arquivo */
int larg, alt, L, H, v;
double eps;

/* Cada gota tem sua componete x e y */
static double Gx[NMAXGOTAS];
static double Gy[NMAXGOTAS];
static double Gt[NMAXGOTAS]; /* Instante em que a gota caiu */

/* Número de gotas geradas */
static int N = 0;

/* Gera uma nova gota */
void
nova_gota(double x, double y, double t){
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
static double
dist(double px, double py, double gx, double gy){
  return sqrt((px - gx) * (px - gx) + (py - gy) * (py - gy));
}

/* Calcula a altura gerada por cada gota em um ponto do lago especificado */
double
calcula_altura(double px, double py, double t){
  int n;
  double h = 0, aux, d;
  #pragma omp parallel for private (d,aux) reduction (+:h)
  for(n = 0; n < N; n++){
    d = dist(px, py, Gx[n], Gy[n]) - v * (t - Gt[n]);
    aux = d * exp(-d * d - (t - Gt[n]) / 10);
    h += aux > eps || aux < -eps ? aux : 0;
  }
  return h;
}

/* Faz o calculo da coordenada do ponto (i, j) no eixo das abcissas*/
double
cx(int j){
  return j * (double)larg / (L - 1);
}

/* Faz o calculo da coordenada do ponto (i, j) no eixo das ordenadas */
double
cy(int i){
  return i * (double)alt / (H - 1);
}
