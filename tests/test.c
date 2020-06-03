#include "../libs/itree.h"

int getBalance(ITree N) {
    if (N == NULL)
        return 0;
    return itree_altura(N->left) - itree_altura(N->right);
}

#define COUNT 5
// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(ITree root, int space) {
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("[%.2f, %.2f] H: %d\n", root->intervalo[0], root->intervalo[1], getBalance(root));

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(ITree root) {
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

ITree insert_in_tree(ITree it, double a, double b) {
    double *ar = malloc(sizeof(double) * 2);
    ar[0] = a;
    ar[1] = b;
    return itree_insertar(it, ar);
}

int main() {
    ITree arbol = itree_crear();

    arbol = insert_in_tree(arbol, 1, 2);
    arbol = insert_in_tree(arbol, 1, 3);
    arbol = insert_in_tree(arbol, 1, 4);
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