#ifndef _IMPRIMIR_H_
#define _IMPRIMIR_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "diccionario.h"
#include "caracteres.h"
#include "vectores.h"

#define CANT_DIGITOS 4

void imprimir_entero(int n, int f, double x, double y, SDL_Renderer *renderer);
void imprimir_entero_con_ceros(int n, int f, double x, double y, SDL_Renderer *renderer);

void imprimir_matriz(float **v, size_t n, SDL_Renderer *renderer);
void imprimir_caracter(matriz_car_t m, size_t n, int f, double x, double y, SDL_Renderer *renderer);

//Imprime la cadena cad, escalada por f en la posicion (x,y).
void imprimir_cadena(char cad[], int f, double x, double y, SDL_Renderer *renderer);

#endif
