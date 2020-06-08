#include "itree.h"

int itree_balance(ITree N) {
    if (N == NULL)
        return 0;
    return itree_altura(N->left) - itree_altura(N->right);
}

#define COUNT 10
// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(ITree root, int space) {
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("[%.2f, %.2f] H: %d - MAX: %.2f\n", root->intervalo[0], root->intervalo[1], itree_balance(root), root->max);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(ITree root) {
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

ITree insert_in_tree(ITree it, double a, double b) {
    double *ar = malloc(sizeof(double) * 2);
    ar[0] = a;
    ar[1] = b;
    printf("########\n");
    print2D(it);
    printf("########\n");
    return itree_insertar(it, ar);
}
///////////////////////////////////////////

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
    return (1 + max_i(itree_altura(it->left), itree_altura(it->right)));
}

double itree_max(ITree it) {
    if (it == NULL)
        return 0;
    return it->max;
}

double itree_update_max(ITree it) {
    return max_d(max_d(itree_max(it->left), itree_max(it->right)), it->intervalo[1]);
}

ITree itree_rotar_der(ITree it) {
    ITree left = it->left;
    ITree lr = left->right;

    left->right = it;
    it->left = lr;

    itree_update_max(it);
    itree_update_max(left);

    return left;
}

ITree itree_rotar_izq(ITree it) {
    ITree right = it->right;
    ITree rl = right->left;

    right->left = it;
    it->right = rl;

    itree_update_max(it);
    itree_update_max(right);

    return right;
}

// Inserta un intervalo en un arbol
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

    if (intervalo_min(inter, it->intervalo)) {
        /* el intervalo se inserta a la izquierda si el comienzo es menor
        o si es igual pero el final es menor */
        it->left = itree_insertar(it->left, inter);
        it->max = max_d(it->max, it->left->max);
    } else if (intervalo_min(it->intervalo, inter)) {
        it->right = itree_insertar(it->right, inter);
        it->max = max_d(it->max, it->right->max);
    } else  // si el intervalo ya existe, no se vuelve a insertar
        return it;

    /* si se inserta en uno de los subarboles
    se debe asegurar que se mantenga el balance */
    int balance = itree_balance(it);

    if (balance > 1) {  // caso desbalanceado hacia la izquierda
        if (intervalo_min(it->left->intervalo, inter))
            /* si se inserto a la derecha del subarbol izquierdo
            primero se debe rotar este hacia la izquierda */
            it->left = itree_rotar_izq(it->left);
        return itree_rotar_der(it);
    }
    if (balance < -1) {  // caso desbalanceado hacia la derecha
        if (intervalo_min(inter, it->right->intervalo))
            /* si se inserto a la izquierda del subarbol derecho
            primero se debe rotar este hacia la derecha */
            it->right = itree_rotar_der(it->right);
        return itree_rotar_izq(it);
    }
    // caso ya balanceado
    return it;
}

/* Funcion auxiliar a eliminacion de intervalos
usada para hallar minimo intervalo de subarbol derecho
luego de eliminar */
ITree itree_minimo(ITree it) {
    if (it == NULL)
        return NULL;

    if (it->left == NULL)
        return it;

    return itree_minimo(it->left);
}

// Elimina un intervalo de un árbol de intervalos
ITree itree_eliminar(ITree it, double inter[2]) {
    if (it == NULL)
        return it;

    if (intervalo_min(inter, it->intervalo)) {
        it->left = itree_eliminar(it->left, inter);
    } else if (intervalo_min(it->intervalo, inter)) {
        it->right = itree_eliminar(it->right, inter);
    } else {  // caso de eliminar intervalo actual
        if (it->right == NULL) {
            /* si no hay subarbol derecho
            solo se necesita eliminar la raiz
            y devolver el izquierdo */
            ITree temp = it;
            it = it->left;
            free(temp);
        } else if (it->left == NULL) {
            /* si no hay subarbol izquierdo
            solo se necesita eliminar la raiz
            y devolver el derecho */
            ITree temp = it;
            it = it->right;
            free(temp);
        } else {  // caso de ningun subarbol vacio
            // se reemplaza la raiz por el minimo intervalo derecho
            ITree nuevo = itree_minimo(it->right);
            it->intervalo[0] = nuevo->intervalo[0];
            it->intervalo[1] = nuevo->intervalo[1];
            // se elimina la nueva raiz del subarbol derecho
            it->right = itree_eliminar(it->right, nuevo->intervalo);
            /* se vuelve a calcular el maximo
            en caso de que haya sido del intervalo eliminado */
            if (it->right != NULL)
                it->max = max_d(it->max, it->right->max);
            it->max = max_d(nuevo->intervalo[1], it->left->max);
        }
    }

    if (it == NULL)  // caso de haber eliminado el unico intervalo
        return it;

    int balance = itree_balance(it);

    if (balance > 1) {  // caso desbalanceado a izquierda
        if (itree_balance(it->left) < 0)
            it->left = itree_rotar_izq(it->left);
        return itree_rotar_der(it);
    }

    if (balance < -1) {  // caso desbalanceado a derecha
        if (itree_balance(it->right) > 0)
            it->right = itree_rotar_der(it->right);
        return itree_rotar_izq(it);
    }
    // caso ya balanceado
    return it;
}

/* Determina si un intervalo se intersecta con alguno de
los intervalos del arbol y, en caso afirmativo,
retorna un apuntador al nodo correspondiente */
ITree itree_intersecar(ITree it, double inter[2]) {
    if (it == NULL)
        return NULL;

    // Caso de intersecar con e intervalo actual
    if (intervalo_interseca(it->intervalo, inter))
        return it;

    /* Si hay subarbol izquierdo y su maximo supera
    al comienzo de nuestro intervalo, se puede hallar
    interseccion alli */
    if (it->left != NULL)
        printf("\n##PRE-BEGIN\nit->left->max: %.2f\tinter[0]: %.2f\t Comp: %d\n", it->left->max, inter[0], it->left->max >= inter[0]);
    if (it->left != NULL && (it->left->max >= inter[0]))
        return itree_intersecar(it->left, inter);

    /* Si no se cumple ninguno de los casos anteriores,
    solo puede haber interseccion a la derecha */
    return itree_intersecar(it->right, inter);
}

// Recorrido primero en profundidad del arbol de intervalos
void itree_recorrer_dfs(ITree arbol, ITreeOrdenDeRecorrido orden, FuncionVisitante visit) {
    if (arbol == NULL)
        return;
    if (orden == ITREE_RECORRIDO_IN) {
        itree_recorrer_dfs(arbol->left, orden, visit);
        visit(arbol->intervalo);
        itree_recorrer_dfs(arbol->right, orden, visit);
    }
    if (orden == ITREE_RECORRIDO_PRE) {
        visit(arbol->intervalo);
        itree_recorrer_dfs(arbol->left, orden, visit);
        itree_recorrer_dfs(arbol->right, orden, visit);
    }
    if (orden == ITREE_RECORRIDO_POST) {
        itree_recorrer_dfs(arbol->left, orden, visit);
        itree_recorrer_dfs(arbol->right, orden, visit);
        visit(arbol->intervalo);
    }
}

// Recorrido primero a lo ancho del arbol de intervalos
void itree_recorrer_bfs(ITree it, FuncionVisitante visit) {
    if (it == NULL)
        return;
    // se utiliza una cola para guardar en orden nodos por visitar
    Cola cola = cola_crear();
    ITree nodo;
    cola = cola_encolar(cola, (void *)it);
    for (; cola != NULL; cola = cola_desencolar(cola)) {
        nodo = (ITree)cola_primero(cola);
        visit(nodo->intervalo);
        // se agregan los hijos que tenga al final de la cola
        if (nodo->left != NULL)
            cola = cola_encolar(cola, (void *)nodo->left);
        if (nodo->right != NULL)
            cola = cola_encolar(cola, (void *)nodo->right);
    }
    cola_destruir(cola);
}
