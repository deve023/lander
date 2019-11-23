#ifndef _ESTRELLAS_H_
#define _ESTRELLAS_H_

#include <SDL2/SDL.h>

#include "lista.h"
#include "vectores.h"
#include "matematica.h"

#define ESTRELLAS_CANT 50

bool cielo_crear(SDL_Renderer *r);
void cielo_destruir();

// Grafica el cielo sobre el terreno.
bool cielo_graficar(float **terreno, size_t n);

#endif
