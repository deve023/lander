#ifndef _MATEMATICA_H_
#define _MATEMATICA_H_

#include <stdlib.h>

/*
Recibe un vector de coordenadas, calcula el valor de la coordenada
y en la posicion x sobre las rectas generadas por v.
*/
float coord_y_en_recta(float **v, size_t n, float x);

/*
Recibe dos numeros min y max.
Devuelve un numero aleatorio perteneciente al intervalo [min,max].
*/
float randomf(float min, float max);

#endif // _MATEMATICA_H_
