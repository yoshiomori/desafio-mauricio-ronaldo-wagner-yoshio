#include <stdio.h> /* printf */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include <math.h> /* sqrt, exp */

/* Existe um número máximo de gotas que podem
 * ser geradas */
#define NMAXGOTAS 1000

/* Cada gota tem sua componete x e y */
static double Gx[NMAXGOTAS];
static double Gy[NMAXGOTAS];

/* Número de gotas geradas */
static int N = 0;

/* Gera uma nova gota */
void
nova_gota(double x, double y){
  if (N < NMAXGOTAS){
    Gx[N] = x;
    Gy[N++] = y;
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
void
calcula_altura(double px, double py, int v, double t, double eps, double *h){
  int n;
  double vt = v * t, aux, d;
  for(n = 0; n < N; n++){
    d = dist(px, py, Gx[n], Gy[n]) - vt;
    aux = d * exp(d * d - t / 10);
    *h += aux > eps ? aux : 0;
  }
}
