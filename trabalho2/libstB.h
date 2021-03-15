#ifndef __BSTB__
#define __BSTB__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 128

struct t_nodeB {
    int chave;
    struct t_nodeB *left, *right, *p;
};
typedef struct t_nodeB t_nodeB;

//Cria um nodo do tipo B
//retorna o nodo criado
t_nodeB *create_nodeB (int );

//Dado uma arvore em formato de parenteses alinhados, monta essa árvore
//retorna o seu ponteiro
t_nodeB *monta_arvoreB (char *, int *);

//Retira o comando da entrada e puxa a árvore para o começo da string
//retorna o comando
char trata_comando (char *);

//Soma a árvore b
//retorna a soma
int soma_arvore (t_nodeB *);

//Destroi recurssivamente a árvore B
//percurso pós ordem
void destroiArvoreB(t_nodeB *);

//Imprime a árvore B, no formato de parênteses alinhados
//percurso em ordem
void imprimir_arvoreB (t_nodeB *);

#endif