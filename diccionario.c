#include "diccionario.h"

#include <stdio.h>
#include <stdlib.h>

#include "caracteres.h"

const char caracteres[] = {[A] = 'A', [B] = 'B', [C] = 'C', [D] = 'D', [E] = 'E', [F] = 'F', [G] = 'G', [H] = 'H', [I] = 'I',
	[J] = 'J', [K] = 'K', [L] = 'L', [M] = 'M', [N] = 'N', [O] = 'O', [P] = 'P', [Q] = 'Q', [R] = 'R', [S] = 'S', [T] = 'T',
	[U] = 'U', [V] = 'V', [W] = 'W', [X] = 'X', [Y] = 'Y', [Z] = 'Z', [CERO] = '0', [UNO] = '1', [DOS] = '2', [TRES] = '3',
	[CUATRO] = '4', [CINCO] = '5', [SEIS] = '6', [SIETE] = '7', [OCHO] = '8', [NUEVE] = '9', [ARRIBA] = '^', [ABAJO] = 'v',
	[DERECHA] = '>', [IZQUIERDA] = '<', [ESPACIO] = ' '};

const int (*(matrices[]))[2] = {[A] = caracter_a, [B] = caracter_b, [C] = caracter_c, [D] = caracter_d, [E] = caracter_e,
	[F] = caracter_f, [G] = caracter_g, [H] = caracter_h, [I] = caracter_i, [J] = caracter_j, [K] = caracter_k, [L] = caracter_l,
	[M] = caracter_m, [N] = caracter_n, [O] = caracter_o, [P] = caracter_p, [Q] = caracter_q, [R] = caracter_r, [S] = caracter_s,
	[T] = caracter_t, [U] = caracter_u, [V] = caracter_v, [W] = caracter_w, [X] = caracter_x, [Y] = caracter_y, [Z] = caracter_z,
	[CERO] = caracter_0, [UNO] = caracter_1, [DOS] = caracter_2, [TRES] = caracter_3, [CUATRO] = caracter_4, [CINCO] = caracter_5,
	[SEIS] = caracter_6, [SIETE] = caracter_7, [OCHO] = caracter_8, [NUEVE] = caracter_9, [ARRIBA] = caracter_arriba,
	[ABAJO] = caracter_abajo, [DERECHA] = caracter_derecha, [IZQUIERDA] = caracter_izquierda, [ESPACIO] = caracter_espacio};

const size_t cant_puntos_en_caracter[] = {[A] = 7, [B] = 12, [C] = 4, [D] = 7, [E] = 7, [F] = 6, [G] = 7, [H] = 6, [I] = 6,
	[J] = 4, [K] = 6, [L] = 3, [M] = 5, [N] = 4, [O] = 5, [P] = 5, [Q] = 9, [R] = 7, [S] = 6, [T] = 4, [U] = 4, [V] = 3,
	[W] = 5, [X] = 5, [Y] = 5, [Z] = 4, [CERO] = 5, [UNO] = 2, [DOS] = 6, [TRES] = 7, [CUATRO] = 5, [CINCO] = 6, [SEIS] = 5,
	[SIETE] = 3, [OCHO] = 7, [NUEVE] = 5, [ARRIBA] = 5, [ABAJO] = 5, [DERECHA] = 5, [IZQUIERDA] = 5, [ESPACIO] = 1};

matriz_car_t char_a_matriz(char letra, size_t *n) {
	for(size_t i = 0; i < CANT_CARACTERES; i++)
		if(caracteres[i] == letra){
			*n = cant_puntos_en_caracter[i];
			return matrices[i];
		}
	*n = 0;
	return NULL;
}
