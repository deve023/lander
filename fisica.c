#include "fisica.h"

double computar_velocidad(double vi, double a, double dt) {
    return vi + a*dt;
}

double computar_posicion(double pi, double vi, double dt) {
    return pi + vi*dt;
}
