#include <stdio.h> /* printf */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include <math.h> /* sqrt, exp */
#include <xmmintrin.h>

/* Existe um número máximo de gotas que podem
 * ser geradas */
#define NMAXGOTAS 1000

#define arredonda(A) ((A) > eps || (A) < -eps ? (A) : 0)
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
  return sqrtf(((px - gx) * (px - gx) + (py - gy) * (py - gy)));
}

void
unroll_calculo_altura(float px, float py, float *gx, float *gy, float *gt,
			     float t, float *resp){
  float v10 = 10, e[4], vv = v;
  __m128 SSEpxgx = _mm_sub_ps(_mm_load1_ps(&px), _mm_load_ps(gx)),
    SSEpygy = _mm_sub_ps(_mm_load1_ps(&py), _mm_load_ps(gy)),
    SSE10 = _mm_load1_ps(&v10), SSEgt = _mm_load_ps(gt),
    SSEt = _mm_load1_ps(&t),
    /* Calculando distancia entre o ponto e a gota */
    SSEd = _mm_sub_ps(_mm_sqrt_ps(_mm_add_ps(_mm_mul_ps(SSEpxgx, SSEpxgx),
  					     _mm_mul_ps(SSEpygy, SSEpygy))),
  		      _mm_mul_ps(_mm_load1_ps(&vv), _mm_sub_ps(SSEt, SSEgt)));

  /* Calculando o valor dentro da exponencial */
  _mm_store_ps(e,
  	       _mm_sub_ps(_mm_div_ps(_mm_sub_ps(SSEgt, SSEt), SSE10),
			  _mm_mul_ps(SSEd, SSEd)));
  /* Calculando a exponencial de cada elemento */
  e[0] = expf(e[0]);
  e[1] = expf(e[1]);
  e[2] = expf(e[2]);
  e[3] = expf(e[3]);

  /* multiplicando a distancia com resultado da exponenciação */
  _mm_store_ps(resp, _mm_mul_ps(SSEd, _mm_load_ps(e)));
}

/* Calcula a altura gerada por cada gota em um ponto do lago especificado */
float
calcula_altura(float px, float py, float t){
  int n;
  float h = 0, d, vecd[4];

  /* Tratando dos primeiros */
  for(n = 0; n < N % 4; n++){
    d = dist(px, py, Gx[n], Gy[n]) - v * (t - Gt[n]);
    d = d * expf(-d * d - (t - Gt[n]) / 10);
    h += arredonda(d);
  }

  /* Tratando do resto */
  for(n = 4; n < N; n += 4){
    unroll_calculo_altura(px, py, &Gx[n], &Gy[n], &Gt[n], t, vecd);
    h += arredonda(vecd[0]);
    h += arredonda(vecd[1]);
    h += arredonda(vecd[2]);
    h += arredonda(vecd[3]);
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
