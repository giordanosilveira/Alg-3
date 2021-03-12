#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libstB.h"

t_nodeB *create_nodeB (int numero) {
	
	t_nodeB *new;

    //Aloca espaço e testa para ver se alocou
	new = (t_nodeB*)malloc(sizeof(t_nodeB));
    if (!new) {
        perror ("Não foi possível alocar memória");
        exit (1);
    }

    //Inicializa o ponteiro da esquerda, direita e pai como NULL
    new->chave = numero;	
	new->left = NULL;
	new->right = NULL;
	new->p = NULL;

	return new;

}
t_nodeB *monta_arvoreB (char *expr, int *i){

    int j, tam;
    char num[MAX];

	t_nodeB *tree;
	tree = NULL;

    //Testa para ver se é um parênteses aberto
    //Ou seja, se vai precisar criar um novo nodo
	if (expr[*i] == '(') {
		
        (*i)++;
        j = 0;                                              //índice para o vetor num

        //Enquanto não é uma parênteses fechado (fim de um nó) ou aberto (começo de outro nó),
        //copia esses caracteres para o vertor num
        while (expr[*i] != ')' && expr[*i] != '(') {    
            num[j] = expr[*i];
            j++;
            (*i)++;
        }
        num[j] = '\0';

        //Teste que serve para resolver os parenteses vazios da árvore
        tam = strlen (num);
        if (tam) {
            //Mostra qual nó vai ser criado e cria esse nó
            long key;
            char *ptr;

		    //printf("Criando nó %s\n", num);
            key = strtol (num, &ptr, 10);

            //Monta primeiramente a árvore da esquerda e depois a direita
		    tree = create_nodeB (key);
            tree->left = monta_arvoreB(expr,i);
            tree->right = monta_arvoreB(expr,i);
            (*i)++;
        }

	}
	return tree;
	
}
//Retira o comando da entrada e puxa a árvore para o começo da string
char trata_comando (char *palavra) {

    int i;
    char a;
    a = palavra[0];
    for (i = 2; palavra[i] != '\0'; i++) {  //A árvore começa na casa 2 do vetor,
        palavra[i - 2] = palavra[i];        //então puxa ela duas casa para traz
    }
    palavra[i] = '\0';

    return a;
}
//Soma a árvore b
int soma_arvore (t_nodeB *node) {

    if (node == NULL)
        return 0;
    
    return (node->chave + soma_arvore(node->left) + soma_arvore(node->right));
    
}
//Destroi recurssivamente a árvore B
void destroiArvoreB(t_nodeB *node) {

    if (node != NULL) {
        destroiArvoreB (node->left);
        destroiArvoreB (node->right);
        node->left = NULL;              //nulifica os ponteiros
        node->right = NULL;
        free (node);
    }

}
//Imprime a árvore B, no formato de parênteses alinhados
void imprimir_arvoreB (t_nodeB *treeB) {

    if (treeB != NULL) {
        printf ("(");
        printf ("%d", treeB->chave);
        imprimir_arvoreB (treeB->left);
        imprimir_arvoreB (treeB->right);
        printf (")");
    }
}