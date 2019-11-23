#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include <SDL2/SDL.h>

#include "terreno.h"
#include "cielo.h"

bool background_crear(terreno_t **t, SDL_Renderer *renderer);
void background_destruir(void *terreno);

void background_graficar(const terreno_t *terreno, SDL_Renderer *renderer);

#endif
