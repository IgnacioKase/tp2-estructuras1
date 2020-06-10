#ifndef __INTERVALO_H__
#define __INTERVALO_H__

#include <stdio.h>
#include <stdlib.h>

int intervalo_min(double x[2], double y[2]);

void intervalo_imprimir(double intervalo[2]);

int intervalo_es_valido(double intervalo[2]);

int intervalo_interseca(double x[2], double y[2]);

int max_i(int a, int b);

double max_d(double a, double b);

#endif