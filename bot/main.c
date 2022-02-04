#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaces.h"
#include "methods.h"
#include "read.h"
#include "grid.h"
#include "print.h"

int main() {
  // GLOBAIS ----------------------
  int HEIGHT, WIDTH;
  char MY_ID[MAX_STR];
  int dinheiro = 0;
  int estoque_peixes = 0;
  StatusEstoque estoque_status = Vazio;
  Barco meu_barco;
  // --------------------------------


  /* Degubar  */
  setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // === INÍCIO DA PARTIDA ===
  scanf("AREA %i %i", &HEIGHT, &WIDTH);  // lê a dimensão da área de pesca: altura (h) x largura (w)
  scanf(" ID %s", MY_ID);        // ...e o id do bot. Obs: o " " antes de ID é necessário para ler o '\n' da linha anterior


  // Print Meu id
  fprintf(stderr, "Meu id = %s\n", MY_ID);

  while (1) {

    // ----------------------
    // Leitura dos dados
    // ----------------------

    // GRID
    int grid[HEIGHT][WIDTH];
    readDataGrid(HEIGHT, WIDTH, grid);

    // Imprimir grid
    //printGrid(HEIGHT, WIDTH, grid);


    // BOTS
    int num_bots;
    scanf(" BOTS %i", &num_bots);

    Barco bots[num_bots];
    readDataBots(num_bots, bots);

    // Percorrer os bots até achar o com seu ID
    for (int i = 0; i < num_bots; i++) {
      if( strcmp( bots[i].id, MY_ID ) == 0 ){
        strcpy( meu_barco.id, bots[i].id );
        meu_barco.posicao.x = bots[i].posicao.x;
        meu_barco.posicao.y = bots[i].posicao.y;
        break;
      }
    }

    // Imprime os bots
    printBots(num_bots, bots);

    // Imprime o seu bot
    fprintf(stderr, "*NOSSO BOT => ID: %s // X: %d, Y: %d\n\n", meu_barco.id, meu_barco.posicao.x, meu_barco.posicao.y);



    // --------------------------------------
    // Filtro e seleção dos dados relevante
    // --------------------------------------

    // Pega TODOS os campos com alguma propridade (posicoes que nao são só agua)
    int numero_lugares;
    Posicao *temp;
    temp = achar_lugares(HEIGHT, WIDTH, grid, &numero_lugares);

    Posicao pontos_importantes[ numero_lugares ];
    PointerToArray_Posicao(temp, pontos_importantes, numero_lugares);

    fprintf(stderr, "numero lugares legais: %d \n\n", numero_lugares);

    // Imprime eles
    //printPosicoes(numero_lugares, pontos_importantes);



    // -------------------------------------------
    // Analise e seleção dos pontos MAIS PROXIMOS
    // -------------------------------------------

    // Ajuste todas as coordenadas dos lugares referente ao eixo do seu barco
    ajustar_coordenadas(meu_barco.posicao, pontos_importantes, numero_lugares);

    fprintf(stderr, "Lugare AJEITADOS: (CENTRO: X%d Y%d) \n", meu_barco.posicao.x, meu_barco.posicao.y);

    //printPosicoes(numero_lugares, pontos_importantes);

    Posicao *tempL = malloc(sizeof(Posicao));
    for (int i = 1; i < numero_lugares; i++){
      for (int j = 0; j < numero_lugares - i; j++) {
        int distancia1 = module( pontos_importantes[j].x ) + module( pontos_importantes[j].y);
        int distancia2 = module( pontos_importantes[j+1].x) + module( pontos_importantes[j+1].y);

        if ( distancia1 < distancia2 ) {
          continue;
        }

        if ( distancia1 == distancia2 ){
          if( pontos_importantes[j].tipo > pontos_importantes[j+1].tipo ){
            continue;
          }
        }

        *tempL =pontos_importantes[j];
        pontos_importantes[j] =pontos_importantes[j + 1];
        pontos_importantes[j + 1] = *tempL;
      }
    }
    free(tempL);


    Posicao lugares_proximos[9];
    for (int i = 0; i < 9; i++){
      lugares_proximos[i] = pontos_importantes[i];
    }

    printPosicoes(9, lugares_proximos);



    // ALGORITMO PARA FILTRAR POR PREFERENCIA, ANALISANDO O ESTOQUE ATUAL DO CABA...

    // Seta pra onde ir...

    /* if(lugares_proximos[0].x > 0){ */
    /*   printf("UP\n"); */
    /* } */
    /* if (lugares_proximos[0].y > 0){ */
    /*   printf("LEFT\n"); */
    /* } */
    /* if(lugares_proximos[0].x < 0){ */
    /*   printf("DOWN\n"); */
    /* } */
    /* if(lugares_proximos[0].y < 0){ */
    /*   printf("RIGHT\n"); */
    /* } */

    char resposta[MAX_STR];
    printf("DOWN\n");
    scanf("%s", resposta);
    fgets(resposta, MAX_STR, stdin);
  }

  return 0;
}
