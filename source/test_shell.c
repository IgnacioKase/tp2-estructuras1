#include "../libs/shell.h"

int main(int argc, char const *argv[]) {
    //Checkeamos recibir los parametros correctamente
    if (argc != 2) {
        printf("---------------------------------------\n\n");
        printf("ERROR: ingrese la cantidad de personas y la direccion de los archivos:\n\n");
        printf("1 - Archivo de test (un comando por linea)\n");
        printf("Ejemplo:\n\n");
        printf("$ test_shell test_cases.txt\n\n");
        printf("---------------------------------------\n");
        exit(-1);
    }

    FILE *fInput = fopen(argv[1], "r");
    ITree itree = itree_crear();
    int continuar = 1;
    char buf[MAX_STDIN];

    // Bucle de Shell
    while (fgets(buf, MAX_STDIN - 1, fInput) != NULL && continuar) {
        continuar = loop_shell(buf, &itree);
    }

    fclose(fInput);
    itree_destruir(itree);
    return 0;
}