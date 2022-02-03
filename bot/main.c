#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaces.h"
#include "methods.h"
#include "read.h"
#include "grid.h"

int **criar_matrix(int height, int width){
  int **matrix = malloc(sizeof(int*) * width);

  for(int i=0; i < width; i++)
    matrix[i] = malloc(sizeof(int) * height);

  return matrix;
}

int main() {

  // globais ----------------------
  int HEIGHT, WIDTH;
  int grid[HEIGHT][WIDTH];
  char MY_ID[MAX_STR];
  int dinheiro = 0;
  int estoque_peixes = 0;
  StatusEstoque estoque_status = Vazio;
  Barco barco;
  // --------------------------------


  /* Degubar  */
  setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // === INÍCIO DA PARTIDA ===
  scanf("AREA %i %i", &HEIGHT, &WIDTH);  // lê a dimensão da área de pesca: altura (h) x largura (w)
  scanf(" ID %s", MY_ID);        // ...e o id do bot
  // obs: o " " antes de ID é necessário para ler o '\n' da linha anterior


  // Print Meu id
  fprintf(stderr, "Meu id = %s\n", MY_ID);
  // -------------

  while (1) {

    // LER GRID
    // int **tempMatrix;
    // tempMatrix = criar_matrix(HEIGHT, WIDTH);

    readDataGrid(HEIGHT, WIDTH, grid);

    // for(int i = 0; i < width; i ++)
    //   PointerToArray_Int(temp[i], grid[i], width);


        fprintf(stderr, "\n----------------------------\n");
    for(int i = 0; i < HEIGHT; i ++){
      for (int y = 0; y < WIDTH; y++){
        fprintf(stderr, "%i ", grid[i][y] );
      }
      fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n----------------------------\n");


    // LER BOTS
    int num_bots;
    scanf(" BOTS %i", &num_bots);

    Barco bots[num_bots], *temp_bots;
    temp_bots = readDataBots(num_bots);
    PointerToArray_Barco(temp_bots, bots, num_bots);

    printf("SELL\n");
    scanf("%s", resposta);
    break;


    // Bots => bots[]
    // grid => grid[][]



    for( int i=0; i < num_bots; i++){
      //printf("Bots desse jogo: X: %d Y:%d ", bots[i].x, bots[i].y );
      fprintf(stderr, "Bots desse jogo: ID: %s // X: %d Y:%d \n",
          bots[i].id,
          bots[i].posicao.x,
          bots[i].posicao.y
          );
    }
    fprintf(stderr, "\n");






    // Pega quantos campos possuem propriedade...
    int numero_lugares;
    Posicao *temp;
    temp = achar_lugares(HEIGHT, WIDTH, grid, &numero_lugares);

    Posicao pontos_importantes[ numero_lugares ];
    PointerToArray_Posicao(temp, pontos_importantes, numero_lugares);

    fprintf(stderr, "numero lugares legais: %d \n\n", numero_lugares);

    for( int i=0; i < numero_lugares; i++){
        //printf("Bots desse jogo: X: %d Y:%d ", bots[i].x, bots[i].y );
        fprintf(stderr, "\t%d: %d %d // %d\n",
                i,
                pontos_importantes[i].x,
                pontos_importantes[i].y,
                pontos_importantes[i].tipo
               );
    }
    fprintf(stderr, "\n");



    printf("DOWN\n");
    scanf("%s", resposta);
    fgets(resposta, MAX_STR, stdin);

    continue;

    // Ajuste todas as coordenadas dos lugares referente ao eixo do seu barco
    //ajustar_coordenadas(/*AQUI VAI SUA COORD*/, lugares, numero_lugares);


    /* Posicao *temp = malloc(sizeof(Posicao)); */
    /* for (int i = 1; i < numero_lugares; i++){ */
    /*   for (int j = 0; j < numero_lugares - i; j++) { */
    /*     int distancia1 = lugares[j].x - lugares[j].y; */
    /*     int distancia2 = lugares[j+1].x - lugares[j+1].y; */
    /*     if ( distancia2 > distancia1 ) { */
    /*       continue; */
    /*     } */
    /*     *temp = lugares[j]; */
    /*     lugares[j] = lugares[j + 1]; */
    /*     lugares[j + 1] = *temp; */
    /*   } */
    /* } */
    /* free(temp); */

    /* Posicao lugares_proximos[5]; */
    /* for (int i = 0; i < 5; i++){ */
    /*   lugares_proximos[i] = lugares[i]; */
    /* } */

    /* free(lugares); */

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



    scanf("%s", resposta);
    fgets(resposta, MAX_STR, stdin);


  }

  return 0;
}
