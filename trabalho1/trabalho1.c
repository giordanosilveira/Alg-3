#include<stdio.h>
#include<stdlib.h>
#define MAX 100


struct t_node {
	char key;
	struct t_node *left, *right, *pai;   
};
typedef struct t_node t_node;

t_node *create_node (char valor) {
	
	t_node *new;
	new = (t_node*)malloc(sizeof(t_node));

	new->key = valor;	
	new->left = NULL;
	new->right = NULL;
	new->pai = NULL;

	return new;

}

int *allocate_menI (int n) {

	int *vetor;

	vetor = malloc(sizeof(int)*n);

	return vetor;

}
char *allocate_men (int n) {

	char *vetor;

	vetor = malloc(sizeof(int)*n);


	return vetor;
}
int main () {

	int *numero;
	char *expressao, i;
	t_node *raiz;

	i = 0;
	expressao = allocate_men (MAX);
	numero = allocate_menI (MAX);

	fgets (expressao, MAX, stdin);

	raiz = monta_arvore(expressao, i);

	avalia_expressao (raiz, numero);
	
	return 0;
}
