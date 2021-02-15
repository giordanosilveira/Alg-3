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
	tree = NULL;
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
        posordem(no->left);        
        printf ("%c ", no->key);
        posordem(no->right);
    }
	printf ("\n");
}
int avalia_expressao (t_node* raiz) {

	int r_valor, l_valor;

	if (raiz == NULL)
		return 0;

	if (!raiz->left && !raiz->right)
		return raiz->key - '0';
	
	l_valor = avalia_expressao (raiz->left);
	r_valor = avalia_expressao (raiz->right);

	if (raiz->key == '+')
		return l_valor + r_valor;

	if (raiz->key == '-')
		return l_valor - r_valor;
		
	if (raiz->key == '*')
		return l_valor * r_valor;
		
	if (raiz->key == '/') {
		if (r_valor == 0) {
			printf ("Valor inválidoo, divisão por 0, encerrando programa\n");
			exit (1);
		}
		return l_valor / r_valor;
	}

}
int main () {

	int resultado, i;
	char *expressao;
	t_node *arvore;

	i = 0;
	expressao = allocate_men (MAX);
	//numero = allocate_menI (MAX);

	fgets (expressao, MAX, stdin);

	arvore = monta_arvore(expressao, &i);
	resultado = avalia_expressao (arvore);

	printf ("Resultado = %d\n", resultado);

	return 0;
}
//(*(-(5)(+(3)(7)))(*(7)(/(2)(+(3)(4)))))