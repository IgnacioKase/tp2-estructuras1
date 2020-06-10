#include "../libs/shell.h"

/*
 TRABAJO PRÁCTICO 2
 ÁRBOL AVL DE INTERVALOS DOUBLE CON INTERPRETE
 INTEGRANTES:
       - VALENTINA, PRATO
       - IGNACIO, KASEVICH
 GIT: https://github.com/IgnacioKase/tp2-estructuras1
 10/06/2020
*/

/*
 LEER PDFs/Informe.pdf
*/


int main() {
    printf("\nIngrese 'help' para informacion sobre los comandos\n");

    ITree itree = itree_crear();
    int continuar = 1;
    char buf[MAX_STDIN];

    // Bucle de Shell
    while (continuar) {
        printf(">> ");

        fgets(buf, MAX_STDIN - 1, stdin);
        
        /* continuar = 0 indica que el usuario
        pidio salir */
        continuar = loop_shell(buf, &itree);
    }
    
    itree_destruir(itree);
    return 0;
}
