#ifndef _TERRENO_H_
#define _TERRENO_H_

#include <stdlib.h>
#include <SDL2/SDL.h>

#include "config.h"
#include "vectores.h"
#include "imprimir.h"

typedef struct terreno terreno_t;

terreno_t *terreno_crear();
void terreno_destruir(void *t);
void terreno_graficar(const terreno_t *t, SDL_Renderer *renderer);

float **terreno_get_coords(const terreno_t *t);
size_t terreno_get_tam(const terreno_t *t);

#endif
