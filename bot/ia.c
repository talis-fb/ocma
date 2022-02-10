#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaces.h"
#include "methods.h"
#include "ia.h"

Relevancia analise_relevancia_ponto(int estoque, int tipo){
  if(estoque == 0) {
    if(tipo == 1) return nenhum;
    if(12 <= tipo && tipo <= 19) return medio;
    if(22 <= tipo && tipo <= 29) return alto;
    if(32 <= tipo) return perfeito;
  }

  if(estoque < 7 ){
    if(tipo == 1) return baixo;
    if(12 <= tipo && tipo <= 19) return medio;
    if(22 <= tipo && tipo <= 29) return alto;
    if(32 <= tipo) return perfeito;
  }

  if(estoque < 10 ){
    if(tipo == 1) return alto;
    if(12 <= tipo && tipo <= 19) return medio;
    if(22 <= tipo && tipo <= 29) return medio;
    if(32 <= tipo) return perfeito;
  }

  if(estoque == 10 ){
    if(tipo == 1) return perfeito;
  }

  if(estoque > 10 ){
    fprintf(stderr, "TU SE LASCOUUU! \n");
  }

  return nenhum;
}


Posicao loop_decisao(int estoque, Posicao opcoes[], int i, int max){
  int tipo = opcoes[i].tipo;
  int distancia = module(opcoes[i].x) + module(opcoes[i].y);

  Relevancia relevancia_ponto = analise_relevancia_ponto(estoque, tipo);

  if(i>=max){
    fprintf(stderr, "Deu ruim...:/ \n");
    return opcoes[i];
  }

  if( distancia == 0 ){
    if( relevancia_ponto > 2 )
      return opcoes[i];
  }

  if( distancia < 3 ){
    if( relevancia_ponto > 3 )
      return opcoes[i];
  }

  if( relevancia_ponto == perfeito ){
    return opcoes[i];
  }

  //fprintf(stderr, "Lugar (%d,%d) T%d Est%d  Rel%d \n", opcoes[i].x, opcoes[i].y, tipo, estoque, relevancia_ponto);

  return loop_decisao(estoque, opcoes, (i+1), max );
}

Posicao decidir(Barco barco, int n, Posicao opcoes[n]){
  //fprintf(stderr, "INICIADA DECISAO... \n");

  //int tolerancia_distancia = 14; // Até que distancia ele decide ir atras do maior
  int estoque = barco.estoque;

  return loop_decisao(estoque, opcoes, 0, n);
}
