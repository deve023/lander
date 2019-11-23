#include "nave.h"

struct nave {
	float x;
	float y;
	float vx;
	float vy;
	float ax;
	float ay;
	double angulo;
	double pot;
};

static const float nave_grande[28][2] = {
	{-3, -5},
	{-6, -2},
	{-6, 2},
	{-2, 6},
	{2, 6},
	{6, 2},
	{6, -2},
	{3, -5},
	{6, -5},
	{6, -8},
	{8.5, -13},
	{10, -13},
	{7, -13},
	{8.5, -13},
	{6, -8},
	{3, -8},
	{5, -12},
	{-5, -12},
	{-3, -8},
	{3, -8},
	{-6, -8},
	{-8.5, -13},
	{-10, -13},
	{-7, -13},
	{-8.5, -13},
	{-6, -8},
	{-6, -5},
	{6, -5},
};

static const float nave_chorro[3][2] = {
	{-NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y},
	{0, NAVE_GRANDE_TOBERA_Y},
	{NAVE_GRANDE_TOBERA_X, NAVE_GRANDE_TOBERA_Y}
};

nave_t *nave_crear() {
	nave_t *n = malloc(sizeof(nave_t));
	if(n == NULL)
		return NULL;

	n->x = NAVE_X_INICIAL;
	n->y = VENTANA_ALTO - NAVE_Y_INICIAL;
	n->vx = NAVE_VX_INICIAL;
	n->vy = NAVE_VY_INICIAL;
	n->ax = 0;
	n->ay = GRAVEDAD;
	n->angulo = NAVE_ANGULO_INICIAL;
	n->pot = NAVE_POTENCIA_INICIAL;

	return n;
}

void nave_destruir(void *n) {
	free(n);
}

float nave_get_x(const nave_t *n) {
	return n->x;
}

float nave_get_y(const nave_t *n) {
	return n->y;
}

float nave_get_vx(const nave_t *n) {
	return n->vx;
}

float nave_get_vy(const nave_t *n) {
	return n->vy;
}

double nave_get_angulo(const nave_t *n) {
	return n->angulo;
}

double nave_get_pot(const nave_t *n) {
	return n->pot;
}

void nave_rotar(nave_t *n, double angulo) {
	n->angulo += angulo;
}

void nave_incrementar_potencia(nave_t *n, double pot) {
	n->pot += pot;
}

void nave_mover(nave_t *n, float dt) {
	n->ax = - n->pot * sin(n->angulo);
	n->ay = GRAVEDAD - n->pot * cos(n->angulo);

	n->vx = computar_velocidad(n->vx, n->ax, dt);
	n->vy = computar_velocidad(n->vy, n->ay, dt);

	n->x = computar_posicion(n->x, n->vx, dt);
	n->y = computar_posicion(n->y, n->vy, dt);

	if(n->x > VENTANA_ANCHO)
		n->x = 0;
	if(n->x < 0)
		n->x = VENTANA_ANCHO;
}

bool nave_dibujar(const nave_t *n, SDL_Renderer *renderer) {
	float **nave_sprite = vector_desde_matriz(nave_grande, 28);
	if(nave_sprite == NULL)
		return false;

	float **chorro_sprite = vector_desde_matriz(nave_chorro, 3);
	if(chorro_sprite == NULL) {
		vector_destruir(nave_sprite, 28);
		return false;
	}

	vector_rotar(nave_sprite, 28, n->angulo);
	vector_trasladar(nave_sprite, 28, n->x, -n->y);

	chorro_sprite[1][1] -= n->pot;

	vector_rotar(chorro_sprite, 3, n->angulo);
	vector_trasladar(chorro_sprite, 3, n->x, -n->y);

	imprimir_matriz(nave_sprite, 28, renderer);
	imprimir_matriz(chorro_sprite, 3, renderer);

	vector_destruir(nave_sprite, 28);
	vector_destruir(chorro_sprite, 3);

	return true;
}

bool nave_actualizar(nave_t *n, float dt, SDL_Renderer *renderer) {
	nave_mover(n, dt);
	return nave_dibujar(n, renderer);
}
