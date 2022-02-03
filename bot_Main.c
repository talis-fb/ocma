#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 50
#define MAX_LINE 50

// Definições
typedef struct IPosicao {
  int x, y;
  int tipo;
} Posicao;

typedef enum IStatusEstoque  {
  Vazio = 0,
  Razoavel = 5,
  Cheio = 10
} StatusEstoque;

typedef struct IBarco {
  char id[MAX_STR];
  Posicao posicao;
  int estoque;
  StatusEstoque status_estoque;
} Barco;

void PointerToArray_Posicao(Posicao *pointer, Posicao vetor[], int n){
  for( int i=0; i < n; i++)
    vetor[i] = pointer[i];

  free(pointer);
}

void PointerToArray_Barco(Barco *pointer, Barco vetor[], int n){
  for( int i=0; i < n; i++)
    vetor[i] = pointer[i];

  free(pointer);
}


void readDataGrid(int h, int w, int *grid) {
  // lê os dados da área de pesca
  fprintf(stderr, "GRID: \n");
  for (int x = 0; x < h; x++) {
    for (int y = 0; y < w; y++) {
      scanf("%i", ((grid + y)+x) );
      fprintf(stderr, "%d ", *((grid + y)+x) );
    }
    fprintf(stderr, "\n");
  }
}

Barco *readDataBots(int n) {
  Barco *bots = malloc(sizeof(Posicao) * n);
  for (int i = 0; i < n; i++) {
    scanf("%s %i %i", &bots[i].id, &bots[i].posicao.y, &bots[i].posicao.x );
  }

  return bots;
}

Posicao *achar_lugares(int h, int w, int grid[h][w], int *numero_lugares){
  Posicao *lugares = malloc(sizeof(Posicao));

  int n = 0;
  for (int x = 0; x < h; x++) {
    for (int y = 0; y < w; y++) {

      //if( grid[x][y]> 0 && grid[x][y] < 50 ) {
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

void ajustar_coordenadas(Posicao CENTRO, Posicao *coordenadas, int length){
  for (int i = 0; i < length; i++) {
    coordenadas[i].x = CENTRO.x - coordenadas[i].x;
    coordenadas[i].y = CENTRO.y - coordenadas[i].y;
  }
}

int main() {

  // globais ----------------------
  int HEIGHT, WIDTH;
  int grid[HEIGHT][WIDTH];
  char MY_ID[MAX_STR];
  int dinheiro = 0;
  int estoque_peixes = 0;
  StatusEstoque estoque_status = Vazio;
  char resposta[MAX_STR];   // dados temporários

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
    readDataGrid(HEIGHT, WIDTH, &grid[0][0]);

    fprintf(stderr, "GRID (dnv):: \n");
    for (int x = 0; x < HEIGHT; x++) {
      for (int y = 0; y < WIDTH; y++) {
        fprintf(stderr, "%d ", grid[x][y] );
      }
      fprintf(stderr, "\n");
    }

    // LER BOTS
    int num_bots;
    scanf(" BOTS %i", &num_bots);

    Barco bots[num_bots], *temp_bots;
    temp_bots = readDataBots(num_bots);
    PointerToArray_Barco(temp_bots, bots, num_bots);

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
    fgets(resposta, MAX_LINE, stdin);

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
    fgets(resposta, MAX_LINE, stdin);


  }

  return 0;
}
