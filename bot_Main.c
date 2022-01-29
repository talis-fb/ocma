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

Barco barco;


void readDataGrid(int h, int w, int grid[h][w]) {
    // lê os dados da área de pesca
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            scanf("%i", ((*grid + i)+j) );
        }
    }
}

Posicao *readDataBots(int n, Barco barco) {
    char id[MAX_STR];

    Posicao *bots = malloc(sizeof(Posicao) * n);

    for (int i = 0; i < n; i++) {
        scanf("%s %i %i", id, &bots[n].x, &bots[n].y);

        if( strcmp(id, barco.id) == 0 ){
            barco.posicao.x = bots[n].x;
            barco.posicao.y = bots[n].y;
        }
    }

    return bots;
}

Posicao *achar_lugares(int h, int w, int grid[h][w], int *numero_lugares){
    Posicao *lugares = malloc(sizeof(Posicao) );

    int n = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {

            if(grid[i][j] > 0) {
                n++;
                lugares = realloc(lugares, sizeof(Posicao) * (n+1) );

                lugares[n].x = i;
                lugares[n].y = j;
                lugares[n].tipo = grid[i][j];
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
    barco.id[0] = 'b';
    barco.id[2] = 'o';
    barco.id[3] = 't';
    barco.id[4] = '_';
    barco.id[4] = 'C';
    barco.id[5] = '\n';

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
        readDataGrid(HEIGHT, WIDTH, grid);

        // LER BOTS
        int num_bots;
        Posicao *bots;
        scanf(" BOTS %i", &num_bots);
        bots = readDataBots(num_bots, barco);

        // Pega quantos campos possuem propriedade...
        int numero_lugares;
        Posicao *lugares;
        lugares = achar_lugares(HEIGHT, WIDTH, grid, &numero_lugares);

        // Ajuste todas as coordenadas dos lugares referente ao eixo do seu barco
        ajustar_coordenadas(barco.posicao, lugares, numero_lugares);


        Posicao *temp = malloc(sizeof(Posicao));
        for (int i = 1; i < numero_lugares; i++){
            for (int j = 0; j < numero_lugares - i; j++) {
                int distancia1 = lugares[j].x - lugares[j].y;
                int distancia2 = lugares[j+1].x - lugares[j+1].y;
                if ( distancia2 > distancia1 ) {
                    continue;
                }
                *temp = lugares[j];
                lugares[j] = lugares[j + 1];
                lugares[j + 1] = *temp;
            }
        }
        free(temp);

        Posicao lugares_proximos[5];
        for (int i = 0; i < 5; i++){
            lugares_proximos[i] = lugares[i];
        }

        free(lugares);

        // ALGORITMO PARA FILTRAR POR PREFERENCIA, ANALISANDO O ESTOQUE ATUAL DO CABA...

        // Seta pra onde ir...

        if(lugares_proximos[0].x > 0){
            printf("UP\n");
        }
        if (lugares_proximos[0].y > 0){
            printf("LEFT\n");
        }
        if(lugares_proximos[0].x < 0){
            printf("DOWN\n");
        }
        if(lugares_proximos[0].y < 0){
            printf("RIGHT\n");
        }

        // Leitura de resposta ao envio do comando
        scanf("%s", resposta);
        fgets(resposta, MAX_LINE, stdin);
    }

    //
    return 0;
}
