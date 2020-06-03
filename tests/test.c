#include "../libs/itree.h"

int main() {
    ITree arbol = itree_crear();

    arbol = insert_in_tree(arbol, 1, 4);
    arbol = insert_in_tree(arbol, 1, 3);
    arbol = insert_in_tree(arbol, 1, 2);
    arbol = insert_in_tree(arbol, 1, 5);
    arbol = insert_in_tree(arbol, 2, 7);
    arbol = insert_in_tree(arbol, 3, 5);
    arbol = insert_in_tree(arbol, 2, 4);
    double a[2] = {1.0, 4.0};
    arbol = itree_eliminar(arbol, a);
    print2D(arbol);
    // arbol = insert_in_tree(arbol, 0, 0.1);
    // arbol = insert_in_tree(arbol, 0.2, 0.4);
    // arbol = insert_in_tree(arbol, 0.1, 0.2);
    // arbol = insert_in_tree(arbol, 0, 2);
    // arbol = insert_in_tree(arbol, 0, 2);
    // arbol = insert_in_tree(arbol, 3, 6);
    // arbol = insert_in_tree(arbol, 1, 2);
    // arbol = insert_in_tree(arbol, 5, 6);
    // arbol = insert_in_tree(arbol, 7, 10);
    // arbol = insert_in_tree(arbol, 8, 12);
    // arbol = insert_in_tree(arbol, 10, 11);
    print2D(arbol);
}