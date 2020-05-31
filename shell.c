#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/itree.h"

#define MAX_STDIN 25

static void imprimir_intervalo(double* intervalo) {
    printf("[%.2f, %.2f] ", intervalo[0], intervalo[1]);
}

int menor(int a, int b) {
    return a < b;
}

void empty_stdin() {
    int c = getchar();
    while (c != '\n' && c != EOF)
        c = getchar();
}

int match(char* comando) {
    if (!strcmp(comando, "dfs"))
        return 1;
    if (!strcmp(comando, "bfs"))
        return 2;
    if (!strcmp(comando, "salir"))
        return 3;
    if (!strcmp(comando, "help"))
        return 4;
    return 0;
}

void help() {
    printf("\nComandos:\n");
    printf("i [a,b]: inserta el intervalo [a,b] en el arbol\n");
    printf("e [a,b]: elimina el intervalo [a,b] del arbol\n");
    printf("? [a,b]: interseca el intervalo [a,b] ");
    printf("con los intervalos del arbol\n");
    printf("dfs: imprime los intervalos del arbol ");
    printf("con recorrido primero en profundidad\n");
    printf("bfs: imprime los intervalos del arbol ");
    printf("con recorrido primero a lo ancho\n");
    printf("salir: destruye el arbol y termina el programa\n\n");
}

int main() {
    printf("\nIngrese 'help' para informacion sobre los comandos\n");

    ITree itree = itree_crear();

    // Bucle de Shell
    while (1) {
        char buf[MAX_STDIN];
        char comando[6];
        double arg[2];

        printf(">> ");

        // [^\n] indica "leer hasta encontrar..."
        scanf("%[^\n]s", buf);
        // Limpiamos el buffer para le proxima entrada
        empty_stdin();

        int args = sscanf(buf, "%s [%lf, %lf]", comando, arg, &arg[1]);
        //args = cant de elementos escaneados

        switch (args) {
            case 1:
                switch (match(comando)) {
                    case 1:
                        itree_recorrer_dfs(itree, BTREE_RECORRIDO_PRE, imprimir_intervalo);
                        puts("");
                        break;
                    case 2:
                        itree_recorrer_bfs(itree, BTREE_RECORRIDO_PRE, imprimir_intervalo);
                        puts("");
                        break;
                    case 3:
                        itree_destruir(itree);
                        return 0;
                        break;
                    case 4:
                        help();
                        break;
                    default:
                        printf("ERROR: comando invalido.\n");
                        printf("Ingrese 'help' para informacion sobre los comandos.\n");
                        break;
                }
                break;
            case 3:
                if (strlen(comando) == 1) {
                    switch (comando[0]) {
                        case 'i':
                            itree = itree_insertar(itree, arg);
                            break;
                        case 'e':
                            itree = itree_eliminar(itree, arg);
                            break;
                        case '?':
                            if (itree_intersecar(itree, arg) == NULL) {
                                printf("No\n");
                            } else {
                                printf("Si\n");
                            }
                            break;
                        default:
                            printf("ERROR: comando invalido.\n");
                            printf("Ingrese 'help' para informacion sobre los comandos.\n");
                            break;
                    }
                } else {
                    printf("ERROR: comando invalido.\n");
                    printf("Ingrese 'help' para informacion sobre los comandos.\n");
                }
                break;
            default:
                printf("ERROR: cantidad invalida de argumentos.\n");
                printf("Ingrese 'help' para informacion sobre los comandos.\n");
                break;
        }
    }

    return 0;
}
