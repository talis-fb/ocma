#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaces.h"
#include "methods.h"
#include "read.h"

void readDataGrid(int h, int w, int grid[h][w]) {
  for (int x = 0; x < h; x++) {
    for (int y = 0; y < w; y++) {
      scanf("%i", &grid[x][y] );
    }
  }
}

Barco *readDataBots(int n) {
  Barco *bots = malloc(sizeof(Posicao) * n);
  for (int i = 0; i < n; i++) {
    scanf("%s %i %i", &bots[i].id, &bots[i].posicao.y, &bots[i].posicao.x );
  }

  return bots;
}
