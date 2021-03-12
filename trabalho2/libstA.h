#ifndef __BSTA__
#define __BSTA__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libstB.h"

struct t_nodeA {
    t_nodeB *chave;
    struct t_nodeA *left, *right, *p;
};
typedef struct t_nodeA t_nodeA;

//Cria um nodo do tipo A
t_nodeA *create_nodeA (t_nodeB *);

//Função que insere um nodo recursivamente na árvore
t_nodeA* inserir (t_nodeA* , t_nodeB *);

//Imprime a árvore A, no formato de conchetes "nova linha"
//Percuso em ordem
void imprimir_arvoreA (t_nodeA *treeA);

//Destroi a árvore A recurssivamente
//percursso pos ordem
void destroiArvoreA (t_nodeA *treeA);

//Busca para ver se o valor é encontrado na árvore A
t_nodeA *busca (t_nodeA *node,int valor);

//Função que ajusta os filhos do pai do primeiro nodo dado
//e ajusta o no pai do filho do primeiro nodo dado
void ajustaNoPai (t_nodeA *nodo, t_nodeA *);

//Função que acha o valor mínimo de um nó
t_nodeA *min (t_nodeA *node);

//Função que acha um sucessor de um nodo
t_nodeA* sucessor (t_nodeA*node);

//Remove um nodo dado e atualiza a raiz se precisar
//retorna a raiz
t_nodeA* remover (t_nodeA *node, t_nodeA* root);


#endif