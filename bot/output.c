#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaces.h"
#include "output.h"

void pescar(Barco *barco){
  fprintf(stderr, "Pescando...");
  printf("FISH\n");
  barco->estoque++;
}

void vender_porto(Barco *barco){
  fprintf(stderr, "Vendendo...");
  printf("SELL\n");
  barco->estoque = 0;
}

void mover(Barco *barco, Posicao aonde, Barco bots[], int num_bots){
  if(aonde.x > 0){
    fprintf(stderr, "Up...");
    printf("UP\n");
    return;
  }
  if (aonde.y > 0){
    fprintf(stderr, "LEft...");
    printf("LEFT\n");
    return;
  }
  if(aonde.x < 0){
    fprintf(stderr, "Down...");
    printf("DOWN\n");
    return;
  }
  if(aonde.y < 0){
    fprintf(stderr, "Right...");
    printf("RIGHT\n");
    return;
  }
}
