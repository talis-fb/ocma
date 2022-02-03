
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaces.h"
#include "methods.h"
#include "grid.h"


void ajustar_coordenadas(Posicao CENTRO, Posicao coordenadas[], int length){
  for (int i = 0; i < length; i++) {
    coordenadas[i].x = CENTRO.x - coordenadas[i].x;
    coordenadas[i].y = CENTRO.y - coordenadas[i].y;
  }
}

Posicao *achar_lugares(int h, int w, int grid[h][w], int *numero_lugares){
  Posicao *lugares = malloc(sizeof(Posicao));

  int n = 0;
  for (int x = 0; x < h; x++) {
    for (int y = 0; y < w; y++) {
      if( grid[x][y] == 1 || (  grid[x][y] > 10 && grid[x][y] < 40 ) ) {
        n++;
        lugares = realloc(lugares, sizeof(Posicao) * (n) );

        lugares[n-1].x = x;
        lugares[n-1].y = y;
        lugares[n-1].tipo = grid[x][y];
      }
    }
  }

  *numero_lugares = n;
  return lugares;
}
