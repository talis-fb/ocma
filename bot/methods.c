#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaces.h"
#include "methods.h"

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
