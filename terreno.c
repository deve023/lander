#include "terreno.h"

struct terreno {
    float **coords;
    size_t n;
};

static const float terreno_estatico[][2] = {
    {0, -VENTANA_ALTO + 100},
    {VENTANA_ANCHO / 4, -3 * VENTANA_ALTO / 4},
    {3 * VENTANA_ANCHO / 4, -3 * VENTANA_ALTO / 4},
    {VENTANA_ANCHO / 2, -VENTANA_ALTO * 2.0 / 3},
    {VENTANA_ANCHO + 1, -VENTANA_ALTO + 100}
};

terreno_t *terreno_crear() {
    terreno_t *t = malloc(sizeof(terreno_t));

    t->n = 0;

	size_t nt = 5;
	float **terreno = vector_desde_matriz(terreno_estatico, nt);
	if(terreno == NULL)
		return NULL;

	//Asignamos la coordenada al medio aleatoriamente:
	terreno[2][0] = rand() % VENTANA_ANCHO;

	//Iterativamente densificamos 300 veces achicando el margen cada vez:
	for(int i = 1; i < 301; i++) {
		float **aux = vector_densificar(terreno, nt, 2 * (i + 5), 100 / i);
		vector_destruir(terreno, nt);
		if(aux == NULL)
			return NULL;
		terreno = aux;
		nt = 2 * (i + 5);
	}

	t->n = nt;
	t->coords = terreno;

    return t;
}

void terreno_destruir(void *t) {
    vector_destruir(((terreno_t *)t)->coords, ((terreno_t *)t)->n);
    free(t);
}

void terreno_graficar(const terreno_t *t, SDL_Renderer *renderer) {
    imprimir_matriz(t->coords, t->n, renderer);
}

float **terreno_get_coords(const terreno_t *t) {
    return t->coords;
}

size_t terreno_get_tam(const terreno_t *t) {
    return t->n;
}
