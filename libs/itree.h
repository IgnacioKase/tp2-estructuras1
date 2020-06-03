#ifndef __ITREE_H__
#define __ITREE_H__

#include <stdio.h>
#include <stdlib.h>

#include "cola.h"

typedef void (*FuncionVisitante)(double *intervalo);

typedef struct _ITNodo {
    double intervalo[2];
    double max;
    struct _ITNodo *left;
    struct _ITNodo *right;
} ITNodo;

typedef enum {
    BTREE_RECORRIDO_IN,
    BTREE_RECORRIDO_PRE,
    BTREE_RECORRIDO_POST
} ITreeOrdenDeRecorrido;

typedef ITNodo *ITree;

ITree itree_crear();

void itree_destruir(ITree it);

ITree itree_insertar(ITree it, double inter[2]);

ITree itree_eliminar(ITree it, double inter[2]);

ITree itree_intersecar(ITree it, double inter[2]);

void itree_recorrer_dfs(ITree it, ITreeOrdenDeRecorrido orden, FuncionVisitante visit);

void itree_recorrer_bfs(ITree it, FuncionVisitante visit);

int itree_altura(ITree it);

/////////
int getBalance(ITree N);
void print2DUtil(ITree root, int space);
void print2D(ITree root);
ITree insert_in_tree(ITree it, double a, double b);
///////////////

#endif
