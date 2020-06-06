#include "../libs/shell.h"

int main() {
    printf("\nIngrese 'help' para informacion sobre los comandos\n");

    ITree itree = itree_crear();
    int continuar = 1;
    char buf[MAX_STDIN];
    int args;

    // Bucle de Shell
    while (continuar) {
        printf(">> ");

        // [^\n] indica "leer hasta encontrar \n (sin incluirlo)"
        scanf("%[^\n]s", buf);

        // Limpiamos el buffer para la proxima entrada
        empty_stdin();

        continuar = loop_shell(buf, &itree);
    }
    itree_destruir(itree);
    return 0;
}
