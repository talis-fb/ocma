#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaces.h"
#include "print.h"

void printGrid(int h, int w, int grid[h][w]) {
  fprintf(stderr, "\n----------- GRID ----------\n");
  for(int x = 0; x < h; x ++){
    for (int y = 0; y < w; y++){
      fprintf(stderr, "%i ", grid[x][y] );
    }
    fprintf(stderr, "\n");
  }
  fprintf(stderr, "\n----------------------------\n");
}

void printBots(int n, Barco bots[n]) {
  // Imprime os bots
  for( int i=0; i < n; i++ ){
    fprintf(stderr, "Bots desse jogo: ID: %s // X: %d, Y:%d \n",
        bots[i].id,
        bots[i].posicao.x,
        bots[i].posicao.y
        );
  }
}

void printBarco(Barco barco){
  // Imprime o seu bot
  fprintf(stderr, "*NOSSO BOT => ID: %s // X: %d, Y: %d\n\n", barco.id, barco.posicao.x, barco.posicao.y);

}

void printPosicoes(int n, Posicao posicoes[n]){
  for( int i=0; i < n; i++){
    fprintf(stderr, "\t%d // X:%d Y:%d \n",
      posicoes[i].tipo,
      posicoes[i].x,
      posicoes[i].y
    );
  }
  fprintf(stderr, "\n");
}
