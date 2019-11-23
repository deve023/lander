#include "cielo.h"

#include <SDL2/SDL.h>

typedef int (*sprite_t)[2];

typedef struct star {
    sprite_t sprite;
    float x;
    float y;
} star_t;

static SDL_Renderer *renderer;

static int height, width;

static lista_t *cielo;

static int estrella_sprite[5][2] = {
    {-1,0},
    {1,0},
    {0,0},
    {0,1},
    {0,-1}
};

static star_t *estrella_crear(float x, float y) {
    star_t *s = malloc(sizeof(star_t));
    if(s == NULL)
        return NULL;

    s->sprite = estrella_sprite;
    s->x = x;
    s->y = y;

    return s;
}

static void estrella_destruir(void *s) {
    free(s);
}

static void estrella_imprimir(star_t *s) {
    for(int i = 0; i < 5 - 1; i++)
			SDL_RenderDrawLine(
				renderer,
				s->sprite[i][0] + s->x,
				-s->sprite[i][1] + s->y,
				s->sprite[i+1][0] + s->x,
				-s->sprite[i+1][1] + s->y
			);
}

bool cielo_crear(SDL_Renderer *r) {
    cielo = lista_crear();
    if(cielo == NULL)
        return false;

    renderer = r;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    for(size_t i = 0; i < ESTRELLAS_CANT; i++) {
        float pos_x = randomf(0, width);
        float pos_y = randomf(0, height);

        star_t *s = estrella_crear(pos_x, pos_y);
        if(s == NULL) {
            lista_destruir(cielo, estrella_destruir);
            return false;
        }

        lista_insertar_final(cielo, s);
    }

    return true;
}

void cielo_destruir() {
    lista_destruir(cielo, estrella_destruir);
}

bool cielo_graficar(float **terreno, size_t n) {
    lista_iterador_t *iter_star = lista_iterador_crear(cielo);
	if(iter_star == NULL)
		return false;

	for(; !lista_iterador_termino(iter_star); lista_iterador_siguiente(iter_star))
	{
		star_t *s = lista_iterador_actual(iter_star);

        if(vector_esta_arriba(terreno, n, s->x, -s->y))
            estrella_imprimir(s);

	}
	lista_iterador_destruir(iter_star);

    return true;
}
