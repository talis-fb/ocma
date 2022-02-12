#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaces.h"
#include "methods.h"
#include "read.h"
#include "grid.h"
#include "print.h"
#include "output.h"
#include "ia.h"
#include <time.h>

void delay(int number_of_seconds){
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < (start_time + milli_seconds) ){
      //
    }
}

int main() {
  // GLOBAIS ----------------------
  int HEIGHT, WIDTH;
  char MY_ID[MAX_STR];
  int dinheiro = 0;
  int estoque_peixes = 0;
  StatusEstoque estoque_status = Vazio;
  Barco meu_barco;
  meu_barco.estoque = 0;
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

    Barco bots_temp[num_bots];
    readDataBots(num_bots, bots_temp);

    // Percorrer os bots até achar o com seu ID
    //  Quando ele acha, ele registra mas não escreve, como faltará sempre um
    //  logo
    num_bots--;
    Barco bots[num_bots];
    for (int i = 0; i < (num_bots+1); i++) {
      if( strcmp( bots_temp[i].id, MY_ID ) == 0 ){
        strcpy( meu_barco.id, bots_temp[i].id );
        meu_barco.posicao.x = bots_temp[i].posicao.x;
        meu_barco.posicao.y = bots_temp[i].posicao.y;
        continue;
      }
      bots[i].posicao.x = bots_temp[i].posicao.x;
      bots[i].posicao.y = bots_temp[i].posicao.y;
      strcpy( bots[i].id, bots_temp[i].id );
      //bots[i].id = bots_temp[i].id;
     // bots[i] = bots_temp[i];
    }

    //for (int i = 0; i < num_bots; i++) {

    Posicao posicoes_bots[num_bots];
    for (int i = 0; i < num_bots; i++) {
      posicoes_bots[i].x = bots[i].posicao.x;
      posicoes_bots[i].y = bots[i].posicao.y;
    }

    Lados bots_ao_lado;
    bots_ao_lado.up = 0;
    bots_ao_lado.down = 0;
    bots_ao_lado.left = 0;
    bots_ao_lado.right = 0;

    for (int i = 0; i < num_bots; i++) {
      if( posicoes_bots[i].x == meu_barco.posicao.x)
        if( posicoes_bots[i].y == (meu_barco.posicao.y - 1))
          bots_ao_lado.right = 1;
      if( posicoes_bots[i].x == meu_barco.posicao.x)
        if( posicoes_bots[i].y == (meu_barco.posicao.y + 1))
          bots_ao_lado.left = 1;
      if( posicoes_bots[i].x == (meu_barco.posicao.x + 1))
        if( posicoes_bots[i].y == meu_barco.posicao.y)
          bots_ao_lado.up = 1;
      if( posicoes_bots[i].x == (meu_barco.posicao.x - 1))
        if( posicoes_bots[i].y == meu_barco.posicao.y)
          bots_ao_lado.down = 1;
    }



    // Imprime os bots
    printBots(num_bots, bots);

    // Imprime o seu bot
    fprintf(stderr, "*NOSSO BOT => ID: %s // X: %d, Y: %d\n\n", meu_barco.id, meu_barco.posicao.x, meu_barco.posicao.y);



    // --------------------------------------
    // Filtro e seleção dos dados relevante
    // --------------------------------------

    int numero_todos_lugares;
    Posicao *todos_pontos_importantes_temp;

    // Pega TODOS os campos com alguma propridade (posicoes que nao são só agua)
    todos_pontos_importantes_temp = achar_lugares(HEIGHT, WIDTH, grid, &numero_todos_lugares);

    // Transforma o pointer para um array (a função já faz o free do pointer)
    Posicao todos_pontos_importantes[ numero_todos_lugares ];
    PointerToArray_Posicao(todos_pontos_importantes_temp, todos_pontos_importantes, numero_todos_lugares);

    // Agora ele filtra, e retorna TODOS os pontos em que um bot não está encima
    Posicao *pontos_importantes_temp = NULL; //malloc(sizeof(Posicao));
    int numero_lugares = 0;

    pontos_importantes_temp = remove_elements_from_array_Posicao( posicoes_bots, num_bots, todos_pontos_importantes, numero_todos_lugares, &numero_lugares );

    Posicao pontos_importantes[ numero_lugares ];
    PointerToArray_Posicao(pontos_importantes_temp, pontos_importantes, numero_lugares);


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

    // Aqui ele ordena todos os pontos, por meio da "distancia", sendo ela a soma do eixo com o Y
    //  Além disso ele considera pontos
    Posicao *tempL = malloc(sizeof(Posicao));
    for (int i = 1; i < numero_lugares; i++){
      for (int j = 0; j < numero_lugares - i; j++) {
        int distancia1 = module( pontos_importantes[j].x ) + module( pontos_importantes[j].y);
        int distancia2 = module( pontos_importantes[j+1].x) + module( pontos_importantes[j+1].y);

        // Verifica as distancia e as ordena SE nenhum dos pontos for bot
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

    printPosicoes(15, pontos_importantes);


    // DECISAO PARA ONDE IR
    Posicao lugar_para_ir = decidir(meu_barco, numero_lugares, pontos_importantes);
    int tipo_lugar = lugar_para_ir.tipo;

    if(lugar_para_ir.x == 0 && lugar_para_ir.y == 0){
      if(tipo_lugar == 1 ){
        vender_porto(&meu_barco);
      } else {
        pescar(&meu_barco);
      }
    } else {
        mover(&meu_barco, lugar_para_ir, bots_ao_lado, HEIGHT, WIDTH);
    }


    char resposta[MAX_STR];
    scanf("%s", resposta);
    fgets(resposta, MAX_STR, stdin);
    delay(100);
  }

  return 0;
}
