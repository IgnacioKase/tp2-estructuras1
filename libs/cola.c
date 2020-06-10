#include "cola.h"

// Crea nueva cola vacia
Cola cola_crear() {
    return NULL;
}

int cola_es_vacia(Cola c) {
    return c == NULL;
}

// Devuelve el primer elemento de la cola
void* cola_primero(Cola c) {
    assert(c);
    return c->dato;
}

// Agrega dato al final de la cola
Cola cola_encolar(Cola c, void* dato) {
    CNodo* nuevoNodo = malloc(sizeof(CNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->sig = NULL;

    if (c == NULL)
        return nuevoNodo;

    Cola nodo = c;
    for (; nodo->sig != NULL; nodo = nodo->sig);
    /* Se busca el final de la cola para agregar
       el nuevo elemento a lo ultimo */

    nodo->sig = nuevoNodo;
    return c;
}

// Elimina el primer elemento de la cola
Cola cola_desencolar(Cola c) {
    assert(c);
    Cola top = c->sig;
    free(c);
    return top;
}

// Libera toda la cola
void cola_destruir(Cola c) {
    while (c != NULL) {
        c = cola_desencolar(c);
    }
}
