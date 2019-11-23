#ifndef _DICCIONARIO_H_
#define _DICCIONARIO_H_

#include <stdio.h>

#define CANT_CARACTERES 41

typedef enum {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, CERO, UNO, DOS,
	TRES, CUATRO, CINCO, SEIS, SIETE, OCHO, NUEVE, ARRIBA, ABAJO, DERECHA, IZQUIERDA, ESPACIO} car_t;

extern const char caracteres[CANT_CARACTERES];

extern const int (*(matrices[]))[2];

extern const size_t cant_puntos_en_caracter[CANT_CARACTERES];

typedef const int (*matriz_car_t)[2];

/*
Devuelve el elemento de matrices correspondiente a letra y en la direccion de memoria de n guarda la cantidad su tamano.
*/
matriz_car_t char_a_matriz(char letra, size_t *n);

#endif //_DICCIONARIO_H_
