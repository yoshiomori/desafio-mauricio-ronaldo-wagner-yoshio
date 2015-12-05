#include <stdio.h>
#include "../lib/ondas_lib.h"

extern float v, eps;

int main(){
  float h;
  v = 10;
  eps = 0.001;
  nova_gota(0, 0, 0);
  h = calcula_altura(2, 0, 0);
  printf("%lf\n", h);
  return 0;
}
