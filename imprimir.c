#include "imprimir.h"

static int cant_digitos(int n) {
    int cant = 1;
	while(n/10 > 0) {
		n /= 10;
		cant++;
	}

    return cant;
}


static bool entero_a_cadena(int n, char **cadena) {
	char *cad = malloc(sizeof(char) * (cant_digitos(n) + 1));
	if(cad == NULL)
		return false;

	sprintf(cad, "%4d", n);

	*cadena = cad;

	return true;
}

static bool entero_a_cadena_con_ceros(int n, char **cadena) {
	char *cad = malloc(sizeof(char) * (CANT_DIGITOS + 1));
	if(cad == NULL)
		return false;

	sprintf(cad, "%04d", n);

	*cadena = cad;

	return true;
}

void imprimir_matriz(float **v, size_t n, SDL_Renderer *renderer) {
	for(int i = 0; i < n - 1; i++)
			SDL_RenderDrawLine(
				renderer,
				v[i][0],
				-v[i][1],
				v[i+1][0],
				-v[i+1][1]
			);
}

void imprimir_caracter(matriz_car_t car, size_t n, int f, double x, double y, SDL_Renderer *renderer) {
	for(size_t i = 0; i < n - 1; i++)
			SDL_RenderDrawLine(
				renderer,
				car[i][0] * f + x,
				-car[i][1] * f + y,
				car[i+1][0] * f + x,
				-car[i+1][1] * f + y
			);
}

void imprimir_entero(int n, int f, double x, double y, SDL_Renderer *renderer) {
	char *cad;

	if(entero_a_cadena(n, &cad)) {
		imprimir_cadena(cad, f, x, y, renderer);

		free(cad);
    }
}

void imprimir_entero_con_ceros(int n, int f, double x, double y, SDL_Renderer *renderer) {
	char *cad;

	if(entero_a_cadena_con_ceros(n, &cad)) {
		imprimir_cadena(cad, f, x, y, renderer);

		free(cad);
	}
}

void imprimir_cadena(char cad[], int f, double x, double y, SDL_Renderer *renderer) {
	size_t i, n;
	for(i = 0; cad[i] != '\0'; i++) {
		matriz_car_t matriz = char_a_matriz(cad[i], &n);
		imprimir_caracter(matriz, n, f, x, y, renderer);

		x += CARACTER_ANCHO * f;
	}
}
