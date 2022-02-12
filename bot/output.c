#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaces.h"
#include "methods.h"
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

void mover(Barco *barco, Posicao aonde, Lados bots_ao_lado, int HEIGHT, int WIDTH){
  if(aonde.x > 0){
    if(bots_ao_lado.up){
      if(aonde.y > 0){
        fprintf(stderr, "LEft mas com alguem no meio...");
        printf("LEFT\n");
        return;
      }
      fprintf(stderr, "RIGHT mas com alguem no meio...");
      printf("RIGHT\n");
      return;
    }

    fprintf(stderr, "Up...");
    printf("UP\n");
    return;
  }

  if (aonde.y > 0){
    if(bots_ao_lado.left){
      if(aonde.x > 0){
        fprintf(stderr, "UP mas com alguem no meio...");
        printf("UP\n");
        return;
      }
      fprintf(stderr, "DOWN mas com alguem no meio...");
      printf("DOWN\n");
      return;
    }

    fprintf(stderr, "LEft...");
    printf("LEFT\n");
    return;
  }

  if(aonde.x < 0){
    if(bots_ao_lado.down){
      if(aonde.y > 0){
        fprintf(stderr, "LEFT mas com alguem no meio...");
        printf("LEFT\n");
        return;
      }
      fprintf(stderr, "RIGHT mas com alguem no meio...");
      printf("RIGHT\n");
      return;
    }

    fprintf(stderr, "Down...");
    printf("DOWN\n");
    return;
  }

  if(aonde.y < 0){
    if(bots_ao_lado.right){
      if(aonde.x > 0){
        fprintf(stderr, "UP mas com alguem no meio...");
        printf("UP\n");
        return;
      }
      fprintf(stderr, "DOWN mas com alguem no meio...");
      printf("DOWN\n");
      return;
    }

    fprintf(stderr, "Right...");
    printf("RIGHT\n");
    return;
  }

}
