#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaces.h"
#include "read.h"

void readDataGrid(int h, int w, int grid[h][w]) {
  // Ler o grid
  for (int x = 0; x < h; x++) {
    for (int y = 0; y < w; y++) {
      scanf("%i", &grid[x][y] );
    }
  }

}

void readDataBots(int n, Barco bots[n]) {
  //Barco *bots = malloc(sizeof(Posicao) * n);
  for (int i = 0; i < n; i++) {
    scanf("%s %i %i", bots[i].id, &bots[i].posicao.x, &bots[i].posicao.y );
  }

  //return bots;
}
