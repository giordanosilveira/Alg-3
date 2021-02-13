#include<stdio.h>
#include<stdlib.h>
#define MAX 100


struct t_node {
	char key;
	struct t_node *left, *right, *pai;   
};
typedef struct t_node t_node;

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

t_node *create_node (char valor) {
	
	t_node *new;
	new = (t_node*)malloc(sizeof(t_node));

	new->key = valor;	
	new->left = NULL;
	new->right = NULL;
	new->pai = NULL;

	return new;

}

t_node *monta_arvore(char *expr, int *i){

	t_node *tree;
	if (expr[*i] == '(') {
		(*i)++;
		printf("Criando nó %c\n", expr[*i]);
		tree = create_node (expr[*i]);
		(*i)++;
		tree->left = monta_arvore(expr,i);
		tree->right = monta_arvore(expr,i);
		(*i)++;
	}
	return tree;
	
}
void posordem(t_node *no){
    if (no != NULL){    
        printf ("%c ", no->key);
        posordem(no->left);        
        posordem(no->right);
    }
}
int main () {

	int *numero, i;
	char *expressao;
	t_node *raiz, *t;

	i = 0;
	expressao = allocate_men (MAX);
	numero = allocate_menI (MAX);

	fgets (expressao, MAX, stdin);

	raiz = monta_arvore(expressao, &i);
	posordem (raiz);
	//avalia_expressao (raiz, numero);
	
	return 0;
}
