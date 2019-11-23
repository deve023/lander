#include "background.h"

bool background_crear(terreno_t **t, SDL_Renderer *renderer) {
    // Inicializo terreno
    terreno_t *terreno = terreno_crear();
    if(terreno == NULL)
        return false;


    // Inicializo cielo
    if(!cielo_crear(renderer)) {
        terreno_destruir(terreno);
		return false;
	}

    *t = terreno;
    return true;
}

void background_destruir(void *terreno) {
    terreno_destruir(terreno);
    cielo_destruir();
}

void background_graficar(const terreno_t *terreno, SDL_Renderer *renderer) {
    terreno_graficar(terreno, renderer);
    cielo_graficar(terreno_get_coords(terreno), terreno_get_tam(terreno));
}
