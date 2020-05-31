#include "itree.h"

int max_i(int a, int b) {
    return a > b ? a : b;
}

double max_d(double a, double b) {
    return a > b ? a : b;
}

ITree itree_crear() {
    return NULL;
}

void itree_destruir(ITree it) {
    if (it == NULL)
        return;
    itree_destruir(it->left);
    itree_destruir(it->right);
    free(it);
}

int itree_altura(ITree it) {
    if (it == NULL)
        return -1;
    // TODO: No hace falta esta condición?
    // if (btree_empty(arbol->left) && btree_empty(arbol->right))
    // return 0;
    return (1 + max_i(itree_altura(it->left), itree_altura(it->right)));
}

ITree itree_rotar_der(ITree it) {
    ITree left = it->left;
    ITree lr = left->right;

    left->right = it;
    it->left = lr;
    if (lr != NULL)
        it->max = max_d(it->max, lr->max);
    left->max = max_d(left->max, it->max);

    return left;
}

ITree itree_rotar_izq(ITree it) {
    ITree right = it->right;
    ITree rl = right->left;

    right->left = it;
    it->right = rl;
    if (rl != NULL)
        it->max = max_d(it->max, rl->max);
    right->max = max_d(right->max, it->max);

    return right;
}

ITree itree_insertar(ITree it, double inter[2]) {
    if (it == NULL) {
        ITree nodo = malloc(sizeof(ITNodo));
        nodo->intervalo[0] = inter[0];
        nodo->intervalo[1] = inter[1];
        nodo->max = inter[1];
        nodo->left = NULL;
        nodo->right = NULL;
        return nodo;
    }

    if (inter[0] < it->intervalo[0]) {
        it->left = itree_insertar(it->left, inter);
        it->max = max_d(it->max, it->left->max);
    } else if (inter[0] > it->intervalo[0] || inter[1] != it->intervalo[1]) {
        it->right = itree_insertar(it->right, inter);
        it->max = max_d(it->max, it->right->max);
    } else {
        return it;
    }

    int dif = itree_altura(it->left) - itree_altura(it->right);

    if (dif > 1) {
        if (inter[0] >= it->left->intervalo[0])
            it->left = itree_rotar_izq(it->left);
        return itree_rotar_der(it);
    } else if (dif < -1) {
        if (inter[0] < it->right->intervalo[0])
            it->right = itree_rotar_der(it->right);
        return itree_rotar_izq(it);
    }

    return it;
}

ITree itree_minimo(ITree it) {
    if (it == NULL)
        return NULL;

    if (it->left == NULL)
        return it;

    return itree_minimo(it->left);
}

ITree itree_eliminar(ITree it, double inter[2]) {
    if (it == NULL)
        return it;

    if (it->intervalo[0] > inter[0]) {
        it->left = itree_eliminar(it->left, inter);
    } else if (it->intervalo[1] != inter[1]) {
        it->right = itree_eliminar(it->right, inter);
    } else {
        if (it->right == NULL) {
            ITree temp = it;
            it = it->left;
            free(temp);
        } else {
            ITree nuevo = itree_minimo(it->right);
            it->intervalo[0] = nuevo->intervalo[0];
            it->intervalo[1] = nuevo->intervalo[1];
            it->max = nuevo->intervalo[1];
            it->right = itree_eliminar(it->right, nuevo->intervalo);
            if (it->right != NULL)
                it->max = max_d(it->max, it->right->max);
            if (it->left != NULL)
                it->max = max_d(it->max, it->left->max);
        }
    }

    if (it == NULL)
        return it;

    int dif = itree_altura(it->left) - itree_altura(it->right);

    if (dif > 1) {
        if (itree_altura(it->left->left) - itree_altura(it->left->right) < 0)
            it->left = itree_rotar_izq(it->left);
        return itree_rotar_der(it);
    } else if (dif < -1) {
        if (itree_altura(it->right->left) - itree_altura(it->right->right) > 0)
            it->right = itree_rotar_der(it->right);
        return itree_rotar_izq(it);
    }
    return it;
}

ITree itree_intersecar(ITree it, double inter[2]) {
    if (it == NULL)
        return NULL;

    if (it->max < inter[0])
        return NULL;
    if (it->intervalo[0] > inter[1])
        return itree_intersecar(it->left, inter);
    if (it->intervalo[1] < inter[0]) {
        if (it->right == NULL)
            return itree_intersecar(it->left, inter);
        if (it->left == NULL)
            return itree_intersecar(it->right, inter);
        if (it->max == it->right->max) {
            ITree intersec = itree_intersecar(it->right, inter);
            if (intersec != NULL || it->left->max < inter[0])
                return intersec;
            return itree_intersecar(it->left, inter);
        }
        return itree_intersecar(it->left, inter);
    }
    return it;
}

void itree_recorrer_dfs(ITree arbol, ITreeOrdenDeRecorrido orden, FuncionVisitante visit) {
    if (arbol == NULL)
        return;
    if (orden == BTREE_RECORRIDO_IN) {
        itree_recorrer_dfs(arbol->left, orden, visit);
        visit(arbol->intervalo);
        itree_recorrer_dfs(arbol->right, orden, visit);
    }
    if (orden == BTREE_RECORRIDO_PRE) {
        visit(arbol->intervalo);
        itree_recorrer_dfs(arbol->left, orden, visit);
        itree_recorrer_dfs(arbol->right, orden, visit);
    }
    if (orden == BTREE_RECORRIDO_POST) {
        itree_recorrer_dfs(arbol->left, orden, visit);
        itree_recorrer_dfs(arbol->right, orden, visit);
        visit(arbol->intervalo);
    }
}

void itree_recorrer_bfs(ITree it, ITreeOrdenDeRecorrido orden, FuncionVisitante visit) {
    if (it == NULL)
        return;
    Cola cola = cola_crear();
    ITree nodo;
    cola = cola_encolar(cola, (void*)it);
    for (; cola != NULL; cola = cola_desencolar(cola)) {
        nodo = (ITree)cola_primero(cola);
        if (orden == BTREE_RECORRIDO_IN) {
            if (nodo->left != NULL)
                cola = cola_encolar(cola, (void*)nodo->left);
            visit(nodo->intervalo);
            if (nodo->right != NULL)
                cola = cola_encolar(cola, (void*)nodo->right);
        }
        if (orden == BTREE_RECORRIDO_PRE) {
            visit(nodo->intervalo);
            if (nodo->left != NULL)
                cola = cola_encolar(cola, (void*)nodo->left);
            if (nodo->right != NULL)
                cola = cola_encolar(cola, (void*)nodo->right);
        }
        if (orden == BTREE_RECORRIDO_POST) {
            if (nodo->left != NULL)
                cola = cola_encolar(cola, (void*)nodo->left);
            if (nodo->right != NULL)
                cola = cola_encolar(cola, (void*)nodo->right);
            visit(nodo->intervalo);
        }
    }
    cola_destruir(cola);
    free(nodo);
}
