#include "intervalo.h"

int intervalo_min(double x[2], double y[2]) {
    return x[0] < y[0] || (x[0] == y[0] && x[1] < y[1]);
}

void intervalo_imprimir(double intervalo[2]) {
    printf("[%.2f, %.2f] ", intervalo[0], intervalo[1]);
}

int intervalo_es_valido(double intervalo[2]) {
    return intervalo[0] <= intervalo[1];
}