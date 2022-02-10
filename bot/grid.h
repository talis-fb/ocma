#ifndef GRID
#define GRID

void ajustar_coordenada(Posicao CENTRO, Posicao coordenada);
void ajustar_coordenadas(Posicao CENTRO, Posicao *coordenadas, int length);
Posicao *achar_lugares(int h, int w, int grid[h][w], int *numero_lugares);

#endif
