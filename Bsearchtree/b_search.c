#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "b_search.h"

void init_bstH (t_bst * tree) {
    tree->elemnt = BEGIN_H;
}

int tree_empty (t_bst * tree) {

    if (tree->elemnt == BEGIN_H)
        return 1;
    return 0;

}

int creat_Rnode (t_bst * tree, int key) {

    t_node *root;

    root = (t_node *)malloc(sizeof(t_node));
    if (root == NULL)
        return 0;

    root->key = key;
    root->p = NULL;
    root->left = NULL;
    root->right = NULL;

    return 1;
}

t_node * create_node (int key) {

    t_node *new;

    new = (t_node *) malloc (sizeof(t_node));
    if (new == NULL) 
        return NULL;

    new->key = key;
    new->left = NULL;
    new->right = NULL;
    new->p = NULL;

    return new;
}
void tree_insert (t_bst *tree, t_node *new) {

    t_node *x, *y;

    x = tree->root;
    while (x != NULL) {
        y = x;
        if (new->key < x->key)
            x = x->left;
        else x = x->right;
    }
    new->p = y;
    if (new->key < y->key)
        y->left = new;
    else y->right = new;

} 
void preorder_twalk (t_node *x) {

    if ( x != NULL) {
        printf ("%d ", x->key);
        preorder_twalk (x->left);
        preorder_twalk (x->right);
    }

}
void inorder_twalk (t_node *x) {

    if ( x != NULL) {
        inorder_twalk (x->left);
        printf ("%d ", x->key);
        inorder_twalk (x->right);
    }

} 
int main () {

    t_bst tree;
    t_node *new;

    init_bstH (&tree);

    srand (time(NULL));
    if (tree_empty(&tree)) {
        tree.root = create_node (rand()%R_NUM);
        if (tree.root == NULL) {
            perror ("couldn't allocate memory");
            exit (1);
        }
    }

    for (int i = 0; i < MAX; i++) {

        new = create_node (rand() % R_NUM);
        if (new == NULL) {
            perror ("Couldn't allocate memory");
            exit (1);
        }
        tree_insert (&tree,new);
    }
    
    inorder_twalk (tree.root);
    printf ("\n");

    preorder_twalk (tree.root);
    printf ("\n");
    return 0;
}
