#ifndef _NAVE_H_
#define _NAVE_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "config.h"
#include "fisica.h"
#include "vectores.h"
#include "imprimir.h"

#define NAVE_GRANDE_TOBERA_X 5
#define NAVE_GRANDE_TOBERA_Y -12

#define NAVE_CHICA_TOBERA_X 4
#define NAVE_CHICA_TOBERA_Y 9.5

typedef struct nave nave_t;

nave_t *nave_crear();
void nave_destruir(void *n);

bool nave_actualizar(nave_t *n, float dt, SDL_Renderer *renderer);

float nave_get_x(const nave_t *n);
float nave_get_y(const nave_t *n);
float nave_get_vx(const nave_t *n);
float nave_get_vy(const nave_t *n);
double nave_get_angulo(const nave_t *n);
double nave_get_pot(const nave_t *n);

void nave_rotar(nave_t *n, double angulo);
void nave_incrementar_potencia(nave_t *n, double pot);
void nave_mover(nave_t *n, float dt);

bool nave_dibujar(const nave_t *n, SDL_Renderer *renderer);

#endif // _NAVE_H_
