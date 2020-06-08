#include "../libs/shell.h"

int main() {
    printf("\nIngrese 'help' para informacion sobre los comandos\n");

    ITree itree = itree_crear();
    int continuar = 1;
    char buf[MAX_STDIN];

    // Bucle de Shell
    while (continuar) {
        printf(">> ");

        fgets(buf, MAX_STDIN - 1, stdin);

        continuar = loop_shell(buf, &itree);
    }
    
    itree_destruir(itree);
    return 0;
}
