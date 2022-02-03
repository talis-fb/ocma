#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaces.h"
#include "methods.h"

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
