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

void empty_stdin() {
    int c = getchar();
    while (c != '\n' && c != EOF)
        c = getchar();
}

/* Funcion auxiliar para switch sobre los comandos
de longitud mayor a 1 */
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

// Informacion sobre los comandos posibles
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
    printf("Recuerde que los intervalos deben contener numeros\n\n");
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

        // [^\n] indica "leer hasta encontrar \n (sin incluirlo)"
        scanf("%[^\n]s", buf);

        int args = sscanf(buf, "%s [%lf, %lf]", comando, arg, &arg[1]);
        // args = cant de elementos escaneados

        // Limpiamos el buffer para la proxima entrada
        empty_stdin();

        switch (args) {
            /* Se debe recibir 1 comando y para algunos casos
            2 numeros correspondientes al intervalo,
            por lo tanto debe haber 1 o 3 argumentos */
            case 1:
                /* los comandos que no reciben intervalo tienen varios
                caracteres y por lo tanto se llama a una funcion para
                comparar el recibido con los posibles */
                switch (match(comando)) {
                    case 1:
                        itree_recorrer_dfs(itree, ITREE_RECORRIDO_IN, imprimir_intervalo);
                        puts("");
                        break;
                    case 2:
                        itree_recorrer_bfs(itree, imprimir_intervalo);
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
                /* los comandos que reciben intervalo tienen 1 caracter
                y se debe chequear que el intervalo sea valido
                (que el final no sea menor al comienzo) */
                if (strlen(comando) == 1 && arg[0] <= arg[1]) {
                    switch (comando[0]) {
                        case 'i':
                            itree = itree_insertar(itree, arg);
                            break;
                        case 'e':
                            itree = itree_eliminar(itree, arg);
                            break;
                        case '?':
                            if (itree_intersecar(itree, arg)) {
                                printf("Si\n");
                            } else {
                                printf("No\n");
                            }
                            break;
                        default:
                            printf("ERROR: comando invalido.\n");
                            printf("Ingrese 'help' para informacion sobre los comandos.\n");
                            break;
                    }
                } else if (arg[0] > arg[1]) {
                    printf("ERROR: intervalo invalido.\n");
                    printf("El extremo izquierdo no puede superar al derecho\n");
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
