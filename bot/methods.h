#ifndef METHODS
#define METHODS

Posicao *remove_elements_from_array_Posicao(Posicao elementos[], int len_el, Posicao vetor[], int len_vetor, int *novo_tamanho);
int IsIntoArray(int el, int vetor[], int n);
void PointerToArray_Posicao(Posicao *pointer, Posicao vetor[], int n);
void PointerToArray_Barco(Barco *pointer, Barco vetor[], int n);
void PointerToArray_Int(int *pointer, int vetor[], int n);
int module(int n);

#endif
