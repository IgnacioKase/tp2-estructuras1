#ifndef __ITREE_H__
#define __ITREE_H__

typedef void (*FuncionVisitante) (double* intervalo);

typedef struct _ITNodo {
  double intervalo[2];
  double max;
  struct _ITNodo *left;
  struct _ITNodo *right;
} ITNodo;

typedef ITNodo *ITree;

ITree itree_crear();

void itree_destruir(ITree it);

ITree itree_insertar(ITree it, double inter[2]);

ITree itree_eliminar(ITree it, double inter[2]);

ITree itree_intersecar(ITree it, double inter[2]);

void itree_recorrer_dfs(ITree it, FuncionVisitante visit);

void itree_recorrer_bfs(ITree it, FuncionVisitante visit);

int itree_altura(ITree it);

#endif
