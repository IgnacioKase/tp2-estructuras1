#ifndef __COLA_H__
#define __COLA_H__

typedef struct _CNodo {
  void *dato;
  struct _CNodo *sig;
} CNodo;

typedef CNodo *Cola;

Cola cola_crear();

int cola_es_vacia(Cola c);

void* cola_primero(Cola c);

Cola cola_encolar(Cola c, void* dato);

Cola cola_desencolar(Cola c);

void cola_destruir(Cola c);

#endif
