#ifndef __ITREE_H__
#define __ITREE_H__

#include <stdio.h>
#include <stdlib.h>

#include "cola.h"
#include "intervalo.h"

/*
    Comentarios de las funciones en el archivo .c
*/

#define PRINT_2D_SPACES 8

typedef void (*FuncionVisitante)(double *intervalo);

typedef struct _ITNodo {
    double intervalo[2];
    double max;
    struct _ITNodo *left;
    struct _ITNodo *right;
} ITNodo;

typedef enum {
    ITREE_RECORRIDO_IN,
    ITREE_RECORRIDO_PRE,
    ITREE_RECORRIDO_POST
} ITreeOrdenDeRecorrido;

typedef ITNodo *ITree;

ITree itree_crear();

void itree_destruir(ITree it);

int itree_altura(ITree it);

void itree_imprimir_2d(ITree root);

ITree itree_insertar(ITree it, double inter[2]);

ITree itree_eliminar(ITree it, double inter[2]);

ITree itree_intersecar(ITree it, double inter[2]);

void itree_recorrer_dfs(ITree it, ITreeOrdenDeRecorrido orden, FuncionVisitante visit);

void itree_recorrer_bfs(ITree it, FuncionVisitante visit);

#endif
