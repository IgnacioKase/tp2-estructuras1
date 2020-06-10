#include "intervalo.h"

/* Devuelve si el intervalo x es el minimo
   entre x e y */
int intervalo_min(double x[2], double y[2]) {
    /* consideramos intervalo inimo al que comienza antes
    (o termina antes en caso de tener el mismo comienzo) */
    return x[0] < y[0] || (x[0] == y[0] && x[1] < y[1]);
}

void intervalo_imprimir(double intervalo[2]) {
    printf("[%f, %f] ", intervalo[0], intervalo[1]);
}

int intervalo_es_valido(double intervalo[2]) {
    /* el intervalo es valido siempre y cuando
    el comienzo no supere al final */
    return intervalo[0] <= intervalo[1];
}

// Devuelve si hay interseccion entre x e y
int intervalo_interseca(double x[2], double y[2]) {
    return x[0] <= y[1] && y[0] <= x[1];
}

int max_i(int a, int b) {
    return a > b ? a : b;
}

double max_d(double a, double b) {
    return a > b ? a : b;
}

