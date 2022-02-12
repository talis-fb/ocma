#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaces.h"
#include "methods.h"

Posicao *remove_elements_from_array_Posicao(Posicao elementos[], int len_el, Posicao vetor[], int len_vetor, int *novo_tamanho){
   // Agora ele remove TODOS os campo que possuem a mesma coordenada de um bot
  Posicao *novo_vetor = NULL; //calloc(1, sizeof(Posicao));
  int novo_vetor_len = 0;

  for(int i = 0; i < len_vetor; i++){
    Posicao el_vetor = vetor[i];
    int eh_um_elemento_do_array = 0;

    for(int j = 0; j < len_el; j++){
      Posicao el = elementos[j];
      if(el.x == el_vetor.x && el.y == el_vetor.y){
        eh_um_elemento_do_array = 1;
        break;
      }
    }

    if(eh_um_elemento_do_array)
      continue;

    novo_vetor = realloc(novo_vetor, sizeof(Posicao) * (novo_vetor_len+1) );
    novo_vetor[novo_vetor_len] = el_vetor;
    novo_vetor_len++;
  }

  *novo_tamanho = novo_vetor_len;
  return novo_vetor;

}


int IsIntoArray(int el, int vetor[], int n){
  int is_in = 0;
  for(int i = 0; i < n;i++){
    if(el == vetor[i])
      is_in = 1;
  }
  return is_in;
}

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

void PointerToArray_Int(int *pointer, int vetor[], int n){
  for( int i=0; i < n; i++)
    vetor[i] = pointer[i];

  free(pointer);
}

int module(int n){
  if(n<0)
    return n * (-1);
  else
    return n;
}
