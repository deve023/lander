#include <stdio.h>
#include <SDL2/SDL.h>
#include <time.h>

#include "config.h"
#include "nave.h"
#include "terreno.h"
#include "vectores.h"
#include "fisica.h"
#include "imprimir.h"
#include "matematica.h"
#include "background.h"

#define DT (1.0 / JUEGO_FPS)

// Muestra la pantalla de inicio
void welcome_screen(const terreno_t *terreno, SDL_Renderer *renderer);

// Imprime las variables del juego en la pantalla.
void imprimir_variables(const nave_t *nave, const int puntaje, const double tiempo, const double combustible, const double altitud, SDL_Renderer *renderer);

// Actualiza las variables del juego y las imprime en pantalla. Recibe la nave y el terreno para calcular la altitud. Devuelve falso si el combustible llega a cero.
bool variables_actualizar(const nave_t *nave, const terreno_t *terreno, double *altitud, double *combustible, double *tiempo, int puntaje, float dt, SDL_Renderer *renderer);

// Evento aterrizar. Ajusta puntaje y combustible de acuerdo al estado de la nave.
void aterrizaje(nave_t *nave, int *puntaje, double *combustible, SDL_Renderer *renderer);

// Libera los recursos asociados a SDL y cierra la ventana.
void SDL_Finalizar(SDL_Cursor *cursor, SDL_Renderer *renderer, SDL_Window *window);

int main() {

    srand(time(NULL));

    // Inicializar pantalla
    SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	SDL_Cursor *cursor;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
	SDL_SetWindowTitle(window, "Lunar Lander");

	int32_t cursorData[2] = {0, 0};
	cursor = SDL_CreateCursor((Uint8 *)cursorData, (Uint8 *)cursorData, 8, 8, 4, 4);
	SDL_SetCursor(cursor);

	int dormir = 0;

    // Inicializo nave
    nave_t *nave = nave_crear();
    if(nave == NULL) {
        SDL_Finalizar(cursor, renderer, window);

		return 1;
    }

    // Inicializo background
    terreno_t *terreno;
    if(!background_crear(&terreno, renderer)) {
        nave_destruir(nave);
        SDL_Finalizar(cursor, renderer, window);

        return 1;
    }

    // Inicializo variables del juego
    int puntaje = 0;
	double tiempo = 0;
	double combustible = JUEGO_COMBUSTIBLE_INICIAL;
	double altitud;

    bool game_start = false; // Indica si comenzo la partida

    unsigned int ticks = SDL_GetTicks();
	while(1) {
		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				break;
	    	if (event.type == SDL_KEYDOWN) {
				switch(event.key.keysym.sym) {
					case SDLK_ESCAPE:
						fprintf(stdout, "Puntaje: %d\n", puntaje);
                        nave_destruir(nave);
                        background_destruir(terreno);
                        SDL_Finalizar(cursor, renderer, window);

						return 1;
                    case SDLK_SPACE:
                        if(!game_start)
                            game_start = true;
                        break;
					case SDLK_UP:
						if(game_start && nave_get_pot(nave) < NAVE_MAX_POTENCIA) {
							nave_incrementar_potencia(nave, NAVE_POTENCIA_PASO);
						}
						break;
					case SDLK_DOWN:
						if(game_start && nave_get_pot(nave) > 0) {
							nave_incrementar_potencia(nave, -NAVE_POTENCIA_PASO);
						}
						break;
					case SDLK_RIGHT:
						if(game_start && nave_get_angulo(nave) > -PI/2) {
							nave_rotar(nave, -NAVE_ROTACION_PASO);
							combustible -= JUEGO_COMBUSTIBLE_RADIANES * NAVE_ROTACION_PASO;
						}
						break;
					case SDLK_LEFT:
						if(game_start && nave_get_angulo(nave) < PI/2) {
							nave_rotar(nave, NAVE_ROTACION_PASO);
							combustible -= JUEGO_COMBUSTIBLE_RADIANES * NAVE_ROTACION_PASO;
						}
				}
			}
		    continue;
		}
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

        if(!game_start)
            welcome_screen(terreno, renderer);
        else {
            nave_actualizar(nave, DT, renderer);
            background_graficar(terreno, renderer);
            if(!variables_actualizar(nave, terreno, &altitud, &combustible, &tiempo, puntaje, DT, renderer))
                break;

            if(!vector_esta_arriba(terreno_get_coords(terreno), terreno_get_tam(terreno), nave_get_x(nave), -nave_get_y(nave) + NAVE_GRANDE_TOBERA_Y)) {
                aterrizaje(nave, &puntaje, &combustible, renderer);

                // Reseteo nave y background
                nave_destruir(nave);
                nave = nave_crear();
                if(nave == NULL)
                    break;

                background_destruir(terreno);
                if(!background_crear(&terreno, renderer))
            		break;

                dormir = 2000;
            }

        }
        SDL_RenderPresent(renderer);
        ticks = SDL_GetTicks() - ticks;
        if(dormir) {
            SDL_Delay(dormir);
            dormir = 0;
        }
        else if(ticks < 1000 / JUEGO_FPS)
             SDL_Delay(1000 / JUEGO_FPS - ticks);

        ticks = SDL_GetTicks();
    }

    fprintf(stdout, "Puntaje: %d\n", puntaje);

	nave_destruir(nave);
    background_destruir(terreno);

    SDL_Finalizar(cursor, renderer, window);
	return 0;
}

void welcome_screen(const terreno_t *terreno, SDL_Renderer *renderer) {
    imprimir_cadena("PRESS SPACE TO START", 2 * CARACTERES_ESCALAMIENTO, (VENTANA_ANCHO - 20 * CARACTER_ANCHO * 2 * CARACTERES_ESCALAMIENTO) / 2, VENTANA_ALTO / 3, renderer);

    imprimir_cadena("SCORE", CARACTERES_ESCALAMIENTO, 50, 100, renderer);
    imprimir_cadena("TIME", CARACTERES_ESCALAMIENTO, 50, 100 + 2 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);
    imprimir_cadena("FUEL", CARACTERES_ESCALAMIENTO, 50, 100 + 4 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);
    imprimir_cadena("ALTITUDE", CARACTERES_ESCALAMIENTO, VENTANA_ANCHO - 350, 100, renderer);
    imprimir_cadena("HORIZONTAL SPEED", CARACTERES_ESCALAMIENTO, VENTANA_ANCHO - 350, 100 + 2 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);
    imprimir_cadena("VERTICAL SPEED", CARACTERES_ESCALAMIENTO, VENTANA_ANCHO - 350, 100 + 4 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);

    background_graficar(terreno, renderer);

    imprimir_cadena("PRESS ESC TO QUIT", 1, 10, VENTANA_ALTO - CARACTER_ALTO, renderer);
}

void imprimir_variables(const nave_t *nave, const int puntaje, const double tiempo, const double combustible, const double altitud, SDL_Renderer *renderer) {
    imprimir_cadena("SCORE", CARACTERES_ESCALAMIENTO, 50, 100, renderer);
    imprimir_cadena("TIME", CARACTERES_ESCALAMIENTO, 50, 100 + 2 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);
    imprimir_cadena("FUEL", CARACTERES_ESCALAMIENTO, 50, 100 + 4 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);

    imprimir_entero_con_ceros(puntaje, CARACTERES_ESCALAMIENTO, 150, 100, renderer);
    imprimir_entero_con_ceros(tiempo, CARACTERES_ESCALAMIENTO, 150, 100 + 2 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);
    imprimir_entero_con_ceros(combustible, CARACTERES_ESCALAMIENTO, 150, 100 + 4 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);

    imprimir_cadena("ALTITUDE", CARACTERES_ESCALAMIENTO, VENTANA_ANCHO - 350, 100, renderer);
    imprimir_cadena("HORIZONTAL SPEED", CARACTERES_ESCALAMIENTO, VENTANA_ANCHO - 350, 100 + 2 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);
    imprimir_cadena("VERTICAL SPEED", CARACTERES_ESCALAMIENTO, VENTANA_ANCHO - 350, 100 + 4 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);

    imprimir_entero(abs(altitud), CARACTERES_ESCALAMIENTO, VENTANA_ANCHO - 120, 100, renderer);
    imprimir_entero(abs(nave_get_vx(nave)), CARACTERES_ESCALAMIENTO, VENTANA_ANCHO - 120, 100 + 2 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);
    imprimir_entero(abs(nave_get_vy(nave)), CARACTERES_ESCALAMIENTO, VENTANA_ANCHO - 120, 100 + 4 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);

    if(nave_get_vx(nave) > 0)
        imprimir_cadena(">", CARACTERES_ESCALAMIENTO, VENTANA_ANCHO - 70, 100 + 2 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);
    else if(nave_get_vx(nave) < 0)
        imprimir_cadena("<", CARACTERES_ESCALAMIENTO, VENTANA_ANCHO - 70, 100 + 2 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);

    if(nave_get_vy(nave) > 0)
        imprimir_cadena("v", CARACTERES_ESCALAMIENTO, VENTANA_ANCHO - 70, 100 + 4 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);
    else if(nave_get_vy(nave) < 0)
        imprimir_cadena("^", CARACTERES_ESCALAMIENTO, VENTANA_ANCHO - 70, 100 + 4 * CARACTER_ALTO * CARACTERES_ESCALAMIENTO, renderer);

    imprimir_cadena("PRESS ESC TO QUIT", 1, 10, VENTANA_ALTO - CARACTER_ALTO, renderer);
}

bool variables_actualizar(const nave_t *nave, const terreno_t *terreno, double *altitud, double *combustible, double *tiempo, int puntaje, float dt, SDL_Renderer *renderer) {
    *altitud = -coord_y_en_recta(terreno_get_coords(terreno), terreno_get_tam(terreno), nave_get_x(nave)) - nave_get_y(nave) + NAVE_GRANDE_TOBERA_Y;

    *combustible -= nave_get_pot(nave) * JUEGO_COMBUSTIBLE_POT_X_SEG * DT;
    if(*combustible <= 0)
        return false;

    *tiempo += dt;

    imprimir_variables(nave, puntaje, *tiempo, *combustible, *altitud, renderer);

    return true;
}

void aterrizaje(nave_t *nave, int *puntaje, double *combustible, SDL_Renderer *renderer) {
    if(fabs(nave_get_vx(nave)) > VX_DESTROYED || fabs(nave_get_vy(nave)) > VY_DESTROYED || fabs(nave_get_angulo(nave)) > ANGULO_LANDED) {
        *puntaje += PUNTAJE_DESTROYED;
        *combustible -= COMBUSTIBLE_PENALIDAD;
        imprimir_cadena("DESTROYED", 2 * CARACTERES_ESCALAMIENTO, 545, 200, renderer);
    }
    else if(fabs(nave_get_vx(nave)) < VX_LANDED && fabs(nave_get_vy(nave)) < VY_LANDED && fabs(nave_get_angulo(nave)) < ANGULO_LANDED) {
        *puntaje += PUNTAJE_LANDED;
        imprimir_cadena("YOU HAVE LANDED", 2 * CARACTERES_ESCALAMIENTO, 500, 200, renderer);
    }
    else {
        *puntaje += PUNTAJE_LANDED_HARD;
        imprimir_cadena("YOU LANDED HARD", 2 * CARACTERES_ESCALAMIENTO, 500, 200, renderer);
    }
}

void SDL_Finalizar(SDL_Cursor *cursor, SDL_Renderer *renderer, SDL_Window *window) {
    SDL_FreeCursor(cursor);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}
