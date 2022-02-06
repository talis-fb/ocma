#ifndef IA
#define IA

typedef enum IRelevancia  {
  nenhum,
  baixo,
  medio,
  alto,
  perfeito
} Relevancia;

Relevancia analise_relevancia_ponto(int estoque, int tipo);
Posicao loop_decisao(int estoque, Posicao opcoes[], int i, int max);
Posicao decidir(Barco barco, int n, Posicao opcoes[n]);

#endif
