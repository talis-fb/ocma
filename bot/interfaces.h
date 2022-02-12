#ifndef INTERFACES
#define INTERFACES

#define MAX_STR 50

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
  /* char id[MAX_STR]; */
  char *id;
  Posicao posicao;
  int estoque;
  StatusEstoque status_estoque;
} Barco;

typedef struct ILados {
  int up;
  int left;
  int right;
  int down;
} Lados;

#endif
