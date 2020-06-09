#include "cola.h"

Cola cola_crear() {
    return NULL;
}

int cola_es_vacia(Cola c) {
    return c == NULL;
}

void* cola_primero(Cola c) {
    assert(c);
    return c->dato;
}

Cola cola_encolar(Cola c, void* dato) {
    CNodo* nuevoNodo = malloc(sizeof(CNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->sig = NULL;

    if (c == NULL)
        return nuevoNodo;

    Cola nodo = c;
    for (; nodo->sig != NULL; nodo = nodo->sig);

    nodo->sig = nuevoNodo;
    return c;
}

Cola cola_desencolar(Cola c) {
    assert(c);
    Cola top = c->sig;
    free(c);
    return top;
}

void cola_destruir(Cola c) {
    while (c != NULL) {
        c = cola_desencolar(c);
    }
}
